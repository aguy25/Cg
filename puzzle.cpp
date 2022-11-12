#include<bits/stdc++.h>
#include <GL/gl.h>
#include <GL/glut.h>


using namespace std;
typedef enum
{
    MODE_BITMAP,
    MODE_STROKE
} mode_type;
struct st{
    double x;
    double y;
    double rgb[3];
    int number;
};
static mode_type mode;
static int font_index1;

int flg = 1, index1=6, action = -1, stopIndex=-1,stat=1;

int grid[3][3] = {{4,3,2},
                 {7,5,8},
                 {0,6,1}};
int totStep = 0;
int arr[10] ={};


double color[9][3] = {{0,0,0},{1,0,1},{1,1,0},{1,0,0},{0,0,1},{0,1,0},{1,1,1},{0,1,1},{0.5,0.3,0.5}};
double primaryPosition[9][2] = {{-60,-60},{20,-60},{20,20},{-20,20},{-60,20},{-20,-20},{-20,-60},{-60,-20},{20,-20}};
double Position[9][2] = {{-60,20},{-20,20},{20,20},{-60,-20},{-20,-20},{20,-20},{-60,-60},{-20,-60},{20,-60}};
double counter = 40;
typedef struct st blok;

blok bloks[9];

int getNum(vector<int>& v)
{
 
    int n = v.size();
    srand(time(NULL));
    int index = rand() % n;
    int num = v[index];
    swap(v[index], v[n - 1]);
    v.pop_back();
    return num;
}
 
void generateRandom(int n)
{
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        v[i] = i;

    int k=0;
    while (v.size()) {
        arr[k]=getNum(v);
        k++;
    }
}

void randomize(){
    generateRandom(9);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            grid[i][j]=arr[i*3+j];
            primaryPosition[grid[i][j]][0]=Position[i*3+j][0];
            primaryPosition[grid[i][j]][1]=Position[i*3+j][1];
        }
    }
}
void reset(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            grid[i][j]=arr[i*3+j];
            primaryPosition[grid[i][j]][0]=Position[i*3+j][0];
            primaryPosition[grid[i][j]][1]=Position[i*3+j][1];
        }
    }
}

void findZero(int *x, int *y){
    int flag = 0, i = 0, j = 0;
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(grid[i][j] == 0){
                flag = 1;
                break;
            }
        }
        if(flag == 1) break;
    }
    *x  = i;
    *y = j;
}

bool check(){
    int cnt = 1;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(i == 2 && j == 2) break;
            if(grid[i][j] != cnt) return false;
            cnt++;
        }
    }
    return true;
}

void print_stroke_string(void* font, char* s)
{
    if (s && strlen(s))
    {
        while (*s)
        {
            glutStrokeCharacter(font, *s);
            s++;
        }
    }
}


void draw_stuff(int index1,double tx,double ty)
{
    char string[8][256];
    unsigned int count;

    void* stroke_fonts[2] =
    {
        GLUT_STROKE_ROMAN,
        GLUT_STROKE_ROMAN
    };


    count = 0;string[0][count] = 49;string[0][++count] = '\0';
    count = 0;string[1][count] = 50;string[1][++count] = '\0';
    count = 0;string[2][count] = 51;string[2][++count] = '\0';
    count = 0;string[3][count] = 52;string[3][++count] = '\0';
    count = 0;string[4][count] = 53;string[4][++count] = '\0';
    count = 0;string[5][count] = 54;string[5][++count] = '\0';
    count = 0;string[6][count] = 55;string[6][++count] = '\0';
    count = 0;string[7][count] = 56;string[7][++count] = '\0';

    glColor3f(0.0, 0.0, 0.0);

    int stroke_scale = 10;
    glPushMatrix();
    {
        glTranslatef(tx,ty,0);
        glScalef(0.2, 0.2, 0.2);
        print_stroke_string(stroke_fonts[font_index1], string[index1]);
    }
    glPopMatrix();

}



void shuffle_array(int arr[], int n)
{
 
    unsigned seed = 0;
 
    shuffle(arr, arr + n,
            default_random_engine(seed));
 
    // Printing our array
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}



void drawGrid(){
    int i;

    glColor3f(1, 1, 1);

    glBegin(GL_LINES);{

        for(int i = -60;i <= 60; i+=40){
            
            glVertex3f(-60, i, 0);
            glVertex3f(60, i, 0);


            glVertex3f(i, -60, 0);
            glVertex3f(i, 60, 0);
        }
    }
    glEnd();
}

