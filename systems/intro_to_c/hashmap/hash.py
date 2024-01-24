def hash_djb2(s):                                       
    hash = 5381
    for x in s:
        # ord(x) simply returns the unicode rep of the
        # character x
        hash = (( hash << 5) + hash) + ord(x)
    # Note to clamp the value so that the hash is 
    # related to the power of 2
    # print(hash & 0xFFFFFFFF)
    print(hash)
    return hash & 0xFFFFFFFF

hash_djb2("item a")