import sys
import re
alpha_to_decimal = {
    "a": 10, 
    "b": 11, 
    "c": 12, 
    "d": 13, 
    "e": 14, 
    "f": 15,
}

def char_to_decimal(char) -> int:
    if char.isdigit():
        return int(char)
    return alpha_to_decimal[char.lower()]

def six_digit_hex(hex):
    rgb_values = []
    val = 0
    for i in range(len(hex)):
        if hex[i] == "#":
            continue

        val ^= char_to_decimal(hex[i])
        if i % 2 == 0:
            rgb_values.append(val)          
            val >>= 8 # zero out the value
        else:
            val <<= 4 # move the 4 right bits 4 to the left
    r, g, b = rgb_values
    return f"rgb({r} {g} {b})"

def three_digit_hex(hex):
    rgb_values = []
    val = 0
    for i in range(len(hex)):
        if hex[i] == "#":
            continue
        decimal_val = char_to_decimal(hex[i])
        val ^= decimal_val
        val <<= 4 # move the 4 right bits 4 to the left
        val ^= decimal_val
        rgb_values.append(val)
        val = 0
    r, g, b = rgb_values
    return f"rgb({r} {g} {b})"    

def four_digit_hex(hex):
    rgb_values = []
    val = 0
    for i in range(len(hex)):
        if hex[i] == "#":
            continue
        decimal_val = char_to_decimal(hex[i])
        val ^= decimal_val
        val <<= 4 # move the 4 right bits 4 to the left
        val ^= decimal_val
        rgb_values.append(val)
        val = 0
    r, g, b, a = rgb_values
    alpha_val = '%.5f'%(a / 255)
    return f"rgba({r} {g} {b} / {alpha_val})"   

def eight_digit_hex(hex):
    rgb_values = []
    val = 0
    for i in range(len(hex)):
        if hex[i] == "#":
            continue

        val ^= char_to_decimal(hex[i])
        if i % 2 == 0:
            rgb_values.append(val)          
            val >>= 8 # zero out the value
        else:
            val <<= 4 # move the 4 right bits 4 to the left
    r, g, b, a = rgb_values
    alpha_val = '%.5f'%(a / 255)
    return f"rgba({r} {g} {b} / {alpha_val})"

def hex_to_rgb(hex):
    if len(hex) - 1 == 3:
        return three_digit_hex(hex)
    elif len(hex) - 1 == 4:
        return four_digit_hex(hex)
    elif len(hex) - 1 == 6:
        return six_digit_hex(hex)
    else:
        return eight_digit_hex(hex)

    

if __name__ == "__main__":
    sys.stdout.write(
        re.sub(r'#[0-9a-fA-F]+', 
        lambda x: hex_to_rgb(x.group(0)), 
        sys.stdin.read())
    )