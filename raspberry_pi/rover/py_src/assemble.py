from bin import lyncs_rover
import rover_module as gps
from rover_module import height
from time import sleep

#height.judgeHight1()
#print("phase1")
#height.judgeHight2()
#print("phase2")

cs = lyncs_rover.arduino_control()
if cs.Init() == -1:
    print('error')
#cs.Transfer(0, 6)
#sleep(1)

while True:
    length, theta = gps.r_theta_to_goal(35.555355, 139.655751)
    for i in range(25):
        judge=cs.Csearch1()
        if length*1000 < 100 and judge == 1:
            cs.Csearch2()
    #if r_theata[0]*1000 < 20:
    #    cs.Csearch2()
    #else:
    if length*1000>=100:
        cs.Transfer(int(theta*1000), 5)
        print(int(theta*1000))
        print('5')