void drawSquare(double x,double y,double r,double g,double b){


    glColor3f(r, g, b);
    glBegin(GL_QUADS);{
        glVertex3f(x + 1, y + 1, 0);
        glVertex3f(x + 39, y + 1, 0);
        glVertex3f(x + 39,y + 39 , 0);
        glVertex3f(x + 1, y + 39, 0);
    }
    glEnd();

}



void display()
{


    glClearColor(0, 0, 0, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,100,  0,0,0,  0,1,0);

    glColor3f(0, 1, 0);

    if(check()){
        glColor3f(1, 1, 1);

        int stroke_scale = 1;
        glPushMatrix();
        {
            glTranslatef(-60,65,0);
            glScalef(0.03, 0.03, 0.2);
            string k1= to_string(totStep);
            string k2= "Congrats, You completed the puzzle in \n" + k1 + "\n steps!";
            char k3[128]; 
            strcpy(k3,k2.c_str());
            print_stroke_string(GLUT_STROKE_ROMAN, k3 );
        }
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(-60,45,0);
            glScalef(0.03, 0.03, 0.2);
            string k2= "Press F1 to replay or F2 to exit";
            char k3[128]; 
            strcpy(k3,k2.c_str());
            print_stroke_string(GLUT_STROKE_ROMAN, k3 );
        }
        glPopMatrix();
    }
    else if(stat==1){
        glColor3f(1, 1, 1);

        int stroke_scale = 1;
        glPushMatrix();
        {
            glTranslatef(-70,65,0);
            glScalef(0.03, 0.03, 0.2);
            string k2= "Welcome to 8-Puzzle Game, Press F1 to play or F2 to exit";
            char k3[128]; 
            strcpy(k3,k2.c_str());
            print_stroke_string(GLUT_STROKE_ROMAN, k3 );
        }
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(-70,55,0);
            glScalef(0.03, 0.03, 0.2);
            string k2= "Use arrow keys to move the tiles";
            char k3[128]; 
            strcpy(k3,k2.c_str());
            print_stroke_string(GLUT_STROKE_ROMAN, k3 );
        }
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(-70,45,0);
            glScalef(0.03, 0.03, 0.2);
            string k2= "The aim is to put the numerical pieces at its right place as follows";
            char k3[128]; 
            strcpy(k3,k2.c_str());
            print_stroke_string(GLUT_STROKE_ROMAN, k3 );
        }
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(-20,35,0);
            glScalef(0.03, 0.03, 0.2);
            string k2= "1 2 3";
            char k3[128]; 
            strcpy(k3,k2.c_str());
            print_stroke_string(GLUT_STROKE_ROMAN, k3 );
        }
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(-20,30,0);
            glScalef(0.03, 0.03, 0.2);
            string k2= "4 5 6";
            char k3[128]; 
            strcpy(k3,k2.c_str());
            print_stroke_string(GLUT_STROKE_ROMAN, k3 );
        }
        glPopMatrix();
        glPushMatrix();
        {
            glTranslatef(-20,25,0);
            glScalef(0.03, 0.03, 0.2);
            string k2= "7 8";
            char k3[128]; 
            strcpy(k3,k2.c_str());
            print_stroke_string(GLUT_STROKE_ROMAN, k3 );
        }
        glPopMatrix();
    }
    else{
        drawGrid();
        int temp1 = -60;
        int temp2 = -60;

        for(int i = 1; i < 10; i++){
            if(flg == 1){
                bloks[i - 1].number = grid[(i - 1) / 3][(i - 1) % 3];
                bloks[i - 1].x = primaryPosition[i - 1][0];
                bloks[i - 1].y = primaryPosition[i - 1][1];
            }
            for(int j = 0; j < 3; j++) bloks[i - 1].rgb[j] = color[i - 1][j];
            if(i - 1 != stopIndex){
                double inc = 0.05;

                for(int k = 0; k < 5; k++){

                        if(i == 9) draw_stuff(7, bloks[i - 1].x + 10 + inc, bloks[i - 1].y + 10);
                        else draw_stuff(i - 2, bloks[i - 1].x + 10 + inc, bloks[i - 1].y + 10);
                        inc = inc + 0.05;


                }
                drawSquare(bloks[i - 1].x,bloks[i - 1].y,bloks[i - 1].rgb[0],bloks[i - 1].rgb[1],bloks[i - 1].rgb[2]);
            }
        }
        glColor3f(1, 1, 1);

        int stroke_scale = 1;
        glPushMatrix();
        {
            glTranslatef(-60,-65,0);
            glScalef(0.03, 0.03, 0.2);
            string k2= "Press F1 to replay, F2 to exit or F3 to reset";
            char k3[128]; 
            strcpy(k3,k2.c_str());
            print_stroke_string(GLUT_STROKE_ROMAN, k3 );
        }
        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(-60,65,0);
            glScalef(0.03, 0.03, 0.2);
            string k1= to_string(totStep);
            string k2= "Steps taken: "+ k1;
            char k3[128]; 
            strcpy(k3,k2.c_str());
            print_stroke_string(GLUT_STROKE_ROMAN, k3 );
        }
        glPopMatrix();
        flg = 0;
    }




    glutSwapBuffers();
}

