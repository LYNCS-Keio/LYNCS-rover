from micropyGPS import MicropyGPS
import serial
import 

def gps_measurement():
    my_gps = MicropyGPS()
    while !(my_gps.clean_sentenses > 20)
        s = serial.Serial('/dev/serial0', 9600, timeout=10)
        print(s.readline())
        sentence = s.readline().decode('utf-8') # GPSデーターを読み、文字列に変換する
        if sentenses[0] != '$'
            for x in sentence: # 読んだ文字列を解析してGPSオブジェクトにデーターを追加、更新する
                my_gps.update(x)
    print(my_gps.latitude)
    print(my_gps.longitude)