#include "Tetris.h"

void Main()
{
	p = initLink();
	SetWindowTitle("俄罗斯方块");
	InitGraphics();
	initRandomNum();
	current_x = 2;
	current_y = 5.6;
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();
	registerTimerEvent(TimerEventProcess);
	registerKeyboardEvent(myKeyboardEventProcess);
	registerMouseEvent(myMouseEventProcess);
	registerCharEvent(CharEventProcess);
	displaychar();
}

//定时器
void TimerEventProcess(int timerID)
{
	if (enter == 1)//如果进入游戏了
	{
		if (timerID == TIMER_BLINK && enable_mov_Tetris == 1)
		{

			if (current_y == 5.6)//随机生成下一个方块
			{
				next = rand() % 7;
				if (next == 0) next = next + rand() % 4;
				else if (next == 1) next = next + 3 + rand() % 4;
				else if (next == 2) next = next + 6 + rand() % 4;
				else if (next == 3) next = next + 9 + rand() % 2;
				else if (next == 4) next = next + 10 + rand() % 2;
				else if (next == 5) next = next + 11 + rand() % 2;
				else if (next == 6) next = next + 12;
			}

			if (current_y > 0.5)
			{
				//判断能否下落
				if (!board[Transferx(current_x + Block[i].x1*0.3)][Transfery(current_y + Block[i].y1*0.3) - 1]

					&& !board[Transferx(current_x + Block[i].x2*0.3)][Transfery(current_y + Block[i].y2*0.3) - 1]
					&& !board[Transferx(current_x + Block[i].x3*0.3)][Transfery(current_y + Block[i].y3*0.3) - 1]
					&& !board[Transferx(current_x + Block[i].x4*0.3)][Transfery(current_y + Block[i].y4*0.3) - 1])
				{
					if_fall = 1;//可以下落
					current_y = current_y - 0.3;
				}
				else
					if_fall = 0;//不可以下落
				//到底了，标记坐标和颜色
				if (current_y <= 0.6 || if_fall == 0)
				{
					anti_keyboard = 0;
					board[Transferx(current_x + Block[i].x1*0.3)][Transfery(current_y + Block[i].y1*0.3)] = 1;
					board[Transferx(current_x + Block[i].x2*0.3)][Transfery(current_y + Block[i].y2*0.3)] = 1;
					board[Transferx(current_x + Block[i].x3*0.3)][Transfery(current_y + Block[i].y3*0.3)] = 1;
					board[Transferx(current_x + Block[i].x4*0.3)][Transfery(current_y + Block[i].y4*0.3)] = 1;
					color[Transferx(current_x + Block[i].x1*0.3)][Transfery(current_y + Block[i].y1*0.3)] = i;
					color[Transferx(current_x + Block[i].x2*0.3)][Transfery(current_y + Block[i].y2*0.3)] = i;
					color[Transferx(current_x + Block[i].x3*0.3)][Transfery(current_y + Block[i].y3*0.3)] = i;
					color[Transferx(current_x + Block[i].x4*0.3)][Transfery(current_y + Block[i].y4*0.3)] = i;
					while (FullLine() != 0)//满行消减
					{
						KillLine(FullLine());
						score += 100;
					}
					//部分数据更新
					current_x = 2;
					current_y = 5.6;
					i = next;
					anti_keyboard = 1;
					if_fall = 1;
					if (GameOver())
					{
						enable_mov_Tetris = 0;
						p = SaveData(p);
						int ch;
						ch = MessageBox(NULL, TEXT("游戏结束！\n点击取消打开排行榜\n"), TEXT("俄罗斯方块"), MB_RETRYCANCEL);
						if (ch == IDRETRY)//重试
						{
							enable_mov_Tetris = 1;
							for (int z1 = 0; z1 < 10; z1++)
								for (int z2 = 0; z2 < 20; z2++)
									board[z1][z2] = 0;
							current_x = 2;
							current_y = 5.6;
							score = 0;
							i = rand() % 19;
							next = rand() % 19;
						}
						else//打开排行榜
						{
							p = SaveData(p);
							display();
							DrawRank();
							enable_mov_Tetris = 0;
							rank = 1;
							enter = 0;
							system("俄罗斯方块.txt");
						}
					}
				}
			}
		}
		display(); // 刷新显示
	}
}

