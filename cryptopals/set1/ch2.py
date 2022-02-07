thing = '1c0111001f010100061a024b53535009181c'
thing2 = '686974207468652062756c6c277320657965'

def bytewise_vec_xor(v1,v2):

    return hex(int(v1,16) ^ int(v2,16))

print(bytewise_vec_xor(thing,thing2))
    

    
