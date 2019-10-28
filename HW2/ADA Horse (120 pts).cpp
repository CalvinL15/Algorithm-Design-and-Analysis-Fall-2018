#include <bits/stdc++.h>
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(),(x).end()
#ifdef _DEBUG_
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...) (void)0
#endif
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int MAXN = 100000 + 10;

ll ans[MAXN];
int id[MAXN];
PII h[MAXN], line;

ll operator*(PII &a, PII &b) {
	return 1ll*a.F*b.F + 1ll*a.S*b.S;
}

bool cmp(int a, int b) {
	return h[a]*line < h[b]*line;
}
bool cmp2(int a, int b) {
	return h[a] < h[b];
}
int mod(int x) {
	return (x%3+3)%3;
}

// [ )
void solve(int l, int r) {
	if(r-l < 200) {
		for(int i=l; i<r; i++) {
			for(int j=i+1; j<r; j++) {
				int x = abs(h[id[i]].F-h[id[j]].F);
				int y = abs(h[id[i]].S-h[id[j]].S);
				if(x < y)	swap(x, y);
				if(x >= y*2)	ans[id[i]] += x;
				else	ans[id[i]] += (x+y)/3*2 + (x+y)%3;
			}
		}
		return ;
	}

	int m = (l+r) / 2;
	solve(l, m);
	solve(m, r);
	ll sum_xpy[3] = {0}, sum_xmy[3] = {0}, cnt_xpy[3] = {0}, cnt_xmy[3] = {0}, sum_x = 0, sum_y = 0, all_sum_x = 0;
	for(int i=m; i<r; i++) {
		int x = h[id[i]].F, y = h[id[i]].S;
		sum_xpy[mod(x+y)] += x+y-mod(x+y);
		cnt_xpy[mod(x+y)]++;
		sum_xmy[mod(x-y)] += x-y-mod(x-y);
		cnt_xmy[mod(x-y)]++;
		sum_x += x;
	}
	all_sum_x = sum_x;
	for(int i=l; i<m; i++) {
		int x = h[id[i]].F, y = h[id[i]].S;
		for(int j=0; j<3; j++) {
			ans[id[i]] += (sum_xpy[j]-cnt_xpy[j]*(x+y-mod(x+y)))/3*2 + cnt_xpy[j]*(j-mod(x+y)+(mod(x+y)>j));
			ans[id[i]] += (sum_xmy[j]-cnt_xmy[j]*(x-y-mod(x-y)))/3*2 + cnt_xmy[j]*(j-mod(x-y)+(mod(x-y)>j));
		}
		ans[id[i]] += sum_x-1ll*(r-m)*x;
	}

	int cur;

	// y = 2x + k
	line = MP(-2, 1);
	sort(id+l, id+m, cmp);
	sort(id+m, id+r, cmp);
	sum_y = 0;
	memset(sum_xpy, 0, sizeof(sum_xpy));
	memset(cnt_xpy, 0, sizeof(cnt_xpy));
	cur = r-1;
	for(int i=m-1; i>=l; i--) {
		int x = h[id[i]].F, y = h[id[i]].S;
		while(cur>=m && line*h[id[i]] < line*h[id[cur]]) {
			// (1)
			sum_y += h[id[cur]].S;
			// (2)
			int mod3 = mod(h[id[cur]].F+h[id[cur]].S);
			sum_xpy[mod3] += (h[id[cur]].F+h[id[cur]].S)-mod3;
			cnt_xpy[mod3]++;

			cur--;
		}
		// (1)
		assert(sum_y - 1ll*y * (r-cur-1) >= 0);
		ans[id[i]] += sum_y - 1ll*y * (r-cur-1);
		// (2)
		for(int j=0; j<3; j++) {
			assert((sum_xpy[j]-(x+y-mod(x+y))*cnt_xpy[j])/3*2 + cnt_xpy[j]*(j-mod(x+y)+(mod(x+y)>j)) >= 0);
			ans[id[i]] -= (sum_xpy[j]-(x+y-mod(x+y))*cnt_xpy[j])/3*2 + cnt_xpy[j]*(j-mod(x+y)+(mod(x+y)>j));
		}
	}

	// y = -2x + k
	line = MP(2, 1);
	sort(id+l, id+m, cmp);
	sort(id+m, id+r, cmp);
	sum_y = 0;
	memset(sum_xmy, 0, sizeof(sum_xmy));
	memset(cnt_xmy, 0, sizeof(cnt_xmy));
	cur = m;
	for(int i=l; i<m; i++) {
		int x = h[id[i]].F, y = h[id[i]].S;
		while(cur<r && line*h[id[i]] > line*h[id[cur]]) {
			// (5)
			sum_y += h[id[cur]].S;
			// (4)
			int mod3 = mod(h[id[cur]].F-h[id[cur]].S);
			sum_xmy[mod3] += h[id[cur]].F-h[id[cur]].S-mod3;
			cnt_xmy[mod3]++;

			cur++;
		}
		// (5)
		assert(1ll*y * (cur-m) - sum_y >= 0);
		ans[id[i]] += 1ll*y * (cur-m) - sum_y;
		// (4)
		for(int j=0; j<3; j++) {
			int mod3 = mod(x-y);
			assert((sum_xmy[j]-(x-y-mod3)*cnt_xmy[j])/3*2 + cnt_xmy[j]*(j-mod3+(mod3>j)) >= 0);
			ans[id[i]] -= (sum_xmy[j]-(x-y-mod3)*cnt_xmy[j])/3*2 + cnt_xmy[j]*(j-mod3+(mod3>j));
		}
	}


	// y = 1/2 x + k
	line = MP(-1, 2);
	sort(id+l, id+m, cmp);
	sort(id+m, id+r, cmp);
	sum_x = 0;
	memset(sum_xpy, 0, sizeof(sum_xpy));
	memset(cnt_xpy, 0, sizeof(cnt_xpy));
	cur = m;
	for(int i=l; i<m; i++) {
		int x = h[id[i]].F, y = h[id[i]].S;
		while(cur<r && line*h[id[i]] > line*h[id[cur]]) {
			// (2)
			int mod3 = mod(h[id[cur]].F+h[id[cur]].S);
			sum_xpy[mod3] += h[id[cur]].F+h[id[cur]].S-mod3;
			cnt_xpy[mod3]++;
			// (3)
			sum_x += h[id[cur]].F;

			cur++;
		}
		
		// (2)
		for(int j=0; j<3; j++) {
			//assert(sum_xpy - 1ll*(h[id[i]].F+h[id[i]].S)*(cur-m) >= 0);
			ans[id[i]] -= (sum_xpy[j]-(x+y-mod(x+y))*cnt_xpy[j])/3*2 + cnt_xpy[j]*(j-mod(x+y)+(mod(x+y)>j));
		}
		// (3)
		assert((all_sum_x - sum_x) - 1ll*(r-cur)*x >= 0);
		ans[id[i]] -= (all_sum_x - sum_x) - 1ll*(r-cur)*x;
	}

	// y = -1/2 x + k
	line = MP(1, 2);
	sort(id+l, id+m, cmp);
	sort(id+m, id+r, cmp);
	sum_x = 0;
	memset(sum_xmy, 0, sizeof(sum_xmy));
	memset(cnt_xmy, 0, sizeof(cnt_xmy));
	cur = r-1;
	for(int i=m-1; i>=l; i--) {
		int x = h[id[i]].F, y = h[id[i]].S;
		while(cur>=m && line*h[id[i]] < line*h[id[cur]]) {
			// (4)
			int mod3 = mod(h[id[cur]].F-h[id[cur]].S);
			sum_xmy[mod3] += h[id[cur]].F-h[id[cur]].S-mod3;
			cnt_xmy[mod3]++;
			// (3)
			sum_x += h[id[cur]].F;

			cur--;
		}
		
		// (4)
		for(int j=0; j<3; j++) {
			//assert(sum_xmy - 1ll*(h[id[i]].F-h[id[i]].S)*(r-cur-1) >= 0);
			ans[id[i]] -= (sum_xmy[j]-(x-y-mod(x-y))*cnt_xmy[j])/3*2 + cnt_xmy[j]*(j-mod(x-y)+(mod(x-y)>j));
		}
		// (3)
		assert((all_sum_x - sum_x) - 1ll*(cur-m+1)*x >= 0);
		ans[id[i]] -= (all_sum_x - sum_x) - 1ll*(cur-m+1)*x;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		id[i] = i;
		scanf("%d%d", &h[id[i]].F, &h[id[i]].S);
	}

	sort(id, id+n, cmp2);
	solve(0, n);
	sort(id, id+n, cmp2);
	for(int i=0; i<n; i++)	h[id[i]].F *= -1;
	reverse(id, id+n);
	solve(0, n);

	for(int i=0; i<n; i++)	printf("%lld\n", ans[i]);
    
    return 0;
}