void animate()
{
    if(flg == 0 && action != -1){
        if(action == 1){
            int limit = bloks[index1].y + counter;
            if(limit <= 60 && counter > 0 ){
                int x, y;
                findZero(&x, &y);
                stopIndex = grid[x][y];
                bloks[index1].y += 1;
                counter -= 1;
            }
            if(counter <= 0 ){
                action = -1;
                stopIndex = -1;
                int x, y;
                findZero(&x, &y);
                int t = grid[x][y];
                bloks[t].y -= 40;

            }
        }

        else if(action == 2){
            int limit = bloks[index1].y + counter;
            if(limit >= -60 && counter < 0 ){
                int x, y;
                findZero(&x, &y);
                stopIndex = grid[x][y];
                bloks[index1].y -= 1;
                counter += 1;
            }
            if(counter >= 0 ){
                action = -1;
                stopIndex = -1;
                int x, y;
                findZero(&x, &y);
                int t = grid[x][y];
                bloks[t].y += 40;
            }

        }

        else if(action == 3){
            int limit = bloks[index1].x + counter;
            if(limit <= 60 && counter > 0 ){
                int x, y;
                findZero(&x, &y);
                stopIndex = grid[x][y];
                bloks[index1].x += 1;
                counter -= 1;
            }
            if(counter <= 0 ){
                action = -1;
                stopIndex = -1;
                int x, y;
                findZero(&x, &y);
                int t = grid[x][y];
                bloks[t].x -= 40;
            }
        }

        else if(action == 4){
            int limit = bloks[index1].x + counter;

            if(limit >= -60 && counter < 0 ){
                int x, y;
                findZero(&x, &y);
                stopIndex = grid[x][y];
                bloks[index1].x -= 1;
                counter += 1;

            }
            if(counter >= 0 ){
                action = -1;
                stopIndex = -1;
                int x, y;
                findZero(&x, &y);
                int t = grid[x][y];
                bloks[t].y += 40;
            }
        }
        glutPostRedisplay();

    }
    glutPostRedisplay();

}

void specialKeyListener(int key, int x, int y)
{
    if(key==GLUT_KEY_F1){
        stat=0;
        randomize();
        flg=1;
        totStep=0;
    }
    else if(key==GLUT_KEY_F2){
        exit(0);
    }
    else if(key==GLUT_KEY_F3){
        stat=0;
        flg=1;
        reset();
        totStep=0;
    }
    else if (key == GLUT_KEY_UP && action == -1){
        int x, y;
        findZero(&x, &y);
        if(x < 2){
            swap(grid[x][y], grid[x + 1][y]);
            action = 1;
            counter = 40;
            index1 = grid[x][y];
            totStep++;
        }

    }

    else if (key == GLUT_KEY_DOWN && action == -1){
        int x, y;
        findZero(&x, &y);
        if(x > 0){
            swap(grid[x][y], grid[x - 1][y]);
            action = 2;
            counter = -40;
            index1 = grid[x][y];
            totStep++;
        }

    }
    else if (key == GLUT_KEY_LEFT && action == -1){
        int x, y;
        findZero(&x, &y);
        if(y < 2){
            swap(grid[x][y], grid[x][y + 1]);
            action = 4;
            counter = -40;
            index1 = grid[x][y];
            totStep++;
        }

    }
    else if (key == GLUT_KEY_RIGHT && action == -1){
        int x, y;
        findZero(&x, &y);
        if(y > 0){
            swap(grid[x][y], grid[x][y - 1]);
            action = 3;
            counter = 40;
            index1 = grid[x][y];
            totStep++;
        }

    }

}

void init()
{
    mode = MODE_STROKE;
    font_index1 = 1;

    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();


    gluPerspective(70, 1, 0.1, 10000.0);





}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitWindowSize(1000, 750);
    glutInitWindowPosition(0, 0);


    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow("CSO-351");


    init();

    glEnable(GL_DEPTH_TEST);


    glutDisplayFunc(display);

    glutSpecialFunc(specialKeyListener);

    glutIdleFunc(animate);

    glutMainLoop();



    return 0;
}

