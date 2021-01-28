from math import log
import byte_rep as rep

def entropy(p):

    return -p*log(p,2)

def entropy_vec(v):

    return sum([entropy(x) for x in v])

def to_prob_dist(v):

    dist = []
    for elem in set(v):

        dist.append(v.count(elem) / len(v))

    return dist

#read file and decode
with open('c8.txt') as _file:
    
    record = dict()
    for file_data in _file.readlines():
        
        data = rep.DataRep()
        data.setFromHexString(file_data.rstrip())

        # turn into probability distribution and record entropy
        record[file_data]= entropy_vec(to_prob_dist(data.toIntList()))

    # print line with lowest entropy
    print(min(record.keys(),key=lambda x: record[x]))



