#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
int map[9][9]={0};
int num,i,j,k,number;
char str[11][30],c; 
FILE *fp1,*fp2; 
bool isPlace(int count){
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
//同一小格
int tempRow = row / 3 * 3;
int tempCol = col / 3 * 3;
for(j = tempRow; j < tempRow + 3;++j){
for(int k = tempCol; k < tempCol + 3; ++k){
if(map[j][k] == map[row][col] && j != row && k != col){
return false;
}
}
}
return true;
}
void backtrace(int count,int max) //count表示回溯层数  max表示输出终局个数 
{
	if(num>=max)
	{
	    return;
	    printf("js\n");
	}
    else if(count==81&&num<max)
	{
		printf("sc\n");
        for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
		{
	        if(j==8)
            fprintf(fp1,"%d\n",map[i][j]);
            else
            fprintf(fp1,"%d ",map[i][j]);
        }
        printf("wc\n");
        fprintf(fp1,"\n");
        num++;
        return;
    }
    int row = count / 9;
    int col = count % 9;
    if(map[row][col]==0)
    {
        for(int i = 1; i <= 9; ++i)
	    {
            map[row][col] = i;//赋值
            if(isPlace(count))//可以放
            backtrace(count+1,max);//进入下一层 
        }
        map[row][col] = 0;//回溯
    }
    else
    backtrace(count+1,max);
}
void read_solve(char s[])
{
	if((fp2=fopen(s,"r"))==NULL)
	{
		printf("无法打开残局输入文件\n");
		return ;
	}
	while(1)  //挨个读取残局 
	{
		for(i=0;i<9;i++) 
		{
			for(j=0;j<9;j++)
			{
				fscanf(fp2,"%d",&map[i][j]);
				printf("%d",map[i][j]);
			}
		}
		fgetc(fp2);
		if(feof(fp2)!=0)
		{
			num=0;
		    backtrace(0,1);
			break;
		}
		else 
		{
			num=0;
		    backtrace(0,1);
		}
	} 
	fclose(fp2);
	return;
}
int main(int argc,char *argv[])
{
	if((fp1=fopen("sudoku.txt","w"))==NULL)
	{
		printf("无法打开生成终局文件\n");
		return 0;
	}
	if(argc==3&&strcmp("-s",argv[1])==0)
	{
		read_solve(argv[2]);
		fclose(fp1);
	}
    else if(argc==3&&strcmp("-c",argv[1])==0)
    {
    	for(i=0;i<strlen(argv[2]);i++)
		{
			if(argv[2][i]>='0'&&argv[2][i]<='9') number=number*10+(argv[2][i]-'0');
			else
			{
				printf("参数格式不正确\n");
				number=0;
				break;
			}
		}
    	map[0][0]=9;
    	num=0;
    	backtrace(0,number);
    	fclose(fp1);
    }
    else
  	printf("参数格式不正确\n");
    return 0;
}

