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
#include "draw.h"

#define TIMER_BLINK 1//时钟编号
#define deltax 0.3;
#define deltay 0.3;

//数据结构体定义
struct BLOCK;

//存储分数的链表
struct link;

//存储俄罗斯方块类型
struct BLOCK Block[19] = {
	/*x1,y1,x2,y2,x3,y3,x4,y4, color,  num*/
	{ 0, 0, 0, 1, 0, 2, 1, 2,  "Cyan",  0}, /*        */
	{-1, 1, 0, 1, 1, 0, 1, 1,  "Cyan",  1}, /*  #     */
	{ 0, 0, 1, 0, 1, 1, 1, 2,  "Cyan",  2}, /*  #     */
	{-1, 0,-1, 1, 0, 0, 1, 0,  "Cyan",  3}, /*  ##    */

	{ 0, 0, 0, 1, 0, 2, 1, 0, "Magenta",4},/*         */
	{-1, 0,-1, 1, 0, 1, 1, 1, "Magenta",5},/*  ##     */
	{ 0, 2, 1, 0, 1, 1, 1, 2, "Magenta",6},/*  #      */
	{-1, 0, 0, 0, 1, 0, 1, 1, "Magenta",7},/*  #      */

	{-1, 1, 0, 0, 0, 1, 1, 1, "Blue",   8},/*        */
	{-1, 1, 0, 0, 0, 1, 0, 2, "Blue",   9},/*        */
	{-1, 0, 0, 0, 0, 1, 1, 0, "Blue",  10},/*   #    */
	{ 0, 0, 0, 1, 0, 2, 1, 1, "Blue",  11},/*  ###   */

	{-1, 1, 0, 0, 0, 1, 1, 0, "Yellow",12},/*  ##    */
	{ 0, 0, 0, 1, 1, 1, 1, 2, "Yellow",13},/*   ##   */

	{-1, 0, 0, 0, 0, 1, 1, 1,  "Red"  ,14},/*    ##  */
	{ 0, 1, 0, 2, 1, 0, 1, 1,  "Red"  ,15},/*   ##   */

	{ 0, 0, 0, 1, 0, 2, 0, 3, "Orange" ,16},/*  #     */
	{-1, 0, 0, 0, 1, 0, 2, 0, "Orange" ,17},/*  #     */
										    /*  #     */
										    /*  #     */

	{ 0, 0, 0, 1, 1, 0, 1, 1, "Brown" ,18},/*  ##    */
										   /*  ##    */
};

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

//回调函数
void TimerEventProcess(int timerID);//定时器
void myKeyboardEventProcess(int key, int event);//键盘回调函数
void myMouseEventProcess(int x, int y, int button, int event);//鼠标回调函数
void CharEventProcess(char ch);//获取输入的字符

//游戏函数
int Transferx(double tipx);//把界面的x坐标（double）转换成数组的x坐标
int Transfery(double tipy);//把界面的y坐标（double）转换成数组的y坐标
int FullLine();//判断满行
void KillLine(int);//清除底行
int TouchLeftWall(double x, int num);//判断如果左移会不会触到左边界
int TouchRightWall(double x, int num);//判断如果右移会不会触到右边界
int GameOver();//游戏结束

//初始化
void initRandomNum();//随机初始化

//文件读写
struct link *SaveData(struct link *p);//保存最高纪录并写入文件
struct link *initLink();//从文件读取数据建立链表
struct link *insert(struct link *p);//插入新用户（采用头插）
struct link *datasort(struct link *head);//冒泡排序（交换节点法）

//变量定义
double winwidth, winheight;//窗口长度、宽度
double current_x, current_y;//当前方块原点坐标
int board[11][21];//存放坐标是否填充
int color[11][21];//存放坐标的颜色
int score;//记录分数
int enter = 0;//判断是否进入游戏
int rank = 0;//判断是否打开排行榜界面
int mseconds;//定时器调用时间
int t = 0, r = 0;//按钮
int i;//当前的方块序号
int next;//下一个方块序号
int enable_mov_Tetris = 1;//允许方块移动
int if_fall = 0;//标记能否下落
int anti_keyboard = 1;//在判断满行时不执行键盘操作
int c = 0;//判断是否选择了难度等级
int flag = 0;//判断是否按了exit（如果按了就保存成绩后退出)
char name[80];//存储当前用户名
struct link *p = NULL;//链表头节点