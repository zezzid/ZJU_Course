#pragma once
#include<stdio.h>
#include <string.h>

//存储分数的链表
extern struct link {
	char	name[80];
	int     score;
	struct link	*next;
};
extern char name[80];
extern int score;

struct link *SaveData(struct link *p);//保存最高纪录并写入文件
struct link *initLink();//从文件读取数据建立链表
struct link *insert(struct link *p);//插入新用户（采用头插）
struct link *datasort(struct link *head);//冒泡排序（交换节点法）
