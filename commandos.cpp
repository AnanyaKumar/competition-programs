/**
 * Asia-Pacific Informatics Olympiad 2010, Q1
 * Ananya Kumar, 2011
 * NUS High School
 *
 * Gets 70/100 (Bronze cutoff was 83/300)
 */

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

long sfq[1000001] = {0};
long memo[1000001] = {0};
long a, b, c;
long num, sum, prevTemp;

long computePolynomial ( int N )
{
	return a * N * N + b * N + c;
}

int main ()
{
	long temp;
	sum = 0;
	int i,j;
	cin >> num;
	cin >> a >> b >> c;
	long polMax = abs((int)(sqrt(abs(c)/(-a))));
	cout << c << " " << a << endl;
	
	for ( i = 1; i <= num; i++ ) 
	{ 
		cin >> temp;
		sum += temp;
		sfq[i] = sum;
	}
	
	cout << polMax << " " << (int)(sum/num) << endl;
	
	for ( i = 0; i < num; i++ )
	{		
		for ( j = i+1; j <= num; j++ )
		{
			temp = computePolynomial(sfq[j] - sfq[i]);
			if ( abs(i-polMax) < 110 && i < i < num-1000 ) break;
			prevTemp = temp;
			memo[j] = max(memo[j],memo[i]+temp);
		}
	}
	
	cout << memo[num] << endl;
}