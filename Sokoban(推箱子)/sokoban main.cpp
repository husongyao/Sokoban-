#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
void  menu();                               //游戏菜单
int  move(int key, struct game *gamedata);  //推箱子移动逻辑
void  new_map(int i, struct game *gamedata);  //新建地图 
void  game_loop(struct game *gamedata);      //游戏主循环
void  show_map(struct game *gamedata,int step);  //显示游戏画面
int   do_win(struct game *gamedata);            //判断输赢
int  save_game(struct game *gamedata);          //保存游戏
int  load_game(struct game *gamedata);          //读取游戏
 
/* 
  游戏主要结构体
  Q  是墙壁
  M  是自己的小人
  B  是可以推的箱子
  E  是要把箱子推到的目的地
  1 是游戏关卡数 
  2 不可动地图部件   墙壁   目的地
  3 可动物件       自己的小人  可以推的箱子

*/
struct game     
{
    int level;
    char stop_map[16][16];
    char game_map[16][16];
};

int main()
{
    SetConsoleTitle("SoKoBan 推箱子");   //更改进程名
 /*   测试按键
    char  key_A, key;
    while (1)
    {
        key_A = _getch();
        key = _getch();// 72 =↑   80 ↓   75 ←  77→
        printf("%d,%d\r\n", key_A, key);
    }
     */
    
    /*
    先:
        移动 √
        游戏逻辑  √
        判断输赢  √
         
    后:
        判断通关     √
        选择关卡     √
        保存游戏     √
        读取游戏     √
        游戏菜单     √
        显示步数     √
        显示第几关   √
        重试         √
        回到菜单     √

        改成堆模式存放
    */
 
     //初始关卡  
    int now_level = 1;
 
    menu();   //进入菜单  如果开始游戏 就继续执行后续

    game now_map;     //声明结构体 now_map

    new_map(now_level, &now_map);    //给now map新建地图

    game_loop(&now_map);     //进入游戏循环
     

     
    system("pause");
    return EXIT_FAILURE;
}
 
 
  

void show_map(game *data,int step)
{
     printf("   推箱子  第%d关  当前移动步数%d \r\n", (*data).level,step);

    for (int i = 0; i < 16; i++)
    {
        for (int k = 0; k < 16; k++)
        {
            if ((*data).game_map[i][k] == 'B' || (*data).game_map[i][k] == 'M')
            {
                switch ((*data).game_map[i][k])
                {
                case 'M':
                    printf("☆");
                    break;
                case 'B':
                    if ((*data).game_map[i][k] == 'B' && (*data).stop_map[i][k] == 'E')
                    {
                        printf("●");
                    }
                    else
                    {
                        printf("○");
                    }
                    break;
                default:
                    break;
                }
            }
            else
            {
                switch ((*data).stop_map[i][k])
                {
                case 'N':
                    printf("  ");
                    break;
                case 'Q':
                    printf("■");
                    break;
                case 'E':
                    printf("◎");
                    break;
                default:
                    break;
                }
                
            }
        }
        printf("\r\n");
    }
    printf("移动   ↑       M\r\n ");
    printf("    ←↓→  回到菜单\r\n\r\n");
    printf("ctrl+s 保存当前游戏\r\n\r\nEsc退出    R重试\r\n ");
}



