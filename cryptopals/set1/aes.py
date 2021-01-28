import byte_rep as rep

class AES:

    '''
    class to perform AES decryption in ECB mode
    '''

    def __init__(self):
        
        self.data = rep.DataRep()
        self.key = rep.DataRep()
        self.round_keys = []

    def setData(self,hexstr):

        self.data.setFromHexString(hexstr)

    def setKey(self,hexstr):

        self.key.setFromHexString(hexstr)

    def __byteSub(self):


    def __shiftRow(self):


    def __mixColumn(self):


    def __addRoundKey(self):


    def __initKeyMix(self):
