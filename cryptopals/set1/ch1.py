import base64

# function
def hex_to_base64(hex_string):

    hex_bytes = bytes.fromhex(hex_string)
    print(hex_bytes)
    return base64.b64encode(hex_bytes)

# testing
test = '49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d'

correct_result = b'SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t'

result = hex_to_base64(test)

if result == correct_result:

    print("success!")

else:

    print("failure :(")
