#include <stdio.h> 
#include <stdlib.h> 
#pragma GCC Optimize ("Ofast") 
#include <limits.h>

typedef long long int ll;

struct adjacency 
{ 
	ll target, weight; 
	struct adjacency* next; 
}; 

struct AdjList 
{ 
	struct adjacency *head; 
}; 

struct Graph 
{ 
	ll V; 
	struct AdjList* array; 
}; 


struct adjacency* newAdjListNode(ll target, ll weight) 
{ 
	struct adjacency* newNode = (struct adjacency*) malloc(sizeof(struct adjacency)); 
	newNode->target = target; 
	newNode->weight = weight; 
	newNode->next = NULL; 
	return newNode; 
} 

struct Graph* createGraph(ll V) 
{ 
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph)); 
	graph->V = V; 
	graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList)); 
	for (int i = 0; i < V; i++) 
		graph->array[i].head = NULL; 

	return graph; 
} 

ll addEdge(struct Graph* graph, ll src, ll target, ll weight) 
{ 
	struct adjacency* newNode = newAdjListNode(target, weight); 
	newNode->next = graph->array[src].head; 
	graph->array[src].head = newNode; 

	newNode = newAdjListNode(src, weight); 
	newNode->next = graph->array[target].head; 
	graph->array[target].head = newNode; 
} 
 
struct MinHeapNode {  
	ll v, dist; 
	} ; 

struct MinHeap { 	
	ll size, capacity, *pos;	 
	struct MinHeapNode **array; 
}	; 


struct MinHeapNode* newMinHeapNode(ll v, ll dist) 
{ 
	struct MinHeapNode* minHeapNode = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode)); 
	minHeapNode->v = v; 
	minHeapNode->dist = dist; 
	return minHeapNode; 
} 


struct MinHeap* createMinHeap(ll capacity) 
{	
	ll sz = sizeof(ll); 
	struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap)); 
	minHeap->pos = (ll *)malloc(capacity * sz); 
	minHeap->size = 0; 
	minHeap->capacity = capacity; 
	minHeap->array = (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

ll swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) 
{ 
	struct MinHeapNode* t = *a; 
	*a = *b, *b = t; 
} 

ll minHeapify(struct MinHeap* minHeap, ll index) 
{ 
	ll smallest = index;
	ll left = 2*index+1;
	ll right = 2*index+2; 

	if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist) 
		smallest = left; 

	if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist ) 
		smallest = right; 
	
	if (smallest != index) 
	{
		MinHeapNode *smallestNode = minHeap->array[smallest]; 
		MinHeapNode *indexNode = minHeap->array[index]; 
		minHeap->pos[smallestNode->v] = index; 
		minHeap->pos[indexNode->v] = smallest; 
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
		minHeapify(minHeap, smallest); 
	} 
} 

ll isEmpty(struct MinHeap* minHeap) 
{	
	ll ret = minHeap->size == 0; 
	return ret;
} 

struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 
	if (isEmpty(minHeap)) 
		return NULL; 
 
	struct MinHeapNode* root = minHeap->array[0]; 
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
	minHeap->array[0] = lastNode; 
	minHeap->pos[root->v] = minHeap->size-1; 
	minHeap->pos[lastNode->v] = 0; 

	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return root; 
} 

ll dK(struct MinHeap* minHeap, ll v, ll dist) 
{
	ll i; 
	i = minHeap->pos[v]; 
	minHeap->array[i]->dist = dist; 
	while(i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) 
	{ 	
		minHeap->pos[minHeap->array[i]->v] = (i-1)/2; 
		minHeap->pos[minHeap->array[(i-1)/2]->v] = i; 
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 
		ll x = (i-1)/2;
		i = x; 
	} 
} 

bool isInMinHeap(struct MinHeap *minHeap, ll v) 
{ 
	if ((minHeap->pos[v] < minHeap->size)) 
		return true; 
	return false; 
} 


ll ans(ll dist[], ll n) 
{ 
	ll max = -15;
	ll i;
	for (i = 0; i < n; i++){
		if(dist[i] == LONG_MAX){
			return -1;
		}
		if(max <= dist[i])
			max = dist[i];		
	}
	return max;
} 

//Dijkstra 
ll dijkstra(struct Graph* graph, ll src) 
{ 
	ll V = graph->V, dist[V];	  
	struct MinHeap* minHeap = createMinHeap(V); 
	ll v;
	for (v = 0; v < V; v++) 
	{ 
		dist[v] = LONG_MAX; 
		minHeap->array[v] = newMinHeapNode(v, dist[v]); 
		minHeap->pos[v] = v; 
	} 
	minHeap->array[src] = newMinHeapNode(src, dist[src]); 
	minHeap->pos[src] = src; 
	dist[src] = 0; 
	dK(minHeap, src, dist[src]);  
	minHeap->size = V; 

	while(!isEmpty(minHeap)) 
	{ 
		struct MinHeapNode* minHeapNode = extractMin(minHeap); 
		ll u = minHeapNode->v; 
		struct adjacency* meow = graph->array[u].head; 
		while(meow != NULL) 
		{ 
			v = meow->target; 

			if (isInMinHeap(minHeap, v) && dist[u] != LONG_MAX && meow->weight + dist[u] < dist[v]) 
			{ 
				dist[v] = dist[u] + meow->weight; 
				dK(minHeap, v, dist[v]); 
			} 
			meow = meow->next; 
		}	 
	} 
	ll answer = ans(dist, V);
	return answer; 
} 

int main() 
{ 
	ll n; 
	ll m; 
	scanf("%lld %lld", &n, &m);
	ll a[m], b[m], c[m];
	struct Graph* graph = createGraph(n);
	ll i; 
	for(i = 0; i < m; i++){
		scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);
		addEdge(graph, a[i]-1, b[i]-1, c[i]); 
	}
		
	ll ans = dijkstra(graph, 0); 
	printf("%lld", ans);
		
	return 0; 
} 

