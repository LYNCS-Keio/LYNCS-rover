from bin import lyncs_rover
import rover_module as gps
from rover_module import height
from time import sleep

goal_lat, goal_log = [35.555744, 139.654071]

cs = lyncs_rover.arduino_control()
if cs.Init() == -1:
    print('error')
## test before falling
count = 0
while True:
    count += 1
    judge_data0 = height.readData()
    cs.LogOutput('phase1, height::' + str(judge_data0))
    if count > 20:
        break

while True:
    coord = gps.lat_long_measurement()
    if coord is not None:
        cs.LogOutput('lat::' + str(coord[0]) + ', long::' + str(coord[1]))
        break

sleep(30)  # fall

# after landing
cs.LogOutput('landed.')

count = 0
while True:
    count += 1
    judge_data0 = height.readData()
    cs.LogOutput('phase2, height::' + str(judge_data0))
    if count > 20:
        break

while True:
    coord = gps.lat_long_measurement()
    if coord is not None:
        cs.LogOutput('lat::' + str(coord[0]) + ', long::' + str(coord[1]))
        break

cs.Transfer(0,2)
sleep(20)

while True:

    for i in range(25):
        judge = cs.Csearch1()
        if judge == 1:
            cs.Csearch2()

cs.Transfer(0, 3)