//references: https://codeforces.com/blog/entry/8221?fbclid=IwAR2E9hbwtoSA0LMln05lVKWJSgGv4Z9Mc7QfoKPcIqTB0mrTmsUuJupOgj8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define mod 1000000007

typedef long long ll;

ll dpa[1001][3][3][3][33];
int mem[1001][3][3][3][33];
char l[1001], r[1001];
int sb[1001], bb[1001];
int len;

int utility(int a, int b){
	return (a*10+b)%33;
}

ll dp(int idx, int count3, int count6, int count9, int lo, char digit[1001], int mod33){
	if(idx == len){
		if (count3 % 3 != 0)
			return 0;
		if(count6 % 3 != 0)
			return 0;	
		if(count9 % 3 != 0)
			return 0;
		if(mod33 % 3 != 0)
			return 0;
		if(mod33 % 11 != 0)
			return 0;				
		return 1;	
	}
	
	long long int ret = 0;

	int dig;

	if (lo) {
	    if (mem[idx][count3][count6][count9][mod33]) {
	       return dpa[idx][count3][count6][count9][mod33];
	    } 
		else {
	       mem[idx][count3][count6][count9][mod33] = 1;
	       long long int r = 0;
	       for (dig = 0; dig <= 9; dig++) {
	       if(dig == 3)
	            r=(r+dp(idx + 1,(count3+1)%3, count6,count9, lo, digit, utility(mod33, dig)))%mod;
	        else if(dig==6)
	        	r=(r+dp(idx + 1,count3, (count6+1)%3, count9, lo, digit, utility(mod33, dig)))%mod;
	        else if(dig==9)
	            r=(r+dp(idx + 1,count3, count6, (count9+1)%3 , lo, digit,utility(mod33, dig)))%mod;
	        else
	            r=(r+dp(idx + 1,count3, count6, count9, lo, digit, utility(mod33, dig)))%mod;
	       }
	       dpa[idx][count3][count6][count9][mod33] = r%mod;
	       return r%mod;
	    }
	}

	int limit = digit[idx] - '0';

	for (dig = 0; dig <= limit; ++dig) {
        if(dig==3)
            ret = (ret+dp(idx + 1,(count3+1)%3, count6,count9, (lo || (dig < (digit[idx] - '0'))), digit, utility(mod33, dig)))%mod;
        else if(dig==6)
            ret = (ret+dp(idx + 1,count3, (count6+1)%3,count9, (lo || (dig < (digit[idx] - '0'))), digit, utility(mod33, dig)))%mod;
        else if(dig==9)
            ret = (ret+dp(idx + 1,count3, count6, (count9+1)%3 , (lo || (dig < (digit[idx] - '0'))), digit, utility(mod33, dig)))%mod;
        else
        	ret = (ret+dp(idx + 1,count3, count6, count9, (lo || (dig < (digit[idx] - '0'))), digit, utility(mod33, dig)))%mod;
}
	return ret%mod;
}
	


ll solve(char x[]){
	memset(dpa, 0, sizeof(dpa));
	memset(mem, 0, sizeof(mem));
	len = strlen(x);
	return dp(0, 0, 0, 0, 0, x, 0);
}

ll check(char in[]){
	int count3 = 0, count6 = 0, count9 = 0;
	int len = strlen(in);
	for(int i = 0; i < len; i++){
		if (in[i] == '3') 
			count3++;
		if (in[i] == '6')
			count6++;
		if (in[i] == '9')
			count9++; 	 
	}
	if(count3 % 3 != 0) return 0;
	if(count6 % 3 != 0) return 0;
	if(count9 % 3 != 0) return 0;
	
	int even = 0;
	int odd = 0;
	for(int i = 0; i<len; i+=2)
		even += in[i]-'0';
	
	for(int i = 1; i<len; i+=2)
		odd += in[i]-'0';		
	
	int meow = odd-even;
	if(meow % 11 != 0)
		return 0;
	int meow2 = odd+even;
	if(meow%3 != 0)
		return 0;	
	
	return 1;		
}

int main(){
	scanf("%s %s", &l, &r);
	ll solutionl = solve(l);
	ll solutionr = solve(r);
	if(solutionr < solutionl)
		printf("%lld", (solutionr-solutionl+check(l)+mod)%mod);
	else printf("%lld", (solutionr-solutionl+check(l))%mod);
	return 0;
}
