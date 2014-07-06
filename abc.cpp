/**
 * French Australian Regional Informatics Olympiad 2010, Q2
 * Ananya Kumar, 2012
 * NUS High School
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<string> dic[21];
char next[256];
int N, M;
bool found;

int main ()
{
	int i, j, k;
	string tmps;
	scanf("%d",&N);
	//dic.assign(N,"");
	
	for ( i = 0; i < N; i++ )
	{
		cin >> tmps;
		dic[tmps.size()].push_back(tmps);
	}
	
	for ( i = 0; i < 21; i++ ) sort(dic[i].begin(),dic[i].end());
	scanf("%d",&M);
	
	for ( i = 'a'; i < 'z'; i++ ) next[i] = i+1;
	next['z'] = 'a';
	
	while ( M-- )
	{
		cin >> tmps;
		found = false;
		
		if ( binary_search(dic[tmps.size()].begin(),dic[tmps.size()].end(),tmps) )
		{
			cout << tmps << endl;
			continue;
		}
		
		for ( j = 0; j < tmps.size(); j++ )
		{
			tmps[j] = next[tmps[j]];
			
			for ( k = 0; k < 25; k++ )
			{
				if ( binary_search(dic[tmps.size()].begin(),dic[tmps.size()].end(),tmps) )
				{
					cout << tmps << endl;
					found = true;
					break;
				}
				
				tmps[j] = next[tmps[j]];
			}
			
			if ( found ) break;
		}
		
		if ( !found ) cout << "?" << endl;
	} 
}