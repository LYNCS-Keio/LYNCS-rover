# -*- coding: utf-8 -*-
import micropyGPS
import serial
from math import radians
from math import degrees
from math import atan2
from math import acos
from math import sin
from math import cos


def gps_reader(sentence): 
    my_gps = micropyGPS.MicropyGPS(9, 'dd')
    for x in sentence:
        my_gps.update(x)
    return [my_gps.latitude[0], my_gps.longitude[0]]

def gps_measurement():
    s = serial.Serial('/dev/serial0', 9600, timeout=10)
    s.readline()
    sentence = s.readline().decode('utf-8')  # GPSデーターを読み、文字列に変換する
    if sentence[0] == '$':
        lat_and_long = gps_reader(sentence)
    return [lat_and_long[0], lat_and_long[1]]


r = 6378.137  # km


def convert_lat_long_to_r_theta(lat0, long0, lat1, long1):
    y0 = radians(lat0)
    x0 = radians(long0)
    y1 = radians(lat1)
    x1 = radians(long1)
    deltax = x1 - x0

    theta = atan2(sin(deltax), (cos(y0) * tan(y1) - sin(y0) * cos(deltax)))
    distance = r * acos(sin(y0) * sin(y1) + cos(y0) * cos(y1) * cos(deltax))
    return [distance, theta]
