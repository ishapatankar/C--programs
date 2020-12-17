#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct MNT 
{
	char mname[20];
	int PP,KP,MDTP,KPDTP;
}mnt[5];

struct KPDT 
{
	char pname[15],Def[15];
}kpdt[15];

struct MDT 
{
char opcode[15],value[35];
}mdt[30];


char PNT[15][15],APT[10][15],fn[30];
int MDT_Ptr=0,MNT_Ptr=0,KPDT_Ptr=0,PNT_Ptr=0,APT_Ptr=0,MEC=0,n=0;
char Buffer[80], t1[35], t2[35], t3[35];
char temp[40], temp1[40], temp2[40], temp3[40];
FILE *fp;

main(int argc, char *argv[])
{
	int i,j,k;
	if(argc==2)
		strcpy(fn,argv[1]);
	else
	{
		printf("Enter filename\t");
		scanf("%s",fn);
	}
	
	fp=fopen(fn,"r");
	if(fp==NULL)
	{
		printf("File not found");
	}
	else
	{
		while(fgets(Buffer,80,fp))
	 	{
			if(feof(fp))
				break;
			n=sscanf(Buffer,"%s %s %s",t1,t2,t3); 

			if((n==1) && (strcasecmp(t1,"MACRO")==0))
	 		{
				fgets(Buffer,80,fp);
				n=sscanf(Buffer,"%s %s",t1,t2);
				if(searchmnt(t1)==-1)
				{
					strcpy(mnt[MNT_Ptr].mname,t1);
					mnt[MNT_Ptr].KPDTP = KPDT_Ptr;
	 				mnt[MNT_Ptr].MDTP = MDT_Ptr;

					Make_KPDT_PNT(t2);
				}
		 		else if((strcasecmp(t1,"MEND")==0) && n==1)
	 			{
	 				strcpy(mdt[MDT_Ptr].opcode,"MEND");
					strcpy(mdt[MDT_Ptr++].value," ");
	 				MNT_Ptr++;
	 				PNT_Ptr = 0;
	 			}
			}
			else if(t2[0]=='&')
	 		{
				t2[strlen(t2)]='\0';
				k = searchpnt(t2+1);
				if(k==-1)
				{
					 printf("\n1Error: Parameter %s not found",t2+1);
					 exit(0);
				}
				sprintf(temp,"(P,%d)",k);
				k = searchpnt(t3+1);
				if(k==-1)
				{
					printf("\n2Error: Parameter %s not found",t3+1);
					exit(0);
				}	
				sprintf(temp1,"%s (P,%d)",temp,k);
				strcpy(mdt[MDT_Ptr].opcode,t1);
				strcpy(mdt[MDT_Ptr++].value,temp1);
			}
			else
			{
				k = searchmnt(t1);
				if(k==-1)
					printf("%s",Buffer);
				else
				{
					i=j=APT_Ptr=0;
					strcat(t2,",");
					while(t2[j])
					{
						if(t2[j]==',')
						{
						 	temp[i]='\0';
						 	i=0;

							strcpy(APT[APT_Ptr++],temp);
						 }
						 else
						 	temp[i++] = t2[j];
						 	j++;
					}
					if(APT_Ptr!=mnt[k].PP)
					{
						 printf("\nPosition Parameters Missing");
						 exit(0);
					}
					if(mnt[k].KP !=0)
					{
						for(i=mnt[k].KPDTP;i<=(mnt[k].KPDTP+mnt[k].KP);i++)
						{
							strcpy(APT[APT_Ptr++],kpdt[i].Def);
						}

					}
					Expand(k);
				}
			}
		}
	}
	
		Print_MNT();
		Print_PNT();
		Print_KPDT();
		Print_MDT();
		Print_APT();
		fclose(fp);
		
}	

