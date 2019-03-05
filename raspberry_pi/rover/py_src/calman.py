import numpy as np

stack_time = 0
mu = np.mat([45,56,0,0,0,0])
Sigma = np.mat([0,0,0,0,0,0]\
                [0,0,0,0,0,0]\
                [0,0,0,0,0,0]\
                [0,0,0,0,0,0]\
                [0,0,0,0,0,0]\
                [0,0,0,0,0,0])



def lineCalman(get_time,x_mes,y_mes,v_ookisa,v_hougaku):
    global stack_time
    global Sigma
    global mu
    x_var = 0.000000000974
    y_var = 0.000000000474
    vx_var = 1
    vy_var = 1
    r = 6378.137
    v_hougaku_rad = radians(v_hougaku)
    vx_mes = v_ookisa*sin(v_hougaku_rad)/1000/6378.137
    vy_mes = v_ookisa*cos(v_hougaku_rad)/1000/(6378.137*cos(x_mes))
    delta_T = get_time - stack_time
    stack_time = get_time
    Y = np.mat(x_mes,y_mes,vx_mes,vy_mes)
    F = np.mat([1,0,delta_T,0,delta_T**2/2,0],\
                [0,1,0,delta_T,0,delta_T**2/2],\
                [0,0,1,0,delta_T,0]\
                [0,0,0,1,0,delta_T]\
                [0,0,0,0,1,0]\
                [0,0,0,0,0,1])
    H = np.mat([1,0,0,0,0,0]\
                [0,1,0,0,0,0]\
                [0,0,1,0,0,0]\
                [0,0,0,1,0,0])
    R = np.mat([x_var,0,0,0]\
                [0,y_var,0,0]\
                [0,0,vx_var,0]\
                [0,0,0,vy_var])

    mu_ = F * mu
    Sigma_ = F * Sigma * F.T

    yi = Y - H * mu_
    S = H * Sigma_ * H.T + R
    K = Sigma_ * H.T * S.I
    mu = mu_ + K * yi
    Sigma = Sigma_ - K * H * Sigma_

    if __name__ == '__main__':
        lineCalman(2,3,4,5,6)
