def generate_fibs():

	'''
	return a list of all even fibonacci
	numbers less that 4 million 
	'''

	ret = []
	fib1 = 1
	fib2 = 2
	
	while True:

		if fib2 > 4000000:
			break
		elif fib2 % 2 == 0:
			ret.append(fib2)
		
		fib1, fib2 = fib2, fib1 + fib2

	return ret

print(sum(generate_fibs()))
