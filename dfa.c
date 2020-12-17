#include<stdio.h>
#include<stdlib.h>
int nos,inis,nofs,nosym;
int final[10],tt[10][10];
char sym[10];
getpos(char c)
{
	int i;
	for(i=0;i<nosym;i++)
	{
		if(sym[i]==c)
			return i;
	}
	return -1;
}

finals(int cr)
{
	int i;
	for(i=0;i<nos;i++)
	{
		if(cr==final[i])
			return 1;
	}
	return -1;
}
void main()
{
	int ch;
	do
	{
		printf("\n1.Accept transition table\n2.Display transition table\n3.Validate\nEnter your choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:accept();
				break;
			case 2:display();
				break;
			case 3:validate();
				break;
		}
	}
	while(ch!=3);
}
accept()
{
	int i,j;
	printf("Enter total no of states\n");
	scanf("%d",&nos);
	printf("total no of final state\n");
	scanf("%d",&nofs);
	printf("Enter initial state\n");
	scanf("%d",&inis);
	printf("Enter final states\n");
	for(i=0;i<nofs;i++)
	{
		scanf("%d",&final[i]);
	}
	printf("Enter total no of symbols\n");
	scanf("%d",&nosym);
	printf("Enter symbols\n");
	for(i=0;i<nosym;i++)
	{
		scanf(" %c",&sym[i]);
	}
	
	printf("Enter transition table\n");
	for(i=0;i<nos;i++)
	{
		for(j=0;j<nosym;j++)
		{
			scanf("%d",&tt[i][j]);
		}
	}
	
}

display()
{ 	
	int i,j;
	printf("Transition table\n");
	for(i=0;i<nos;i++)
	{
		for(j=0;j<nosym;j++)
		{
			printf("%d\t",tt[i][j]);
		}
		printf("\n");
	}
}	
validate()
{
	char str[30];
	int i,curr,pos,trans[30][30],f;
	
	printf("Enter string");
		scanf("%s",str);
	curr=inis;
	for(i=0;i<str[i]!='\0';i++)
	{
		pos=getpos(str[i]);
		if(pos==-1)
		{
			printf("\nInvalid symbol");
			exit(0);
		}
		curr=trans[curr][pos];
		
	}
	f=finals(curr);
	if(f==1)
		printf("\nvalid string");
	if(f==-1)
		printf("\ninvalid string");
}

