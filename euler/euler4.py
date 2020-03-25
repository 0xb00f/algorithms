def is_palindrome(n):

	num_list = list(map(int,str(n)))

	return num_list == num_list[::-1]

vals = [x for x in range(100,1000)]

result = 0

for i in vals:

	for j in vals:

		val = i*j

		if val > result and is_palindrome(val):

			result = val

print(result)
