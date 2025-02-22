import sys

buffer_original = bytearray(open(sys.argv[1], 'rb').read())
buffer_original_ext = buffer_original + buffer_original
buffer_new = bytearray(open(sys.argv[2], 'rb').read())
buffer_final = bytearray(len(buffer_new))

for i in range(len(buffer_original)):
    buffer_final[i] = buffer_original_ext[i] ^ buffer_new[i]

open(sys.argv[3], 'wb').write(buffer_final)
