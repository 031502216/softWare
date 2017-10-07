/* 
//1.标签，空闲时间段，活动时间段段固定，生成时随机从中选择 
//2.定义全局的四个合集，以便于信息的表示 
//3.具体的一些简化及其它约定，详见注释 
*/ 

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>                                                                                   
#include "cJSON.h"

/*标签合集*/ 
char TAG[][20] = {"film", "music", "reading", 
    "study", "English", "chess", "football", 
	"programming", "dance", "basketball"};
/*部门常规活动时间段合集*/ 
char DAILY[][20] = {"9:00~10:00", "12:30~13:30", "18:30~19:30", "21:00~22:00"};
/*学生空闲时间段合集*/
char FREE[][20] = {"9:00~11:30", "12:30~14:00", "18:30~20:00", "21:00~22:30"};
char WEEK[][5] = {"Mon", "Tues", "Wed", "Thur", "Fri", "Sat", "Sun"}; 

/*定义部门*/ 
struct Department
{
	char number[5];
	int member_limit;
	
	/*对应TAG中十个标签*/
	/*1表示有，0表示没有*/ 
	int tags[10];
	
	/*纵向七个代表星期，0表示没有，1表示有*/
	/*横向为当日常规活动时间，约定一天至多一次。来自部门常规活动时间段合集*/
	int event_schedules[7][2];
}D[20];	

/*定义学生*/ 
struct Student
{
	char number[10];
	
	/*对应TAG中十个标签*/
	/*1表示有，0表示没有*/
	int tags[10];
	
	/*意愿部门特点标签合集*/
	/*用于生成学生兴趣标签*/ 
	int d_tags[10];
	 
	/*纵向七个代表星期，0表示没有，1表示有*/
	/*横向为当日空闲时间，最多两个，来自学生空闲时间段合集*/
	int free_time[7][3];
	
	/*20个部门，有意愿记为1，否则置0*/ 
	int wanted_department[20];
	int department_count;
	int department_order[5];
}S[300]; 

