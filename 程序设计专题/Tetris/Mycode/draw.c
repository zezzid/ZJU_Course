#pragma once
#include "draw.h"

//开始界面——绘制标题，登录
void drawTopic()
{
	double x = 1.0;
	double y = 1.0;
	double w = 1.0;
	double h = GetFontHeight() * 2;
	static char str[80] = "用户名：";
	SetPenSize(1);
	SetPenColor("Blue");
	MovePen(x, y);
	drawBox(4.8, 5.4, 1.0, 1.0, 1, "俄罗斯方块", 'S', "white");
	SetPenColor("red");
	drawBox(3.8, 4.4, 1.0, 1.0, 1, "Tetris", 'S', "white");
	SetPenColor("Blue");
	SetPointSize(10);
	MovePen(4.8, 6.4);
	DrawLine(-1.0, 0.0);
	DrawLine(0.0, -1.0);
	MovePen(4.8, 4.4);
	DrawLine(1.0, 0.0);
	DrawLine(0.0, 1.0);
	drawBox(4 - TextStringWidth("  用户名："), 2, TextStringWidth("  用户名："), 0.5, 0, " 用户名：", 'S', "red");
}

//选择难度等级
void ChooseLevel()
{
	double x = 1.0;
	double y = 2;
	double w = 2.5;
	double h = 0.5;
	if (button(GenUIID(0), x + 0.8, y + 0.5, 1, 0.4, "简单"))
	{
		c = 1;
		mseconds = 1000;
	}
	else if (button(GenUIID(0), x + 0.8, y, 1, 0.4, "一般"))
	{
		c = 1;
		mseconds = 500;
	}
	else if (button(GenUIID(0), x + 0.8, y - 0.5, 1, 0.4, "困难"))
	{
		c = 1;
		mseconds = 250;
	}
}

//画用户名的输入框
void displaychar()
{
	DisplayClear();
	drawTopic();
	double x1 = 4;
	double y1 = 2;
	double w1 = 2.5;
	double h1 = 0.5;
	static char str[80] = "";
	if (textbox(GenUIID(0), x1, y1, w1, h1, str, sizeof(str)))
	{
		r = 1;
		strcpy(name, str);
	}
	displaystart();//画确认按钮
	ChooseLevel();//选择难度
}

//画登录界面的确认按钮
void displaystart()
{
	double x = 3.5;
	double y = 2;
	double w = 2.5;
	double h = 0.5;
	if ((button(GenUIID(0), x + 0.8, y - 0.5, 1, 0.4, "确认")) && (r == 1) && (c == 1))
	{
		p = SaveData(p);
		enter = 1;
		display();
		startTimer(TIMER_BLINK, mseconds);
	}
}

//画当前的方块
void DrawMoving(double x, double y)
{
	SetPenColor(Block[i].color);
	drawRectangle(current_x + Block[i].x1*0.3, current_y + Block[i].y1*0.3, 0.3, 0.3, 1);
	drawRectangle(current_x + Block[i].x2*0.3, current_y + Block[i].y2*0.3, 0.3, 0.3, 1);
	drawRectangle(current_x + Block[i].x3*0.3, current_y + Block[i].y3*0.3, 0.3, 0.3, 1);
	drawRectangle(current_x + Block[i].x4*0.3, current_y + Block[i].y4*0.3, 0.3, 0.3, 1);
}

//绘制已经落下的方块
void DrawSilent()
{
	int j, k, h;
	for (j = 0; j < 10; j++)
	{
		for (k = 0; k < 14; k++)
		{
			if (board[j][k] == 1)
			{
				h = color[j][k];
				SetPenColor(Block[h].color);
				drawRectangle(0.5 + j * 0.3, 0.5 + k * 0.3, 0.3, 0.3, 1);
			}
		}
	}
}

//画网格
void DrawLattice()
{
	int i, j;
	SetPenSize(.5);
	for (i = 1; i < 20; i++)
	{
		SetPenColor("Light Gray");
		MovePen(0.5, 0.5 + i * 0.3);
		DrawLine(3, 0);
	}
	for (j = 1; j < 10; j++)
	{
		SetPenColor("Light Gray");
		MovePen(0.5 + j * 0.3, 0.5);
		DrawLine(0, 6);
	}
	SetPenColor("Red");
	MovePen(0.5, 4.4);
	DrawLine(3, 0);
}

