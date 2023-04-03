# Confetti Button

Hopefully you have something to celebrate, because the confetti is coming!

For this project, you will use C++ graphics with classes to get a button to react to mouse and keyboard activity.

You may work individually or with a partner of your choosing.

Note to Windows users: remember to copy freeglut.dll from the cmake-build-debug folder of the Graphics-Starter activity to the cmake-build-debug folder here.

Note to Mac users: if you are running Catalina, remember to multiply the width and height by 2 in the glViewport line.

Note to Linux users: remember to use the alternate CMakeLists.txt from the Graphics-Starter activity.

## Setup

Use this Guided Project template to create a new repository (see [GitHub-with-CLion](https://github.com/uvmcs120s2023/GitHub-with-CLion) repo for directions).
**Your repository must be named with the convention: Confetti-Button-netid**, where netid is your UVM NetID username.
* If you are collaborating, the format is Confetti-Button-netid1-netid2. Have one partner create the repository and give the other partner access on GitHub: on the repository page, go to the Settings tab, choose Manage Access, and add the person with their GitHub username.

Remember to commit and push frequently.

# Requirements

1. Read through the header and .cpp files for Quad and Button. 
1. Implement the methods in Quad.cpp and Button.cpp that have TODO comments.
1. Read through graphics.cpp. Notice the global Button object at the top of the file.
1. Implement the TODO parts of graphics.cpp.
1. Run the program. It should have a button labeled "Spawn" that produces confetti.
1. Use an enum to get three screens:
    * A start screen that displays a message. It should not be a button, it should be a string you print. Look at the Button draw method for an example of how to do this. Pressing the ```s``` key should move you to the second screen.
    * The second screen will be the given confetti-spawning program.
    * Once 100 confetti have been spawned, go to an end screen that prints a message of your choice.
1. Make the button move with the arrow keys.

## Grading

If you are collaborating, both partners have to submit the project.

### Grading Rubric
- [ ] (2 pts) Implement draw method in the Quad class.
- [ ] (2 pts) Implement isOverlapping method in the Button class.
- [ ] (7 pts) Implement all TODOs in graphics.cpp.
- [ ] (3 pts) Create the three screens as described above with an enum.
- [ ] (1 pt) Transition between the first and second screens using the ```s``` key.
- [ ] (1 pt) Transition between the second and third screens when 100 confetti are spawned.
- [ ] (4 pts) Move the Button with the arrow keys.