int main()
{
	srand(time(0));
	
	int i, j, k, l, m;
	/*20个部门信息初始化*/ 
	for(i = 0; i < 20; i++)
	{
		/*初始化部门编号*/ 
		strcpy(D[i].number, "D000");
		if(i < 9)
		{
			D[i].number[3] = '0' + i + 1;
		}
		else
		{
			D[i].number[2] = '0' + ((i + 1) / 10);
			D[i].number[3] = '0' + ((i + 1) % 10);
		}
		/*check
		printf("%s\n", D[i].number);
		*/
		
		/*初始化招收人数，范围[10, 15]*/
		D[i].member_limit = rand() % 6 + 10;
		/*check
		printf("%d\n", D[i].member_limit);
		*/
		
		/*初始化部门特点标签，约定为4-6个*/
		j = rand() % 3 + 4;
		memset(D[i].tags, 0, sizeof(int) * 10);
		while(j > 0)
		{
			k = rand() % 10;
			if(D[i].tags[k] == 0)//过滤重复的随机数 
			{
				/*标记有该特点标签*/ 
				D[i].tags[k] = 1;
				j--;
			}
		} 
		/*check
		for(j = 0; j < 10; j++) 
		    printf("%d", D[i].tags[j]);
		printf("\n");
		*/
		
		/*初始化部门常规活动时间*/
		/*约定一天至多一次，每周三到四次*/
		memset(D[i].event_schedules, 0, sizeof(D[i].event_schedules)); 
		j = rand() % 2 + 3;
		while(j > 0)
		{		
			k = rand() % 7;
			if (D[i].event_schedules[k][0] == 0)//过滤重复的随机数
			{
				j--; 
				/*标记有该星期*/
				D[i].event_schedules[k][0] = 1;
				/*从部门常规活动时间段合集任选一个*/
				D[i].event_schedules[k][1] = rand() % 4;
			}
		} 
		/*check 
		for(j = 0; j < 7; j++) 
		    printf("%d%d\n", D[i].event_schedules[j][0], D[i].event_schedules[j][1]);
		printf("\n");
		*/		
	}
	
	/*学生信息初始化*/  
	for(i = 0; i < 300; i++)
	{
		/*初始化学生编号*/ 
		strcpy(S[i].number, "031502000");
		if(i < 9)
		{
			S[i].number[9] = '0' + i + 1;
		}
		else if(i < 99)
		{
			S[i].number[8] = '0' + ((i + 1) / 10);
			S[i].number[9] = '0' + ((i + 1) % 10);
		}
		else
		{
			S[i].number[7] = '0' + ((i + 1) / 100);
			S[i].number[8] = '0' + ((i + 1) / 10 % 10);
			S[i].number[9] = '0' + ((i + 1) % 10);
		}
		/*check
		printf("%s\n", S[i].number);
		*/
		
		/*初始化意愿部门，范围[1, 5]*/
		S[i].department_count = rand() % 5 + 1;	 
		memset(S[i].wanted_department, 0, sizeof(int) * 20);
		memset(S[i].d_tags, 0, sizeof(int) * 10);
		memset(S[i].department_order, 0, sizeof(int) * 5);	
		for(j = 0; j < S[i].department_count; )
		{
			k = rand() % 20;//20个部门随机 
			if(S[i].wanted_department[k] == 0)//过滤重复 
			{
				S[i].department_order[j++] = k;
				S[i].wanted_department[k] = 1;
				/*初始化意愿部门标签合集*/
				for(l = 0; l < 10; l++)
				{
					if(D[k].tags[l] == 1)
					{
						S[i].d_tags[l] = 1;
					}
				}
			} 
		} 
		/*check
		if(i % 3 == 0)
		{
			printf("wanted_order:");
			for(j = 0; j < 5; j++)
			{
				printf("%d ", S[i].department_order[j]);
			}
			printf("\nwanted_d:");
		    for (j = 0; j < 20; j++)
		    {
		    	printf("%d", S[i].wanted_department[j]);
			}
			printf("\nd_tags:");
			for(j = 0; j < 10; j++)
			{
				printf("%d", S[i].d_tags[j]);
			}
			printf("\n");
	    }
		*/
		
		/*初始化兴趣标签*/
		/*约定3-4个，从d_tags中随机取*/
		j = rand() % 2 + 3;
		memset(S[i].tags, 0, sizeof(int) * 10);
		while(j > 0)
		{
			k = rand() % 10;
			if(S[i].d_tags[k] == 1)
			{
				j--;
				S[i].d_tags[k] = 0;
				S[i].tags[k] = 1;
			}
		}
		/*check
		for(j = 0; j < 10; j++) 
		    printf("%d", S[i].tags[j]);
		printf("\n");
		*/ 
		
		/*初始化空闲时间段*/
		/*一周三至四天*/
		/*每天随机两个时间段*/ 
		memset(S[i].free_time, 0, sizeof(S[i].free_time)); 
		j = rand() % 2 + 3;
		while(j > 0)
		{		
			k = rand() % 7;
			if (S[i].free_time[k][0] == 0)//过滤重复的随机数
			{
				j--; 
				/*标记有该星期*/
				S[i].free_time[k][0] = 1;
				/*从空闲时间段合集任选两个*/
				l = rand() % 4;
				S[i].free_time[k][1] = l;
				do
				{
					m = rand() % 4;
				}
				while(m == l);
				S[i].free_time[k][2] = m; 		
			}
		} 
		/*check 
		for(j = 0; j < 7; j++) 
		    printf("%d%d%d\n", S[i].free_time[j][0], S[i].free_time[j][1], S[i].free_time[j][2]);
		printf("\n");
		*/		
		
	}
//	cJSON * student =  cJSON_CreateObject();
//	cJSON * free_time =  cJSON_CreateObject();
//	cJSON * student_no =  cJSON_CreateObject();
//	cJSON * applications_department =  cJSON_CreateObject();
//	cJSON * tags =  cJSON_CreateObject();
//	cJSON * root =  cJSON_CreateObject();
//	cJSON * item =  cJSON_CreateObject();
//	
//	cJSON_AddItemToObject(root, "student", student=cJSON_CreateArray());
//	for(i = 0; i < 300; i++) { 
//		cJSON_AddItemToArray(student, item = cJSON_CreateObject()); 
//		cJSON_AddItemToObject(item, "free_time", free_time=cJSON_CreateArray());
//		//for(j = 0;j<S[i].free_time.length();j++) 
//	}
	printf("%s",WEEK[0][1]);
	printf("6666");
	return 0;
} 
