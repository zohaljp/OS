To compile the program:
- Run make, to compile all the files.
- Make sure to include main.c and scnerios.txt, Makefile in the same directory 
- Alternatively, could also run gcc -pthread main.c

To run the program:
- Include scenarios.txt to run all scenarios for the program.
-All scenarios are in the scenario.txt, the program will run and execute all scenarios once ran.

 make

 ./rwmain

Scenario Begins:

Scenario 1: Have majority of threads as read threads to show that write threads will not enter until Crtical section is empty 
Scenario 2: Mostly writer threads to show that only 1 writer is allowed per write 
Scenario 3: Tring to Starve write by only having 2 writes in the whole sequence
Scenario 4 : Tring to Starve write by only having 2 writes in the whole sequence
Scenario 5: Tring to Starve write by only having 2 writes in the whole sequence
Scenario 6 : Starve writer by having reads after writes 
Scenario 7 : complete random order to see if the distrubution of ressources is close to equal
Scenario 8 : complete random order to see if the distrubution of ressources is close to equal
Scenario 9 : complete random order to see if the distrubution of ressources is close to equal

