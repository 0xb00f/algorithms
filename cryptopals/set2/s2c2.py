import byte_rep as rep
from Crypto.Cipher import AES

def to_blocks(data,size):

    return [data[i:i+size] for i in range(0,len(data),size)]

# get file data
with open('c7.txt') as _file:

    file_data = _file.read()
    data = rep.DataRep()
    data.setFromHexString(file_data)
    
# pad the plaintext

# split data into 16 byte blocks
blocks = to_blocks(data.toIntList())

# intialise cipher (?), key, initial vector
IV = bytes(16)
key = b'YELLOW SUBMARINE'
cipher = AES.new(key,AES.MODE_ECB)

# for each block
for b in block:
    
    # xor the block with the iv - figure this out, not object method
    '''
    would it be useful it all these transformations on the data,
    such as turning into block and operating on them
    '''
    
    # encrypt the block using the key

    '''
    #cipher = AES.new(key,AES.MODE_ECB)
    curr_block = cipher.decrypt(b)
    ??? what does this do? do i decrypt? how do i build a plaintext?
    '''
    # emcrypted block becomes new iv
