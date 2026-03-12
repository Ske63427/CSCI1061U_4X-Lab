# Lab 6
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

# New Terrain

Before implementing any new content, take some time to review the Terrain.h and Plains.h files. Because Terrain has a **pure virtual function** getType that is equal to 0 (in other words, not implemented), Terrain is what we call an **abstract class** - it is not possible to create a Terrain object, but it serves as a sort of template for other classes that can represent different kinds of areas (e.g. Plains, Water, Mountains, Forests, etc.). The Plains class **inherits** from the Terrain class, which is done in the first line of code:
```
class Plains : public Terrain {
```
Here, we declare that a Plains \* is \* a Terrain - the "is a" relationship is an example of the OOP principle of **Inheritance**. This means that Plains is obligated to implement the pure virtual function getType in order to be a **concrete** (and not an abstract) class that can be **instantiated**. We would say that Terrain is an **abstraction** of what it means to be an area in the World, and Plains is just one example of what that might look like in reality.

The reason we say public Terrain when defining a Plains is because we want the public Terrain functions to remain public for our program. In a case where Terrain has public functions that we don't want anyone accessing through a Plains, you would inherit from Terrain using either private or protected (**protected** is like private, except that subclasses can still access the member). This protection of data from being accessed is part of **encapsulation**, where a class should avoid making too many members public unless necessary.

To get some practice implementing your own derived class (that inherits from Terrain, just like Plains does), choose a type of Terrain (either from the aforementioned examples, or make up your own!), and add the class to the program. You must, at a minimum:

 - Create a new type of Terrain that will behave differently than Plains (you can think about this now and implement it later, but be prepared to tell your TA what the purpose of this Terrain is - perhaps certain Units cannot enter a Water space)
 - Modify the World.cpp's constructor to place some of that Terrain on the grid instead of Plains. This should be done according to a systematic rule (e.g. a line, a square, or purely randomly placed) rather than in hard-coded positions
 - Modify the World.cpp's displayMap function to display your terrain type using a different symbol than the . for Plains
     - You will later need to adjust the displayMapWithSight function to do this as well, but it can't be implemented just yet since we don't have any Units to see anything

# Units and Scouts

Now that we have a slightly more varied World, we need to populate it with Units. Each Player will control Units that perform **actions** on their turn, which differ based on the type of Unit. This is an example of **Polymorphism** - we want the Players to be able to use the same interface to interact with their Units, but what actually happens should be dependent on the Unit's type. To do so, we'll need to make the Unit class an abstract class with virtual methods, and then create our own derived class that is the Player's first Unit.

You can create a header file for Unit (i.e. Unit.h) since it won't have much implemented in it and won't change for the rest of this lab. Here is the necessary content for the Unit abstract class:

 - A single integer member variable representing the sight range of the unit (needed to displayMapWithSight, so Players only get to see what their Units see)
 - A constructor, virtual deconstructor, and getter function for the sight
 - virtual functions to get the name of the Unit and perform an action in the World
     - The action method will need two parameters - one for the number representing which Player controls the Unit, and another which is a reference to the World.
     - Because the World needs to know what a Unit is in order for its functions to work, and the Unit needs to know what a World is in order to interact with it, we have created a **Circular Dependency**. To resolve this, you will need to put the following code at the top of your Unit header (below the include guards):
    ```
    class World; // Forward declaration
    ```

Once you have completed the abstract Unit class, it should now be possible to uncomment the code from the World.h and World.cpp files. You should also take this time to modify the Player.h and Player.cpp files to complete the TODOs listed in each. Make sure your code can still be built and run (use make clean before using make if necessary) after these changes.

You should be able to demonstrate to your TA the successful integration of the abstract Unit class and explain how it serves as a foundation for creating specialized Unit types.
Show and explain your work to the TA, then switch your driver and navigator roles before moving on.

Now that we have an abstract Unit class, we can create our first type of Unit - a Scout. Scouts are very simple Units that move one space a turn (North, South, East, or West), and have a sight of 2. When a Scout takes its action, it should:

 - use the world's displayMapWithSight function
 - Prompt the user with a choice of where to move
 - call the World's moveUnit function

Modify main.cpp to initialize each Player with one Scout, placing them in a random location using the functions provided in World.cpp. In the main game loop, iterate through each Player, and for each Unit in their vector of units, perform that Unit's action. If you have done so correctly, the game should now allow each Player to move their Scout around the World. Demonstrate Scouts moving on the map and interacting with the grid.

# Improving the Map