//function to serach in Macro Name table
int searchmnt(char *s)
{
	int m;
	for (m=0;m<=MNT_Ptr;m++)
	{
		if(strcmp(s,mnt[m].mname)==0)
			return(m);
	}
	return(-1);
}	
//function to search Parameter Name table
int searchpnt(char *s)
{
	int m;
	for (m=0;m<=PNT_Ptr;m++)
	{
		if(strcmp(PNT[m],s)==0)
			return(m);
	}
	return(-1);
}
Print_MNT()
{
	int i;
	printf("\nMacro name table");
	printf("\nMname\tPP\tKP\tMDTP\tKPDTP\n");
	for(i=0;i<=MNT_Ptr;i++)
	{
		printf("%s\t%d\t%d\t%d\t%d\n",mnt[i].mname,mnt[i].PP,mnt[i].KP,mnt[i].MDTP,mnt[i].KPDTP);
	}
}

Print_PNT()
{
	int i;
	printf("\nparameter name table");
	printf("\npname");
	for(i=0;i<=PNT_Ptr;i++)
	{
		printf("\n%s",PNT[i]);
	}
}
Print_KPDT() 
{
	int i;
	printf("\nKeyword parameter ");
	printf("\nPname\tDef\n");
	for(i=0;i<=KPDT_Ptr;i++)
	{
		printf("%s\t%s\n",kpdt[i].pname,kpdt[i].Def);
	}
}
Print_MDT() 
{
	int i;
	printf("\nMacro definition table");
	printf("\nOpcode\tValue\n");
	for(i=0;i<=MDT_Ptr;i++)
	{
		printf("%s\t%s\n",mdt[i].opcode,mdt[i].value);
	}
}
Print_APT() 
{
	int i;
	printf("\nActual parameter table");
	printf("\nName");
	for(i=0;i<=APT_Ptr;i++)
	{
		printf("\n%s",APT[i]);
	}
}
//function to add parameters to KPDT and PNT
Make_KPDT_PNT(char *s)
{
	int i=0,j=0,k=0;
	strcat(s,",");
	while(*s && *s!='=')
	{
		if(*s==',')
		{
			temp[i]='\0';
			j++;
			i=0;
			k = searchpnt(temp);
			if(k==-1)
				strcpy(PNT[PNT_Ptr++],temp);
			else
			{
				printf("\nError: Multiple Declaration of Symbol %s in Argument List",temp);
				exit(0);
			}
		}
		else if(*s!='&')
		temp[i++]=*s;
		s++;
		
	}
		mnt[MNT_Ptr].PP = j;
		j=0;

		while(*s)
		{
			if(*s=='=')
			{
				temp[i]='\0';
				i=0;
				k = searchpnt(temp);
				if(k==-1)
				{
					strcpy(PNT[PNT_Ptr++],temp);
					strcpy(kpdt[KPDT_Ptr].pname,temp);
				}
				else
				{
					printf("\nError: Multiple Declaration of Symbol %s in Argument List",temp);
				 	exit(0);
				}
			}
			else if(*s==',')
			{
				temp[i]='\0';
				j++;
				i=0;
				strcpy(kpdt[KPDT_Ptr++].Def,temp);
			}
			else if(*s!='&')
			temp[i++]=*s;
			s++;
		}
		mnt[MNT_Ptr].KP = j;
}
Expand(int n)
{
	int a;
 	MEC = mnt[n].MDTP;
	while(strcmp(mdt[MEC].opcode,"MEND")!=0)
 	{
		sscanf(mdt[MEC].value,"%s %s",t1,t2);
		t1[strlen(t1)]='\0';
		a = atoi(strstr(t1,",")+1);
		sprintf(temp1,"%s",APT[a]);
		t2[strlen(t2)]='\0';
		a = atoi(strstr(t2,",")+1);
		sprintf(temp,"%s %s",temp1,APT[a]);
		printf("+%s\t%s\n",mdt[MEC].opcode,temp);
		 MEC++;
	 }
}