//画背景
void DrawBackground()
{
	double w, h;
	w = winwidth;
	h = winheight;
	SetPenColor("Black");
	drawRectangle(0.5, 0.5, 3, 6, 1);
	SetPenColor("blue");
	drawRectangle(5, 0.2 + 6.6 * 1 / 4 - 0.55, 2.2, 6.6 / 3, 0);
	drawRectangle(5, 0.2 + 6.6 * 5 / 8 - 0.55, 2.2, 6.6 / 3, 0);
	drawBox(w / 2, (h - 6.6) / 2 + 6.6 * 1 / 4 + 6.6 / 4 * 2 / 3, 2.2, 6.6 / 4 / 3.0, 1, "SCORE", 'c', "white");
	SetPenColor("blue");
	drawBox(w / 2, (h - 6.6) / 2 + 6.6 * 5 / 8 + 6.6 / 4 * 2 / 3, 2.2, 6.6 / 4 / 3.0, 1, "NEXT", 'c', "white");
	DrawScore();
	DrawButton();
	DrawMenu();
}

//在右边画生成的下一个方块
void DrawNext(int i)
{
	SetPenColor(Block[i].color);
	drawRectangle(6 + Block[i].x1*0.3, 4.2 + Block[i].y1*0.3, 0.3, 0.3, 1);
	drawRectangle(6 + Block[i].x2*0.3, 4.2 + Block[i].y2*0.3, 0.3, 0.3, 1);
	drawRectangle(6 + Block[i].x3*0.3, 4.2 + Block[i].y3*0.3, 0.3, 0.3, 1);
	drawRectangle(6 + Block[i].x4*0.3, 4.2 + Block[i].y4*0.3, 0.3, 0.3, 1);
}

//显示分数
void DrawScore()
{
	char Say[100];
	SetPenColor("Black");
	sprintf(Say, "%d", score);
	SetPointSize(50);
	drawLabel(5.8, 1.9, Say);
	SetPointSize(1);
}

//画按钮 
void DrawButton()
{
	double fH = GetFontHeight();
	double h = fH * 2;
	double x = winwidth / 4;
	double y = winheight / 4;
	double w = TextStringWidth("暂停") * 3;
	double dx = w + TextStringWidth("暂");
	double dy = h * 2;
	int z1, z2;
	if (button(GenUIID(0), w * 4 / 5 + 7, (h - 6.6) / 2 + 6.6 * 12 / 17, 6.6 / 17 * 2, 6.6 / 17 * 2, "about us"))
	{
		enable_mov_Tetris = 0;
		if (MessageBox(NULL, TEXT("游戏名：俄罗斯方块\n操作说明：\n↑：旋转方块\n←：方块左移\n→：方块右移\n↓：加速下落\n快捷键说明：\nCtrl-0 打开排行榜\nCtrl-C 关闭排行榜\nCtrl-R 重新开始\nCtrl-P 暂停\nCtrl-E 退出\nCtrl-A 关于游戏\n玩法说明：《俄罗斯方块》的基本规则是移动，旋转和摆放\n自动输出的各种方块，使之排列成完整一行或多行并且消除得分。\n消除一行得100分\n祝您好运！\n制作者：罗仪 杨雨欣 叶奕含"), TEXT("about us"), MB_OK))
		{
			enable_mov_Tetris = 1;
		}
	}
	if (button(GenUIID(0), w * 4 / 5 + 7, (h - 6.6) / 2 + 6.6 * 15 / 17, 6.6 / 17 * 2, 6.6 / 17 * 2, "pause"))
	{
		enable_mov_Tetris = !enable_mov_Tetris;
		anti_keyboard = !anti_keyboard;
	}
	if (button(GenUIID(0), w * 4 / 5 + 7, (h - 6.6) / 2 + 6.6 * 18 / 17, 6.6 / 17 * 2, 6.6 / 17 * 2, "reset"))
	{
		enable_mov_Tetris = 1;
		for (z1 = 0; z1 < 10; z1++)
			for (z2 = 0; z2 < 20; z2++)
				board[z1][z2] = 0;
		current_x = 2;
		current_y = 5.6;
		score = 0;
	}
	if (button(GenUIID(0), w * 4 / 5 + 7, (h - 6.6) / 2 + 6.6 * 21 / 17, 6.6 / 17 * 2, 6.6 / 17 * 2, "exit"))
	{
		flag = 1;
		p = SaveData(p);
		exit(-1);
	}
}

