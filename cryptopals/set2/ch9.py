def pad_block(b,blen):

    diff = blen - len(b)
    
    return b + b'\x04'*diff

a = b'yellow submarine'
print(pad_block(a,20))
