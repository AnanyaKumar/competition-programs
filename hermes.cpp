/**
 * International Olympiad of Informatics 2004, Day 1 Q2
 * Ananya Kumar, 2012
 * NUS High School
 */

#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

#define INF 1000000000
#define ORI 1005
#define MAXD 2020

typedef pair<int,int> ii;
ii prev, cur;

int prevrow[MAXD], prevcol[MAXD];
int currow[MAXD], curcol[MAXD];

int main ()
{
	int N;
	FILE *in = fopen("hermes.in","r");
	FILE *out = fopen("hermes.out","w");
	fscanf(in,"%d",&N);
	cur = make_pair(ORI,ORI);
	int i, j, k;
	int ans = INF;
	
	//Initialize original row and column (origin is 0, everything else INF)
	
	for ( i = 0; i < MAXD; i++ )
	{
		currow[i] = INF;
		curcol[i] = INF;
		prevrow[i] = INF;
		prevcol[i] = INF;
	}
	
	currow[ORI] = 0;
	curcol[ORI] = 0;
	
	//Read in data and perform computations
	
	for ( j = 0; j < N; j++ )
	{
		fscanf(in,"%d %d",&prev.first,&prev.second);
		prev.first += ORI; prev.second += ORI;

		swap(cur,prev);
		
		for ( i = 0; i < MAXD; i++ )
		{
			prevrow[i] = currow[i];
			prevcol[i] = curcol[i];
			currow[i] = INF;
			curcol[i] = INF;
		}
		
		//Update new row and column from old row and column
					
		for ( i = 0; i < MAXD; i++ )
		{
			currow[i] = min(currow[i], prevrow[i]+abs(cur.second-prev.second));
			curcol[prev.second] = min(curcol[prev.second], prevrow[i]+abs(i-cur.first));
			
			curcol[i] = min(curcol[i], prevcol[i]+abs(cur.first-prev.first));
			currow[prev.first] = min(currow[prev.first], prevcol[i]+abs(i-cur.second));
		}
	}
	
	//Scan current row and column to output minimum
	
	for ( i = 0; i < MAXD; i++ )
	{
		ans = min(ans,currow[i]);
		ans = min(ans,curcol[i]);
	}
	
	fprintf(out,"%d\n",ans);
}