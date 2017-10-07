#include <stdio.h>                                                                                            
#include "cJSON.h"

int main()
{
	const char *student[]={"031502004","031502293","031502006","031502294"};
	const char *member[]={"031502004","031502293","031502006","031502294"};
	const char *department_no[] = {"D001","D002","D003","D004"};  
	const char *unlucky_department[] = {"D005","D006","D007","D008"};
    cJSON * admitted =  cJSON_CreateObject();
    cJSON * department =  cJSON_CreateObject();
    cJSON * unlucky_student =  cJSON_CreateObject();
	cJSON * root =  cJSON_CreateObject();
    cJSON * item =  cJSON_CreateObject();

    cJSON_AddItemToObject(root, "unlucky_student", unlucky_student=cJSON_CreateArray());
    for(int i = 0; i < 4; i++) { 
	cJSON_AddItemToArray(unlucky_student,cJSON_CreateString(student[i])); 
	}  
	
    cJSON_AddItemToObject(root, "admitted", admitted=cJSON_CreateArray());
    for(int i = 0; i < 4; i++) {   
	cJSON_AddItemToArray(admitted, item = cJSON_CreateObject()); 
	cJSON_AddItemToObject(item, "member", cJSON_CreateString(member[i])); 
	cJSON_AddItemToObject(item, "department_no", cJSON_CreateString(department_no[i])); 
	}  
	
    cJSON_AddItemToObject(root, "unlucky_department", department=cJSON_CreateArray());
    for(int i = 0; i < 4; i++) {  
	cJSON_AddItemToArray(department,cJSON_CreateString(unlucky_department[i])); 
	} 

    printf("%s\n", cJSON_Print(root));
    return 0;
}
