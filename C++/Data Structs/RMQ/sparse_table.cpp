//Basic Range minimum/maximum query function

//Assumption- 0-based indexing everywhere

//Most naive implementaion
//O(nlog n) precomputation
//O(1) query
//O(nlog n) space complexity
const int MAX = 100005;
const int LIM = 17;		//equals ceil(log2(MAX))

vector<int> inp;
int lg[MAX];			//contains log of numbers from 1 to n
int p2[LIM];			//comtains powers of 2
int rmq[LIM][MAX];		//sparse table implementation

void build_rmq() {
	int n = inp.size();
	for(int i=2; i<n; ++i) {
		lg[i] = lg[i/2] + 1;
	}
	p2[0] = 1;
	for(int i=0; i<n; ++i) {
		rmq[0][i] = inp[i];
	}
	for(int i=1; i<=lg[n]; ++i) {
		p2[i] = 1<<i;
		int x = n-p2[i], y = p2[i-1];
		for(int j=0; j<=x; ++j) {
			rmq[i][j] = max(rmq[i-1][j], rmq[i-1][j+y]);
		}
	}
}

int query(int i, int j) {
    int x = lg[j-i+1];
    return max(rmq[x][i], rmq[x][j-p2[x]+1]);
}