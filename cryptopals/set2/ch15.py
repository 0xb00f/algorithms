def validate_padding(ctext):
	
	count = 0
	rev = ctext.encode()[::-1]
	pad_byte = rev[0]
	for i in range(len(rev)):

		if rev[i] == pad_byte:
			count += 1
			continue
		else:
			break
	
	if count == pad_byte:

		return ctext[:-pad_byte]
	else:

		raise Exception("invalid padding")

a = "ICE ICE BABY\x04\x04\x04\x04"
b = "ICE ICE BABY\x05\x05\x05\x05"
c = "ICE ICE BABY\x01\x02\x03\x04"

for s in [a,b,c]:
	try:
		print(validate_padding(s))
	except:
		print("INVALID PADDING:",s)
