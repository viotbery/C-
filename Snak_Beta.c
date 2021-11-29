/*
    #蛇身需要重新定义，考虑到蛇尾的消失，应该使用链表结构。@completed!
    #完善蛇身的控制逻辑                                  @completed!
    #添加在范围内随机生成的食物                          @completed!
    #添加吃到食物后的效果                               @half completed!->吃完食物后，隔一段运行距离才会生成新一段
    #添加失败判定                                       @completed!
        *碰到墙壁游戏失败                               
        *碰到蛇身游戏失败                               
    #将代码函数化                                       @completed!
    #简化代码，优化逻辑，压缩行数
    #美化页面，地图外添加可选项
    #添加玩家id和积分功能                               @completed!
    #添加读取和保存本地分数
*/

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#define WDITH 30
#define HEIGHT 30
#define LEN 4
typedef struct snakeDot     //在使用typedef时要注意如果省略类型说明符可能会导致warning！5axxw.com/questions/content/3ghtuh
{
    COORD dot;              
    struct snakeDot *preDotP;       
    struct snakeDot *nextDotP;   
}   snakeDot, *snakeDotP;

typedef struct              //定义蛇的结构体
{
    snakeDotP header;         //蛇的头节点指针
    int len;                //蛇身长度
    char dir;               //蛇目前运动方向
}   snake, *P_Snake;

int source = 0;                         //全局变量，分数
void gotoxy(int x,int y);               //定义光标定位函数
void drawMap();                         //绘制地图
void initSnake(P_Snake pSnake);         //初始化蛇身
void drawSnake(P_Snake pSnake);         //绘制蛇身
int key(P_Snake pSnake);                //获取按键状态
int moveSnake(P_Snake pSnake, COORD food);              //蛇身移动
void foodCreat(COORD *food);                            //生成食物
int inci(P_Snake pSnake, snakeDotP newHeader, COORD food);      //碰撞事件，返回0表示无事发生，返回-1表示死亡，返回1表示吃到食物
void screen();                          //屏显函数，传入1为欢迎界面，2为死亡界面，3为打印分数

int main()
{   
    snake peter;
    int flag = 1;
    COORD food;
    int init = 0;
    initSnake(&peter);
    drawMap();
    screen(1);
    system("cls");
    drawMap();
    drawSnake(&peter);
    foodCreat(&food);
    screen(3);
    while(flag == 1)
    {   
        int keyRturn = key(&peter);
        if (keyRturn != -1)
        {   
            
            init = moveSnake(&peter, food);
            if ( init == 1)
            {
                foodCreat(&food);
                source++;
                screen(3);
            }
            else if ( init == -1)
            {
                flag = 0;
                
            }
            drawSnake(&peter);
            Sleep(350);
        }
        else 
        {   
            printf("stop!\n");
            break;
        }    
    }
    system("cls");
    drawMap();
    screen(2);
    gotoxy(WDITH / 2, HEIGHT / 2 + 2);
    system("pause");
}

void gotoxy(int x, int y)
{  
    HANDLE handle; //定义句柄变量handle
    COORD coord; //定义结构体coord (坐标系coord)
    coord.X = x; //横坐标x
    coord.Y = y; //纵坐标y
    handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台输出句柄(值为-11)
    SetConsoleCursorPosition(handle, coord); //移动光标
} 

void drawMap()
{
    int x,y;
    system("cls");

    for(x = 1,y=1; x<HEIGHT * 2 + 1 && y<WDITH + 1;x+=2,y++)
    {
        gotoxy(x + 1, 1);
        printf("■");
        gotoxy(2, y);
        printf("■");
        gotoxy(WDITH * 2 + 2, y);
        printf("■");
        gotoxy(x + 1, HEIGHT);
        printf("■");
    }
    Sleep(1000);   
    
}

void initSnake(P_Snake pSnake)
{
    int i;
    snakeDotP headNode;
    headNode = (snakeDotP)malloc(sizeof(snakeDot));//先生成一个实际的头结点，之后生成的节点接在后面
    headNode->dot.X = HEIGHT;
    headNode->dot.Y = WDITH / 2;
    headNode->preDotP = NULL;
    headNode->nextDotP = NULL;
    for (i = 0; i < LEN; i++)
    {
        snakeDotP snakeNode= (snakeDotP)malloc(sizeof(snakeDot));//新生成一个节点
        snakeNode->dot.X = headNode->dot.X + 2;
        snakeNode->dot.Y = headNode->dot.Y;
        snakeNode->preDotP = NULL;
        snakeNode->nextDotP = headNode;
        snakeNode->nextDotP->preDotP = snakeNode;
        headNode = snakeNode;
    }
    pSnake->header = headNode;
    pSnake->dir = 'd';
    pSnake->len = LEN;
}

