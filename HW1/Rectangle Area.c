#include <stdio.h>
#include <stdlib.h>
#define RANGE 100001
#pragma optimize "0Fast"

typedef unsigned long long int ull;
ull area = 0;
struct P{
	ull x, y;
};

struct P dot[RANGE];
int RECURSE(struct P arr[], int a, int b, int c){
	int p1 = a-b+1; //bagian 1
	int p2 = c-a; //bagian 2
	struct P left[p1], right[p2];
	ull rx[p2+1] = {0}, ry[p2+1] = {0}, sav[p2+1] = {0};
	for(int i = 0; i<p2; i++){
		right[i] = arr[a+i+1];
		rx[i+1] = rx[i] + right[i].x;
		ry[i+1] = ry[i] + right[i].y;
		sav[i+1] = sav[i] + (right[i].x * right[i].y);
	} 
	ull idx = 0;
	for(int i = 0; i <p1; i++){
		left[i] = arr[b+i];
		ull meow = left[i].x * left[i].y;
		while(idx < p2 && left[i].y > right[idx].y)
			idx++;
		area += (sav[p2] - sav[idx]) + (meow*(p2-idx)) - ((ry[p2]-ry[idx])*left[i].x) - ((rx[p2]-rx[idx])*left[i].y); 
		area -= sav[idx] + meow*idx - rx[idx]*left[i].y - ry[idx]*left[i].x;
	}
	int i = 0, j = 0, k = b;
	int count = 0;
	while(i < p1 && j < p2){
		if (left[i].y > right[j].y) { 
            arr[k] = right[j]; 
            j++;
            count++;
        } 
        else { 
       		arr[k] = left[i]; 
            i++; 
        } 
        k++; 
	}
	while(i < p1) { 
        arr[k] = left[i]; 
        i++; 
        k++;
    } 
    while(j < p2){ 
        arr[k] = right[j]; 
        j++; 
        k++; 
    }
}

void mergesort(struct P arr[], int kiri, int kana){
	int tengah;
	if(kiri < kana){
		tengah = (kana-kiri)/2 + kiri;
		mergesort(arr, kiri, tengah);
		mergesort(arr, tengah+1, kana);
		RECURSE(arr, tengah, kiri, kana); 
	}
}

int ptr (const void *p, const void *q){
	struct P *A = (struct P *)p;
	struct P *B = (struct P *)q;
	return ((*A).x - (*B).x);
}

int main(int argc, char const *argv[]){
	int S;
	scanf("%d ", &S);
	for(int i = 0; i<S; i++){
		scanf("%llu %llu", &dot[i].x, &dot[i].y);
	}
	qsort(dot, S, sizeof(struct P), ptr);
	mergesort(dot, 0, S-1);
	printf("%llu\n", area);
	return 0;
}

