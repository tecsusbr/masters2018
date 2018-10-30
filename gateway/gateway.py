# MQTT Gateway

import paho.mqtt.client as mqtt
from threading import Thread
import serial
import json

SERVER_MQTT = "iot.eclipse.org"
PORT_MQTT = 1883
TOPIC_CMD = "master2018/strlight/cmd/"
TOPIC_REC = "master2018/strlight/rec/"
SERIAL = "COM5"


def on_connect(con, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    con.subscribe(TOPIC_REC)

# The callback for when a PUBLISH message is received from the server.


def on_message(con, userdata, msg):
    global ser
    print(msg.topic+" "+str(msg.payload))
    m = msg.payload.replace('\'', '')
    if m.find('{') == 0:
        m = json.loads(m)
        if 'uid' in m and 'light' in m:
            # @<UID><light>
            s = '@{:0>2}{}'.format(m['uid'], m['light'])
            print(s)
            ser.write(s)


def sub_loop():
    sub = mqtt.Client()
    sub.on_connect = on_connect
    sub.on_message = on_message
    sub.connect(SERVER_MQTT, PORT_MQTT, 60)
    sub.loop_forever()


def pub_loop():
    pub = mqtt.Client()
    pub.connect(SERVER_MQTT, PORT_MQTT, 60)
    pub.loop_start()
    while True:
        # msg = raw_input()
        # msg = {"light": 1, "temp": 12, "hum": 41, "uid": 1}
        # pub.publish(TOPIC_CMD + "1", json.dumps(msg))
        msg = ser.readline()
        print(msg)
        # #<UID>;<light>;<temp>;<humildade>\n
        if msg:
            msg = msg[1:].split(';')
            if len(msg) == 4:
                uid, light, temp, humildade = [int(x) for x in msg]
                topico = '{}{}'.format(TOPIC_CMD, uid)
                pay = dict(light=light, temp=temp, hum=humildade, uid=uid)
                payload = json.dumps(pay)
                pub.publish(topico, payload)

ser = serial.Serial(SERIAL, 38400)
sub_t = Thread(target=sub_loop, args=())
sub_t.start()

pub_t = Thread(target=pub_loop, args=())
pub_t.start()
