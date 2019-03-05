import numpy as np
import math
import rover_module as gps
import csv
import time
import sys

stack_time = 0
mu = np.mat([0, 0, 0, 0, 0, 0])
Sigma = np.mat([
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0]])

def setfirst(lat_in,low_in):
    global mu
    mu = np.mat([lat_in, low_in, 0, 0, 0, 0])




def lineCalman(get_time, x_mes, y_mes, v_ookisa, v_hougaku):
    global Sigma
    global mu
    global stack_time
    x_var = 0.000000000974
    y_var = 0.000000000474
    vx_var = 0.000141440438/(10**14)
    vy_var = 0.008214481518/(10**14)
    r = 6378.137
    v_hougaku_rad = math.radians(v_hougaku)
    vx_mes = v_ookisa * math.sin(v_hougaku_rad) / 1000 / 6378.137
    vy_mes = v_ookisa * math.cos(v_hougaku_rad) / 1000 / (6378.137 * math.cos(x_mes))
    delta_T = get_time - stack_time
    stack_time = get_time
    Y = np.mat([x_mes, y_mes, vx_mes, vy_mes])
    F = np.mat([
        [1, 0, delta_T, 0, delta_T**2 / 2, 0],
        [0, 1, 0, delta_T, 0, delta_T**2 / 2],
        [0, 0, 1, 0, delta_T, 0],
        [0, 0, 0, 1, 0, delta_T],
        [0, 0, 0, 0, 1, 0],
        [0, 0, 0, 0, 0, 1]
        ])
    H = np.mat([
        [1, 0, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0],
        [0, 0, 1, 0, 0, 0],
        [0, 0, 0, 1, 0, 0]
        ])
    R = np.mat([
        [x_var, 0, 0, 0],
        [0, y_var, 0, 0],
        [0, 0, vx_var, 0],
        [0, 0, 0, vy_var]
        ])

    mu_ = F * mu.T
    Sigma_ = F * Sigma * F.T

    yi = Y.T - H * mu_
    S = H * Sigma_ * H.T + R
    K = Sigma_ * H.T * S.I
    mu = (mu_ + K * yi).T
    Sigma = Sigma_ - K * H * Sigma_
    return mu[0:1]


if __name__ == '__main__':
    stack_time
    stack_time = time.time()
    args = sys.argv
    data_num = int(args[1])
    data_path = 'gps_data_calman.csv'
    while True:
        list_dis_thet = gps.lat_long_measurement()
        if list_dis_thet is not None:
            setfirst(list_dis_thet[0],list_dis_thet[1])
            break

    with open(data_path, mode='w', newline='') as f:
            writer = csv.writer(f)
            writer.writerow([ '緯度', '経度', '総数', data_num])
            for i in range(data_num):
                lat_long = gps.lat_long_measurement()
                vel = gps.velocity_measurement()
                mes_time = time.time()
                if lat_long[0] is not None and lat_long[1] is not None and vel[0] is not None and vel[1] is not None:
                    lat_low=lineCalman(mes_time, lat_long[0],lat_long[1],vel[0]* 1852 / 3600, vel[1])
                    writer.writerow(lat_low)
                    time.sleep(1)
