#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<bits/stdc++.h> 
#pragma optimize "O3"

typedef long long int lld;
typedef unsigned long long int ull;

lld checkIlluminati(lld a){
	int count3 = 0, count6 = 0, count9 = 0;
	if (a%33 != 0)
		return 0;
	else{
		int temp;
		while(a != 0){
			temp = a%10;
			if(temp == 3) count3++;
			else if(temp == 6) count6++;
			else if(temp == 9) count9++;	
			a = a/10;
		}	
	}
	if(count3 % 3 != 0) return 0;
	if(count6 % 3 != 0) return 0;
	if(count9 % 3 != 0) return 0;
	
	return -1;		
}
int n, m;
lld countPaths(lld maze[1001][1001]){
	if (maze[0][0] == -1) 
        return 0;
	
	for(int i = 0; i<n; i++){
		if (maze[i][0] == 0) 
            maze[i][0] = 1;
        else break; 
	}	 
	for (int i= 1; i<m; i++) {
        if (maze[0][i] == 0) 
            maze[0][i] = 1; 
        else break;
	}
	 for (int i=1; i<n; i++) 
    { 
        for (int j=1; j<m; j++) 
        { 
      
            if (maze[i][j] == -1) 
                continue; 
  
            if (maze[i-1][j] > 0) {
                maze[i][j] = (maze[i][j] + (maze[i-1][j]%1000000007)); 
            }
  
            if (maze[i][j-1] > 0) 
                maze[i][j] = (maze[i][j] + (maze[i][j-1]%1000000007)); 
        } 
    } 
 
    return (maze[n-1][m-1] > 0) ? maze[n-1][m-1] : 0; 
} 


int main(){
	lld matrix[1001][1001];
	scanf("%d %d", &n, &m);
	int i, j;
	for(i = 0; i<n; i++)
		for(j = 0; j<m; j++){
			scanf("%lld ", &matrix[i][j]);
			matrix[i][j] = checkIlluminati(matrix[i][j]);
		}
	
	printf("%lld", countPaths(matrix) % 1000000007);
	return 0;
}
