"""
Implement variable width encoding with 
protocol buffers

A wire format that is an encoding of bytes that 
you can transmit over the network th at is compact. You can 
easily encode things like schemas.  
"""

def encode(n) -> bytes:
    buf = bytearray()
    buf.append
    while n:
        # get lower order 7 bits by AND'ing it with 0b01111111 or Ox7f in hex
        part = n & 0x7F
        n >>= 7
        if n > 0:
            part |= 0x80
        buf.append(part)
    return buf

def decode(b):
    n = 0
    for i in range(len(b) - 1, -1, -1):
        n ^= (b[i] & 0x7F)
        if i > 0:
            n <<= 7
    return n

if __name__ == "__main__":
    assert encode(150) == b'\x96\x01'
    assert encode(1) == b'\x01'
    assert decode(b'\x96\x01') == 150
    files = [
        "./1.uint64", 
        # "./150.uint64", 
        # "./maxint.uint64"
    ]
    for index, f in enumerate(files):
        with open(f, "rb") as f:
            b = f.read()
            int_val = int.from_bytes(b, "big")
            assert int_val == decode(encode(int_val))
    for n in range(1 << 32):
        assert decode(encode(n)) == n
    print("OK")