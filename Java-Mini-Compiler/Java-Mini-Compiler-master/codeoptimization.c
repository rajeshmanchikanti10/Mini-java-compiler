#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct SymTable
{
    char idName[50];
    int value;
    int type;  //0-int , 1-float , 2-true , 3-false
    int line_no;
    int scope;
};

struct OPT
{
	char op[10];
	char arg1[10];
	char arg2[10];
	char result[10];
};

struct mappping{
	char ext[100];
	char ori[100];
	}map[100];


int symcount=0;
int optcount=0,finaloptcount;
FILE *fp,*fp1;
struct OPT OPT[100];
struct SymTable sy[50];


int isDigit(char t[100])
{
	//printf("inside digit %s\n",t);
	if(t!=NULL)
	{
		int check=atoi(t);
		//printf("value of check %s for %d\n",t,check);
		if(check==0)
			return 1;
		else
			return 0;
	}
	return 1;
}




int findinSymbolTable(char key[])
{
	for(int i=0;i<symcount;i++)
	{
		if(strcmp(key,sy[i].idName)==0)
			return sy[i].value;
	}
	return -1;
}



void my_itoa(int num, char temp1[20])
{
	sprintf(temp1,"%d",num);
	//return temp1;
}



void constant_propagation()
{
int i;
for(int i=0;i<optcount;i++)
{
	if(isDigit(OPT[i].arg1)==1)
	{	
		int value=findinSymbolTable(OPT[i].arg1);
		if(value!=-1)
		{
		sprintf(OPT[i].arg1,"%d",value);
		//printf("line number %d\n",i);
		}
	}
	if(isDigit(OPT[i].arg2)==1)
	{
		int value=findinSymbolTable(OPT[i].arg2);
		//printf("%d\n",value);
		if(value!=-1)
		{
		sprintf(OPT[i].arg2,"%d",value);
		//printf("line number %d\n",i);
		}
	}12
}



	//printf("the value of ind %d\n",ind);
	printf("\n--------------------------------------------------------\n");
	printf("\nOPTIMIZED INTERMEDIATE CODE\n\n");
	printf("--------------------------------------------------------\n");
	printf("--------------------------------------------------------\n");
	printf("\n%17s%10s%10s%10s%10s","post","op","arg1","arg2","result\n");
	printf("--------------------------------------------------------\n");
	
	for(i=0;i<finaloptcount;i++)
	{
		printf("\n%15d%10s%10s%10s%10s", i,OPT[i].op, OPT[i].arg1,OPT[i].arg2,OPT[i].result);
	}
	printf("\n\t\t -----------------------");
	printf("\n");


}



int counter=0;
void constant_folding()
{
	//printf("inside \n");	
	int i=0;
	int flag=0;
	int temp;
	char temp1[10];
	for(i=0;i<optcount;i++)
	{
		char s[100];
		char s1[100];
		strcpy(s,OPT[i].arg1);	
		strcpy(s1,OPT[i].arg2);
		flag=isDigit(s);
		if(flag==1)
		{
			continue;
			//printf("fail\n");
		}
		else
		{
			flag=isDigit(s1);
			if(flag==1)
			{
				continue;
			}
			else
			{
				//printf("both are number %d\n",i);
				char a= OPT[i].op[0];
				//printf("a value is %c\n",a);
				switch(a)
				{
					case '+': 
				//		  printf("inside the case %d \n",i);
						  temp = atoi(s) + atoi(s1);
				//		  printf("value of temp %d\n",temp);
						  my_itoa(temp,temp1);
				//		  printf("value of temp1 %s\n",temp1);
						  strcpy(OPT[i].arg1,temp1);
					          strcpy(OPT[i].op,"=");
						  strcpy(OPT[i].arg2,"");
						  break;
					case '-': 
				//		  printf("inside the case %d \n",i);
						  temp = atoi(s) - atoi(s1);
				//		  printf("value of temp %d\n",temp);
						  my_itoa(temp,temp1);
				//		  printf("value of temp1 %s\n",temp1);
						  strcpy(OPT[i].arg1,temp1);
					          strcpy(OPT[i].op,"=");
						  strcpy(OPT[i].arg2,"");
						  break;
					case '/':
						//printf("inside the case %d \n",i);
						  temp = atoi(s)/atoi(s1);
				//		  printf("value of temp %d\n",temp);
						  my_itoa(temp,temp1);
				//		  printf("value of temp1 %s\n",temp1);
						  strcpy(OPT[i].arg1,temp1);
					          strcpy(OPT[i].op,"=");
						  strcpy(OPT[i].arg2,"");
						  break;
					case '*':
						//printf("inside the case %d \n",i);
						  temp = atoi(s)*atoi(s1);
				//		  printf("value of temp %d\n",temp);
						  my_itoa(temp,temp1);
				//		  printf("value of temp1 %s\n",temp1);
						  strcpy(OPT[i].arg1,temp1);
					          strcpy(OPT[i].op,"=");
						  strcpy(OPT[i].arg2,"");
						  break;
						
						
				}
				char b= OPT[i+1].op[0];
				//printf("hello1 %c\n",b);
		
				if(b=='=')
				{
					 strcpy(OPT[i].result,OPT[i+1].result);
					 int j=0;
                  			 for(j=i+1;j<optcount;j++)
					{
							OPT[j]=OPT[j+1];
					}
					optcount--;
					//tIndex--;
					counter+=1;
					
				}
				else
				{
					int k;
					strcpy(OPT[i+1].arg1,OPT[i].arg1);
					for(k=i+1;k<optcount;k++)
					{
							OPT[k-1]=OPT[k];
					}
					optcount--;
					//tIndex--;
					i=i-1;
					counter+=1;
					
				}
		
			}
		}		
		flag=0;
		//printf("so m3 \n");	
	}

	//printf("the value of ind %d\n",ind);
	printf("\n--------------------------------------------------------\n");
	printf("\nOPTIMIZED INTERMEDIATE CODE\n\n");
	printf("--------------------------------------------------------\n");
	printf("--------------------------------------------------------\n");
	printf("\n%17s%10s%10s%10s%10s","post","op","arg1","arg2","result\n");
	printf("--------------------------------------------------------\n");
	
	for(i=0;i<finaloptcount;i++)
	{
		printf("\n%15d%10s%10s%10s%10s", i,OPT[i].op, OPT[i].arg1,OPT[i].arg2,OPT[i].result);
	}
	printf("\n\t\t -----------------------");
	printf("\n");
}


