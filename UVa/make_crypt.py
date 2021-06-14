from random import choices, shuffle

def do_perm(line,abet,perm):

    mapping = dict(zip(abet,perm))
    ret = ""
    for i in range(len(line)):

        if line[i] == ' ':

            ret += " "

        else:

            ret += mapping[line[i]]

    return ret

abet = "abcdefghijklmnopqrstuvwxyz"
permd = abet
words = ["now","for","eleven","same","fuzzy","apple","the","tree",
         "dog","and","banana","santa","train","xanax","smell","fortune",
         "spade","daniel","baseball","excellent","aim","spain","melt",
         "rain","weep","thought","sport","stay", "rose","love","beautiful",
         "happy","forever"]

plines = []
clines = []

for i in range(5000):

    print("testing ",permd)
    line = ' '.join(choices(words,k=8))
    plines.append(line)
    l = list(permd)
    shuffle(l)
    permd = ''.join(l)
    res=do_perm(line,abet,permd)
    clines.append(res)

infile = "tests.in"
outfile = "tests.out"

with open(infile,'w') as in_f:

    in_f.write(str(len(words))+'\n')

    for w in words:

        in_f.write(w+'\n')

    for c in clines:

        in_f.write(c+'\n')
        
    
with open(outfile,'w') as out_f:

    for w in plines:

        out_f.write(w+'\n')
