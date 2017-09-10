#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
int map[9][9]={0};
int num=0;
ofstream fout;

bool Isvaild(int  count)
{
	int row = count / 9;  
    int col = count % 9;  
    int j;  
    //同一行  
    for(j = 0; j < 9; ++j){  
        if(map[row][j] == map[row][col] && j != col){  
            return false;  
        }  
    }  
    //同一列  
    for(j = 0; j < 9; ++j){  
        if(map[j][col] == map[row][col] && j != row){  
            return false;  
        }  
    }  
    //九宫格  
    int Row = row / 3 * 3;  
    int Col = col / 3 * 3;  
    for(j = Row; j < Row + 3;++j){  
        for(int k = Col; k < Col + 3; ++k){  
            if(map[j][k] == map[row][col] && j != row && k != col){  
                return false;  
            }  
        }  
    }  
    return true;  
}

void back(int k,int request){ 
	while(1)  
    {  
        int i = k/9;  
        int j = k%9;  
  
        while(1)  
        {  
            map[i][j]++;  
            if(map[i][j] == 10)  
            {  
                map[i][j] = 0;  
                --k;  
                break;  
            }  
            else if(Isvaild(k))  
            {  
                ++k;  
                break;  
            }  
        }  
        if(k == 81)  
        {  
            for(int i = 0; i < 9; ++i){  
	            for(int j =  0; j < 9; ++j){  
	                fout<<map[i][j]<<" ";  
	                //cout<<map[i][j]<<" ";  
	            }  
	            fout<<endl;  
	            //cout<<endl; 
	        } 
	        num++;
	        fout<<endl;
	        //cout<<endl;
            if(num >= request)  
                return;  
  
            --k;  
        }
        
    }   

}
int main(int argc,char *argv[]){
	int request;
	map[0][0]=7;
	fout.open("sudoku.txt");
	char* a = argv[1]; 
	if(!(a[0] == '-' && a[1] == 'c')){
		printf("输入不合法，请按要求输入。\n");
		return 0;
	}
	if (sscanf(argv[2], "%d", &request) == 0)
	{
		cout << "输入不合法，请按要求输入。\n" << endl;
		return 0;
	}
	back(0,request);
	fout.close();
	return 0;
}