//键盘回调函数
void myKeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event);
	if (r == 1 && enter == 1) //如果输入了用户名并且进入了游戏
	{
		switch (event)
		{
		case KEY_DOWN:
			switch (key)
			{
			case VK_LEFT://按左箭头
				if (anti_keyboard == 1 && TouchLeftWall(current_x, i)
					&& !board[Transferx(current_x + Block[i].x1*0.3) - 1][Transfery(current_y + Block[i].y1*0.3)]
					&& !board[Transferx(current_x + Block[i].x2*0.3) - 1][Transfery(current_y + Block[i].y2*0.3)]
					&& !board[Transferx(current_x + Block[i].x3*0.3) - 1][Transfery(current_y + Block[i].y3*0.3)]
					&& !board[Transferx(current_x + Block[i].x4*0.3) - 1][Transfery(current_y + Block[i].y4*0.3)])
					current_x -= deltax;
				break;
			case VK_RIGHT:
				if (anti_keyboard == 1 && TouchRightWall(current_x, i)
					&& !board[Transferx(current_x + Block[i].x1*0.3) + 1][Transfery(current_y + Block[i].y1*0.3)]
					&& !board[Transferx(current_x + Block[i].x2*0.3) + 1][Transfery(current_y + Block[i].y2*0.3)]
					&& !board[Transferx(current_x + Block[i].x3*0.3) + 1][Transfery(current_y + Block[i].y3*0.3)]
					&& !board[Transferx(current_x + Block[i].x4*0.3) + 1][Transfery(current_y + Block[i].y4*0.3)])
					current_x += deltax;
				break;
			case VK_DOWN:
				if (anti_keyboard == 1 && if_fall == 1 && current_y > 0.9 
					&& !board[Transferx(current_x + Block[i].x1*0.3)][Transfery(current_y + Block[i].y1*0.3) - 1] 
					&& !board[Transferx(current_x + Block[i].x2*0.3)][Transfery(current_y + Block[i].y2*0.3) - 1] 
					&& !board[Transferx(current_x + Block[i].x3*0.3)][Transfery(current_y + Block[i].y3*0.3) - 1] 
					&& !board[Transferx(current_x + Block[i].x4*0.3)][Transfery(current_y + Block[i].y4*0.3) - 1])
					current_y -= deltay;
				break;
			case VK_UP:
				if (anti_keyboard == 1)
				{
					if (i >= 0 && i <= 3 && TouchLeftWall(current_x, (i + 1) % 4) && TouchRightWall(current_x, (i + 1) % 4))
							i = (i + 1) % 4;
						else if (i >= 4 && i <= 7 && TouchLeftWall(current_x, (i - 3) % 4 + 4) && TouchRightWall(current_x, (i - 3) % 4 + 4))
							i = (i - 3) % 4 + 4;
						else if (i >= 8 && i <= 11 && TouchLeftWall(current_x, (i - 7) % 4 + 8) && TouchRightWall(current_x, (i - 7) % 4 + 8))
							i = (i - 7) % 4 + 8;
						else if ((i == 12 || i == 13) && TouchLeftWall(current_x, (i - 11) % 2 + 12) && TouchRightWall(current_x, (i - 11) % 2 + 12))
							i = (i - 11) % 2 + 12;
						else if ((i == 14 || i == 15) && TouchLeftWall(current_x, (i - 13) % 2 + 14) && TouchRightWall(current_x, (i - 13) % 2 + 14))
							i = (i - 13) % 2 + 14;
						else if ((i == 16 || i == 17) && TouchLeftWall(current_x, (i - 15) % 2 + 16) && TouchRightWall(current_x, (i - 15) % 2 + 16))
							i = (i - 15) % 2 + 16;
						break;
				}
			}
		}
		display();
	}
}

//鼠标回调函数
void myMouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);
	if (enter == 1)//进入游戏
		display();
	else if (enter == 0 && rank == 0)//在初始界面
	{
		displaystart();
		ChooseLevel();
	}
	else if (rank == 1)//在排行榜界面
	{
		DrawRank();
	}
}

//获取输入的字符
void CharEventProcess(char ch)
{
	uiGetChar(ch); /*获取字符*/
	displaychar(); /*更新显示*/
}

//把界面的x坐标（double）转换成数组的x坐标
int Transferx(double tipx)
{
	int flag;
	double eps = 0.1;
	for (flag = 0; flag < 10; flag++)
	{
		if (fabs(tipx - 0.5 - flag * 0.3) < eps)
			return flag;
	}
}

//把界面的y坐标（double）转换成数组的y坐标
int Transfery(double tipy)
{
	int flag;
	double eps = 0.1;
	for (flag = 0; flag < 20; flag++)
	{
		if (fabs(tipy - 0.5 - flag * 0.3) < eps)
			return flag;
	}
}

//判断满行
int FullLine()
{
	int k, j;
	//int tp = 0;
	for (j = 0; j < 20; j++)
	{
		for (k = 0; k < 10; k++)
		{
			if (board[k][j] == 0)
				break;
		}
		if (k == 10)
			break;
	}
	if (k == 10) return j + 1;
	else    return 0;
}

//清除底行
void KillLine(int a)
{
	int i, j, k;
	for (i = 0; i < 10; i++)
		board[i][a - 1] = 0;
	for (j = 0; j < 10; j++)
	{
		for (k = a; k < 20; k++)
		{
			if (board[j][k] == 1)
			{
				board[j][k - 1] = board[j][k];
				color[j][k - 1] = color[j][k];
				board[j][k] = 0;
				color[j][k] = 0;
			}
		}
	}
	display();
}

//判断如果左移会不会触到左边界
int TouchLeftWall(double x, int num)
{
	if ((x + Block[num].x1*0.3 - 0.3) >= 0.4
		&& (x + Block[num].x2*0.3 - 0.3) >= 0.4
		&& (x + Block[num].x3*0.3 - 0.3) >= 0.4
		&& (x + Block[num].x4*0.3 - 0.3) >= 0.4)
		return 1;
	else
		return 0;
}

//判断如果右移会不会触到右边界
int TouchRightWall(double x, int num)
{
	if ((x + Block[num].x1*0.3 + 0.3) <= 3.2
		&& (x + Block[num].x2*0.3 + 0.3) <= 3.2
		&& (x + Block[num].x3*0.3 + 0.3) <= 3.2
		&& (x + Block[num].x4*0.3 + 0.3) <= 3.2)
		return 1;
	else
		return 0;
}

//游戏结束
int GameOver()
{
	int j, k;
	for (j = 0; j < 10; j++)
	{
		if (board[j][12] == 1)
		{
			k = 1;
			break;
		}
		else
			k = 0;
	}
	return k;
}

//随机初始化
void initRandomNum()
{
	srand(time(0) + rand());
	i = rand() % 19;
}
