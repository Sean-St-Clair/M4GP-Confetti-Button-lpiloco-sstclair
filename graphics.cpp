#include "graphics.h"
#include "Button.h"
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

GLdouble width, height;
int wd;
Button spawn({1, 0, 0}, {100, 100}, 100, 50, "Spawn");
vector<Quad> confetti;
enum screen {start, conf, final};
screen currentScreen = start;
int confettiCount = 98;

void spawnConfetti() {
    confetti.push_back(Quad({rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0},
                            {rand() % (int) width, rand() % (int) height}, 10, 10));
}

void init() {
    width = 500;
    height = 500;
    srand(time(0));
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*
     * Draw here
     */
    switch (currentScreen) {
        case start:
            glColor3f(1, 1, 1);
            glRasterPos2i(50, 150);
            for (const char &letter: "Welcome to Sean St Confetti's Personal") {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }

            glColor3f(1, 1, 1);
            glRasterPos2i(175, 200);
            for (const char &letter: "Confetti Button") {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }

            glColor3f(1, 1, 1);
            glRasterPos2i(165, 275);
            for (const char &letter: "Press the 's' key") {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }
            break;
        case conf:
            spawn.draw();

            for (const Quad &piece: confetti) {
                piece.draw();
            }
            break;
        case final:
            glColor3f(1, 1, 1);
            glRasterPos2i(50, 150);
            for (const char &letter: "Well done spawning 100 pieces of confetti,") {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }

            glColor3f(1, 1, 1);
            glRasterPos2i(175, 200);
            for (const char &letter: "you can leave now.") {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
            }
            break;
    }



    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    } else if (key == 115){
        currentScreen = conf;
    }


    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    // The amount of pixels to be moved
    int moveSpeed = 3;
    int moveX = 0;
    int moveY = 0;
    switch (key) {
        case GLUT_KEY_DOWN:
            moveY += moveSpeed;
            break;
        case GLUT_KEY_LEFT:
            moveX -= moveSpeed;
            break;
        case GLUT_KEY_RIGHT:
            moveX += moveSpeed;
            break;
        case GLUT_KEY_UP:
            moveY -= moveSpeed;
            break;
    }
    // Moves the spawn button TODO: if on the correct scene
    spawn.move(moveX, moveY);
    glutPostRedisplay();
}

void cursor(int x, int y) {
    if (spawn.isOverlapping(x, y)) {
        spawn.hover();
    } else {
        spawn.release();
    }
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    // If the left button is down and the cursor is overlapping with the Button, call the pressDown method. Otherwise, call the release method.
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && spawn.isOverlapping(x, y)) {
        spawn.pressDown();
    } else {
        spawn.release();
    }
    // If the left button is up and the cursor is overlapping with the Button, call spawnConfetti.
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && spawn.isOverlapping(x, y)) {
        spawnConfetti();
        if (confettiCount == 100) {
            currentScreen = final;
        } else {
            ++confettiCount;
        }
    }
    glutPostRedisplay();
}

void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int) width, (int) height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Confetti!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