void drawSnake(P_Snake pSnake)
{   
    int i;
    snakeDotP temp = (snakeDotP)malloc(sizeof(snakeDot));
    temp = pSnake->header;
    gotoxy(temp->dot.X, temp->dot.Y); 
    printf("〇");
    temp = temp->nextDotP;
    for (i = 1; i < pSnake->len; i++)
    {    
        gotoxy(temp->dot.X, temp->dot.Y); 
        printf("■");
        if (i != pSnake->len - 1)
        {
            temp = temp->nextDotP;
        }
        else 
        {
            gotoxy(temp->nextDotP->dot.X, temp->nextDotP->dot.Y);
            printf("  ");
        }
    }
}

int key(P_Snake pSnake)
{   
    int flag = 0;
    char key;
    if (kbhit() != 0)
    {   
        key = getch();
        switch(key)
        {
        case 'd':; case 'D':
        {   
            if (pSnake->dir != 'a')
            {
                pSnake->dir = 'd';
            }
        }break;
        case 'a':; case 'A':
        {
            if (pSnake->dir != 'd')
            {
                pSnake->dir = 'a';
            }
        }break;
        case 'w':; case 'W':
        {
            if (pSnake->dir != 's')
            {
                pSnake->dir = 'w';
            }
        }break;
        case 's':; case 'S':
        {
            if (pSnake->dir != 'w')
            {
                pSnake->dir = 's';
            }
        }break;
        }
        flag = 1;
        if (key == 'x')
        {
            pSnake->dir = 'x';
            flag = -1;
        }
    }
    return flag;
}

int moveSnake(P_Snake pSnake, COORD food)
{   
    int incit;
    snakeDotP newHead;//创建新的节点，代替新的头结点
    P_Snake visualSnake;//创建一条虚拟蛇，用来代替真蛇走之后会发生的事
    newHead = (snakeDotP)malloc(sizeof(snakeDot));
    switch (pSnake->dir)
    {
    case 'a'://向左走，创建新的 头节点X坐标自减2，Y坐标不动，next，pre都不动.len-1，打印的时候不打印
            if (pSnake->dir != 'd')
            {
                newHead->dot.X = pSnake->header->dot.X-2;
                newHead->dot.Y = pSnake->header->dot.Y;
            }break;
    case 'd':
            if (pSnake->dir != 'a')
            {
                newHead->dot.X = pSnake->header->dot.X+2;
                newHead->dot.Y = pSnake->header->dot.Y;
            }break;
    case 'w':
            if (pSnake->dir != 's')
            {
                newHead->dot.X = pSnake->header->dot.X;
                newHead->dot.Y = pSnake->header->dot.Y-1;
            }break;
    case 's':
            if (pSnake->dir != 'w')
            {
                newHead->dot.X = pSnake->header->dot.X;
                newHead->dot.Y = pSnake->header->dot.Y+1;
            }break;
    default:
        break;
    }
    incit = inci(pSnake, newHead, food);
    if (incit != 1)
    {
        pSnake->header->preDotP = newHead;
        newHead->nextDotP = pSnake->header;
        newHead->preDotP = NULL;
        pSnake->header = newHead;
    }
    return incit;
}

void foodCreat(COORD * food)
{
    srand((unsigned int)time(NULL));
    food->X = (rand() % (HEIGHT -2) + 2) * 2;
    food->Y = rand() % (WDITH - 4) + 3;
    gotoxy(food->X, food->Y);
    printf("☆");
}

int inci(P_Snake pSnake, snakeDotP visualHeader, COORD food)
{   
    int incit = 0;
    int i,j;
    snakeDot temp;
    temp = *(pSnake->header->nextDotP);
    if (visualHeader->dot.X == food.X && visualHeader->dot.Y == food.Y)
    {
        incit = 1;
        snakeDotP newHeader = (snakeDotP)malloc(sizeof(snakeDot));
        newHeader->dot.X = food.X;
        newHeader->dot.Y = food.Y;
        newHeader->nextDotP = pSnake->header;
        pSnake->header = newHeader;
        pSnake->len ++;

    }
    else if (visualHeader->dot.X == HEIGHT * 2 || visualHeader->dot.X == 1 || visualHeader->dot.Y == 1 || visualHeader->dot.Y == WDITH)
    {
        incit = -1;
    }
    else 
    {
        for (i = 0; i < pSnake->len; i++)
        {   
            if (temp.dot.X == visualHeader->dot.X && temp.dot.Y == visualHeader->dot.Y)
            {
                incit = -1;
            }
            if (i != pSnake->len - 1)
                temp = *(temp.nextDotP);
        }
    }
    return incit;
}

void screen(int id)
{
    gotoxy(WDITH / 2, HEIGHT / 2);
    if (id == 1)
    {
        printf("欢迎进入贪吃蛇游戏！");
    }
    else if (id == 2)
    {
        printf("游戏结束，你死掉了！");
    }
    gotoxy(WDITH / 2, HEIGHT / 2 + 1);
    if (id == 1)
    {
        printf("版本 beta 1.0");system("pause");
    }
    else if (id == 2)
    {   
        printf("你是个菜狗，贪吃蛇都玩不明白");
    }
    if (id == 3)
    {
        gotoxy(WDITH * 3, HEIGHT / 2);
        printf ("分数：%d", source);
    }
}