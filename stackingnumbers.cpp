/**
 * Australian Informatics Olympiad Senior 2003, Q2
 * Ananya Kumar, 2011
 * NUS High School
 */

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 32
#define MAXB 35000

int best[MAXB];
bool done[MAXN] = {false};
int cur[6];

int choice[MAXN];
int bestChoice[MAXN];
int s, b;
int highs = 0;

void recur ( int num )
{
	if ( num == 5 )
	{
		int t1 = (4*choice[cur[1]]+6*choice[cur[2]]+4*choice[cur[3]]+choice[cur[4]])%b;
		int t2 = (choice[cur[1]]+4*choice[cur[2]]+6*choice[cur[3]]+4*choice[cur[4]])%b;
		int maxt = max(t1,t2);
		int mint = min(t1,t2);
		//printf("%d %d %d %d\n",choice[cur[1]],choice[cur[2]],choice[cur[3]],choice[cur[4]]);
		int i, j;
		
		i = best[mint];
		while ( done[i] ) i = (i+s-1)%s;
		done[i] = true;
		
		j = best[maxt];
		while ( done[j] ) j = (j+s-1)%s;
		int curh = ((choice[i]+mint)%b) * ((choice[j]+maxt)%b);
		
		if ( curh >= highs )
		{
			highs = curh;
			copy(cur+1,cur+5,bestChoice+1);
			
			if ( t1 == mint )
			{
				bestChoice[0] = i;
				bestChoice[5] = j;
			}
			
			else
			{
				bestChoice[0] = j;
				bestChoice[5] = i;
			}
		}
					 
		done[i] = false;
	}
	
	else 
	{
		int maxs = s;
		if ( num == 3 ) maxs = cur[2];
		
		for ( int i = 0; i < maxs; i++ )
		{
			if ( done[i] ) continue;
			done[i] = true;
			cur[num] = i;
			recur(num+1);
			done[i] = false;
		}
	}

}

int main ()
{
	FILE *in = fopen("stackin.txt","r");
	FILE *out = fopen("stackout.txt","w");
	fscanf(in,"%d",&b);
	fscanf(in,"%d",&s);
	int i, j, k;
	
	for ( i = 0; i < s; i++ ) 
		fscanf(in,"%d",&choice[i]);
	sort(choice,choice+s);
	
	//Precompute best array
	
	for ( i = 0; i < b; i++ )
	{
		k = 0;
		
		for ( j = 0; j < s; j++ )
		{
			if ( (i+choice[j])%b >= k )
			{
				k = (i+choice[j])%b;
				best[i] = j;
			}
		}
		
		//printf("%d %d\n",i,choice[best[i]]);
	}
	
	recur(1);
	fprintf(out,"%d\n",highs);
	for ( i = 0; i < 6; i++ ) fprintf(out,"%d ",choice[bestChoice[i]]);
	fprintf(out,"\n");
}