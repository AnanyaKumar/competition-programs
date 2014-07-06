/**
 * French Australian Regional Informatics Olympiad 2009, Q2
 * Ananya Kumar, 2012
 * NUS High School
 */

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

#define MAXN 100001
typedef pair<int,int> ii;

int toycolor[MAXN];
int toysubcolor[MAXN]; //Where the index is located in colorloc
vector<int> colorloc[MAXN]; //colorloc[i] stores the locations for the ith color
bool open[MAXN];
priority_queue<ii> farthestColor;
int N, C, K;

int main ()
{
	//Scan data in
	
	scanf("%d %d %d",&N, &C, &K);
	int i, j, t, numc = 0, ans = 0;
		
	for ( i = 1; i <= N; i++ )
	{
		scanf("%d",&toycolor[i]);
		toysubcolor[i] = colorloc[ toycolor[i] ].size();
		colorloc[ toycolor[i] ].push_back(i);
	}
	
	for ( i = 1; i <= C; i++ )
	{
		colorloc[i].push_back(MAXN);
		open[i] = false;
	}
	
	for ( i = 1; i <= N; i++ )
	{
		j = toycolor[i];
				
		if ( !open[j] )
		{
			//If k colors open, find (using pq) color who is farthest away and close it
			
			if ( numc == K )
			{
				t = farthestColor.top().second;
				farthestColor.pop();
				open[t] = false;
				ans++;
			}
			
			else
			{
				numc++;
				ans++;
			}
		}
		
		open[j] = true;
		farthestColor.push(make_pair( colorloc[j][ toysubcolor[i] + 1 ], toycolor[i]) );
	}
	
	printf("%d\n",ans);
}