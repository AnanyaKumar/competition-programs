/**
 
 Author: Ananya Kumar
 Organization: NUS High School
 
 Dijkstra's Algorithm implementation.
 Prints out all the shortest paths
 between source and destination.
 All edge weights must be positive.
 
 Time Complexity: O(Vertices^2)
 
 **/

#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#define INF 1000000

bool prompt = true; //Should the program prompt the user for input?
map<string,int> nameToNum; //Converts the name of a vertex to an assigned number
vector<string> numToName; //Converts the assigned number of a vertex back to its name
int numNodes = 0; //The number of vertices in the graph

string reverse ( string s )
{
	string rs = "";
	for ( int i = s.size()-1; i >= 0; i-- ) rs += s[i];
	return rs;
}

int dfs ( vector<int> *prevArray, int ending, string path ) //Prints out all paths, returns the number of paths
{
	string newpath = path + reverse(numToName[ending]) + " ";
	int numpaths = 0;
	
	if ( (prevArray[ending]).size() == 0 ) //If we have reached the beginning of a path print it out
	{
		cout << reverse(newpath) << endl;
		return 1;
	}
	
	else //Otherwise print out all possible paths before this recursively
	{
		for ( int i = 0; i < (prevArray[ending]).size(); i++ )
		{			
			numpaths += dfs(prevArray,prevArray[ending][i],newpath);
		}
		
		return numpaths;
	}
}

int main ()
{	
	//Prelude
	
	string nl, nl2;
	int i, j, k;
	int w;
		
	if (prompt) cout << "Enter the number of vertices in your graph: ";
	cin >> numNodes;
	if (prompt) cout << "Enter the names of your vertices separated by spaces and/or newlines." << endl;
	
	//Enter the names of the nodes
	
	for ( i = 0; i < numNodes; i++ )
	{
		cin >> nl;
		numToName.push_back(nl);
		nameToNum[nl] = i;
	}
	
	//Enter the connections between each node
	
	int adj[numNodes][numNodes]; //The weight of the edges between every vertex
	int numedges; //The total number of edges
	
	for ( i = 0; i < numNodes; i++ ) //Set all edges to infinity at the start
		for ( j = 0; j < numNodes; j++ )
			adj[i][j] = INF;
	
	if (prompt) cout << "Enter the number of edges in your graph: ";
	cin >> numedges;
	if (prompt) cout << "Enter the edges in your graph in the format 'A B C' (without the quotes), which means draw a directed edge from A to B of positive weight C." << endl;
	
	for ( i = 0; i < numedges; i++ ) //Read in and store all of the edges in the graph
	{
		cin >> nl >> nl2 >> w;
		adj[ nameToNum[nl] ][ nameToNum[nl2] ] = w;
	}
	
	//Find the desired start vertex
	
	int start;
	if (prompt) cout << "Enter the vertex from which the search should begin: ";
	cin >> nl;
	start = nameToNum[nl];
	
	//Run Djikstra to find shortest distance (must print out the method to find)
	
	bool computed[numNodes]; //Has the shortest distance to the node been computed?
	int shortest[numNodes]; //The shortest distance to every node so far
	vector<int> previous[numNodes]; //The previous node(s) in the shortest path
	
	for ( i = 0; i < numNodes; i++ ) //Intialize arrays
	{
		shortest[i] = INF;
		computed[i] = false;
		previous[i] = vector<int>(0);
	}
	
	int cur;
	int closestd;
	shortest[start] = 0;
	
	for ( i = 0; i <= numNodes; i++ )
	{
		//Print the information for current iteration
		
		printf("Iteration Number %d\n\n",i+1);
		printf("%15s %15s %15s\n","Node Name","Distance","Previous");
		
		for ( j = 0; j < numNodes; j++ )
		{
			if ( shortest[j] != INF ) printf("%15s %15d        ",(numToName[j]).c_str(),shortest[j]);
			else printf("%15s %15s        ",(numToName[j]).c_str(),"Infinity");
			
			for ( k = 0; k < (previous[j]).size(); k++ )
			{
				printf("%s ",(numToName[previous[j][k]]).c_str());
			}
			
			printf("\n");
		}
		
		cout << endl;
		if ( i == numNodes ) break;
		
		//Get the closest vertex whose shortest distance hasn't been computed
		
		closestd = INF;
		
		for ( j = 0; j < numNodes; j++ )
		{
			if ( !computed[j] && shortest[j] < closestd )
			{
				closestd = shortest[j];
				cur = j;
			}
		}
		
		//Since that vertex is the closest, its shortest distance has actually been computed!
		
		computed[cur] = true;
		
		//Use this vertex to find the new shortest distance to all other vertices
		
		for ( j = 0; j < numNodes; j++ )
		{
			if ( adj[cur][j]+shortest[cur] == shortest[j] && shortest[j] != INF ) //If the distance through cur is the same, add the vertex to 'previous'
				(previous[j]).push_back(cur);
			
			else if ( adj[cur][j]+shortest[cur] < shortest[j] ) //If the distance through cur is shorter then edit the shortest distance
			{
				shortest[j] = adj[cur][j]+shortest[cur];
				(previous[j]).clear();
				(previous[j]).push_back(cur);
			}
		}
	}
	
	cout << endl << "Algorithm Completed! :D" << endl << endl;
	
	//Get the ending vertex
	
	int endv;
	if (prompt) cout << "Enter the vertex to which you want the shortest paths: ";
	cin >> nl;
	endv = nameToNum[nl];
	
	//Print out all possible shortest paths
	
	cout << "The shortest paths are: " << endl;
	int numpaths = dfs(previous,endv,"");
	printf("\nThere are %d paths of the shortest length.\n",numpaths);
	printf("The distance of the shortest path is %d.",shortest[endv]);
	return 0;
}