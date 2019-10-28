#include <stdio.h>
#include <stdlib.h>

int counttime(int x1, int x2, int y1, int y2){
	int disx = abs(x1 - x2);
	int disy = abs(y1 - y2);
	int time;
    int max, min;
    if(disx > disy){
        max = disx;
        min = disy;
    }
    else {
        max = disy;
        min = disx;
    }
	if(max >= 2*min)
			time = max;
	else time = (max+min)/3 * 2 + (max+min)%3;		
	return time;
}

int main(){
	int time[100001] = {0};
	int N;
	scanf("%d", &N);
	int x[100001];
	int y[100001];
	int i;
	int j = 1;
	for(i = 0; i<N; i++){
		scanf("%d %d", &x[i], &y[i]);
	}

	for(i = 0; i<N; i++)
		for(j = 0; j<N; j++){
			time[i] += counttime(x[i], x[j], y[i], y[j]);
		}
		
	for(i = 0; i<N; i++){
		printf("%d\n", time[i]);
	}
	return 0;
}
