from bin import lyncs_rover
import rover_module as gps
from rover_module import height
from time import sleep


cs = lyncs_rover.arduino_control()
if cs.Init() == -1:
    print('error')

height.judgeHight1()
cs.LogOutput("phase1")
height.judgeHight2()
cs.LogOutput("phase2")

length, theta = [0,0]
while True:
    list_dis_thet = gps.r_theta_to_goal(35.555744, 139.654071)
    if list_dis_thet != None:
        length, theta = list_dis_thet
        break

while True:
    
    list_dis_thet = gps.r_theta_to_goal(35.555744, 139.654071)
    if list_dis_thet != None:
        length, theta = list_dis_thet
    
    coord = gps.lat_long_measurement()
    cs.LogOutput('lat::%f long::%f' % (coord[0], coord[1]))
    length, theta = gps.r_theta_to_goal(35.554486, 139.657568)
    cs.LogOutput('dist::%f angle::%f' % (length, theta))
    for i in range(25):
        judge = cs.Csearch1()
        if length * 1000 < 40 and judge == 1:
            cs.Csearch2()
    # f r_theata[0]*1000 < 20:
    #    cs.Csearch2()
    # else:
    if length * 1000 >= 40:
        cs.Transfer(int(theta * 1000), 5)
