import byte_rep as rep
from collections import Counter

probs ={'E':12.02,'T':9.1,'A':8.12,'O':7.68,'I':7.31,'N':6.96,'S':6.28,
         'R':6.02,'H':5.92,'D':4.32,'L':3.98,'U':2.88,'C':2.71,'M':2.61,
         'F':2.3,'Y':2.11,'W':2.09,'G':2.03,'P':1.82,'B':1.49,'V':1.11,
         'K':0.69,'X':0.17,'Q':0.11,'J':0.1,'Z':0.07,' ':18}

#input: list of ints representing bytes
def score_freqs(s):

    return sum([probs.get(chr(x).upper(),0) for x in s])  

def decode(ciphertext):

    s = rep.DataRep()
    s.setFromHexString(ciphertext)
    record = dict()

    for ch in range(256):

        decrypt = s.singleByteXOR(ch)
        record[ch] = score_freqs(decrypt)

    return max(record.keys(),key=lambda x: record[x])
        
string = '1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736'
print(decode(string))
