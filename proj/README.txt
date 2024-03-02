to run program:
-open MSYS terminal
-open cross compiler
-navigate to directory
- "make"
- "make install TTYDEV=/dev/ttyS4" (replace S4 with the port of your laptop)


Contents:

functions:
moveup: to move the ship up

movedown: to move down

crash: to check for a crash. 1 if there is a crash, 0 if not

rocketsspawn: spawns rockets randomly

rocketsmove: moves rockets to the left. 

hasWon: detects when the player has won (score = 15)


Display elements:
Battlefield: covers the whole display.
consists of 512 (128 * 4) elements, each 8 bits.


Reset: initial condition of Battlefield.

spaceship: 16 element. 16 represents how long it is horizantally.

rockets: 16 elements. represents obstacles to avoid

erase: 16 elements. all 255 to turn off respective pixels.




