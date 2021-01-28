import byte_rep as rep

probs ={'E':12.02,'T':9.1,'A':8.12,'O':7.68,'I':7.31,'N':6.96,'S':6.28,
         'R':6.02,'H':5.92,'D':4.32,'L':3.98,'U':2.88,'C':2.71,'M':2.61,
         'F':2.3,'Y':2.11,'W':2.09,'G':2.03,'P':1.82,'B':1.49,'V':1.11,
         'K':0.69,'X':0.17,'Q':0.11,'J':0.1,'Z':0.07,' ':18}

def score_freqs(s):

    return sum([probs.get(chr(x).upper(),0) for x in s])  

def decode(text):

    s = rep.DataRep()
    s.setFromHexString(text)
    winner = 0
    plaintext = None
    
    for ch in range(256):

        decrypt = s.singleByteXOR(ch)
        score = score_freqs(decrypt)
        if score > winner:

            winner = score
            plaintext = decrypt
            
    return plaintext, winner
        
with open('strs.txt','r') as _file:

    best_score = 0
    best_plaintext = None
    
    for line in _file:

        #decode line and save max score
        plaintext, score = decode(line.rstrip())
        
        if score > best_score:

            best_score = score
            best_plaintext = plaintext
            
    #highest scorer
    print(best_score,''.join([chr(x) for x in best_plaintext]))
