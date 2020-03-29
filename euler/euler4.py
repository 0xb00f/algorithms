def is_palindrome(x):
        
        x = str(x)
        hi = len(x)-1
        lo = 0

        while lo < hi:

                if x[lo] != x[hi]:

                        return False

                lo += 1
                hi -= 1

        return True

vals = [x for x in range(100,1000)]

result = 0

for i in vals:

	for j in vals:

		val = i*j

		if val > result and is_palindrome(val):

			result = val

print(result)
