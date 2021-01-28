from itertools import combinations
import byte_rep as rep
import base64

probs ={
    'a': 0.0651738, 'b': 0.0124248, 'c': 0.0217339, 'd': 0.0349835, 'e': 0.1041442, 'f': 0.0197881, 'g': 0.0158610,
    'h': 0.0492888, 'i': 0.0558094, 'j': 0.0009033, 'k': 0.0050529, 'l': 0.0331490, 'm': 0.0202124, 'n': 0.0564513,
    'o': 0.0596302, 'p': 0.0137645, 'q': 0.0008606, 'r': 0.0497563, 's': 0.0515760, 't': 0.0729357, 'u': 0.0225134,
    'v': 0.0082903, 'w': 0.0171272, 'x': 0.0013692, 'y': 0.0145984, 'z': 0.0007836, ' ': 0.1918182
}

def block_hamming_distance(x,y):

    x_bin = rep.DataRep()
    y_bin = rep.DataRep()

    x_bin.setFromIntList(x)
    y_bin.setFromIntList(y)

    x_binstr = x_bin.toBinString()
    y_binstr = y_bin.toBinString()
    diff = 0

    for (x_i,y_i) in zip(x_binstr,y_binstr):
        
        if x_i != y_i:

            diff += 1

    return diff

def to_blocks(data,size):

    return [data[i:i+size] for i in range(0,len(data),size)]

def transpose_blocks(blocks,bsize):

    ret = []
    for i in range(bsize):

        tmp = []
        for b in range(len(blocks)):

            if i < len(blocks[b]):
                
                tmp.append(blocks[b][i])

        ret.append(tmp)

    return ret
      
def normalised_hamming_dist(blocks,ksize):

    results = [block_hamming_distance(x,y) for (x,y) in combinations(blocks,2)]

    return sum(results) / (len(results) * ksize)

def find_keysize(x):

    record = dict()

    for ksize in range(2,41): 

        # obtain bytes
        data = x.toIntList()
        # split into block lengths
        data =  [data[i:i+ksize] for i in range(0,len(data),ksize)]#to_blocks(data,ksize)
        # find edit distance between consecutive pairs
        hams = [block_hamming_distance(data[i],data[i+1]) for i in range(len(data)-1)]
        # record average, normalised by ksize        
        record[ksize] = normalised_hamming_dist(data[:-1],ksize)

    #return block 5 lengths with least normalised edit distance
    return sorted(record.keys(),key=lambda k: record[k])[:5]

def score_freqs(s):

    return sum([probs.get(chr(x).lower(),0) for x in s])  

def XORdecode(text):

    s = rep.DataRep()
    s.setFromIntList(text)
    winner = 0
    record = dict()
    
    for ch in range(256):

        decrypt = s.singleByteXOR(ch)
        score = score_freqs(decrypt)
        record[ch] = score
        if score > winner:

            winner = score
            xor_key = ch
      
    return xor_key


#read file and decode
with open('c6file.txt') as _file:

    file_data = _file.read()
    file_data = base64.b64decode(file_data)
    data = rep.DataRep()
    data.setFromIntList(list(file_data))

#find likely key sizes
ksizes = find_keysize(data)
record = dict()
for klen in ksizes:
    blocks = data.toIntList()
    blocks = to_blocks(blocks,klen)
    trans_blocks = transpose_blocks(blocks,klen)
    record[klen] = list()
    for tblock in trans_blocks:
        xor_key = XORdecode(tblock)
        record[klen].append(xor_key)

# print results
for ksize in record.keys():

    print("possible key:",''.join([chr(x) for x in record[ksize]]))
    print("decryption:",''.join([chr(x) for x in data.multiByteXOR(record[ksize])]))


