/**
 * French Australian Regional Informatics Olympiad 2008, Q2
 * Ananya Kumar, 2012
 * NUS High School
 *
 * Gets 95/100 points. Additional speed up is needed
 * for 100 points.
 **/

#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXC 40001
#define MAXK 201

vector<int> neigh[MAXC];
int dp[MAXC][MAXK];
int A[MAXC];
int X[MAXC];
int Y[MAXC];
int R[MAXC];
int C, K;

int main ()
{
	scanf("%d %d",&C,&K);
	int i, j, k;
	for ( i = 0; i < C; i++ ) scanf("%d %d %d %d",&X[i],&Y[i],&R[i],&A[i]);
	A[C] = 0;
	
	//Construct the Graph
	for ( i = C-1; i >= 0; i-- )
	{
		for ( j = i+1; j < C; j++ )
		{
			//If circle i is in circle j connect them and break
			if ( (X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]) <= R[j]*R[j] )
			{
				neigh[i].push_back(j);
				neigh[j].push_back(i);
				break;
			}
		}
		
		if ( neigh[i].size() == 0 )
		{
			neigh[i].push_back(C);
			neigh[C].push_back(i);
		}
	}
	
	for ( i = 0; i <= C; i++ ) dp[i][0] = A[i];
	
	for ( i = 1; i <= K; i++ ) //Dynamic Programming
	{		
		for ( j = 0; j <= C; j++ )
		{
			dp[j][i] = dp[j][i-1];
			for ( k = 0; k < neigh[j].size(); k++ ) dp[j][i] = min(dp[j][i],dp[neigh[j][k]][i-1]);
		}
	}
	
	int ans = 0;
	for ( i = 0; i <= C; i++ ) ans = max(ans,A[i]-dp[i][K]);
	printf("%d\n",ans);
	return 0;
}