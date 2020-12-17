#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *mne[15]={"STOP","ADD","SUB","MUL","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT","DC","DS","START","END"};
char *reg[4]={"AREG","BREG","CREG","DREG"};
char *cc[6]={"LT","LE","EQ","GT","GE","ANY"};


struct symtab
{
	char symbol[20];
	int add,len,value;
	int used,declared;
}sym[50];

struct ictab
{
	int addr;
	int opcode;
	int regop;
	char optype;
	int value;
}ic[50];

struct errtab
{
	int lineno;
	char desc[80];
}e[50];

char f[30];
int pc=0,i,j;
char variant[50][50];
int ecnt=0,symcnt=0,varcnt=0;
main(int argc,char *argv[])
{	
	FILE *fp;
	char instr[30],t1[10],t2[10],t3[10],t4[10];
	int n,mresult,symresult,result;
	
	if(argc==2)
		strcpy(f,argv[1]);
	else 
	{
		printf("\nenter file name");
		scanf("%s",f);
	}
		
	fp=fopen(f,"r");
	if(fp==NULL)
	{
		printf("\nfile not found");
	}	
	else
	{				
		pc=0;
		while(!feof(fp))
		{	
			fgets(instr,30,fp);
			if(feof(fp))
				break;
			n=sscanf(instr,"%s %s %s %s",t1,t2,t3,t4);
			if(n==1)
			{
				mresult=searchmne(t1);
				if(mresult==-1)	
				{
					e[ecnt++].lineno=pc;
					strcpy(e[ecnt].desc,"Invalid mnemonic");			
					printf("\nInvalid mnemonic");
				}

				else if(mresult==14 || mresult==13 || mresult == 0)
				{

						if(mresult==14)
							sprintf(variant[varcnt++],"%s","IS 00");
						
						else if(mresult==13)
							sprintf(variant[varcnt++],"%s","AD 01");
							
						else
							sprintf(variant[varcnt++],"%s","IS 0");
				}
				else
				{
					e[ecnt++].lineno=pc;
					strcpy(e[ecnt].desc,"Invalid");
					printf("Invalid");
				}
			
			} //end of if
				
		
			if(n==2)
			{
				mresult=searchmne(t1);
				if(mresult==9 || mresult==10)
				{
					if(searchmne(t2)!=-1 || searchcc(t2)!=-1 || searchreg(t2)!=-1)
					{
						printf("\nInvalid symbol\n");
						e[ecnt++].lineno=pc;
						strcpy(e[ecnt].desc,"Invalid symbol");
					}
					else
					{
						symresult=searchsymbol(t2);
						if(symresult==-1)
						{
							sym[symcnt].add=pc;
							symresult=symcnt;		
							strcpy(sym[symcnt].symbol,t2);
							sym[symcnt++].used=1;
						}
						else
							sym[symresult].used=1;
							sprintf(variant[varcnt++],"IS %d S %d",mresult, symresult);
						
					}
				}
				if(mresult==13)
				{
					pc=atoi(t2)-1;
					sprintf(variant[varcnt++],"AD 01 C %d",pc+1);				
				}
				if(mresult==14)
				{
					symresult=searchsymbol(t2);
				
					if(symresult==-1)
					{	
						symresult=symcnt;
						sym[symcnt].add=pc;		
						strcpy(sym[symcnt].symbol,t2);
						sym[symcnt++].declared=1;
					}
					else
					{	
						
						sym[symresult].used=1;
						
					}
					sprintf(variant[varcnt++],"AD 02 S %d",symresult);
				}
				
				mresult=searchmne(t2);
				if(mresult==0)
				{
					if(searchmne(t2)!=-1 || searchcc(t2)!=-1 || searchreg(t2)!=-1)
					{
						printf("\nInvalid symbol");
						e[ecnt++].lineno=pc;
						strcpy(e[ecnt].desc,"Invalid symbol");
					}	
					else
					{
						symresult=searchsymbol(t1);
						if(symresult==-1)
						{	
							symresult=symcnt;		
							strcpy(sym[symcnt].symbol,t1);
							sym[symcnt++].add=pc;
						}
						else
							sym[symcnt++].add=pc;
							sprintf(variant[varcnt++],"IS %d S %d",mresult,symresult);
					}
				}
				
			}//end of if

			if(n==3)
			{
				mresult=searchmne(t1);

				if(mresult>=1 && mresult<=8)
				{
					if(mresult==7)
					{
						result=searchcc(t2);
						if(result==-1)
						{
							printf("\nInvalid condition code");
							
						}
					}
					
					if(mresult!=7)
					{					
						result=searchreg(t2);
						if(result==-1)
							printf("\nInvalid reg");
					}
					symresult=searchsymbol(t3);
					if(symresult==-1)
					{
						symresult=symcnt;		
						strcpy(sym[symcnt].symbol,t3);
						sym[symcnt++].used=1;
					}
					else
					{
						sym[symresult].used=1;
						
					}
					sprintf(variant[varcnt++],"IS %d %d S %d",mresult,result,symresult);
				}
	
				else if((mresult = searchmne(t2))==10 || (mresult = searchmne(t2))==9)
				{
					symresult=searchsymbol(t1);
					if(symresult==-1)
					{
						symresult=symcnt;		
						strcpy(sym[symcnt].symbol,t1);
						sym[symcnt].declared=1;
						sym[symcnt++].add=pc;
					}
					else
					{
						sym[symcnt].declared=1;
						sym[symresult].add=pc;

					}
				
					symresult=searchsymbol(t3);
					if(symresult==-1)
					{
						symresult=symcnt;
						strcpy(sym[symcnt].symbol,t3);
						sym[symcnt++].used=1;
					}
					else
					{
						sym[symresult].used=1;
						
					}
					sprintf(variant[varcnt++],"IS %d S %d",mresult,symresult);
				}
			
			else if(searchmne(t2)==11 || searchmne(t2)==12)
			{
				symresult=searchsymbol(t1);
				if(symresult==-1)
				{
					symresult=symcnt;		
					strcpy(sym[symcnt].symbol,t1);
					sym[symcnt].declared=1;
					sym[symcnt++].add=pc;
				}
				else
				{
					sym[symcnt].declared=1;
					sym[symresult].add=pc;
					
				}
				if(searchmne(t2)==11)
				{
					sym[symresult].len=1;
					sym[symresult].value=atoi(t3);
					sprintf(variant[varcnt++],"DL 1 C %d",atoi(t3));
				}
				if(searchmne(t2)==12)
				{
					sym[symresult].len=atoi(t3);
					pc=(pc+atoi(t3))-1;
					sym[symresult].value=0;
					sprintf(variant[varcnt++],"DL 2 C %d",atoi(t3));
				}
			}
			
		}//end of if

		if(n==4)
		{
			mresult=searchmne(t2);

			if(mresult>=1 && mresult<=8)
			{
				if(mresult==7)
				{
					result=searchcc(t3);
					if(result==-1)
					printf("\nInvalid condition code");
				}
					
				if(mresult!=7)
				{					
					result=searchreg(t3);
					if(result==-1)
						printf("\nInvalid reg");
				}
				symresult=searchsymbol(t1);
				if(symresult==-1)
				{
					symresult=symcnt;		
					strcpy(sym[symcnt].symbol,t1);
					sym[symcnt++].declared=1;
					sym[symresult].add=pc;
				}
				else
				{
					sym[symresult].declared=1;					
					sym[symresult].used=1;;
					
				}

				symresult=searchsymbol(t4);
				if(symresult==-1)
				{
					symresult=symcnt;		
					strcpy(sym[symcnt].symbol,t4);
					sym[symcnt].used=1;
				}
				else
				{
					sprintf(variant[varcnt++],"IS %d %d S %d",mresult,result,symresult);
				}
				sym[symresult].used=1;
			}
			else
				printf("Invalid");	
		}//end of if
			pc++;
	
		}//end of while
		printsymbol();
		if(ecnt==0)
		{
			printf("\nvariant 1");
			for(i=0;i<varcnt;i++)
			{
					printf("\n%s",variant[i]);
			}
			pass2();
		}
		else
		{
			printerr();
		}
		
	}//end of else	
	

}//end of main

