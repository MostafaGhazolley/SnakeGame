#include <iostream> //cout, cin , endl functions
#include <conio.h> //Keybored inputs functions
#include <windows.h> // sleep function
#include "Game_Objects.h" //header files

/***************
-problems need to fix :
1-fruit spawn inside snake...

***************/

using std::cout;
using std::cin;
using std::endl;

bool gameOver; //Game termination variable to continue or not!
bool wallHack = false;
const unsigned int width=20; //map dimension 2D
const unsigned int height=20; //map dimension 2D
unsigned int x,y,fruitX,fruitY,Score;
unsigned tailmaxX[100], tailmaxY[100];
unsigned nTail;
enum eDirection {STOP =0, LEFT, RIGHT, UP, DOWN, OFF};// HACK
eDirection dir;
unsigned int KEYPRESSED=0;
//static unsigned BiggestScore = 0;


void Setup(void)
{
    gameOver = false;
    dir=STOP;
    x = width / 2;
    y = height / 2;
    /******Randomly adding fruit on map********/
    fruitX = rand() % width;
    fruitY = rand() % height;
    Score = 0; // init Score
}

void Draw()
{
    Sleep(99);
    system("cls"); // System ("clear"); on linux
    for(int i=0;i<width+2;i++)
    {
        cout << "#" ; // edges
    }
    cout << endl;

    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            if(j==0)
            {
                printf("#");    //drawing upper wall
            }
            if (i == fruitY && j == fruitX)
            {
                cout << "F";    //frawing fruits 
            }
            else if(i==y && j==x) //Starting condition
            {
                cout<< "O"; //Starting point
            }
            else
            {
                /******TAILing*******/
                bool print = false;
                for (unsigned k = 0; k < nTail; k++)
                { 
                    if (tailmaxX[k] == j && tailmaxY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    printf(" ");
                }
                
            }
            /****Bottom Edge****/
            if(j==(width-1))
            {
                printf("#");    //wall
            }


        }
        cout << endl;
    }
    for(int i=0;i<width+2;i++)
    {
        cout << "#" ; // edges
    }
    cout << endl;
    cout << "your Score    = " << Score << endl;
    if(wallHack==true)
    {
        cout << "HACK ON!!!!!!!!!" << endl;
    }

    //cout << "HIGHEST SCORE = " << BiggestScore << endl;
}

void Input()
{/*******MOVEMENTS*******/
    //KEYPRESSED=_kbhit();
    if(_kbhit()) //conio.h function for keybored presses key
    {
        //KEYPRESSED=_getch();
        switch(_getch())
        {
        case 'a':
            if (dir != RIGHT)
            dir= LEFT;
            break;
        case 'd':
            if (dir != LEFT)
            dir= RIGHT;
            break;
        case 's':
            if (dir != UP)
            dir= DOWN;
            break;
        case 'w':
            if (dir != DOWN)
            dir= UP;
            break;
        case'x':
            dir = OFF;
            break;
        //case'r':
          //  dir = HACK;
            //break;
        default:
            break;
        }
        
        //KEYPRESSED=0;
    }
}

void Logic()
{
    /*****Adding Tail logic*****/
    unsigned prevX = tailmaxX[0];
    unsigned prevY = tailmaxY[0];
    unsigned prev2X, prev2Y;
    tailmaxX[0] = x;
    tailmaxY[0] = y;
    for (unsigned i = 1; i <= nTail; i++)
    {
        prev2X = tailmaxX[i];
        prev2Y = tailmaxY[i];
        tailmaxX[i] = prevX;
        tailmaxY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    /*******Directions logic******/
    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case OFF:
        gameOver = true;
        break;
    //case HACK: //hacking wall
      //  if (wallHack == true)
        //    wallHack = false;
        //else wallHack = true;
        break;
    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0)
    {
        gameOver = true;
    }
    else
    {
        //Nothing..
    }
    /*if (wallHack== false && (x > width || x < 0 || y > height || y < 0))
    {
        gameOver = true;
    }
    else if (wallHack==true)
    {
        if(x>=width)
        {
            x = 0;
        }
        else if(x<0)
        {
            x = width - 1;
        }
        else
        {
            //nothing
        }

        if (y >= height)
        {
            y = 0;
        }
        else if (x < 0)
        {
            y = height - 1;
        }
        else
        {
            //nothing
        }
    }
    else
    {
        //nothing
    }
    */
    /*****hitting ourselves effect!****/
    for (unsigned i = 0; i < nTail; i++)
    {
        if (tailmaxX[i] == x && tailmaxY[i] == y)
        {
            gameOver = true;
        }
    }
    /*******Eating fruit effect!*********/
    if (x == fruitX && y == fruitY)
    {
        Score += 10;
        /***Set highest Score**/
        //if (Score > BiggestScore)
        //{
        //    BiggestScore = Score;
        //}
        //else
        //{
            //Nothing...
        //}

        fruitX = rand() % width;
        fruitY = rand() % height;
           for (unsigned i = 1; i <= nTail; i++)
            {//check if fruit respawned inside snake tail
               for (unsigned j = 1; j <= nTail; j++)
               {
                    if (tailmaxX[i] == x && tailmaxY[i] == y)
                    {//if so... change the fruit place
                      fruitX = rand() % width;
                      fruitY = rand() % height;
                    }
                    else
                    {
                        //nothing...
                    }
               }
            }
        nTail++;
    }
}
