#pragma once
#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "imgui.h"
#include <math.h>
#include <time.h>
#include "file.h"

#define TIMER_BLINK 1//时钟编号

//数据结构体定义
extern struct BLOCK
{
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;
	double x4;
	double y4;
	char color[8];
	int num;
};

//存储俄罗斯方块类型
extern struct BLOCK Block[19];

extern double current_x, current_y;//当前方块原点坐标
extern double winwidth, winheight;//窗口长度、宽度
extern int c;//判断是否选择了难度等级
extern int mseconds;//定时器调用时间
extern int t, r;//按钮
extern int enter;//判断是否进入游戏
extern int rank;//判断是否打开排行榜界面
extern int i;//当前的方块序号
extern int next;//下一个方块序号
extern int enable_mov_Tetris;//允许方块移动
extern int anti_keyboard;//在判断满行时不执行键盘操作
extern int flag;//判断是否按了exit（如果按了就保存成绩后退出)
extern int board[11][21];//存放坐标是否填充
extern int color[11][21];//存放坐标的颜色
extern char name[80];
extern struct link *p;//链表头节点

//初始界面
void drawTopic();//开始界面——绘制标题，登录
void ChooseLevel();//选择难度等级
void displaychar();//画用户名的输入框
void displaystart();//画登录界面的确认按钮

//游戏界面
void DrawMoving(double x, double y);//画当前的方块
void DrawSilent();//绘制已经落下的方块
void DrawLattice();//画网格
void DrawBackground();//画背景
void DrawNext(int i);//在右边画生成的下一个方块
void DrawScore();//显示分数
void DrawButton();//画按钮
void DrawMenu();//画上方菜单栏 快捷键
void display();//显示

//排行榜界面
void DrawRank();//显示排行榜