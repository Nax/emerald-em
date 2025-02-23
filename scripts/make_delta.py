import sys

buffer_original = bytearray(open(sys.argv[1], 'rb').read())
buffer_final = bytearray(open(sys.argv[2], 'rb').read())

for i in range(len(buffer_final)):
    buffer_final[i] = buffer_final[i] ^ buffer_original[i & (len(buffer_original) - 1)]

open(sys.argv[3], 'wb').write(buffer_final)
