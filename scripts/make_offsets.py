import os

SYMBOLS = [
  'kStarterMons',
  'kFirstBattlePokemon',
  'gWildMonHeaders',
  'gSpeciesInfo',
  'gTrainers',
]

class OffsetsBuilder:
  def __init__(self):
    self.entries = []

  def parse_symbols(self):
    with open(os.path.join(os.path.dirname(__file__), '..', 'emerald', 'pokeemerald.sym'), 'r') as f:
      for line in f:
        splits = line.split(' ')
        if len(splits) < 3:
          continue
        addr = int(splits[0], 16)
        name = splits[2].strip()
        if name in SYMBOLS:
          entry = {
            'addr': addr - 0x08000000,
            'name': name,
          }
          self.entries.append(entry)

  def output_data(self):
    dir = os.path.join(os.path.dirname(__file__), '..', 'build', 'data')
    if not os.path.exists(dir):
      os.makedirs(dir)
    filename = os.path.join(dir, 'offsets.bin')
    with open(filename, 'wb') as f:
      count = len(self.entries)
      f.write(count.to_bytes(4, byteorder='little'))
      for entry in self.entries:
        addr = entry['addr']
        name = bytes(entry['name'], 'utf-8')
        f.write(addr.to_bytes(4, byteorder='little'))
        f.write(len(name).to_bytes(4, byteorder='little'))
        f.write(name)

  def build(self):
    self.parse_symbols()
    self.output_data()

builder = OffsetsBuilder()
builder.build()
