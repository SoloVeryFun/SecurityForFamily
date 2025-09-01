import paho.mqtt.client as mqtt
import random
import userDataBase
from SFFencryption import encrypt

#connect
broker = 'hairdresser.cloudmqtt.com'
port = 18974
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    client.subscribe("topic")


client = mqtt.Client()

client.username_pw_set("python", "python")
client.connect(broker, port, 60)
client.on_connect = on_connect

client.loop_start()
#connect^^^^^

#main
def open(id):
    code = codeGenerator(userDataBase.saveCodeLength(id))
    key, enccode = encrypt.encryptor(code)
    print(key)
    print(enccode)
    client.publish("key", key)
    client.publish("code", enccode)
    return code

def codeGenerator(sign):
    returnCode = ""
    for i in range(sign):
        returnCode += str(random.randint(0,9))
    return returnCode