# -*- coding: utf-8 -*-
#%%
import csv
import rover_module as gps
import time
import sys
args = sys.argv

data_num = int(args[1])
data_path = 'gps_data.csv'
with open(data_path, mode='w', newline='') as f:
    writer = csv.writer(f)
    writer.writerow([data_num])
    for i in range(data_num):
        lat_long = gps.lat_long_measurement()
        if lat_long[0] is not None and lat_long[1] is not None:
            writer.writerow([time.time(), lat_long[0], lat_long[1]])

with open(data_path) as f:
    print(f.read())
# 0,1,2
# "a,b,c","x","y"