from bin import lyncs_rover


cs = lyncs_rover.arduino_control()
while True: 
    cs.Csearch2()