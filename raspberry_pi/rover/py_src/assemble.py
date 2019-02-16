from bin import lyncs_rover
import rover_module as gps
from time import sleep

goal_lat = 0
goal_long =0

while True:
    lyncs_rover.Csearch1()
    r_theata=gps.r_theta_to_goal(goal_lat, goal_long)
    if r_theata[0] < 20:
        lyncs_rover.Csearch2()
    else:
        lyncs_rover.TransferValuesToArduino((int)(r_theata[0]/1000), 0)
    sleep(2)