Once we have a variety of units, our methods of displaying the map will have lost some of their fidelity. We can no longer tell different units apart, and if we were to change each unit to have a unique symbol, we wouldn't be able to determine who owns each unit. To adapt, you will need to modify each map-displaying function to change the original display format into this new style:
```
.. .. .. .. .. .. .. .. .. ..
.. .. .. .. .. .. .. .. .. ..
S3 .. .. .. .. .. .. .. .. S1
.. S1 .. .. .. .. .. .. .. S3
S2 .. .. S3 .. .. B1 .. .. ..
.. .. .. .. .. S2 B2 .. .. ..
.. .. .. .. .. S2 B3 .. .. ..
.. .. S1 .. .. .. .. .. .. ..
.. .. .. .. .. .. .. .. .. ..
~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~ ~~
```

In this format, each unit is identified by a unique letter (S for Scout, B for Boat), and the terrain symbols are duplicated to fill in the necessary space. Change the map displaying functions and make any other changes necessary.
Show and explain your work to the TA to finish the first half of this lab. You must complete this checkpoint during Lab #6 to receive full credit.

For keeping a record of your lab, you should also submit your code here on Canvas. Download your .cpp files and package them into a zip file (your TA can help you do this if you don't know how), then upload it to the assignment page before submitting. Make sure the author names are listed at the top of your main file!
# Part 2: Customization

The remainder of this lab can be completed outside of the lab session, but is due by the end of Lab #7 and must be submitted in person. It is recommended that at a minimum, you use your time between labs to think about what ideas you want to implement, then you can devote Lab #7 to coding and testing.

## New Unit

Now that you have the ability to create different types of units, implement a new type of Unit and give each Player one of them at the start of the game (in addition to their Scout). You are free to decide what the Unit is capable of, however it must interact differently with your new Terrain than the Scout does. For example, if your Terrain was Water, then perhaps a Scout cannot move through Water while your new Unit can. Or perhaps your Player tracks its stores of Wood, and some new WoodCutter Unit can generate Wood when they are standing in a Forest. Be creative and think of how the Unit and Terrain might be thematically connected.
Show and explain your work to the TA.

## Buildings

Most 4X games involve some amount of construction, which allows players to expand their controlled territory and/or to provide some kind of benefit to the player. The simplest form of this is some kind of Settlement or City, which generates units, or upgrades over time to provide continual rewards to the player. Alternatively, you may want to create multiple different buildings where each has a different purpose, such as a Harbor structure that generates a Boat Unit once a turn, or an Fort structure that blocks movement from other players' units.

Create an abstract Building class and at least one subclass that inherits from it. Your inherited building should either generate new units, provide some reward to the player, or give another incentive for players to create that building. Ensure that the player is capable of creating this building on the map, or ensure that the player automatically starts with one.
Show and explain your work to the TA.

## Technology

The ability to research new technologies and upgrades for units is a common feature among 4X games. Often this requires a certain amount of time to elapse, after which the player gains the ability to take new actions, improves the quality of the player's units, or unlocks other stronger technologies. Once researched, a technology usually is a permanent boost to a player for the rest of the game.

Create an abstract Technology class and at least one subclass that inherits from it. Once researched, the technology should empower the player in some way.

Also create a new Unit that is either improved by the technology, unavailable to the player until the technology is researched, or provides the player an enhanced ability to research technologies. Ensure the player can create or has access to these units during the game.
Show and explain your work to the TA.

## Resources

One of the necessary mechanics to limit the number of options available to a player is a resource system. This can come in the form of currency and materials, which are expended when units are created, buildings are constructed, or technologies are researched. For example, if gold is a resource, and placing a goldMine on a mountain space generates 1 gold per turn, then it might cost 2 gold to create a scout. Alternatively, resources can be generated on a turn-by-turn basis, and determine the speed at which major actions are completed. For example, if a player's LumberYard generates 5 wood per turn, then it might take 4 turns to construct a Wagon, whereas owning 2 LumberYards would reduce this to 2 turns.

Implement a resource system that affects Units, Buildings, and Technology. You may not need to create an abstract class for this, if it makes more sense to add additional attributes to the Player class instead.

Create at least one new type of Terrain that provides the player with a way to generate a resource.
Show and explain your work to the TA to finish the final half of this lab. You must show all four checkpoints during Lab #7 receive full credit.

For keeping a record of your lab, you should also submit your code here on Canvas. Download your .cpp files and package them into a zip file (your TA can help you do this if you don't know how), then upload it to the assignment page before submitting. Make sure the author names are listed at the top of your main file!
Bonus Credit - Victory

For a finishing touch and a potential +1 bonus mark, determine a way for a player to win the game. Perhaps they need to acquire a certain number of resources, or claim control over certain Terrain tiles. You may also wish to implement the fourth X in 4X (eXterminate), and allow players to win through conflict by being the last one standing.