// trial 1, mau ku ganti bbrp hal

// diganti kalau buat Windows ini
// nanti jadi Gl/glut.h
#include <GLUT/glut.h>
#include <math.h>

// some stuff
float rotasiBumi = 0.0f;

float rotasiBulan = 0.0f;

float evolusiBulan = 0.0f;

// to make the cicle
void drawCircle(float x_axis, float y_axis, float radius, int segments, float r, float g, float b) {
    glColor3f(r, g, b); 
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x_axis, y_axis); // centre 

    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * M_PI * (float)i / (float)segments;

        float x = radius * cos(theta);
        
        float y = radius * sin(theta);

        glVertex2f(x + x_axis, y + y_axis);
    }

    glEnd();
    
    // Rotation indicator line
    // glColor3f(0, 0, 0);
    // glBegin(GL_LINES);
    // glVertex2f(x_axis, y_axis);
    glVertex2f(x_axis + radius * cos(0), y_axis + radius * sin(0)); // Visualizes the spin
    glEnd();
}

void timer(int value) {
    // keep on updating the angles
    rotasiBumi += 1.0f;

    rotasiBulan += 2.0f;

    evolusiBulan += 0.5f;

    // 0 - 360 degre
    if (rotasiBumi > 360){
        rotasiBumi -= 360;
    }
    else if (rotasiBulan > 360){
        rotasiBulan -= 360;
    }
    else if (evolusiBulan > 360){
        evolusiBulan -= 360;
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); 
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // draw earth at 0, 0
    glPushMatrix();
    glRotatef(rotasiBumi, 0, 0, 1);
    drawCircle(0, 0, 0.2, 100, 0.2, 0.5, 1.0); // colour is blue obv
    glPopMatrix();

    // the moon
    glPushMatrix();
    float moonX = 0.6 * cos(evolusiBulan * M_PI / 180.0);
    float moonY = 0.6 * sin(evolusiBulan * M_PI / 180.0);
        
    // rotation
    glPushMatrix();
    glTranslatef(moonX, moonY, 0); 
    glRotatef(rotasiBulan, 0, 0, 1); 
    drawCircle(0, 0, 0.06, 50, 0.7, 0.7, 0.7); 
    glPopMatrix();
    
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Puter puter");

    glClearColor(1.0, 1.0, 1.0, 1.0); 
    
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();
    return 0;
}