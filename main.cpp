#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;
enum direction{top=1,down,rigt,lft};
struct map1
{
    int width;
    int height;
    int fruitx;
    int fruity;
};

struct snake
{
    int headx;
    int heady;
    int tail;
    int tail_x[100];
    int tail_y[100];
    direction dir;
};
struct player
{
    int score;
    bool lose;
};
map1 map2;snake snake1;player player1;
void shift_the_snake(int arr[],int sz)
{
    for(int i=sz-2;i>=0;i--)
    {
        arr[i+1]=arr[i];
    }
}
void generate_fruit()
{
    srand(time(NULL));
    map2.fruitx=rand()%(map2.width-2)+1;
    map2.fruity=rand()%(map2.height-2)+1;
}
void setup()
{
    map2.width=40;
    map2.height=20;
    generate_fruit();
    snake1.headx=map2.width/2;
    snake1.heady=map2.height/2;
    snake1.tail=0;
    player1.score=0;
    player1.lose=false;
}
void draw()
{
    system("cls");
    for(int i=0;i<map2.height;i++)
    {
        for(int j=0;j<map2.width;j++)
        {
            if(i==0||i==map2.height-1)
                cout<<'*';
            else if(j==0||j==map2.width-1)
                cout<<'*';
            else if(i==snake1.heady&&j==snake1.headx)
                cout<<'O';
            else if(i==map2.fruity&&j==map2.fruitx)
                cout<<'$';
            else
                {
                    bool printed=false;
                    for(int k=0;k<snake1.tail;k++)
                    {
                        if(snake1.tail_x[k]==j&&snake1.tail_y[k]==i)
                        {
                            cout<<'O';
                            printed=true;
                            break;
                        }
                    }
                    if(!printed)
                        cout<<' ';
                }
        }
        cout<<endl;
    }
    cout<<"Player Score : "<<player1.score<<endl;

}
void input()
{
    if(_kbhit())
    {
        char c=_getch();
        switch(c)
        {
            case 'w':snake1.dir=top;
            break;
            case 's':snake1.dir=down;
            break;
            case 'd':snake1.dir=rigt;
            break;
            case 'a':snake1.dir=lft;
            break;
            case 'x':exit(0);
        }
    }
}
void _move()
{
    shift_the_snake(snake1.tail_x,100);
    shift_the_snake(snake1.tail_y,100);
    snake1.tail_x[0]=snake1.headx;
    snake1.tail_y[0]=snake1.heady;
    switch(snake1.dir)
    {
        case top:snake1.heady--;
        break;
        case down:snake1.heady++;
        break;
        case lft:snake1.headx--;
        break;
        case rigt:snake1.headx++;
        break;
    }
    if(snake1.heady>=map2.height||snake1.heady<=0||snake1.headx>=map2.width||snake1.headx<=0)
        player1.lose=true;
    if(snake1.headx==map2.fruitx&&snake1.heady==map2.fruity)
    {
        generate_fruit();
        player1.score++;
        snake1.tail++;
    }
}
int main()
{
    setup();
    while(!player1.lose)
    {
        draw();
        input();
        _move();
        Sleep(1);
    }
    system("pause");
    return 0;
}
