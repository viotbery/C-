/*
    #������Ҫ���¶��壬���ǵ���β����ʧ��Ӧ��ʹ������ṹ��@completed!
    #��������Ŀ����߼�                                  @completed!
    #����ڷ�Χ��������ɵ�ʳ��                          @completed!
    #��ӳԵ�ʳ����Ч��                               @half completed!->����ʳ��󣬸�һ�����о���Ż�������һ��
    #���ʧ���ж�                                       @completed!
        *����ǽ����Ϸʧ��                               
        *����������Ϸʧ��                               
    #�����뺯����                                       @completed!
    #�򻯴��룬�Ż��߼���ѹ������
    #����ҳ�棬��ͼ����ӿ�ѡ��
    #������id�ͻ��ֹ���                               @completed!
    #��Ӷ�ȡ�ͱ��汾�ط���
*/

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#define WDITH 30
#define HEIGHT 30
#define LEN 4
typedef struct snakeDot     //��ʹ��typedefʱҪע�����ʡ������˵�������ܻᵼ��warning��5axxw.com/questions/content/3ghtuh
{
    COORD dot;              
    struct snakeDot *preDotP;       
    struct snakeDot *nextDotP;   
}   snakeDot, *snakeDotP;

typedef struct              //�����ߵĽṹ��
{
    snakeDotP header;         //�ߵ�ͷ�ڵ�ָ��
    int len;                //������
    char dir;               //��Ŀǰ�˶�����
}   snake, *P_Snake;

int source = 0;                         //ȫ�ֱ���������
void gotoxy(int x,int y);               //�����궨λ����
void drawMap();                         //���Ƶ�ͼ
void initSnake(P_Snake pSnake);         //��ʼ������
void drawSnake(P_Snake pSnake);         //��������
int key(P_Snake pSnake);                //��ȡ����״̬
int moveSnake(P_Snake pSnake, COORD food);              //�����ƶ�
void foodCreat(COORD *food);                            //����ʳ��
int inci(P_Snake pSnake, snakeDotP newHeader, COORD food);      //��ײ�¼�������0��ʾ���·���������-1��ʾ����������1��ʾ�Ե�ʳ��
void screen();                          //���Ժ���������1Ϊ��ӭ���棬2Ϊ�������棬3Ϊ��ӡ����

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
    HANDLE handle; //����������handle
    COORD coord; //����ṹ��coord (����ϵcoord)
    coord.X = x; //������x
    coord.Y = y; //������y
    handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨������(ֵΪ-11)
    SetConsoleCursorPosition(handle, coord); //�ƶ����
} 

void drawMap()
{
    int x,y;
    system("cls");

    for(x = 1,y=1; x<HEIGHT * 2 + 1 && y<WDITH + 1;x+=2,y++)
    {
        gotoxy(x + 1, 1);
        printf("��");
        gotoxy(2, y);
        printf("��");
        gotoxy(WDITH * 2 + 2, y);
        printf("��");
        gotoxy(x + 1, HEIGHT);
        printf("��");
    }
    Sleep(1000);   
    
}

void initSnake(P_Snake pSnake)
{
    int i;
    snakeDotP headNode;
    headNode = (snakeDotP)malloc(sizeof(snakeDot));//������һ��ʵ�ʵ�ͷ��㣬֮�����ɵĽڵ���ں���
    headNode->dot.X = HEIGHT;
    headNode->dot.Y = WDITH / 2;
    headNode->preDotP = NULL;
    headNode->nextDotP = NULL;
    for (i = 0; i < LEN; i++)
    {
        snakeDotP snakeNode= (snakeDotP)malloc(sizeof(snakeDot));//������һ���ڵ�
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
    printf("��");
    temp = temp->nextDotP;
    for (i = 1; i < pSnake->len; i++)
    {    
        gotoxy(temp->dot.X, temp->dot.Y); 
        printf("��");
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
    snakeDotP newHead;//�����µĽڵ㣬�����µ�ͷ���
    P_Snake visualSnake;//����һ�������ߣ���������������֮��ᷢ������
    newHead = (snakeDotP)malloc(sizeof(snakeDot));
    switch (pSnake->dir)
    {
    case 'a'://�����ߣ������µ� ͷ�ڵ�X�����Լ�2��Y���겻����next��pre������.len-1����ӡ��ʱ�򲻴�ӡ
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
    printf("��");
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
        printf("��ӭ����̰������Ϸ��");
    }
    else if (id == 2)
    {
        printf("��Ϸ�������������ˣ�");
    }
    gotoxy(WDITH / 2, HEIGHT / 2 + 1);
    if (id == 1)
    {
        printf("�汾 beta 1.0");system("pause");
    }
    else if (id == 2)
    {   
        printf("���Ǹ��˹���̰���߶��治����");
    }
    if (id == 3)
    {
        gotoxy(WDITH * 3, HEIGHT / 2);
        printf ("������%d", source);
    }
}