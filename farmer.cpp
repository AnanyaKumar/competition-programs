/**
 * International Olympiad of Informatics 2004, Day 2 Q2
 * Ananya Kumar, 2012
 * NUS High School
 */

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXQ 150005
bool memo[MAXQ] = {false};
vector<int> strip;

int main ()
{
	FILE *in = fopen("farmer.in","r");
	FILE * out = fopen("farmer.out","w");
	
	int Q, M, K;
	fscanf(in,"%d %d %d",&Q,&M,&K);
	int i, j, field, curstrip;
	memo[0] = true;
	int sumtree = 0;
	int ans;
	
	for ( i = 0; i < M; i++ )
	{
		fscanf(in,"%d",&field);
		for ( j = min(Q-field,sumtree); j >= max(0,Q-150*(M-i)); j-- ) memo[j+field] |= memo[j];
		sumtree += field;
		
		if ( memo[Q] )
		{
			fprintf(out,"%d\n",Q);
			return 0;
		}
	}
	
	if ( sumtree > Q )
	{
		fprintf(out,"%d\n",Q-1);
		return 0;
	}

	for ( i = 0; i < K; i++ )
	{
		fscanf(in,"%d",&curstrip);
		strip.push_back(curstrip);
	}
	
	ans = Q;
	sort(strip.begin(),strip.end());
	
	for ( i = strip.size()-1; i >= 0; i-- )
	{
		sumtree += strip[i];
		ans--;
		
		if ( sumtree >= Q )
		{
			fprintf(out,"%d\n",ans);
			return 0;
		}
	}
}