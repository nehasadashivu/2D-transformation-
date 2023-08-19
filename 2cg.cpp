#include <GL/glut.h>
#include <iostream>
#include<cmath>

// Global variables
int windowWidth = 800;
int windowHeight = 600;
float shapePosX = 0.0f;
float shapePosY = 0.0f;
float shapeAngle = 0.0f;
float shapeScaleX = 1.0f;
float shapeScaleY = 1.0f;
int selectedShape = -1; // -1: No shape selected, 0: Circle, 1: Rectangle, 2: Triangle

// Function to draw a circle
void drawCircle() {
    glPushMatrix();
    glTranslatef(shapePosX, shapePosY, 0.0f);
    glRotatef(shapeAngle, 0.0f, 0.0f, 1.0f);
    glScalef(shapeScaleX, shapeScaleY, 1.0f);
    
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Center vertex
    int numSegments = 100;
    float angle;
    for (int i = 0; i <= numSegments; i++) {
        angle = i * 2.0f * 3.14159f / numSegments;
        glVertex2f(cos(angle) * 0.2f, sin(angle) * 0.2f);
    }
    glEnd();
    
    glPopMatrix();
}

// Function to draw a rectangle
void drawRectangle() {
    glPushMatrix();
    glTranslatef(shapePosX, shapePosY, 0.0f);
    glRotatef(shapeAngle, 0.0f, 0.0f, 1.0f);
    glScalef(shapeScaleX, shapeScaleY, 1.0f);
    
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glBegin(GL_QUADS);
    glVertex2f(-0.2f, -0.2f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glEnd();
    
    glPopMatrix();
}

// Function to draw a triangle
void drawTriangle() {
    glPushMatrix();
    glTranslatef(shapePosX, shapePosY, 0.0f);
    glRotatef(shapeAngle, 0.0f, 0.0f, 1.0f);
    glScalef(shapeScaleX, shapeScaleY, 1.0f);
    
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(-0.2f, -0.2f);
    glVertex2f(0.2f, -0.2f);
    glEnd();
    
    glPopMatrix();
}

// Function to display the shapes
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    if (selectedShape == 0) {
        drawCircle();
    } else if (selectedShape == 1) {
        drawRectangle();
    } else if (selectedShape == 2) {
        drawTriangle();
    }
    
    glFlush();
}

// Function to handle menu selection
void shapeMenu(int shape) {
    selectedShape = shape;
    glutPostRedisplay();
}

// Function to handle mouse input
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        int shapeSubMenu = glutCreateMenu(shapeMenu);
        glutAddMenuEntry("Circle", 0);
        glutAddMenuEntry("Rectangle", 1);
        glutAddMenuEntry("Triangle", 2);
        
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 't':
           shapePosX  += 0.1f;  // Translate right
            break;
        case 'T':
            shapePosX -= 0.1f;  // Translate left
            break;
        case 'u':
           shapePosY += 0.1f;  // Translate up
            break;
        case 'U':
           shapePosY  -= 0.1f;  // Translate down
            break;
        case 'r':
            shapeAngle += 10.0f;  // Rotate clockwise
            break;
        case 'R':
            shapeAngle -= 10.0f;  // Rotate anticlockwise
            break;
        case 's':
             shapeScaleX  += 0.1f;  // Scale up
           shapeScaleY  += 0.1f;
            break;
        case 'S':
             shapeScaleX  -= 0.1f;  // Scale down
            shapeScaleY  -= 0.1f;
            break;
        case 27: // Escape key
            exit(0);
    }
    glutPostRedisplay();
    }
    
// Function to handle window resizing
void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("2D Shape Transformations");
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // White background
    
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    
    return 0;
}