void game_loop(game *data)
{
    system("cls");                      //清屏 清理菜单显示
    int winlevle = (*data).level;       //目前关卡设置为结构体载入的地图的关卡
    int iwin = 0;                       //判断输赢
    char key = 0;                       //判断键盘输入
    char key_A = 0;                     //判断键盘输入
    int moveNumber = 0;                 //移动的步数
    show_map(data, moveNumber);         //先显示游戏画面
    while (1)
    {
        
        key_A = _getch();  
        key = _getch();// 72 =↑   80 ↓   75 ←  77→

        if (key == 72)// printf("↑");
        {
            moveNumber += move(key, data);
            system("cls");
            show_map(data, moveNumber);
            iwin=do_win(data);
        }
        if (key == 80)// printf("↓");
        {
            moveNumber += move(key, data);
            system("cls");
            show_map(data, moveNumber);
            iwin=do_win(data);
        }
        if (key == 75)// printf("←");
        {
            moveNumber += move(key, data);
            system("cls");
            show_map(data, moveNumber);
            iwin=do_win(data);
        }
        if (key == 77) // printf("→");
        {
            moveNumber += move(key, data);
            system("cls");
            show_map(data, moveNumber);
            iwin=do_win(data);
        }
        if (key_A == 19)   // Ctrl+s //保存当前游戏
        {
            int saveNumber = 0;
            saveNumber=save_game(data);
            if (saveNumber == 0)
            {
                printf("保存成功\r\n");
            }
            else
            {
                printf("保存失败\r\n");
            }
            
            
        }
        if (key_A == 82)   // R重试
        {
 
            new_map((*data).level, data);
            moveNumber = 0;
            system("cls");
            show_map(data, moveNumber);
            winlevle = (*data).level;
           
        }
        if (key_A == 114)   // r重试
        {
            new_map((*data).level, data);
            moveNumber = 0;
            system("cls");
            show_map(data, moveNumber);
            winlevle = (*data).level;
            
        }
        if (key_A == 27)   //Esc退出游戏
        {
            printf("退出成功\r\n");
            system("pause");
            exit(EXIT_SUCCESS);
        }
        if (key_A == 109)   // M回到菜单
        {
            main();
        }
        if (iwin == 1)
        {
            if ((*data).level == 10)
            {
                printf("你已通关 太牛啤了,\r\n");
                printf("按任意键重回第一关\r\n");
                system("pause");
                moveNumber = 0;
                new_map(1, data);
                system("cls");
                show_map(data, moveNumber);
                winlevle = (*data).level;
            }
            printf("恭喜过关\r\n");
            system("pause");
            moveNumber = 0;
            new_map(winlevle + 1,data);
            system("cls");
            show_map(data, moveNumber);
            winlevle = (*data).level;
             
        }

         
    }
    
}

