#include <iostream>
using namespace std;

int main(){
	int T;
	int num;
	int maxres[30] = {0};
	int poweroftwo[30];

	for(int i = 0; i <= 29; i++){
		if(i == 0)
		poweroftwo[i] = 1;
		else 
		poweroftwo[i] = 2 * poweroftwo[i-1];
		if(i == 0)
		maxres[i] = 1;
		else maxres[i] = (maxres[i-1] + poweroftwo[i]); 
	}
	cin >> T;
	for(int i = 0; i<T; i++){
		cin >> num;
		int count = 0;
		if(num == 1)
			printf("%d\n", count+1);
		else{	
			while(num > maxres[count]){
				count++;
			}
			printf("%d\n", count+(__builtin_popcount (num-maxres[count-1])));
		}
	}
	return 0;
}



