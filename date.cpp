/**
 * French Australian Regional Informatics Olympiad 2010, Q3
 * Ananya Kumar, 2012
 * NUS High School
 */

#include <cstdio>
using namespace std;

#define MAXR 101
int spam[MAXR][MAXR][MAXR] = {0}; //Age, Height, Weight

inline int sval ( int i, int j, int k )
{
	if ( i < 0 || j < 0 || k < 0 ) return 0;
	else return spam[i][j][k];
}

int main ()
{
	int S, U, i, j, k;
	int a1, a2, h1, h2, w1, w2;
	scanf("%d %d",&S,&U);
	
	//Scan the data and mark vertices of constraint cube
	
	for ( i = 0; i < S; i++ )
	{
		scanf("%d %d %d %d %d %d",&a1,&a2,&h1,&h2,&w1,&w2);
		a2++; h2++; w2++;
		
		spam[a1][h1][w1] += 1;
		spam[a1][h2][w1] -= 1;
		spam[a1][h1][w2] -= 1;
		spam[a1][h2][w2] += 1;
		
		spam[a2][h1][w1] -= 1;
		spam[a2][h2][w1] += 1;
		spam[a2][h1][w2] += 1;
		spam[a2][h2][w2] -= 1;
	}
	
	//Perform a 3D-sum through the 'spam' cube
	
	for ( i = 0; i < MAXR; i++ )
	{
		for ( j = 0; j < MAXR; j++ )
			for ( k = 0; k < MAXR; k++ )
				spam[i][j][k] += sval(i,j-1,k) + sval(i,j,k-1) - sval(i,j-1,k-1);
		
		for ( j = 0; j < MAXR; j++ )
			for ( k = 0; k < MAXR; k++ )
				spam[i][j][k] += sval(i-1,j,k);
	}
	
	//For each non-spammer add the number of visits
	
	int ans = 0;
	
	for ( i = 0; i < U; i++ )
	{
		scanf("%d %d %d %d",&a1,&h1,&w1,&j);
		if ( spam[a1][h1][w1] <= 0 ) ans += j;
	}
	
	printf("%d\n",ans);
}