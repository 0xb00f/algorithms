from Crypto.Cipher import AES

def parse_structured(string):

	split_string = string.split('&')
	ret = dict()

	for pair in split_string:

		split_pair = pair.split('=')
		ret[split_pair[0]] = split_pair[1]

	return ret

def profile_for(string):
	
	return None

out = parse_structured("foo=bar&one=two&id=123")
print(out)
