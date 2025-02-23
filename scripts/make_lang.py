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
    with open(os.path.join(os.path.dirname(__file__), '..', 'emerald', 'charmap.txt'), encoding='utf-8', mode='r') as f:
      for line in f:
        # Skip comments
        line = line.split('@')[0].strip()
        if len(line) == 0 or line[0] != "'":
          continue
        splits = []
        if line[0] == "'" and line[1] == "\\" and line[2] == "'":
          splits = ['', "'", line[4:]]
        else:
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
    with open(os.path.join(os.path.dirname(__file__), '..', 'emerald', 'pokeemerald.sym'), encoding='utf-8', mode='r') as f:
      for line in f:
        splits = line.split(' ')
        if len(splits) < 3:
          continue
        addr = int(splits[0], 16)
        name = splits[2].strip()
        self.symbols[name] = addr

  def transform_string(self, str):
    chars = []
    for c in str:
      if c in self.chars:
        chars.append(self.chars[c])
      else:
        raise ValueError('Unknown character: ' + c)
    chars.append(0xff)
    return bytes(chars)

  def transform_string_pad(self, str, size):
    data = self.transform_string(str)
    data_size = len(data)
    if data_size > size:
      raise ValueError('String too long: ' + str)
    return data + bytes([0xff] * (size - data_size))

  def emit_entry(self, base, id, size, data):
    d = self.transform_string_pad(data, size)
    addr = base + id * size
    self.entries.append({ 'addr': addr, 'data': d })

  def entries_table(self, sym_oftable, sym_buffer, filename, buffer_size):
    filename = os.path.join(os.path.dirname(__file__), '..', 'data', 'text', self.lang, filename)
    total_size = 0
    off_oftable = self.symbol(sym_oftable)
    off_buffer = self.symbol(sym_buffer)
    if not os.path.exists(filename):
      raise ValueError('File not found: ' + filename)
    with open(filename, encoding='utf-8', mode='r') as f:
      for line in f:
        splits = line.split('|')
        if len(splits) < 2:
          continue
        id = int(splits[0])
        str = unicodedata.normalize('NFC', splits[1]).strip()
        str_transformed = self.transform_string(str)
        str_transformed_size = len(str_transformed)
        new_offset = total_size
        total_size += str_transformed_size
        if total_size > buffer_size:
          raise ValueError('Buffer overflow: ' + filename)
        # Append data
        self.entries.append({ 'addr': off_buffer + new_offset, 'data': str_transformed })
        self.entries.append({ 'addr': off_oftable + id * 4, 'data': new_offset.to_bytes(4, byteorder='little') })

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
    self.entries_table('kMovesNamesOffsets', 'kMovesNamesBuffer', 'moves.txt', 16384)
    self.entries_table('kAbilitiesNamesOffsets', 'kAbilitiesNamesBuffer', 'abilities.txt', 8192)
    self.entries_table('kSpeciesNamesOffsets', 'kSpeciesNamesBuffer', 'pokemons.txt', 16384)
    self.output_data()

builder = LangBuilder(sys.argv[1])
builder.build()

