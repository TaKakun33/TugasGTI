#include <GLUT/glut.h>
#include <math.h>

// this is for positioning
float rotasiBumi = 0.0f;
float rotasiBulan = 0.0f; 
float evolusiBulan = 0.0f;

void drawRotatingPlanet(float radius, float rotationAngle, float r, float g, float b) {
    
    // drawing the planets
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    // the i is the number of segments. the higher it is, the smoother it'll be
    for (int i = 0; i <= 100; i++) {
        float theta = 2.0f * M_PI * i / 100.0f;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();

    // drawing the line on the circles / balls
    // offset is for the amount of lines that appears
    for (int offset = 0; offset < 360; offset += 30) {
        float currentAngle = rotationAngle + offset;
        float rad = currentAngle * M_PI / 180.0f;
        float widthFactor = sin(rad);  // how big each ellipse / line is when rotating
        float positionFactor = cos(rad); // wether the line is in front of or behind the planet

        if (positionFactor > 0) {
            // front lines
            glColor3f(0.0f, 0.0f, 0.0f); // colour of the lines
            glLineWidth(1.2f);           // thickness
        } else {
            // rear lines
            glColor3f(r * 0.8f, g * 0.8f, b * 0.8f); // colour of the line
            glLineWidth(0.5f);                       // thickness
        }

        glBegin(GL_LINE_STRIP);
        // smoothness of the line. lower means smoother curve
        for (float i = -M_PI/2; i <= M_PI/2; i += 0.1) {
            float x = (radius * widthFactor) * cos(i);
            float y = radius * sin(i);
            glVertex2f(x, y);
        }
        glEnd();
    }

    // equator
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for (float i = 0; i <= 2.0 * M_PI; i += 0.1) {
        // change the 0.15f to adjust the tilt / perspective of the equator
        glVertex2f(radius * cos(i), (radius * 0.15f) * sin(i)); 
    }
    glEnd();
    
    // the outline of the planet
    glBegin(GL_LINE_LOOP);
    // the i here also makes the outline smoother
    for (int i = 0; i <= 100; i++) {
        float theta = 2.0f * M_PI * i / 100.0f;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // the path for the moon to orbit
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINE_LOOP);
    // the 0.7 here is the radius of the orbit. change this to make it wider/narrower
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * M_PI * i / 100.0f;
        glVertex2f(0.7 * cos(theta), 0.7 * sin(theta));
    }
    glEnd();

    // earth
    glPushMatrix();
        // first parameter is for the planet size, second is for the rotation speed
        drawRotatingPlanet(0.22, rotasiBumi, 0.2, 0.5, 1.0);
    glPopMatrix();

    // moon
    glPushMatrix();
        // the 0.7 here must match the orbit path radius above
        float moonX = 0.7 * cos(evolusiBulan * M_PI / 180.0);
        float moonY = 0.7 * sin(evolusiBulan * M_PI / 180.0);
        glTranslatef(moonX, moonY, 0);
        
        // draw the moon with its own size and spin speed
        drawRotatingPlanet(0.07, rotasiBulan, 0.6, 0.6, 0.6);
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int value) {
    // speed settings
    
    rotasiBumi += 2.0f;   // earth spin speed on its own axis
    rotasiBulan += 1.0f;  // moon spin speed on its own axis
    evolusiBulan += 0.3f; // how fast the moon orbits the earth
    
    // reset the angle if it hits 360
    if (rotasiBumi > 360) rotasiBumi -= 360;
    if (rotasiBulan > 360) rotasiBulan -= 360;
    if (evolusiBulan > 360) evolusiBulan -= 360;

    glutPostRedisplay();
    
    // the 16 is for the frame rate. higher means slower animation overall
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Moon Earth Rotation");
    
    // background colour (1.0 is white)
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}