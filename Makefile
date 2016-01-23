CFLAGS = -I mavlink-build/include/v1.0
CFLAGS += -I mavlink-build/include/v1.0/UMassLaunchComm
CFLAGS += -I serial
SERIAL = serial/rs232.c

all:
	#gcc -I include/v1.0/ -I include/v1.0/common main.c -o test
	gcc $(CFLAGS) vehicle/vehicle.c $(SERIAL) -o startVehicle
	gcc $(CFLAGS) ground/ground.c $(SERIAL) -o startGround
