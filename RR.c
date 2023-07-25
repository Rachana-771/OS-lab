#include<stdio.h>

void findWaitingTime(int proc[],int n,int bt[],int wt[],int quantum){
    int rem_bt[n],i;
    for(i=0;i<n;i++){
        rem_bt[i]=bt[i];
    }

    int t=0;
    while(1){
        int done=1;
        for ( i = 0 ; i < n; i++)
		{

			if (rem_bt[i] > 0)
			{
				done = 0;
				if (rem_bt[i] > quantum)
				{

					t += quantum;
					rem_bt[i] -= quantum;
				}
				else
				{
					t = t + rem_bt[i];

					wt[i] = t - bt[i];

					rem_bt[i] = 0;
				}
			}
		}
        if (done == 1)
		break;

    }
}

void findTurnAroundTime(int proc[], int n,
						int bt[], int wt[], int tat[])
{

	for (int i = 0; i < n ; i++){
		tat[i] = bt[i] + wt[i];
	}
}


void calculate(int proc[],int n,int bt[],int quantum){
  int wt[n], tat[n], total_wt = 0, total_tat = 0;

  findWaitingTime(proc, n, bt, wt, quantum);

  findTurnAroundTime(proc, n, bt, wt, tat);

  printf("\n pnum\t burst\t wait \t tat");
  int i;
	for ( i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		printf("\n%d\t %d\t %d\t %d\t " ,i+1 , bt[i] ,
			 wt[i] , tat[i]);

	}

	printf("\nAverage waiting time =%f ", (float)total_wt / (float)n);
	printf( "\nAverage turn around time =%f ",
		(float)total_tat / (float)n);

}


void main(){
 int val=0,i,j,temp,q;
 int  n;
 printf("\n enter number of processes");
 scanf("%d",&n);
  int proc[n],burst_time[n];
 for (i=0;i<n;i++){
    proc[i]=i+1;
 }
 for(int i=0;i<n;i++){
 printf("\n enter burst time for process %d:",i+1);
 scanf("%d",&val);
 burst_time[i]=val;
 }

  printf("\n enter quantum time");
  scanf("%d",&q);
 calculate(proc,n,burst_time,q);
}
