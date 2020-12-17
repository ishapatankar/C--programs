#include<stdio.h>
#include<stdlib.h>
struct frame
{
	int value,cnt,frq;
}fr[20];

int frame[20],rs[20],cf=0,at[20][20];
int nf,len_ref_str,flag=0;

accept()
{
	int i;
	printf("\nEnter no of frames");
	scanf("%d",&nf);

	printf("\nEnter length of reference string");
	scanf("%d",&len_ref_str);
	
	printf("\nEnter reference string");
	for(i=0;i<len_ref_str;i++)
	{
		scanf("%d",&rs[i]);
	}
		
}

search_page_fifo(int rs)
{
	int i=0;
	for(i=0;i<nf;i++)
	{
		if(rs==frame[i])
			return 1;
		
			
	}
	return -1;
}

fifo()
{
	int k=0,i,j,page_fault=0;
	
	for(i=0;i<len_ref_str;i++)
	{
		j=search_page_fifo(rs[i]);
		
		if(j==-1)
		{
			frame[k]=rs[i];	
			page_fault++;
		}
		display_fifo(frame);
		k=(k+1)%nf;
	}
	printf("\nTotal no of page fault: %d",page_fault);
}

display_fifo(int frame[])
{
	int i=0;

	printf("\n");
	for(i=0;i<nf;i++)
		printf("%d\t",frame[i]);
	printf("\n");
	
}



search_page_lru(int rs)
{
	int i=0;
	for(i=0;i<nf;i++)
	{
		if(rs==fr[i].value)
			return i;
		 
			
	}
	return -1;
}

int getLRU()
{
	int min=999,i,val;
	for(i=0;i<nf;i++)
	{
		if(fr[i].cnt<min)
		{
			min=fr[i].cnt;
			val=i;
		}
		
	}
	return val;
	
}


lru()
{
	int i,k,j,time=1,page_fault=0,d;

	for(i=0,k=0;i<len_ref_str;i++)
	{
		j=search_page_lru(rs[i]);
		
		if(j==-1)
		{
			fr[k].value=rs[i];
			fr[k].cnt=time;
			page_fault++;
			k++;
			time++;
			if(k == nf)
			   break;	
		}
		else
		{
			fr[j].cnt=time;
			time++;			
		}
		for(d=0;d<nf;d++)
			printf("%d\t",fr[d].value);
		printf("\n");
	}

	while(i<len_ref_str)
	{
		
		j=search_page_lru(rs[i]);
		
		if(j==-1)
		{
			k=getLRU();
			fr[k].value=rs[i];
			fr[k].cnt=time;
			page_fault++;
			time++;
			i++;
		}
		else
		{
			fr[j].cnt=time;
			time++;	
			i++;		
		}
		for(d=0;d<nf;d++)
			printf("%d\t",fr[d].value);
		printf("\n");
	
	}
	
		printf("\n Total no of page fault %d",page_fault);

	
		
}


int getLFU()
{
	int fno,i=0,selfno=0,min=999,val,tcnt=0;
	for(fno=0;fno<nf;fno++)
	{
		if(fr[fno].frq<min)
		{
			min=fr[fno].frq;
		}
		
	}
	for(fno=0;fno<nf;fno++)
	{
		if(fr[fno].frq==min)
		{
			at[tcnt][0]=fno;
			at[tcnt][1]=fr[fno].cnt;
			tcnt++;
		}
		
	}
	min=999;
	for(i=0;i<tcnt;i++)
	{
		//printf("arrival :%d \n",at[i][1]);
		if(at[i][1]<min)
		{
			selfno=at[i][0];
			min=at[i][1];
		}
	}

	return selfno;
	
}


lfu()
{
	int i,k,j,page_fault=0,d,time=0;

	for(i=0,k=0;k<nf&&i<len_ref_str;i++)
	{
		j=search_page_lru(rs[i]);
		
		if(j==-1)
		{
			fr[k].value=rs[i];
			fr[k].frq=1;
			fr[k].cnt=time;
			page_fault++;
			k++;
				
		}
		else
		{
			fr[j].frq++;	
		}
		time++;
		for(d=0;d<nf;d++)
			printf("%d (%d)\t",fr[d].value,fr[d].frq);
		printf("\n");
	}
	flag = 1;
	while(i<len_ref_str)
	{
		
		j=search_page_lru(rs[i]);
		
		if(j==-1)
		{
			k=getLFU();
			fr[k].value=rs[i];
			fr[k].frq=1;
			fr[k].cnt = time;
			page_fault++;
			i++;
		}
		else
		{
			fr[j].frq++;
			i++;		
		}
		time++;
		for(d=0;d<nf;d++)
			printf("%d (%d)\t",fr[d].value,fr[d].frq);			
		printf("\n");
	
	}
	
		printf("\n Total no of page fault %d",page_fault);

	
		
}

int getMFU()
{
	int fno,i=0,selfno=0,min=-1,val,tcnt=0;
	for(fno=0;fno<nf;fno++)
	{
		if(fr[fno].frq>min)
		{
			min=fr[fno].frq;
		}
		
	}
	for(fno=0;fno<nf;fno++)
	{
		if(fr[fno].frq==min)
		{
			at[tcnt][0]=fno;
			at[tcnt][1]=fr[fno].cnt;
			tcnt++;
		}
		
	}
	
	min=99;
	for(i=0;i<tcnt;i++)
	{
		//printf("arrival :%d \n",at[i][1]);
		if(at[i][1]<min)
		{
			selfno=at[i][0];
			min=at[i][1];
		}
	}

	return selfno;
	
}
mfu()
{
	int i,k,j,page_fault=0,d,time=0;

	for(i=0,k=0;k<nf && i<len_ref_str;i++)
	{
		j=search_page_lru(rs[i]);
		
		if(j==-1)
		{
			fr[k].value=rs[i];
			fr[k].frq=1;
			fr[k].cnt=time;
			page_fault++;
			k++;
			
		}
		else
		{
			fr[j].frq++;	
		}
		time++;
		for(d=0;d<nf;d++)
			printf("%d\t",fr[d].value);
		printf("\n");
	}

	while(i<len_ref_str)
	{
		
		j=search_page_lru(rs[i]);
		
		if(j==-1)
		{
			k=getMFU();
			fr[k].value=rs[i];
			fr[k].frq=1;
			fr[k].cnt=time;
			page_fault++;
			i++;
		}
		else
		{
			fr[j].frq++;
			i++;		
		}
		time++;
		for(d=0;d<nf;d++)
			printf("%d\t",fr[d].value);
		printf("\n");
	
	}
	
		printf("\n Total no of page fault %d",page_fault);

	
		
}
main()
{
	int ch;
	
	accept();
	do
	{
		printf("\n1.FIFO\n2.LRU\n3.LFU\n4.MFU\n5.Exit\nEnter Your Choice");
		scanf("%d",&ch);

		switch(ch)
		{
			case 1:fifo();
				break;

			case 2:lru();
				break;
		
			case 3:lfu();
				break;
			
			case 4:mfu();
				break;
	
		}
	}while(ch!=5);

	
}
