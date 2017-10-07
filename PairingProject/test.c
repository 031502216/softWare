/* 
//1.��ǩ������ʱ��Σ��ʱ��ζι̶�������ʱ�������ѡ�� 
//2.����ȫ�ֵ��ĸ��ϼ����Ա�����Ϣ�ı�ʾ 
//3.�����һЩ�򻯼�����Լ�������ע�� 
*/ 

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>                                                                                   
#include "cJSON.h"

/*��ǩ�ϼ�*/ 
char TAG[][20] = {"film", "music", "reading", 
    "study", "English", "chess", "football", 
	"programming", "dance", "basketball"};
/*���ų���ʱ��κϼ�*/ 
char DAILY[][20] = {"9:00~10:00", "12:30~13:30", "18:30~19:30", "21:00~22:00"};
/*ѧ������ʱ��κϼ�*/
char FREE[][20] = {"9:00~11:30", "12:30~14:00", "18:30~20:00", "21:00~22:30"};
char WEEK[][5] = {"Mon", "Tues", "Wed", "Thur", "Fri", "Sat", "Sun"}; 

/*���岿��*/ 
struct Department
{
	char number[5];
	int member_limit;
	
	/*��ӦTAG��ʮ����ǩ*/
	/*1��ʾ�У�0��ʾû��*/ 
	int tags[10];
	
	/*�����߸��������ڣ�0��ʾû�У�1��ʾ��*/
	/*����Ϊ���ճ���ʱ�䣬Լ��һ������һ�Ρ����Բ��ų���ʱ��κϼ�*/
	int event_schedules[7][2];
}D[20];	

/*����ѧ��*/ 
struct Student
{
	char number[10];
	
	/*��ӦTAG��ʮ����ǩ*/
	/*1��ʾ�У�0��ʾû��*/
	int tags[10];
	
	/*��Ը�����ص��ǩ�ϼ�*/
	/*��������ѧ����Ȥ��ǩ*/ 
	int d_tags[10];
	 
	/*�����߸��������ڣ�0��ʾû�У�1��ʾ��*/
	/*����Ϊ���տ���ʱ�䣬�������������ѧ������ʱ��κϼ�*/
	int free_time[7][3];
	
	/*20�����ţ�����Ը��Ϊ1��������0*/ 
	int wanted_department[20];
	int department_count;
	int department_order[5];
}S[300]; 

int main()
{
	srand(time(0));
	
	int i, j, k, l, m;
	/*20��������Ϣ��ʼ��*/ 
	for(i = 0; i < 20; i++)
	{
		/*��ʼ�����ű��*/ 
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
		
		/*��ʼ��������������Χ[10, 15]*/
		D[i].member_limit = rand() % 6 + 10;
		/*check
		printf("%d\n", D[i].member_limit);
		*/
		
		/*��ʼ�������ص��ǩ��Լ��Ϊ4-6��*/
		j = rand() % 3 + 4;
		memset(D[i].tags, 0, sizeof(int) * 10);
		while(j > 0)
		{
			k = rand() % 10;
			if(D[i].tags[k] == 0)//�����ظ�������� 
			{
				/*����и��ص��ǩ*/ 
				D[i].tags[k] = 1;
				j--;
			}
		} 
		/*check
		for(j = 0; j < 10; j++) 
		    printf("%d", D[i].tags[j]);
		printf("\n");
		*/
		
		/*��ʼ�����ų���ʱ��*/
		/*Լ��һ������һ�Σ�ÿ�������Ĵ�*/
		memset(D[i].event_schedules, 0, sizeof(D[i].event_schedules)); 
		j = rand() % 2 + 3;
		while(j > 0)
		{		
			k = rand() % 7;
			if (D[i].event_schedules[k][0] == 0)//�����ظ��������
			{
				j--; 
				/*����и�����*/
				D[i].event_schedules[k][0] = 1;
				/*�Ӳ��ų���ʱ��κϼ���ѡһ��*/
				D[i].event_schedules[k][1] = rand() % 4;
			}
		} 
		/*check 
		for(j = 0; j < 7; j++) 
		    printf("%d%d\n", D[i].event_schedules[j][0], D[i].event_schedules[j][1]);
		printf("\n");
		*/		
	}
	
	/*ѧ����Ϣ��ʼ��*/  
	for(i = 0; i < 300; i++)
	{
		/*��ʼ��ѧ�����*/ 
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
		
		/*��ʼ����Ը���ţ���Χ[1, 5]*/
		S[i].department_count = rand() % 5 + 1;	 
		memset(S[i].wanted_department, 0, sizeof(int) * 20);
		memset(S[i].d_tags, 0, sizeof(int) * 10);
		memset(S[i].department_order, 0, sizeof(int) * 5);	
		for(j = 0; j < S[i].department_count; )
		{
			k = rand() % 20;//20��������� 
			if(S[i].wanted_department[k] == 0)//�����ظ� 
			{
				S[i].department_order[j++] = k;
				S[i].wanted_department[k] = 1;
				/*��ʼ����Ը���ű�ǩ�ϼ�*/
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
		
		/*��ʼ����Ȥ��ǩ*/
		/*Լ��3-4������d_tags�����ȡ*/
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
		
		/*��ʼ������ʱ���*/
		/*һ����������*/
		/*ÿ���������ʱ���*/ 
		memset(S[i].free_time, 0, sizeof(S[i].free_time)); 
		j = rand() % 2 + 3;
		while(j > 0)
		{		
			k = rand() % 7;
			if (S[i].free_time[k][0] == 0)//�����ظ��������
			{
				j--; 
				/*����и�����*/
				S[i].free_time[k][0] = 1;
				/*�ӿ���ʱ��κϼ���ѡ����*/
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
