# flight-simulator

This program gets a script which should fly a plane in the http://home.flightgear.org/ simulator, in a language made up by my lecteror, interpets it and executes the commands as they defined.

The program works on 2 different threads.

The first communicate with the flight simulator http://home.flightgear.org/, gets data of the plane's variables and updates the data structure.

The second interpets and executes the script received. This thread updates the plane variables in the simulator. By that, the plane is able to fly. 



