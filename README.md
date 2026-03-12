Labs 6 and 7 will cover the same topic: Object-Oriented Programming (OOP). However, unlike the other labs, this will be the only lab where you can complete some of the work outside of the lab session. You will be required to complete the first four checkpoints during the first lab (Lab #6), however, you may work on the final four checkpoints outside of the lab. You are required to attend Lab #7 to show and explain your work to the TA and receive credit for the final four checkpoints.

---
There are four main principles of OOP:

 - **Abstraction**
 - **Encapsulation**
 - **Inheritance**
 - **Polymorphism**

To illustrate how these principles can be combined in a single program, we will design our own [4X simulation](https://en.wikipedia.org/wiki/4X). 4X is an abbreviation of <u>Explore, Expand, Exploit, Exterminate</u>, which describes many modern strategy video and board games including [Civilization](https://en.wikipedia.org/wiki/Civilization_(series)) or [Twilight Imperium](https://en.wikipedia.org/wiki/Twilight_Imperium). Our simulation will be much simpler, and we will not require the Exterminate element to be included. However, our simulation should allow users to explore unknown areas, expand their influence, and exploit resources that they discover. This will take the form of a simple text-based interface that allows users to type in their commands and view the world through the text output, such as the example below:
```
..........
..........
.0........
..0.......
1.......T.
.......2.2
.......TT.
..1.......
..........
~~~~~~~~~~
```

The world represented in the output above includes mostly empty Plains (.), as well as a River (~) that runs west to east along the bottom of the map. The numbers represent Units that are controlled by the 3 different players (0, 1, 2), and the Ts represent Buildings.

The starter folder contains the initial code for the simulation, as well as a makefile you can use to build it. You are free to modify the makefile as you wish. Be sure to use make clean if you need to rebuild any object files after modifying the header files. The starter code includes:

 - main.cpp - the main file that runs the simulation loop
 - Terrain.h - a header file containing the declaration for an Abstract (more on this later) Terrain class
     - Plains.h - a header file containing the implementation for a Plains class that Inherits (more on this later) from Terrain
 - Player.cpp and Player.h - the code for a Player in the simulator, including their units and property
 - World.cpp and World.h - the code that manages the world of the simulation, including the grid (from above) and its visualization, and the position of units and their placement

 You should be able to build the current program using make. If you run the game executable, it will simply display the empty map since at the moment, there is nothing in the world except for a grid of empty Plains. We will employ <u>**Object-Oriented Principles**</u> in this lab to populate the world and create a simulation that the user actually can interact with.