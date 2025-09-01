import random
from SFFencryption.entable import encry

keys = []

def encryptor(codefromsend):
    value = list(codefromsend)
    code = [int(number) for number in value]

    code = codeencryptor(code)

    enckeys = keyencrypt()
    codearray = cnvertor(code)

    return enckeys, codearray
# encrypt
def codeencryptor(code):
    for i in range(len(code)):
        key = random.randint(1,10)
        code[i] += key
        code[i] *= key
        keys.append(key)

    return code

def keyencrypt():
    message = ""
    for i in range(len(keys)):
        encGroup = random.randint(1, len(encry))
        message += encry[str(encGroup)][str(keys[i])]

    keys.clear()
    return message

def cnvertor(code):
    codearray = ""
    for i in range(len(code)):
        codearray += str(code[i])
        codearray += "/"

    return codearray