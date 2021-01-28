import byte_rep as rep

plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"
k = [ord(x) for x in "ICE"]
s = rep.DataRep()
s.setFromString(plaintext)
s.setFromIntList(s.multiByteXOR(k))
print(s.toHexString())