pass2()
{
	int i=0,lc,token,j;
	char tok1[20],tok2[20],tok3[20],tok4[20],tok5[20];
	printf("\n\n machine code\n\n");
	while(i<varcnt)
	{
		token=sscanf(variant[i],"%s %s %s %s %s",tok1,tok2,tok3,tok4,tok5);
		switch(token)
		{
			case 2:if(strcmp(tok1,"AD")==0)
					lc--;
				else if(strcmp(tok1,"IS")==0)
					printf("%d 000000\n",lc);
				break;
			
			case 4:if(strcmp(tok1,"AD")==0)
					lc=atoi(tok4)-1;
				else if(strcmp(tok1,"IS")==0)
					printf("%d %02d0%03d\n",lc,atoi(tok2),sym[atoi(tok4)].add);
				else if(strcmp(tok1,"DL")==0)
				{
					if(atoi(tok2)==2)
					{
						for(j=0;j<atoi(tok4);j++)
							printf("%d\n",lc++);
							lc--;
					}
					else if(atoi(tok2)==1)
						printf("%d %03d\n",lc,atoi(tok4));
				}
				break;
			case 5:printf("%d %02d%d%03d\n",lc,atoi(tok2),atoi(tok3),sym[atoi(tok5)].add);
				break;				
		}
	lc++;
	i++;
	}

}

int searchmne(char t1[])
{
	int i;
	for(i=0;i<15;i++)
	{
		if(strcasecmp(t1,mne[i])==0)
		return i;
	}
	return -1;
}

int searchcc(char t2[])
{
	int i;
	for(i=0;i<6;i++)
	{
		if(strcasecmp(t2,cc[i])==0)
		return i+1;
	}
	return -1;
} 
int searchreg(char t2[])
{
	int i;
	for(i=0;i<4;i++)
	{
		if(strcasecmp(t2,reg[i])==0)
		return i+1;
	}
	return -1;
} 
int searchsymbol(char t2[])
{
	int i;
	for(i=0;i<symcnt;i++)
	{
		if(strcasecmp(t2,sym[i].symbol)==0)
		return i;
		
	}
	return -1;
} 

printsymbol()
{
	int i;
	printf("\nSymbol table");
	if((sym[symcnt].declared==1) && (sym[symcnt].used==0))
		printf("WARNING: Symbol is defined but not used");

	if((sym[symcnt].declared==0) && (sym[symcnt].used==1))
		printf("WARNING: Symbol is used but not defined");

	printf("\nSymbol\taddress\tlength\tvalue");
	for(i=0;i<symcnt;i++)
	{
		printf("\n%s\t   %d\t    %d\t    %d\n",sym[i].symbol,sym[i].add,sym[i].len,sym[i].value);
	}
} 

printerr()
{
	int i;
	
	for(i=0;i<varcnt;i++)
	{	
		printf("\n%d\t %s",e[i].lineno,e[i].desc);
	}
}


/*printictab()
{
	int i;
	printf("\nIC table");
	printf("\nAddress\topcode\tregop\toptype\tvalue");
	for(i=0;i<iccnt;i++)
	{
		printf("\n%d \t%d \t%d \t%d \t%d\n",ic[i].addr,ic[i].opcode,ic[i].regop,ic[i].optype,ic[i].value);
	} 
}*/
