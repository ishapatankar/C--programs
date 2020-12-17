#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct process
{
	char name[10];
	int arrivTime, CPUBT, turnAT, waitTime, tempCPUBT,priority,newAT,newWT;
}p[50];



void acceptProcessData(int n,int ch);
void sortProcesses(int n);
void printProcessData(int flag,int n);

int isArrived(int t,int n);
int getMin(int t,int n);
int getMaxPriority(int t, int n);

void firstComeFirstServe(int n);
void SJF_NP(int n);
void priorityScheduling_NPre(int n);
void priorityScheduling_Pre(int n);
void SJF_P(int n);


void main()
{
	int n,ch;
	
	while(1)
	{
			printf("\nChoose An Algorithm");
			printf("\n1) First Come First Serve");
			printf("\n2) Shortest Job First(Non pre-emptive)");
			printf("\n3) Shortest Job First(pre-emptive)");
			printf("\n4) Priority Scheduling(Non pre-emptive)");
			printf("\n5) Priority Scheduling(pre-emptive)");
			printf("\n6) Round Robin");
			printf("\n7) Exit");
			printf("\nEnter Your Choice:");
			scanf("%d",&ch);
	

			printf("\nEnter Number of Processes:");
			scanf("%d",&n);
 
			acceptProcessData(n,ch);
			
				
			switch(ch)
			{
				case 1: sortProcesses(n);
					firstComeFirstServe(n);
					printProcessData(2,n);
					break;
				case 2: SJF_NP(n);
					printProcessData(3,n);
					break;
				case 3: SJF_P(n);
					printProcessData(4,n);
					break;
				case 4: priorityScheduling_NPre(n);
					printProcessData(4,n);
					break;
				case 5: priorityScheduling_Pre(n);
					printProcessData(4,n);
					break;
				case 6: roundRobin(n);
					printProcessData(4,n);
					break;
				case 7: exit(0);
					break;
				
			}
	}				
}

void acceptProcessData(int n,int ch)
{
	int i;
	for(i=0;i<n;i++)
	{	
		printf("\n\nProcess %d",i+1);
		
		printf("\nEnter Name:");
		scanf("%s",&p[i].name);
		//gets(p[i].name);

		printf("\nEnter Arrival Time:");
		scanf("%d",&p[i].arrivTime);

		printf("\nEnter CPU Burst Time:");
		scanf("%d",&p[i].CPUBT);

		if(ch==4 || ch==5)
		{
			printf("Enter priority for process(0 is highest):");
			scanf("%d",&p[i].priority);
		}
		p[i].tempCPUBT = p[i].CPUBT;
	}

	printProcessData(0,n);
}
void sortProcesses(int n)
{
	int i,j;
	struct process temp;
	
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-1-i;j++)
		{
			if(p[j].arrivTime > p[j+1].arrivTime)
			{

				temp = p[j+1];
				p[j+1] = p[j];
				p[j] = temp;
			}
		}
	}

	printProcessData(1,n);
}


void printProcessData(int flag,int n)
{
	int i;
	if(flag==0)
		printf("\n\n------------Accepted Process Data-----------");		
	else if(flag==1)
		printf("\n\n------------Process Data After Sorting-----------");
	else if(flag==2)
		printf("\n\n------------Process Data After Completion(FCFS)-----------");
	else if(flag==3)
		printf("\n\n------------Process Data After Completion(SJF NP)-----------");
	else {}
	printf("\n|Id|\tName |\tArrival Time|\tCPUBT |\t TAT   |\t WT   |");
	for(i=0;i<n;i++)
	{
		printf("\n|%d  |\t%s   |\t    %d       |\t %d    |\t %d     |\t  %d   |",i+1,p[i].name,p[i].arrivTime,p[i].CPUBT,p[i].turnAT,p[i].waitTime);
	}

	printf("\n\n");
}

int isArrived(int t,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if((p[i].arrivTime <= t) && (p[i].tempCPUBT != 0))
			return i;	
	}
	return -1;
}


int getMin(int t,int n)
{
	int min=999,i;
	int pid;
	for(i=0;i<n;i++)
	{
		if((p[i].arrivTime <= t) && (p[i].tempCPUBT !=0) && (p[i].CPUBT < min))
		{
			min = p[i].CPUBT;
			pid = i;	
		}
	}

	return pid;
}

int getMaxPriority(int t,int n)
{
	int min=999,i;
	int pid;
	for(i=0;i<n;i++)
	{
		if((p[i].arrivTime <= t) && (p[i].tempCPUBT !=0) && (p[i].priority < min))
		{
			min = p[i].priority;
			pid = i;	
		}
	}

	return pid;
}

