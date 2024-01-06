fout = open("out", "w")

def is_nth_bit_set(n, byte):
    return byte & (1 << n)

# Helper methods to check if the MSB's are the start of a unicode code point
def is_len_two(b):
    for k in range(7, 5, -1):
        if not is_nth_bit_set(k, b):
            return False    
    return not is_nth_bit_set(5, b)

def is_len_three(b):
    for k in range(7, 4, -1):
        if not is_nth_bit_set(k, b):
            return False
    return not is_nth_bit_set(4, b) 

def is_len_four(b):
    for k in range(7, 3, -1):
        if not is_nth_bit_set(k, b):
            return False
    return not is_nth_bit_set(3, b)

NEWLINE = ord("\n")
with open("./cases", "rb") as f:
    lines = f.readlines()
    for index, l in enumerate(lines):
        trunc_len = l[0]
        output_line = bytearray([])
        for i, byte in enumerate(l[1:]):
            # Truncate if there are too many bytes. Also 
            # check if in the middle of a unicode code point. If so
            # don't add any of the bytes and append a new line
            if i >= trunc_len:
                output_line.append(NEWLINE)
                break 
            elif is_len_two(byte) and i + 2 > trunc_len:
                output_line.append(NEWLINE)
                break
            elif is_len_three(byte) and i + 3 > trunc_len:
                output_line.append(NEWLINE)
                break
            elif is_len_four(byte) and i + 4 > trunc_len:
                output_line.append(NEWLINE)
                break

            output_line.append(byte)
        try:
            fout.write(output_line.decode())
        except Exception as e:
            print(e)