from bin import lyncs_rover
aa = 0


while True:

        a = int(input())
        b = int(input())
        #b = 0
        #a = 100
        aa =  a

        axis1 = int(aa )
        axis5 = 30
        axis2 = 20
        button = b


        print(axis1)
        print(b)

        lyncs_rover.TransferValuesToArduino(axis1,b);
        #sleep(0.1)
