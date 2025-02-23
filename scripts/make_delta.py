import sys

buffer_original = bytearray(open(sys.argv[1], 'rb').read())
buffer_final = bytearray(open(sys.argv[2], 'rb').read())

print(len(buffer_original))
print(len(buffer_final))

# COmpute crc32
crc = 0xFFFFFFFF
for i in range(len(buffer_final)):
    crc = crc ^ buffer_final[i]
    for j in range(8):
        if crc & 1:
            crc = (crc >> 1) ^ 0xEDB88320
        else:
            crc = crc >> 1

crc = crc ^ 0xFFFFFFFF
print("CRC32: 0x%08X" % crc)

for i in range(len(buffer_final)):
    buffer_final[i] = buffer_final[i] ^ buffer_original[i & (len(buffer_original) - 1)]

open(sys.argv[3], 'wb').write(buffer_final)
