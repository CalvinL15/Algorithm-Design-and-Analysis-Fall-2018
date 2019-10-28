#include <stdio.h>
#define SIZE 200001
#pragma GCC optimize("Ofast")

typedef  unsigned long long int ull;
int main(){
	int n;
	ull sum = 0, sumarr[SIZE] = {0}, l[SIZE], r[SIZE];
	scanf("%d", &n);
	int count = -1;
	for(int i = 0; i<n; i++){
		count++;
		scanf("%llu %llu", &l[count], &r[count]);
		sumarr[count] = (r[count] - l[count])*(r[count]-l[count]);
		
		for(int k = 0; k<= count-1; k++){
			if(l[count] <= r[k]){
				if(l[count] > l[k]){
					sumarr[k] = (r[count]-l[k]) * (r[count]-l[k]);
				}
				else {
					sumarr[k] = (r[count]-l[count]) * (r[count]-l[count]);
					l[k] = l[count];	
				}
				r[k] = r[count];
			count = k;	
			break;
			}	
		}
		for(int j = 0; j<=count; j++){
			sum += sumarr[j];
		}
		printf("%llu\n", sum);
		sum = 0;
	}
}
