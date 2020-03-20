#module with helper functions for project euler problems

import math

# simple primality test - TODO: more efficient one 
def is_prime(n):

    for i in range(2,int(math.sqrt(n))):

        if n % i == 0:

            return False

    return True

# generate primes up to n
def primes_to(n):

    # uses one version of the sieve of eratosthenes

    record = [True for i in range(n+1)]	

    for i in range(2,int(math.sqrt(n))):

        if record[i]:

            j = i*i

            while j <= n:

                record[j] = False
                j += i

    ret = []

    for i in range(2,len(record)):

        if record[i]:

            ret.append(i)

    return ret

#return the nth prime (a stored list, then a generator?)

# TODO: decompose into list of prime factors
