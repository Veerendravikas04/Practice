#include <stdio.h>


int wait_times[50];
int turn_around_times[50];

void sjf_gantt_chart(int p[][3], int n);

int main(){
    int n;
    printf("Enter Number Of Processes:");
    scanf("%d",&n);
    int p[n][3];
    int i,j,k,temp[3];
    printf("Enter Process details:(Process Id,Arrival Time,Burst Time)\n");
    for(i=0;i<n;i++){
        scanf("%d %d %d",&p[i][0],&p[i][1],&p[i][2]);
    }

    // Sort Based On Arrival Times And Burst Times
    for(i=0;i<n;i++){
        for(j=0;j<n-1;j++){
            if(p[j][1]>p[j+1][1]  || (p[j][1]==p[j+1][1] && p[j][2]>p[j+1][2])){
                for(k=0;k<3;k++){
                    temp[k]=p[j][k];
                    p[j][k]=p[j+1][k];
                }
                for(k=0;k<3;k++){
                    p[j+1][k]=temp[k];
                }
            }
        }
    }

    // Sorted Process
    printf("\nSorted Processes:\n");
    for(i=0;i<n;i++){
        for(k=0;k<3;k++){
            printf("%d ",p[i][k]);
        }
        printf("\n");
    }

    sjf_gantt_chart(p,n);

    return 0;
}

void sjf_gantt_chart(int p[][3], int n) {
    int min_arrival_time = p[0][1]; 
    int max_arrival_time = p[0][1]; 
    int total_burst_time = 0;
    

   //Find Max and Min Arrival Times
    for (int i = 0; i < n; i++) {
        if (p[i][1] < min_arrival_time) {
            min_arrival_time = p[i][1];
        }
        if (p[i][1] > max_arrival_time) {
            max_arrival_time = p[i][1];
        }

        
        turn_around_times[i]=0;

        total_burst_time+=p[i][2];
    }
 for (int i = 0; i < n; i++) {
        wait_times[i] = min_arrival_time;
 }
    printf("\nGannt Chart:\n");

   int executing_process = -1; 
int prev_executing = -1;  
int i = min_arrival_time; 
int completed=0;
while (!completed) {
    
        for (int j = 0; j < n; j++) {
            if (p[j][1] <= i && p[j][2] > 0) {
                if (executing_process == -1 || p[j][2] < p[executing_process][2]) {
                    executing_process = j;
                }
            }
        }

        if (executing_process != -1) {
            p[executing_process][2]--;
            if (p[executing_process][2] == 0) {
                turn_around_times[executing_process] = i + 1 - p[executing_process][1];
            }
            if (executing_process != prev_executing) {
                printf(" %d P%d", i, p[executing_process][0]);
            }
            prev_executing = executing_process;

            for (int k = 0; k < n; k++) {
                if (executing_process != k && p[k][2] > 0) {
                    wait_times[k]++;
                }
            }
        } else {
            printf(" IDLE %d", i);
        }

        executing_process = -1;

    completed = 1;
    for (int j = 0; j < n; j++) {
        if (p[j][2] > 0) {
            completed = 0;
            break;
        }
    }

    if (completed) {
        for (int j = 0; j < n; j++) {
            if (p[j][2] > 0) {
                turn_around_times[j] = total_burst_time + min_arrival_time - p[j][1];
            }
        }
    }

    i++;
}
    printf(" %d",total_burst_time);
    printf("\nWaiting Times:");
    float AvgWT = 0;
    for(i=0;i<n;i++){
        wait_times[i]-=p[i][1];
        AvgWT+=wait_times[i];
        printf("\nP%d : %dms ",p[i][0],wait_times[i]);
    }
    AvgWT=AvgWT/n;
    printf("\nAverage wait time :%0.2fms",AvgWT);
    printf("\nTurn Around Times:");
    float AvgTAT = 0;
    for(i=0;i<n;i++){
        AvgTAT += turn_around_times[i];
        printf("\nP%d : %dms ",p[i][0],turn_around_times[i]);
    }

    AvgTAT=AvgTAT/n;
    printf("\nAverage turn around time :%0.2fms",AvgTAT);
}