import micropyGPS
import serial
import math
import ctypes
from math import sin
from math import cos
from math import tan
from math import atan2
from math import acos
from math import radians
from math import degrees
from time import sleep
high =ctypes.CDLL('./bme280.so')




def gps_measurement():
    my_gps = micropyGPS.MicropyGPS(9, 'dd')
    s = serial.Serial('/dev/serial0', 9600, timeout=10)
    s.readline()
    while my_gps.parsed_sentences < 5:
        sentence = s.readline().decode('utf-8') # GPSデーターを読み、文字列に変換する
        if sentence[0] == '$':
            for x in sentence: # 読んだ文字列を解析してGPSオブジェクトにデーターを追加、更新する
                my_gps.update(x)
    return [my_gps.latitude[0], my_gps.longitude[0]]

r= 6378.137
x1=139.988909
y1=35.685828
x1=radians(x1)
y1=radians(y1)
while True:
    high.Csearch1()

    gpsdata=gps_measurement()

    x2=radians(gpsdata[1])
    y2=radians(gpsdata[0])

    deltax = x2 - x1
    ans = atan2(sin(deltax),(cos(y1)*tan(y2)-sin(y1)*cos(deltax)))
    distance = r*acos(sin(y1)*sin(y2)+cos(y1)*cos(y2)*cos(deltax))
    if distance < 1000:
        high.trns(ans*1000,0);
    else :
        high.Csearch2()
