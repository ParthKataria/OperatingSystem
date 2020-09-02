//Compile using g++
//Assignment 4
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
char filename[100],data[30],name[1000][20];
float arrival[1000],burst1[1000],burst2[1000],iot[1000],iod[1000],prty[1000],turntime[1000],ts,scheduler[1000],WT[1000];
int number;
int time = 0;
typedef struct node
{
	 int id;
	struct node *next;
}Q;
Q *head=NULL;
void input()
{
	FILE *f;
	printf("Enter the name of file:");
	scanf("%s",filename);
	printf("Enter time quantum:");
	scanf("%f",&ts);
	f=fopen(filename,"r");
	int i=0,j;
	if(f==NULL)
		printf("Error in opening the file");
	else
		while(fgets(data, 30, f)) 
		{
	    	sscanf(data,"%s %f %f %f %f %f",name[i],&arrival[i],&burst1[i],&iot[i],&iod[i],&prty[i]);
	    	burst2[i]=burst1[i];
	   		i++;
		}
	number=i;
	fclose(f);
	// for(j=0;j<4;j++)
	// 	printf("%s %f %f %f %f %f %f\n",name[j],arrival[j],burst1[j],iot[j],iod[j],prty[j],burst2[j]);
	// printf("%d\n",number);
}
int remaining()
{
	int i,x=0;
	for(i=0;i<number;i++)
		if(burst2[i]>0)
			x=1;
	return x;
}
void insert(int i)
{
	Q *x,*y;
	x=(Q*)malloc(sizeof(Q));
	x->next=NULL;
	x->id=i;
	if(head == NULL)
		head = x;
	else
	{
		for(y= head;y->next!=NULL; y=y->next);
		y-> next=x;
	}
}
void arrived()
{
	int k;
	for(k=0;k<1000;k++)
		if(arrival[k]==time)
			insert(k);
}
int next()
{
	Q *n;
	int x;
	if(head==NULL)
		return -1;
	else
	{
		x=head->id;
		n=head;
		head=head->next;
		free(n);
		return x;
	}
}
void schedule()
{
	int np,toRun,q, i;
	q = 0;
	arrived();
	while(remaining())
	{
		np=next();
		if(np == -1)
		{
			scheduler[time] = -1;
			time++;
			arrived();
		}
		else
		{
			q=ts;
			if(burst2[np]< q)
				q=burst2[np];
			for(i =q;i>0;i--)
			{
				scheduler[time]=np;
				time++;
				burst2[np]--;
				arrived();
			}
			if(burst2[np]> 0)
				insert(np);
		}
	}
}
void WatingTime()
{
	int i;
	int releaseTime, t;
	for(i=0;i<number; i++)
	{
		for(t=time-1; scheduler[t]!= i; t--);
		releaseTime = t+1;
		WT[i]=releaseTime-arrival[i]-burst1[i];
	}
}
void TurnAround()
{
	int i;
	for(i=0;i<number;i++)
		turntime[i]=burst1[i]+WT[i];
}
void printScheduling()
{
	int i;
	printf("\t\t\t\tROUND ROBIN SCHEDULING\n");
	printf("Process Name\t   Arrival Time\t   Burst Time\t   Turn Around Time\t  Wait Time\n");
	for(i=0;i<number;i++)
		printf("  %s\t           %f\t     %f\t     %f\t          %f\n", name[i],arrival[i],burst1[i],turntime[i],WT[i]);
	float AWT = 0.0,avgTat=0.0,std=0.0;
	for(i=0; i<number; i++)
	{
		AWT+=WT[i];
		avgTat+=turntime[i];
	}
	AWT = AWT/number;
	avgTat=avgTat/number;
	for(i=0;i<number;i++)
		std+=pow(turntime[i]-avgTat,2);
	std=sqrt(std/number);
	printf("\nAverage Waiting Time: %f\n", AWT);
	printf("Average Turn Around Time: %f\n",avgTat);
	printf("Standard Deviation of Average Turn Around Time: %f\n",std);
}
int main()
{
	input();
	schedule();
	WatingTime();
	TurnAround();
	printScheduling();
}
                                                                    //IIT2019016
                                                                  