int move(int key, struct game *games)
{
    int x = 0;
    int y = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int k = 0; k < 16; k++)
        {
            if ((*games).game_map[i][k] == 'M')
            {
                switch (key)
                {
                case 72: //printf("↑");
                    if ((*games).stop_map[i - 1][k] != 'Q')
                    {
                        if ((*games).game_map[i - 1][k] == 'B')
                        {
                            if ((*games).stop_map[i -2 ][k] == 'Q' || (*games).game_map[i - 2][k] == 'B')
                            {
                                return 0;
                            }
                            else
                            {
                                (*games).game_map[i - 2][k] = 'B';
                            }
                        }

                        (*games).game_map[i - 1][k] = 'M';
                        (*games).game_map[i][k] = 'N';
                        return 1;
                    }
                    break;
                case 80: //printf("↓ ");
                    if ((*games).stop_map[i + 1][k] != 'Q')
                    {
                        if ((*games).game_map[i + 1][k] == 'B')
                        {
                            if ((*games).stop_map[i + 2][k] == 'Q' || (*games).game_map[i + 2][k] == 'B')
                            {
                                return 0;
                            }
                            else
                            {
                                (*games).game_map[i + 2][k] = 'B';
                            }
                        }
                        (*games).game_map[i + 1][k] = 'M';
                        (*games).game_map[i][k] = 'N';
                        return 1;
                    }
                    break;
                case 75: //printf("← ");
                    if ((*games).stop_map[i ][k-1] != 'Q')
                    {
                        if ((*games).game_map[i][k-1] == 'B')
                        {
                            if ((*games).stop_map[i][k-2] == 'Q' || (*games).game_map[i][k-2] == 'B')
                            {
                                return 0;
                            }
                            else
                            {
                                (*games).game_map[i][k-2] = 'B';
                            }
                        }
                        (*games).game_map[i][k-1] = 'M';
                        (*games).game_map[i][k] = 'N';
                        return 1;
                    }
                    break;
                case 77: //printf(" →");
                    if ((*games).stop_map[i][k+1] != 'Q')
                    {
                        if ((*games).game_map[i][k+1] == 'B')
                        {
                            if ((*games).stop_map[i][k+2] == 'Q' || (*games).game_map[i][k+2] == 'B')
                            {
                                return 0;
                            }
                            else
                            {
                                (*games).game_map[i][k+2] = 'B';
                            }
                        }
                        (*games).game_map[i][k+1] = 'M';
                        (*games).game_map[i][k] = 'N';
                        return 1;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
    return 0;
}

int  do_win(struct game *data)
{
    int temp = 0;

    for (int i = 0; i < 16; i++)
    {
        for (int k = 0; k < 16; k++)
        {
            if ((*data).game_map[i][k] == 'B' && (*data).stop_map[i][k] != 'E')
            {
                return 0;
            }
        }
    }
    return 1;
}

void  menu( )
{
    int now_level = 1;  //初始关卡
    int buffer = 0;      //菜单选取数字
    int loadTemp = 0;   //判断读取是否成功
    while (1)
    {
        system("cls");
        printf("   推箱子 SOKOBAN \r\n\r\n");
        printf("     1,开始游戏 \r\n");
        printf("     2,选择关卡 \r\n");
        printf("     3,载入游戏 \r\n");
        printf("     4,退出游戏\r\n \r\n");
        scanf_s("%d", &buffer);
        getchar();
        
        switch (buffer)
        {
        case 1:
            return ;
            break;
        case 2:
            printf("输入你要选择的关卡\r\n");
            printf("目前只有1-10关\r\n");
            scanf_s("%d",&now_level);
            getchar();
            if (now_level >= 1 && now_level <= 10)
            {
                game now_map;     //声明结构体 now_map

                new_map(now_level, &now_map);    //给now map初始化地图

                game_loop(&now_map);     //进入游戏循环
                break;
            }
            else
            {
                printf("选择关卡错误\r\n");
                system("pause");
                break;
            }
        case 3:
            game now_map;     //声明结构体 now_map
           
            loadTemp=load_game(&now_map);
            if (loadTemp == 0)
            {
                game_loop(&now_map);     //进入游戏循环
            }
            else
            {
                printf("没找到游戏存档\r\n");
                system("pause");
            }
            break;
        case 4:
            exit(EXIT_SUCCESS);
            break;
        default:
            printf("选择错误\r\n");
            system("pause");
            break;
        }
    }
}

int  save_game(struct game *gamedata)
{
    FILE *fSKB = NULL;

    fopen_s(&fSKB,"SoKoBan.sav", "w");
    if (fSKB != NULL)
    {
        fwrite((game*)gamedata, 1, sizeof(game), fSKB);
        fclose(fSKB);
        return 0;
    }
    fclose(fSKB);

    return -1;
}


int  load_game(struct game *gamedata)
{
    FILE *fSKB = NULL;

    fopen_s(&fSKB, "SoKoBan.sav", "r");
    if (fSKB != NULL)
    {
        fread((game*)gamedata, 1, sizeof(game), fSKB);
        fclose(fSKB);
        return 0;
    }
     

    return 1;
}
void new_map(int i, game *map)
{
    if (i == 1)
    {
        game map_1 =
        { 1,
        {
         'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','N','Q','N','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','E','Q','N','N','N','N','N','N','N','N','N',
        'N','Q','N','E','N','N','Q','N','N','N','N','N','N','N','N','N',
        'N','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','M','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        },
        {
      'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','M','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','B','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','B','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        } };
        *map = map_1;
    }

    if (i == 2)
    {
        game map_1 =
        { 2,{
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','Q','N','N','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','Q','N','Q','Q','Q','N','N','N','N','N','N',
        'N','Q','N','N','N','Q','N','Q','E','Q','N','N','N','N','N','N',
        'N','Q','Q','Q','N','Q','Q','Q','E','Q','N','N','N','N','N','N',
        'N','N','Q','Q','N','N','N','N','E','Q','N','N','N','N','N','N',
        'N','N','Q','N','N','N','Q','N','N','Q','N','N','N','N','N','N',
        'N','N','Q','N','N','N','Q','Q','Q','Q','N','N','N','N','N','N',
        'N','N','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        },
        {
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','M','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','B','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        }};
        *map = map_1;
    }
    if (i == 3)
    {
        game map_1 =
        { 3,{
        'N','Q','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','N','N','Q','Q','Q','N','N','N','N','N','N',
        'Q','Q','N','Q','Q','Q','N','N','N','Q','N','N','N','N','N','N',
        'Q','N','N','N','N','N','N','N','N','Q','N','N','N','N','N','N',
        'Q','N','E','E','Q','N','N','N','Q','Q','N','N','N','N','N','N',
        'Q','Q','E','E','Q','N','N','N','Q','N','N','N','N','N','N','N',
        'N','Q','Q','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        },
        {
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','B','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','M','N','B','N','N','B','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','B','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        } }; *map = map_1;
    }
    if (i == 4)
    {
        game map_1 =
        { 4,{
        'N','N','N','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N',
        'N','Q','Q','Q','N','N','N','N','Q','N','N','N','N','N','N','N',
        'Q','Q','E','N','N','Q','Q','N','Q','Q','N','N','N','N','N','N',
        'Q','E','E','N','N','N','N','N','N','Q','N','N','N','N','N','N',
        'Q','E','E','N','N','N','N','N','Q','Q','N','N','N','N','N','N',
        'Q','Q','Q','Q','Q','Q','N','N','Q','N','N','N','N','N','N','N',
        'N','N','N','N','N','Q','Q','Q','Q','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        },
        {
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','B','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','N','B','N','N','M','N','N','N','N','N','N','N',
        'N','N','N','N','B','N','B','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        }}; *map = map_1;
    }
    if (i == 5)
    {
        game map_1 =
        { 5,{
        'N','N','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N',
        'N','N','Q','N','N','N','N','Q','N','N','N','N','N','N','N','N',
        'Q','Q','Q','N','N','N','N','Q','N','N','N','N','N','N','N','N',
        'Q','N','N','N','E','E','N','Q','N','N','N','N','N','N','N','N',
        'Q','N','N','E','E','E','Q','Q','N','N','N','N','N','N','N','N',
        'Q','Q','Q','Q','N','N','Q','N','N','N','N','N','N','N','N','N',
        'N','N','N','Q','Q','Q','Q','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        },
        {
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','B','B','N','N','N','N','N','N','N','N','N','N',
        'N','M','N','B','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','B','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        }}; *map = map_1;
    }
    if (i == 6)
    {
        game map_1 =
        { 6,{
        'N','N','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N','N',
        'Q','Q','Q','N','N','N','Q','N','N','N','N','N','N','N','N','N',
        'Q','N','N','N','E','N','Q','Q','N','N','N','N','N','N','N','N',
        'Q','N','N','E','N','E','N','Q','N','N','N','N','N','N','N','N',
        'Q','Q','Q','N','E','N','N','Q','N','N','N','N','N','N','N','N',
        'N','N','Q','N','N','N','Q','Q','N','N','N','N','N','N','N','N',
        'N','N','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        },
        {
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','M','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','B','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','B','B','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        }}; *map = map_1;
    }
    if (i == 7)
    {
        game map_1 =
        { 7,{
        'N','N','Q','Q','Q','Q','N','N','N','N','N','N','N','N','N','N',
        'N','N','Q','E','E','Q','N','N','N','N','N','N','N','N','N','N',
        'N','Q','Q','N','E','Q','Q','N','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','E','Q','N','N','N','N','N','N','N','N','N',
        'Q','Q','N','N','N','N','Q','Q','N','N','N','N','N','N','N','N',
        'Q','N','N','Q','N','N','N','Q','N','N','N','N','N','N','N','N',
        'Q','N','N','N','N','N','N','Q','N','N','N','N','N','N','N','N',
        'Q','Q','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        },
        {
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','B','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','B','B','N','N','N','N','N','N','N','N','N','N',
        'N','M','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        } }; *map = map_1;
    }
    if (i == 8)
    {
        game map_1 =
        { 8,{
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','Q','Q','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N',
        'N','Q','N','N','Q','N','N','N','Q','N','N','N','N','N','N','N',
        'N','Q','N','N','E','E','N','N','Q','N','N','N','N','N','N','N',
        'N','Q','N','N','E','E','N','Q','Q','N','N','N','N','N','N','N',
        'N','Q','N','N','E','E','N','N','Q','N','N','N','N','N','N','N',
        'N','Q','N','N','Q','N','N','N','Q','N','N','N','N','N','N','N',
        'N','Q','Q','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        },
        {
         'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','N','N','B','N','N','N','N','N','N','N','N','N',
        'N','N','M','B','N','B','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','N','N','B','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        } }; *map = map_1;
    }
    if (i == 9)
    {
        game map_1 =
        { 9,{
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','Q','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N',
        'N','Q','E','E','N','E','E','Q','N','N','N','N','N','N','N','N',
        'N','Q','E','E','Q','E','E','Q','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','N','N','Q','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','N','N','Q','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','N','N','Q','N','N','N','N','N','N','N','N',
        'N','Q','N','N','Q','N','N','Q','N','N','N','N','N','N','N','N',
        'N','Q','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        },
        {
         'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','B','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','B','B','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','B','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','B','B','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','M','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        }}; *map = map_1;
    }
    if (i == 10)
    {
        game map_1 =
        { 10,{
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','Q','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N',
        'N','Q','E','N','E','N','E','Q','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','N','N','Q','N','N','N','N','N','N','N','N',
        'N','Q','E','N','N','N','E','Q','N','N','N','N','N','N','N','N',
        'N','Q','N','N','N','N','N','Q','N','N','N','N','N','N','N','N',
        'N','Q','E','N','E','N','E','Q','N','N','N','N','N','N','N','N',
        'N','Q','Q','Q','Q','Q','Q','Q','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        },
        {
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','B','B','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','M','B','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','B','B','B','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        'N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N',
        } }; *map = map_1;
    }

     
    return;
}