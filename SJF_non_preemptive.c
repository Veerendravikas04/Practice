#include <stdio.h>

void sjf_gantt_chart(int p[][2],int n);

int main(){
    int n;
    printf("Enter Number Of Processes:");
    scanf("%d",&n);
    int p[n][2];
    int i,j,k,temp[2];
    printf("Enter Process details:(Process Id,Burst Time)\n");
    for(i=0;i<n;i++){
        scanf("%d %d",&p[i][0],&p[i][1]);
    }

    // Sort Based On Arrival Times And Burst Times
    for(i=0;i<n;i++){
        for(j=0;j<n-1;j++){
            if(p[j][1]>p[j+1][1]  || (p[j][1]==p[j+1][1] && p[j][2]>p[j+1][2])){
                for(k=0;k<2;k++){
                    temp[k]=p[j][k];
                    p[j][k]=p[j+1][k];
                }
                for(k=0;k<2;k++){
                    p[j+1][k]=temp[k];
                }
            }
        }
    }

    // Sorted Process
    printf("\nSorted Processes:\n");
    for(i=0;i<n;i++){
        for(k=0;k<2;k++){
            printf("%d ",p[i][k]);
        }
        printf("\n");
    }

    sjf_gantt_chart(p,n);

    return 0;
}

void sjf_gantt_chart(int p[][2],int n){

    int time=0;
    int w[n],t[n];
    float avgW=0,avgT=0;
    printf("Gannt chart:\n");
    for(int i=0;i<n;i++){
        printf("%d P%d ",time,p[i][0]);
        w[i]=time;
        avgW+=w[i];
        time+=p[i][1];
        t[i]=time;
        avgT+=t[i];
    }
    printf("%d",time);
    avgW=avgW/n;
    avgT=avgT/n;
    printf("\nWaiting Times:\n");
    for(int i=0;i<n;i++){
        printf("P%d : %d\n",p[i][0],w[i]);
    }

    printf("Avg Waiting Time: %0.2f",avgW);
    printf("\nTurn Around Times:\n");
    for(int i=0;i<n;i++){
        printf("P%d : %d\n",p[i][0],t[i]);
    }
    printf("Avg Turn Around Time: %0.2f",avgT);

}