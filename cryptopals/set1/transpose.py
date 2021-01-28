def to_blocks_wow(data,size):

    ret =  [data[i:i+size] for i in range(0,len(data),size)][:-1]
    return ret
    '''
    rem = len(data) % size
    diff = size - rem

    if rem > 0 and diff > 0: # dont have to be all same size

        for i in range(diff):

            data.append(0)

    return [data[i:i+size] for i in range(0,len(data),size)]
    '''
    
def transpose_blocks_wow(blocks):

    return list(map(list, zip(*blocks)))

def to_blocks(data,size):

    return [data[i:i+size] for i in range(0,len(data),size)]

def transpose_blocks(blocks,bsize):

    ret = []
    #for every ith element
    for i in range(bsize):
        #for every block
        tmp = []
        for b in range(len(blocks)):

            if i < len(blocks[b]):
                tmp.append(blocks[b][i])

        ret.append(tmp)

    return ret
            

blocks = [1,2,3,4,5,6,7,8,9,10,11]

a = to_blocks(blocks,2)
print(a)
print(transpose_blocks(a,2))