//画上方菜单栏 快捷键
void DrawMenu()
{
	static char *menuListFile[] = { "Rank",
	 "Open | Ctrl-0",
	 "Close | Ctrl-C" };
	static char *menuListTool[] = { "Tool",
	 "Reset | Ctrl-R",
	 "Pause | Ctrl-P",
	 "Exit | Ctrl-E" };
	static char *menuListHelp[] = { "Help",
	 "About Us | Ctrl-A" };
	static char *selectedLable = NULL;
	double fH = GetFontHeight();
	double x = 0;
	double y = winheight;
	double h = fH * 1.5;
	double w = TextStringWidth(menuListHelp[0]) * 2;
	double wlist = TextStringWidth(menuListTool[3])*1.6;
	double xindent = winheight / 20;      // 缩进
	int selection;
	int z1, z2;
	SetPenSize(1);
	//排行榜
	selection = menuList(GenUIID(0), x, y - h, w, wlist, h, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection > 0)
		selectedLable = menuListFile[selection];
	if (selection == 1)
	{
		p = SaveData(p); 
		DrawRank();
		enable_mov_Tetris = 0;
		rank = 1;
		enter = 0;
		system("俄罗斯方块.txt");
	}
	if (selection == 2)
	{
		if (rank == 1)
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
			rank = 0;
			enter = 1;
		}
		
	}
	//工具栏
	selection = menuList(GenUIID(0), x + w, y - h, w, wlist, h, menuListTool, sizeof(menuListTool) / sizeof(menuListTool[0]));
	if (selection > 0)
		selectedLable = menuListTool[selection];
	if (selection == 3)
	{
		flag = 1;
		p = SaveData(p);
		exit(-1);
	}
	if (selection == 2)
		enable_mov_Tetris = !enable_mov_Tetris;
	if (selection == 1)
	{
		for (z1 = 0; z1 < 10; z1++)
			for (z2 = 0; z2 < 20; z2++)
				board[z1][z2] = 0;
		current_x = 2;
		current_y = 5.6;
		score = 0;
		enable_mov_Tetris = 1;
	}
	//关于我们
	selection = menuList(GenUIID(0), x + 2 * w, y - h, w, wlist, h, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection == 1)
	{
		enable_mov_Tetris = 0;
		if (MessageBox(NULL, TEXT("游戏名：俄罗斯方块\n操作说明：\n↑：旋转方块\n←：方块左移\n→：方块右移\n↓：加速下落\n快捷键说明：\nCtrl-0 打开排行榜\nCtrl-C 关闭排行榜\nCtrl-R 重新开始\nCtrl-P 暂停\nCtrl-E 退出\nCtrl-A 关于游戏\n玩法说明：《俄罗斯方块》的基本规则是移动，旋转和摆放\n自动输出的各种方块，使之排列成完整一行或多行并且消除得分。\n消除一行得100分\n祝您好运！\n制作者：罗仪 杨雨欣 叶奕含"), TEXT("about us"), MB_OK))
		{
			enable_mov_Tetris = 1;
		}
	}
}

//显示
void display()
{
	DisplayClear();
	DrawBackground();
	DrawNext(next);
	DrawScore();
	DrawMoving(current_x, current_y);
	DrawSilent();
	DrawLattice();
}

//显示排行榜
void DrawRank()
{
	double fH = GetFontHeight();
	double y = 3.5;
	char ch[10] = { 0 };
	int i = 1;
	struct link *temp = p;
	DisplayClear();
	SetPenSize(1);
	SetPenColor("Blue");
	MovePen(1, 1);
	drawBox(4.8, 5.4, 1.0, 1.0, 1, "俄罗斯方块", 'S', "white");
	SetPenColor("red");
	drawBox(3.8, 4.4, 1.0, 1.0, 1, "Tetris", 'S', "white");
	SetPenColor("Blue");
	SetPointSize(10);
	MovePen(4.8, 6.4);
	DrawLine(-1.0, 0.0);
	DrawLine(0.0, -1.0);
	MovePen(4.8, 4.4);
	DrawLine(1.0, 0.0);
	DrawLine(0.0, 1.0);

	DrawMenu();
	SetPointSize(30);
	drawLabel(1.5, 4, "排行榜：");
	SetPointSize(20);
	while (temp->next)
	{
		temp = temp->next;
		SetPenColor("Red");
		sprintf(ch, "%d", i);//显示排名
		drawLabel(1.5, y, ch);
		i = i + 1;
		SetPenColor("Black");
		drawLabel(2, y, temp->name);
		char string[16] = { 0 };
		sprintf(string, "%d", temp->score);
		drawLabel(3, y, string);
		y = y - fH * 1.5;
	}
	SetPointSize(1);
}