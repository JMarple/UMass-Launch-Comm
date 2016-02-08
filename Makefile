CFLAGS = -I mavlink-build/include/v1.0
CFLAGS += -I mavlink-build/include/v1.0/UMassLaunchComm
CFLAGS += -I serial
CFLAGS += -g -Wall -Wextra -Wshadow
SERIAL = serial/rs232.c
SERIAL += serial/serial.c

all:
	gcc $(CFLAGS) vehicle/vehicle.c $(SERIAL) -o startVehicle
	gcc $(CFLAGS) ground/ground.c $(SERIAL) -o startGround
