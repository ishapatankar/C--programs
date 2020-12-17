#include<stdio.h>
#include<stdlib.h>
int allocated[50][50],max[50][50],need[50][50],available[50];
accept_allocation(int np,int nr)
{
	int i=0,j=0;

	printf("\nEnter allocation matrix");
	for(i=0;i<np;i++)
	{
		for(j=0;j<nr;j++)
		{
			scanf("%d",&allocated[i][j]);
		}
	}
}
accept_max(int np,int nr)
{
	int i=0,j=0;

	
	printf("\nEnter max matrix");
	for(i=0;i<np;i++)
	{
		for(j=0;j<nr;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}

}

calculate_need(int np,int nr)
{
	int i=0,j=0;

	for(i=0;i<np;i++)
	{
		for(j=0;j<nr;j++)
		{
			need[i][j]=max[i][j]-allocated[i][j];	
		}
	}
	printf("\nNeed matrix is calculated");
}

available_vector(int nr)
{
	int j=0;

	printf("\nEnter available vector");
	for(j=0;j<nr;j++)
	{
		scanf("%d",&available[j]);	
	}
}

displaymatrices(int np,int nr)
{
	int i=0,j=0;

	printf("\nAllocation matrix\n");
	for(i=0;i<np;i++)
	{
		for(j=0;j<nr;j++)
		{
			printf("%d",allocated[i][j]);
			printf("\t");
		}
		printf("\n");
	}

	printf("\nMax matrix\n");
	for(i=0;i<np;i++)
	{
		for(j=0;j<nr;j++)
		{
			printf("%d",max[i][j]);
			printf("\t");
		}
		printf("\n");
	}

	printf("\nNeed matrix\n");
	for(i=0;i<np;i++)
	{
		for(j=0;j<nr;j++)
		{
			printf("%d",need[i][j]);
			printf("\t");
		}
		printf("\n");
	}

	printf("\nAvailable\n");
	for(j=0;j<nr;j++)
	{
		printf("%d",available[j]);
		printf("\t");
	}
	printf("\n");
	
}

int banker_algo(int nr,int np)
{
	int i=0,j=0,work[50],flag=1,finish[50],cnt=0,seq[50],x=0,k=0;

	for(j=0;j<nr;j++)
	{
		work[j]=available[j];
	}

	for(i=0;i<np;i++)
	{
		finish[i]=0;
	}

	while(flag)
	{
		flag=0;
		
		for(i=0;i<np;i++)
		{
			j=0;
			if(finish[i]==0)
			{
				for(j=0;j<nr;j++)
				{
					if(need[i][j]>work[j])
						break;
				}
			
				if(j==nr)
				{
					printf("\nProcess %d executed",i);
					finish[i]=1;
					cnt++;
					seq[x++]=i;

					for(k=0;k<nr;k++)
					{
						work[k]=work[k]+allocated[i][k];
					}
					flag=1;
				}
				else
				{
					printf("\nProcess %d is waiting",i);
				}
			}
		}
		
	}
	if(cnt==np)
	{
		printf("\nSafe sequence\n");
		for(i=0;i<np;i++)
		{
			printf("%d\t",seq[i]);
		}
		return 1;
	}
	else
	{
		printf("Unsafe");
		return 0;
	}
}

res_req_algo(int nr,int np)
{
	int p,acc;
	int req[20],j=0;

	printf("\nEnter process");
	scanf("%d",&p);

	printf("Enter request");
	for(j=0;j<nr;j++)
	{
		scanf("%d",&req[j]);
	}

	for(j=0;j<nr;j++)
	{
		if(req[j]>available[j])
		{	
			printf("\nRequest rejected");
			return 0;
		}
	}

	for(j=0;j<nr;j++)
	{
		if(req[j]>need[p][j])
		{
			printf("Request rejected");
			return 0;
		}
	}

	for(j=0;j<nr;j++)
	{
		allocated[p][j]+=req[j];
		available[j]-=req[j];
	}
	calculate_need(np,nr);
	acc=banker_algo(np,nr);
	if(acc==1)
		printf("\nRequest is accepted");
	
	else
		printf("\nRequest is rejected");
	
}


main()
{
	int no_of_pro,no_of_res,i=0,ch,acc;
	char res[50],pro[50];

	printf("\nEnter no. of resources");
	scanf("%d",&no_of_res);
		
	//printf("\nEnter resourse name");
	//for(i=0;i<no_of_res;i++)
	//{
	//	scanf("%s",&res[i]);
	//}
	
	printf("\nEnter no. of process");
	scanf("%d",&no_of_pro);
		
	//printf("\nEnter process name");
	///for(i=0;i<no_of_pro;i++)
	//{
	//	scanf("%s",&pro[i]);
	//}

	do
	{
		printf("\n1.Accept allocation matrix \n2.accept max matrix \n3.Calculate need matrix \n4.Accept available \n5.Display matrices \n6.Accept request and apply Banker's alogorithm \n7.Resource_request algo \n8.Exit");
		printf("\nEnter your choice");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:accept_allocation(no_of_pro,no_of_res);
				break;

			case 2:accept_max(no_of_pro,no_of_res);
				break;

			case 3:calculate_need(no_of_pro,no_of_res);
				break;

			case 4:available_vector(no_of_res);
				break;

			case 5:displaymatrices(no_of_pro,no_of_res);
				break;

			case 6:acc=banker_algo(no_of_res,no_of_pro);
				break;
			case 7:res_req_algo(no_of_res,no_of_pro);
				break;
			case 8:exit(0);

			
		}
	}while(ch!=8);	
	
}