void firstComeFirstServe(int n)
{
	int finish=0,time=0;
	int j;
	int startTime;
	while(finish != n)
	{
		j = isArrived(time,n);	
		if(j!=-1)
		{
			startTime=time;
			time+=p[j].CPUBT;
			p[j].tempCPUBT = 0;
			p[j].turnAT = time - p[j].arrivTime;
			p[j].waitTime = startTime - p[j].arrivTime;
			finish++;
			printf("%d|__%s__|%d ",startTime,p[j].name,time);
		}
		else
		{
			startTime = time;
			time++;
			p[j].waitTime = startTime - p[j].arrivTime;
			printf("%d|__%s__|%d ",startTime,p[j].name,time);
		}
	}

	
}

void SJF_P(int n)
{
	int time=0,finish=0;
	int j,k,i;
	int startTime;
	while(finish!=n)
	{
		j = isArrived(time,n);
		
		if(j!=-1)
		{
			k=getMin(time,n);
			
			p[k].tempCPUBT--;
			time++;
					
			p[k].waitTime = p[k].waitTime + (time - startTime);
			if(p[k].tempCPUBT==0)
			{
				finish++;
				p[k].turnAT = time - p[k].arrivTime;				
			}	
			printf("%d|__%s__|%d ",startTime,p[k].name,time);
		}
		else
		{
			startTime = time;
			p[k].waitTime = startTime - p[k].arrivTime;
			time++;
			//p[k].waitTime = startTime - p[k].arrivTime;
			printf("%d|__%s__|%d ",startTime,p[k].name,time);
		}
	}
}

void SJF_NP(int n)
{
	int time=0,finish=0;
	int j,k,i;
	int startTime;
	while(finish!=n)
	{
		j = isArrived(time,n);
		
		if(j!=-1)
		{
			k=getMin(time,n);
			startTime=time;
			for(i=0;i<p[k].CPUBT;i++)
			{
				p[k].tempCPUBT--;
				time++;
			}
			finish++;
			p[k].turnAT = time - p[k].arrivTime;
			p[k].waitTime = startTime - p[k].arrivTime;
			
			printf("%d|__%s__|%d ",startTime,p[k].name,time);
		}
		else
		{
			startTime = time;
			time++;
			//p[k].waitTime = startTime - p[k].arrivTime;
			printf("%d|__%s__|%d ",startTime,p[k].name,time);
		}
	}
	
}

void priorityScheduling_Pre(int n)
{
	int time=0,finish=0;
	int j,k,i;
	int startTime;
	while(finish!=n)
	{
		j = isArrived(time,n);
		
		if(j!=-1)
		{
			k=getMaxPriority(time,n);
			
			p[k].tempCPUBT--;
			time++;
					
			p[k].waitTime = p[k].waitTime + (time - startTime);
			if(p[k].tempCPUBT==0)
			{
				finish++;
				p[k].turnAT = time - p[k].arrivTime;				
			}	
			printf("__%s__|%d ",p[k].name,time);
		}
		else
		{
			startTime = time;
			p[k].waitTime = startTime - p[k].arrivTime;
			time++;
			//p[k].waitTime = startTime - p[k].arrivTime;
			printf("%d|__%s__|%d ",startTime,p[k].name,time);
		}
	}
}

void priorityScheduling_NPre(int n)
{
	int time=0,finish=0;
	int j,k,i;
	int startTime;
	while(finish!=n)
	{
		j = isArrived(time,n);
		
		if(j!=-1)
		{
			k=getMaxPriority(time,n);
			startTime=time;
			for(i=0;i<p[k].CPUBT;i++)
			{
				p[k].tempCPUBT--;
				time++;
			}
			finish++;
			p[k].turnAT = time - p[k].arrivTime;
			p[k].waitTime = startTime - p[k].arrivTime;
			
			printf("%d|__%s__|%d ",startTime,p[k].name,time);
		}
		else
		{
			startTime = time;
			time++;
			//p[k].waitTime = startTime - p[k].arrivTime;
			printf("__%s__|%d ",p[k].name,time);
		}
	}
}
void roundRobin(int n)
{
	int q;
	int j,i=0,finish=0,time=0,startTime;
	printf("Enter the Time Quantam for the Processes");
	scanf("%d",&q);
	
	while(finish !=n)
	{
		j=isArrived(time,n);
		if(j!=-1)
		{
			startTime=time;
			for(j=0;j<q;j++)
			{
				p[i].tempCPUBT--;
				time++;
				if(p[i].tempCPUBT==0)
				{
					finish++;
					break;
				}
				p[i].waitTime=(startTime-p[i].newAT);
				p[i].newWT=time;
				printf("%d|__%s__|%d ",startTime,p[i].name,time);
			}
		}
		else
		{
			time++;
			printf("%d|____|%d ",startTime,time);
		}
		if(time<p[(i+1)%n].arrivTime)
		{
			i=0;
		}
		else
		{
			i=(i+1)%n;
		}
	}
}
		
			
	
