fout = open("out", "w")

def is_nth_bit_set(n, byte):
    return byte & (1 << n)

# Helper methods to check if the MSB's are the start of a unicode code point
def is_len_two(b):
    return b > 0xc0

def is_len_three(b):
    return b > 0xe0

def is_len_four(b):
    return b > 0xf0

with open("./cases", "rb") as f:
    lines = f.readlines()
    for index, l in enumerate(lines):
        trunc_len = l[0]
        output_line = bytearray([])
        for i, byte in enumerate(l[1:-1]):
            # Truncate if there are too many bytes. Also 
            # check if in the middle of a unicode code point. If so
            # don't add any of the bytes and append a new line
            if i >= trunc_len:
                break 
            elif is_len_two(byte) and i + 2 > trunc_len:
                break
            elif is_len_three(byte) and i + 3 > trunc_len:
                break
            elif is_len_four(byte) and i + 4 > trunc_len:
                break

            output_line.append(byte)
        try:
            fout.write(output_line.decode() + "\n")
        except Exception as e:
            print(e)