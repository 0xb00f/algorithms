threes = {x for x in range(3,1000,3)}
fives = {x for x in range(5,1000,5)}

print(sum(threes.union(fives)))
