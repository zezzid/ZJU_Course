#pragma once
#include "file.h"

//从文件读取数据建立链表
struct link *initLink()
{
	FILE *fp;
	char ch;
	struct link *p = (struct link*)malloc(sizeof(struct link));//创建一个头结点
	memset(p, 0, sizeof(struct link));
	struct link *temp = p;//声明一个指针指向头结点，用于遍历链表
	//生成链表
	if ((fp = fopen("俄罗斯方块.txt", "r")) == NULL) exit(0);
	ch = fgetc(fp);
	if (ch == EOF)//判断是否为空文件
	{
		fclose(fp);
	}
	else
	{
		rewind(fp);//重定位到首地址
		while (1)
		{
			struct link *a = (struct link*)malloc(sizeof(struct link));
			memset(a, 0, sizeof(struct link));
			fscanf(fp, "%s %d", a->name, &a->score);
			a->next = NULL;
			temp->next = a;
			temp = temp->next;
			if (feof(fp)) break;
		}
		if (fclose(fp)) exit(0);
	}
	return p;
}

//保存最高纪录并写入文件
struct link *SaveData(struct link * p)
{
	FILE *fp;
	struct link *temp = p;//创建临时结点temp
	struct link *t = p;//创建临时结点t
	int find = 0;//查找是否为已注册用户
	while (t->next && !find) {
		t = t->next;
		if (!strcmp(t->name, name))
		{
			find = 1;
			//存储最高分
			if (t->score < score)
			{
				t->score = score;
			}
		}
	}
	if (!find)//新用户，插入新结点
	{
		p = insert(p);
	}
	//排序
	p = datasort(p);
	//写入文件
	if ((fp = fopen("俄罗斯方块.txt", "w")) == NULL) exit(0);
	if (temp->next)
	{
		temp = temp->next;
		fprintf(fp, "%s %d", temp->name, temp->score);
	}
	while (temp->next)
	{
		temp = temp->next;
		fprintf(fp, "\n%s %d", temp->name, temp->score);
	}
	if (fclose(fp)) exit(0);
	return  p;
}

//插入新用户（采用头插）
struct link *insert(struct link *p)
{
	struct link *temp = p;
	struct link *c;
	c = (struct link*)malloc(sizeof(struct link));
	memset(c, 0, sizeof(struct link));
	strcpy(c->name, name);
	c->score = score;
	//向链表中插入结点
	c->next = temp->next;
	temp->next = c;
	return p;
}

//冒泡排序（交换节点法）
struct link *datasort(struct link *head) {
	struct link *pre, *cur, *next, *end;//pre前一项 cur当前项 next后一项 end控制循环次数
	end = NULL;
	int flag = 1;//优化冒泡
	while (head->next != end && flag)
	{
		flag = 0;
		//初始化三个指针 ; 判断是否到达结束位置 ; 三个指针集体后移
		for (pre = head, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
		{
			if (cur->score < next->score) //从小到大
			{
				flag = 1;
				pre->next = next;
				cur->next = next->next;
				next->next = cur;

				//此时next变前一项，cur变后一项  交换指针
				struct link *temp = cur; cur = next; next = temp;
			}
		}

		//一轮循环结束 end提前一项
		end = cur;
	}
	return head;
}
