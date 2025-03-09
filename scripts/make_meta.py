import os
import re
import json

class MetaBuilder:
  def __init__(self):
    self.symbols = {}
    self.defines = {}
    self.metaSyms = {}

  def parse_symbols(self):
    with open(os.path.join(os.path.dirname(__file__), '..', 'emerald', 'pokeemerald.sym'), encoding='utf-8', mode='r') as f:
      for line in f:
        splits = line.split(' ')
        if len(splits) < 3:
          continue
        addr = int(splits[0], 16)
        name = splits[2].strip()
        self.symbols[name] = addr

  def parse_defines(self, file, prefix):
    define_prefix = "#define " + prefix + "_"
    file = os.path.join(os.path.dirname(__file__), '..', 'emerald', 'include', 'constants', file)
    with open(file, encoding='utf-8', mode='r') as f:
      for line in f:
        if line.startswith(define_prefix):
          line = line[len(define_prefix):].strip()
          # Remove C++-style comments
          line = line.split('//')[0].strip()
          splits = line.split()
          if len(splits) < 2:
            continue
          name = splits[0]
          value_str = splits[1]
          if re.match('0x[0-9a-fA-F]+', value_str):
            value = int(value_str, 16)
          elif re.match('[0-9]+', value_str):
            value = int(value_str)
          else:
            continue
          self.defines[prefix + '_' + name] = value

  def symbol(self, name):
    data = self.symbols[name]
    if data == None:
      raise ValueError('Unknown symbol: ' + name)
    return data

  def emit_meta_sym_array(self, name, type, sym, prefix, member):
    data = {}
    data['array'] = True
    data['type'] = type
    base = self.symbol(sym)
    stride = self.defines['DATA_' + prefix + '_SIZE']
    offset = self.defines['DATA_' + prefix + '_OFF_' + member]
    base += offset
    data['base'] = base
    data['stride'] = stride
    self.metaSyms[name] = data

  def output_data(self):
    dir = os.path.join(os.path.dirname(__file__), '..', 'build', 'data')
    if not os.path.exists(dir):
      os.makedirs(dir)
    filename = os.path.join(dir, 'meta.json')
    data = {}
    m = data['meta'] = {}
    m['symbols'] = self.metaSyms
    jdata = json.dumps(data)
    with open(filename, mode='w', encoding='utf-8') as f:
      f.write(jdata)

  def build(self):
    self.parse_symbols()
    self.parse_defines('offsets.h', 'DATA')
    self.emit_meta_sym_array('SpeciesStats',      'u8[6]',  'gSpeciesInfo', 'SPECIES', 'STATS')
    self.emit_meta_sym_array('SpeciesTypes',      'u8[2]',  'gSpeciesInfo', 'SPECIES', 'TYPES')
    self.emit_meta_sym_array('SpeciesCatchRate',  'u8',     'gSpeciesInfo', 'SPECIES', 'CATCH_RATE')
    self.emit_meta_sym_array('SpeciesGrowthRate', 'u8',     'gSpeciesInfo', 'SPECIES', 'GROWTH_RATE')
    self.emit_meta_sym_array('SpeciesAbilities',  'u16',    'gSpeciesInfo', 'SPECIES', 'ABILITIES')
    self.output_data()

builder = MetaBuilder()
builder.build()
