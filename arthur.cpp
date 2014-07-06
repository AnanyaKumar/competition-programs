/**
 * Australian Informatics Competition 1999, Q4
 * Ananya Kumar, 2012
 * NUS High School
 *
 * A recursive complete search with many optimizations
 * to prune out incorrect solutions. Time complexity
 * is difficult to analyze.
 */

#include <cstdio>
#include <algorithm>
#define MAXK 12
using namespace std;

int nump;
bool cannot[MAXK][MAXK] = {false}; //cannot[i][j] <=> i cannot sit with j
bool must[MAXK][MAXK] = {false}; //must[i][j] <=> i must sit with j
bool seated[MAXK] = {false}; //seated[i] <=> person i has been seated
int cannotnum[MAXK] = {0};
int mustnum[MAXK] = {0};
int order[MAXK] = {0};

bool isValid ( int seatnum, int right ) //Is the seating assigned so far valid?
{
	int left = order[seatnum-1];
	int me = order[seatnum];
	if ( cannot[me][left] || cannot[me][right] ) return false;
	
	for ( int i = 0; i < nump; i++ )
		if ( i != left && i != right && must[me][i] )
			return false;
	
	return true;
}

bool getSeating ( int seatnum ) //Recursive function to generate a valid seating
{
	int i;
	
	if ( seatnum == nump ) //Base case
	{
		if ( isValid(seatnum-1,0) ) return true;
	}
	
	else
	{
		for ( i = 1; i < nump; i++ )
		{
			if ( !seated[i] ) //Try fitting in each person who hasn't yet been seated
			{
				if ( seatnum > 1 && !isValid(seatnum-1,i) ) continue; //Keep checking if the seating is valid
				seated[i] = true;
				order[seatnum] = i;
				if ( getSeating(seatnum+1) ) return true;
				seated[i] = false;
			}
		}
	}
	
	return false;
}

int main ()
{
	FILE *in = fopen( "arthin.txt", "r" );
	FILE *out = fopen( "arthout.txt", "w" );
	fscanf( in, "%d", &nump );
	
	int k1, k2;
	int i, j;
	bool hasseating = true;
	
	fscanf( in, "%d %d", &k1, &k2 );
	k1--; k2--;
	
	while ( k1 != -1 )
	{
		if ( !must[k1][k2] )
		{
			mustnum[k1]++;
			mustnum[k2]++;
		}
		
		must[k1][k2] = true;
		must[k2][k1] = true;
		
		fscanf( in, "%d %d", &k1, &k2 );
		k1--; k2--;
	}
	
	fscanf( in, "%d %d", &k1, &k2 );
	k1--; k2--;
	
	while ( k1 != -1 )
	{
		if ( !cannot[k1][k2] )
		{
			cannotnum[k1]++;
			cannotnum[k2]++;
		}
		
		if ( must[k1][k2] ) hasseating = false; //cannot[i][j] and must[i][j] can't both be true
		cannot[k1][k2] = true;
		cannot[k2][k1] = true;
		
		fscanf( in, "%d %d", &k1, &k2 );
		k1--; k2--;
	}
	
	seated[0] = true;
	
	for ( i = 0; i < nump; i++ )
		if ( mustnum[i] > 2 || cannotnum[i] >= nump-2 ) //If a person must sit with 2 ppl, or cannot sit with N-1 ppl, then impossible!
			hasseating = false;
	
	if ( (nump > 2 && !hasseating) || !getSeating(1) )
	{
		fprintf(out,"Meeting cancelled.\n");
		return 0;
	}
	
	for ( i = 0; i < nump; i++ ) fprintf(out,"%d ",order[i]+1);
	fprintf(out,"\n");
	return 0;
}