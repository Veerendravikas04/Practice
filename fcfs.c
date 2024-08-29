#include<stdio.h>
#include<stdlib.h>

int main(){
	int n;
	printf("Enter no. of process");
	scanf("%d",&n);
	int a[n],b[n],c[n],t[n],w[n],i,j,k,p[n],temp=0;
	float at=0,aw=0;
	printf("Enter process,arrival time and burst time for each process");
	for(i=0;i<n;i++){
		scanf("%d %d %d",&p[i],&a[i],&b[i]); }
	for(i=0;i<n;i++){
		for(j=0;j<n-1;j++){
					if(a[j]>a[j+1]){
				temp=p[j+1];
				p[j+1]=p[j];
				p[j]=temp;
				temp=a[j+1];
				a[j+1]=a[j];
				a[j]=temp;
				temp=b[j+1];
				b[j+1]=b[j];
				b[j]=temp;
			}
		}
	}
	c[0]=a[0]+b[0];
	for(i=0;i<n;i++){
		temp=0;
		if(c[i-1]<a[i]){
			temp=a[i]-c[i-1];
		}
		c[i]=c[i-1]+b[i]+temp;
	}
	printf("\np\t A.T\t B.T\t C.T\t TAT\t WT");
	for(i=0;i<n;i++){
		t[i]=c[i]-a[i];
		w[i]=t[i]-b[i];
		at+=t[i];
		aw+=w[i];
	}
	at=at/n;
	aw=aw/n;
	for(i=0;i<n;i++){
		printf("\nP%d\t %d\t %d\t %d\t %d\t %d\t",p[i],a[i],b[i],c[i],t[i],w[i]);
	}
	printf("\nAverage turnaroundtime of the process is %f",at);
	printf("\nAverage waitingtime of the process is %f",aw);
}
