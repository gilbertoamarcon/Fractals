#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Branch.h"

#define WINDOW_TITLE    "Video"
#define WINDOW_W        1280
#define WINDOW_H        720
#define Z_NEAR          0.001
#define Z_FAR           120
#define C_FOVY          60
#define PI              3.14159265359
#define FULL_SCREEN     1
#define PLOT_AXIS       0

using namespace std;

int width           = WINDOW_W;
int height          = WINDOW_H;

double z_near       = Z_NEAR;
double z_far        = Z_FAR;
double c_fovy       = C_FOVY;
double c_aspect     = (double)WINDOW_W/WINDOW_H;

double dist        =   12;
double cam_x        =   0;
double cam_y        =   0;
double cam_z        = dist;

double theta        = 90;
double phi          = 90;

int aux             = 0;
double aux1         = 0;
double aux2         = 0;

double r1           = 0;
double r2           = 0;
double r3           = 0;

double max_angle    = 30;
int depth           = 10;
int num_childs      = 4;

int renderBranch(Branch * branch);

double cosd(double ang);

double sind(double ang);

void mouseMove(int x, int y);

void iniGl();

void updateValues();

void keyPressed(unsigned char key, int x, int y);

void plotAxis();

void RenderScene();

Branch galho;

int main(int argc, char **argv){

    galho.init(max_angle,depth,num_childs,0.5);

    glutInit(&argc, argv);

    iniGl();

    glutMainLoop();

    galho.clean();

    return 1;
}

int renderBranch(Branch* branch){
    glPushMatrix();
        glRotatef(branch->angle1,0,1,0);
        glRotatef(branch->angle2,1,0,0);
        glColor3f(branch->r,branch->g,branch->b);
        glBegin(GL_LINES);
            glVertex3f(0,0,0);
            glVertex3f(0,0,branch->length);
        glEnd();
        if(!(branch->order < 1)){
            for(int i = 0; i < branch->numChilds; i++){
                glPushMatrix();
                    glTranslatef(0,0,branch->length*((branch->child)+i)->spot);
                    renderBranch((branch->child)+i);
                glPopMatrix();
            }
        }
    glPopMatrix();
    return 0;
}

double cosd(double ang){
    return cos(PI*ang/180);
}

double sind(double ang){
    return sin(PI*ang/180);
}

void mouseMove(int x, int y){
    theta   = 360*((double)x/WINDOW_W-0.5);
    phi     = 360*((double)y/WINDOW_H-0.5);
    if (theta < 0)
        theta += 360;
    else if(theta > 360)
        theta -= 360;
    if (phi < 0)
        phi += 360;
    else if(phi > 360)
        phi -= 360;
}

void iniGl(){
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutCreateWindow(WINDOW_TITLE);
    glutKeyboardFunc(&keyPressed);
    glutDisplayFunc(&RenderScene);
    glutPassiveMotionFunc(&mouseMove);
    glutIdleFunc(&RenderScene);
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(c_fovy,c_aspect,z_near,z_far);
    glEnable(GL_DEPTH_TEST);
    if (FULL_SCREEN)
        glutFullScreen();
}

void updateValues(){
    cam_x   = dist*sind(theta)*sind(phi);
    cam_y   = dist*cosd(theta)*sind(phi);
    cam_z   = dist*cosd(phi);
    aux     = 2*(phi>180)-1;
}

void keyPressed(unsigned char key, int x, int y){
    double update = true;
    switch (key){
        case 27:
            exit(0);
            break;
        case 'a':
            max_angle += 1;
            break;
        case 'z':
            max_angle -= 1;
            break;
        case 's':
            depth += 1;
            break;
        case 'x':
            depth -= 1;
            break;
        case 'd':
            num_childs += 1;
            break;
        case 'c':
            num_childs -= 1;
            break;
        case 'f':
            dist *= 1.1;
            update = false;
            break;
        case 'v':
            dist /= 1.1;
            update = false;
            break;
        default:
            break;
    }
    if(depth < 1)
        depth = 1;
    if(num_childs < 1)
        num_childs = 1;
    if(update){
        galho.clean();
        galho.init(max_angle,depth,num_childs,0.5);
    }
}

void plotAxis(){
    glColor3f(1,0.5,0.5);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
    glEnd();
    glColor3f(0.5,1,0.5);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
    glEnd();
    glColor3f(0.5,0.5,1);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(0,0,1);
    glEnd();
}

void RenderScene(){
    updateValues();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(cam_x,cam_y,cam_z,0,0,0, 0,0,aux);
    renderBranch(&galho);
    if (PLOT_AXIS)
        plotAxis();
    glPopMatrix();
    glutSwapBuffers();
}
