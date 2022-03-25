from Crypto.Cipher import AES
import os

def pad_bytes(text):

	diff = len(text) % 16
	text = text.encode()

	if diff == 0:

		return text

	else:
		
		return text + (b'\x04' * (16-diff))

def parse_profile(string):

	split_string = string.split('&')
	ret = dict()

	for pair in split_string:

		[x,y] = pair.split('=')
		ret[x] = y

	return ret

def encode_profile(usrdict):

	return "email=" + usrdict['email'] + "&uid=" + usrdict['uid'] + "&role=" + usrdict['role']

def profile_for(user_email):
	
	fake_db = { 
		'dan@wow.com' : parse_profile('email=dan@wow.com&uid=666&role=user'),
		'boof@kd.com.au' : parse_profile('email=boof@kd.com.au&uid=420&role=user')
	}

	sanitise_email = user_email.replace('=','').replace('&','')

	if sanitise_email not in fake_db:

		return None

	return encode_profile(fake_db[sanitise_email])

def encrypt_profile(profile,cipher):
	
	profile = pad_bytes(profile_for(profile))
	return cipher.encrypt(profile)

def decrypt_profile(profile,cipher):
	
	decrypted = cipher.decrypt(profile).replace(b"\x04",b"")
	return parse_profile(decrypted.decode('ascii'))

test = "dan@wow.com"
random_key = os.urandom(16)
cipher = AES.new(random_key,AES.MODE_ECB)
print(profile_for(test))
print(decrypt_profile(encrypt_profile(test,cipher),cipher))

#attack!!!
