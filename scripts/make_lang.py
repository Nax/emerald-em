import sys
import os
import unicodedata

class LangBuilder:
  def __init__(self, lang):
    self.lang = lang
    self.chars = {}
    self.symbols = {}
    self.entries = []

  def parse_charmap(self):
    with open(os.path.join(os.path.dirname(__file__), '..', 'emerald', 'charmap.txt'), 'r') as f:
      for line in f:
        # Skip comments
        line = line.split('@')[0].strip()
        if len(line) == 0 or line[0] != "'":
          continue
        splits = line.split("'")
        if len(splits) < 3:
          continue
        char = unicodedata.normalize('NFC', splits[1])
        data_split = splits[2].split('=')
        if len(data_split) < 2:
          continue
        data = data_split[1].strip()
        data_num = int(data, 16)
        self.chars[char] = data_num

  def parse_symbols(self):
    with open(os.path.join(os.path.dirname(__file__), '..', 'emerald', 'pokeemerald.sym'), 'r') as f:
      for line in f:
        splits = line.split(' ')
        if len(splits) < 3:
          continue
        addr = int(splits[0], 16)
        name = splits[2].strip()
        self.symbols[name] = addr

  def transform_string(self, str, size):
    chars = []
    for c in str:
      if c in self.chars:
        chars.append(self.chars[c])
      else:
        raise ValueError('Unknown character: ' + c)
    chars.append(0xff)
    if (len(chars) > size):
      raise ValueError('String too long: ' + str)
    while len(chars) < size:
      chars.append(0)
    return bytes(chars)

  def emit_entry(self, base, id, size, data):
    d = self.transform_string(data, size)
    addr = base + id * size
    self.entries.append({ 'addr': addr, 'data': d })

  def entries_blocks(self, base, size, filename):
    f = os.path.join(os.path.dirname(__file__), '..', 'data', 'text', self.lang, filename)
    if not os.path.exists(f):
      return
    with open(f, 'r') as f:
      for line in f:
        splits = line.split('|')
        if len(splits) < 2:
          continue
        id = int(splits[0])
        str = unicodedata.normalize('NFC', splits[1]).strip()
        self.emit_entry(base, id, size, str)

  def output_data(self):
    dir = os.path.join(os.path.dirname(__file__), '..', 'build', 'data')
    if not os.path.exists(dir):
      os.makedirs(dir)
    filename = os.path.join(dir, self.lang + '.bin')
    with open(filename, 'wb') as f:
      count = len(self.entries)
      f.write(count.to_bytes(4, byteorder='little'))
      for entry in self.entries:
        addr = entry['addr']
        data = entry['data']
        f.write(addr.to_bytes(4, byteorder='little'))
        f.write(len(data).to_bytes(4, byteorder='little'))
        f.write(data)

  def symbol(self, name):
    data = self.symbols[name]
    if data == None:
      raise ValueError('Unknown symbol: ' + name)
    return data - 0x08000000

  def build(self):
    self.parse_charmap()
    self.parse_symbols()
    self.entries_blocks(self.symbol('kSpeciesNames'), 13, 'pokemons.txt')
    self.output_data()
    pass

builder = LangBuilder(sys.argv[1])
builder.build()
