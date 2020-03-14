#include<stdio.h>
#include<string.h>
#include<io.h>

void char_num(char *file)
{
	//��ѯfile.c�ļ����ַ���Ŀ�ĺ��� 
	int num = 0;
	FILE *f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)
	{	
		while((a = fgetc(f))!=EOF)
		{	
			//�ܿ��ո񡢻��С�Tab�ַ� 
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
	//��ѯfile.c�ļ��е�����Ŀ�ĺ���
	int num = 0,flag;
	FILE *f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)
	{
		while(!feof(f))
		{
			a = fgetc(f);
			//�ж��ַ��Ƿ�Ϊ��Сд��ĸ 
			if((a<='z'&&a>='a')||(a<='Z'&&a>='A'))
				flag = 1;
			//���㵥����Ŀ 
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
	//��ѯfile.c�ļ��������ĺ���
	int num = 1;
	FILE *f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)	
	{
		while(!feof(f))
		{
			a = fgetc(f);
			//���з�Ϊ������־ 
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
	//��ѯfile.c�ļ��п������ĺ���
	int num = 0,count = 0,flag;
	FILE *f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)	
	{
		while(!feof(f))
		{
			a = fgetc(f);
			//����ʱ�����ж� 
			if(a=='\n')
			{
				//�ַ����ڡ�����1�Ͳ�Ϊע����ʱ���м��� 
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
	//��ѯfile.c�ļ��д��������ĺ���
	int num = 0,count = 0,flag = 0;
	FILE *f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)	
	{
		while(!feof(f))
		{
			a = fgetc(f);
			//�����ַ����࣬�ٽ����ж� 
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
	//��ѯfile.c�ļ���ע�������ĺ���
	int num = 0,flag = 0;
	FILE* f;
	char a;
	f = fopen(file,"r");
	if(f!=NULL)
	{
		while(!feof(f))
		{
			a = fgetc(f);
			//����ʱ��־���� 
			if(a=='\n')
			{
				flag = 0;
			}
			//��ע�ͷ����м��� 
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
	//�������ַ����������� 
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
	//�ļ���������*.c�ļ���������Ϣ 
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
	//����wc.exe����������
	FILE *f;
	while(1)
	{	
		//�ж��ļ��Ƿ����
		//���ļ�����ͬ�Ĵ��� 
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


