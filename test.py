import x16rv2_hash, os, sys, time, binascii

def gennonce(decnonce):
  hexnonce = str(hex(decnonce)).replace('0x','')
  while len(hexnonce) < 8:
    hexnonce = '0' + hexnonce
  return str(hexnonce)

#main
#         VERSION PREV BLOCKHASH|
header = '04000000fedcba9876543210123456789abcdef0031d8f75ade0746ec80b7020000000000f33171b804978ce997aafd70e7daffc44fba61609538b77773e32a9b830a73ea732dd15baa220'

target = "0000ffff00000000000000000000000000000000000000000000000000000000"
targetbin = binascii.unhexlify(target)
nonce = 0
while True:
  
  complete_header = str(header) + str(gennonce(nonce))
  hashbin = x16rv2_hash.getPoWHash(binascii.unhexlify(complete_header))[::-1]

  if hashbin < targetbin:
     print('block ' + str(binascii.hexlify(hashbin)))
     print('nonce was ' + str(nonce))
     sys.exit(0)

  if (nonce % 128 == 0):
     fnonce = str(hex(nonce)).replace('0x','')
     while len(fnonce) < 8:
      fnonce = '0' + fnonce
     print(fnonce)

  nonce += 1

