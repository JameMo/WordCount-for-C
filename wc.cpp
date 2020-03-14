#include<stdio.h>
#include<string.h>
#include<io.h>

void char_num(char *file)
{
	//查询file.c文件中字符数目的函数 
	int num = 0;
	FILE *f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)
	{	
		while((a = fgetc(f))!=EOF)
		{	
			//避开空格、换行、Tab字符 
			if(a!=' ' && a!='\n' && a!='\t')
				num++;
		}
	}
	else
	{
		printf("this file does not exist.\n");
	}
	fclose(f);
	printf("char_num:%d\n",num);
}


void word_num(char *file)
{
	//查询file.c文件中单词数目的函数
	int num = 0,flag;
	FILE *f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)
	{
		while(!feof(f))
		{
			a = fgetc(f);
			//判断字符是否为大小写字母 
			if((a<='z'&&a>='a')||(a<='Z'&&a>='A'))
				flag = 1;
			//计算单词数目 
			else if(flag)
			{
				num++;
				flag = 0;	
			}			
		}
	 } 
	 else
	 {
		printf("this file does not exist.\n"); 	
	 }
	 fclose(f);
	 printf("word_num:%d\n",num);
 } 
 
 
void line_num(char *file)
{
	//查询file.c文件中行数的函数
	int num = 1;
	FILE *f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)	
	{
		while(!feof(f))
		{
			a = fgetc(f);
			//换行符为计数标志 
			if(a=='\n')
				num++;
		}	
	}
	else
	{
		printf("this file does not exist.\n"); 
	} 
	fclose(f);
	printf("line_num:%d\n",num);
}
 

void blankline_num(char *file)
{
	//查询file.c文件中空行数的函数
	int num = 0,count = 0,flag;
	FILE *f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)	
	{
		while(!feof(f))
		{
			a = fgetc(f);
			//换行时进行判断 
			if(a=='\n')
			{
				//字符少于、等于1和不为注释行时进行计数 
				if(count<=1&&flag!=2)
					num++;
				count = 0;
			}
			else if(a!='\t'&&a!=' '&&a!='/')
				count++;
			else if(a=='/')
				flag++;
		}	
	}
	else
	{
		printf("this file does not exist.\n"); 
	} 
	fclose(f);
	printf("blankline_num:%d\n",num);	
}


void codeline_num(char *file)
{
	//查询file.c文件中代码行数的函数
	int num = 0,count = 0,flag = 0;
	FILE *f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)	
	{
		while(!feof(f))
		{
			a = fgetc(f);
			//先作字符分类，再进行判断 
			if(a!=' '&&a!='\t'&&a!='\n'&&a!='/')
				count++;
			else if(a=='\n')
			{
				if(count>1&&flag!=2)
					num++;
				count = 0;
			}
			else if(a=='/')
			{
				flag++;
			} 
		}	
	}
	else
	{
		printf("this file does not exist.\n"); 
	} 
	fclose(f);
	printf("codeline_num:%d\n",num);	
}


void commentline_num(char *file)
{
	//查询file.c文件中注释行数的函数
	int num = 0,flag = 0;
	FILE* f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)
	{
		while(!feof(f))
		{
			a = fgetc(f);
			//换行时标志归零 
			if(a=='\n')
			{
				flag = 0;
			}
			//对注释符进行计数 
			else if(a=='/')
			{
				flag++;
				if(flag==2)
					num++;
			}
		}
	}
	else
	{
		printf("this file does not exist.\n");
	}
	fclose(f);
	printf("commentline_num:%d\n",num);
}


char *fun(char *c1,char *c2)
{	
	//将两个字符串进行连接 
	int i,j;
	char *ch;
	for(i=0;c1[i]!='*';i++)
	{
		ch[i]=c1[i];
	}
	for(j=0;c2[j]!='\0';j++,i++)
	{
		ch[i]=c2[j];
	}
	ch[i]='\0';
	return ch;	
}	


void traverse_all(char *file_folder)
{	
	//文件夹内所有*.c文件的所有信息 
	long handle;
	char *ch;
	struct _finddata_t fileinfo;
	handle = _findfirst(file_folder,&fileinfo);
	if(handle==-1L)
		return;
	do
	{
		printf("file name:%s\n",fileinfo.name);
		ch = fun(file_folder,fileinfo.name);
		char_num(ch);
		word_num(ch);
		line_num(ch);
		blankline_num(ch);
		codeline_num(ch);
		commentline_num(ch);
	}while(!_findnext(handle,&fileinfo));	
}


int main(int a,char* arg[])
{
	//运行wc.exe的主函数。
	FILE *f;
	while(1)
	{	
		//判断文件是否存在
		//对文件作不同的处理 
		if((f=fopen(arg[2],"r"))==NULL)
		{
			if(!strcmp("-s",arg[1]))
			{
				traverse_all(arg[2]);	
			}
			else
			{
				printf("NO FILE NOW\n\n");
				scanf("%s%s%s",arg[0],arg[1],arg[2]);
				continue;
			}	
		}
		else if(!strcmp("-c",arg[1]))
		{
			char_num(arg[2]);
		}
		else if(!strcmp("-w",arg[1]))
		{
			word_num(arg[2]);
		}
		else if(!strcmp("-l",arg[1]))
		{
			char_num(arg[2]);
		}
		else if(!strcmp("-a",arg[1]))
		{
			blankline_num(arg[2]);
			codeline_num(arg[2]);
			commentline_num(arg[2]);
		}
		else
		{
			printf("Out of specification\n\n");
		}
		scanf("%s%s%s",arg[0],arg[1],arg[2]);
	}
	return 0;
}


