#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	int sum = 0, ans = -(1ll<<31);
	for(int i=0; i<n; i++) {
		int x;
		scanf("%d", &x);
		sum = max(x, sum+x);
		ans = max(ans, sum);
	}
	printf("%d\n", ans);
    
    return 0;
}
