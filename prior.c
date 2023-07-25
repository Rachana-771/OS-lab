#include<stdio.h>

void waitingtime(int proc[], int n, int burst_time[], int wait_time[]){
    wait_time[0]=0;
    for(int i=1;i<n;i++){
        wait_time[i]=burst_time[i-1] + wait_time[i-1] ;
    }
}

void turnaroundtime( int proc[], int n, int burst_time[], int wait_time[], int tat[]){
    for  (int i = 0 ;i < n ; i++){
      tat[i] = burst_time[i] + wait_time[i];
   }
}


void avgtime(int proc[],int n,int burst_time[],int priority[]){

  int wait_time[n];
  int tat[n];
  int total_wt=0,total_tat=0;
  waitingtime(proc, n, burst_time, wait_time);
  turnaroundtime(proc, n, burst_time, wait_time, tat);
   printf("\npnum \t burst\t wait\t turnaround\t priority");
  for(int i=0;i<n;i++){
    total_wt+=wait_time[i];
    total_tat+=tat[i];
   printf("\n %d \t %d \t %d \t %d \t\t %d",
           proc[i],burst_time[i],wait_time[i],tat[i],priority[i]);
  }

  printf("\n\n Average waiting time: %f ",(float)total_wt/n);
  printf("\n Average turn around time: %f",(float)total_tat/n);

}


void main(){
 int val=0,i,j,temp;
 int  n;
 printf("\n enter number of processes");
 scanf("%d",&n);
  int proc[n],burst_time[n],priority[n];
 for (i=0;i<n;i++){
    proc[i]=i+1;
 }
 for(int i=0;i<n;i++){
 printf("\n enter burst time and priority for process %d:",i+1);
 scanf("%d\t%d",&burst_time[i],&priority[i]);
 }


 for(i=0;i<n;i++){
    for(j=i;j<n;j++){
        if(priority[i]>priority[j]){
            temp=priority[i];
            priority[i]=priority[j];
            priority[j]=temp;

            temp=burst_time[i];
            burst_time[i]=burst_time[j];
            burst_time[j]=temp;

            temp=proc[i];
            proc[i]=proc[j];
            proc[j]=temp;
        }
    }
 }

 avgtime(proc,n,burst_time,priority);
}