void copy_prop()
{
	int i=0;
	int k =0;
	int flag=0;
	int temp;
	char temp1[10];
	char ext1[100];
	char ext2[100];
	optcount = finaloptcount;
	int remove[100] ;
	int cnt = 0;


	for(i=0;i<optcount;i++)
	{
		
		char a= OPT[i].op[0];
		
		if(a =='=')
		{
		strcpy(map[k].ext,OPT[i].result);	
		strcpy(map[k].ori,OPT[i].arg1);
		k++;
		}
		
	}




	for(i=0;i<optcount;i++)
	{
		char a= OPT[i].op[0];
		

		strcpy(ext1,OPT[i].arg1);
		int check = isDigit(ext1);
		//printf("%s , a is %c Is digit %d \n" ,ext1 , a ,  check);
		int ach = strncmp(ext1, "t" , 1) ; 
		if(check == 1 && a=='=' &&  ach!=0 )
		{	
			remove[cnt] = i;
			cnt++;
		}

		else{
			strcpy(ext1,OPT[i].arg1);	
			strcpy(ext2,OPT[i].arg2);
			for(int j=0;j<k;j++)
			{
			if(strcmp(ext1, map[j].ext)==0)
				strcpy(OPT[i].arg1 , map[j].ori);
			if(strcmp(ext2, map[j].ext)==0)
				strcpy(OPT[i].arg2 , map[j].ori);
			}
	     	   }
	}


	for(int m=0; m<cnt ;m++)
	{	
		printf("%d \n" , remove[m]);		
		for (int x = remove[m]-m ; x <  optcount - 1; x++)
		{
			OPT[x] = OPT[x + 1];
			
		}
		finaloptcount= finaloptcount -1;
	}
	

	//printf("the value of ind %d\n",ind);
	printf("\n--------------------------------------------------------\n");
	printf("\nOPTIMIZED INTERMEDIATE CODE\n\n");
	printf("--------------------------------------------------------\n");
	printf("--------------------------------------------------------\n");
	printf("\n%17s%10s%10s%10s%10s","post","op","arg1","arg2","result\n");
	printf("--------------------------------------------------------\n");
	
	for(i=0;i<finaloptcount;i++)
	{
		printf("\n%15d%10s%10s%10s%10s", i,OPT[i].op, OPT[i].arg1,OPT[i].arg2,OPT[i].result);
	}
	printf("\n\t\t -----------------------");
	printf("\n");

}






int main()
{
fp=fopen("im.txt","r");
fp1=fopen("symbletable.txt","r");
int i;


/*reading optimized code*/
while(fread(&OPT[optcount],sizeof(struct OPT),1,fp))
{
optcount++;
}


finaloptcount=optcount;
for(i=0;i<optcount;i++)
	printf("\n%15d%10s%10s%10s%10s", i,OPT[i].op, OPT[i].arg1,OPT[i].arg2,OPT[i].result);

	printf("\n\t\t -----------------------");
	printf("\n");
	
	
/*reading symbol table*/

while(fread(&sy[symcount],sizeof(struct SymTable),1,fp1))
{
symcount++;
}

printf("\n\t\tAfter copy propagation\n");
copy_prop();

printf("\n\t\t -----------------------");
printf("\n");

printf("\n\t\t After constant propagation\n");
constant_propagation();

printf("\n\t\t -----------------------");
printf("\n");

printf("\n\t\t After constant_folding\n");
constant_folding();


	






return 0;
}
