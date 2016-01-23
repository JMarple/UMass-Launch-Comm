all:
	#gcc -I include/v1.0/ -I include/v1.0/common main.c -o test
	gcc vehicle/vehicle.c -o startVehicle
	gcc ground/ground.c -o startGround
