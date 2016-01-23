# UMass Launch Team Communications 2016
Communications for UMass Launch Team

The goal for this code is to create a way to communicate information from a rocket to a ground control station.  The rocket will have a raspi connected to a 900Mhz long-range radio, where information will be sent to a laptop on the ground using the mavlink protocol.   

There are two parts for this project:
 - The code running on the raspi that will send out all the information
 - The code running on the laptop which will save the information and present it in some way if wanted.  

Some Notes:
The mavlink-build folder was built by doing the following in linux (adjust the file locations for whereever the mavlink github repo is and the mavlink-build folder is on your machine)
 - cd ~/code/UMass-Launch-Comm/mavlink-build
 - cmake ../../mavlink 
 - make

To generate the UmassLaunchComm.xml file, go to the cloned mavlink repo and run python mavgenerate.py, and use the GUI to generate the files to mavlink-build/include/v1.0/
 
