/*

    Name:Ryan Kilkenney
    Date: 11/24/2020
    Purpose: Program takes a list of strings and a 2d vector of weights, sets a graph, and finds the shortest path 
             from the source string to the furtherest string 

*/


#include <iostream>
#include <vector>
#include <climits>

using namespace std;


//used to recursively print out the pred[] array, inspiration from link in README
void printp(int parent[], int j, vector<string> names) 
{   
    if (parent[j] == - 1) 
        return; 
  
    printp(parent, parent[j], names); 
    cout << names[j] << " ";
} 
  
//used to set up the printp function by finding the farthest distance and inputting it into the printp function 
void print(int dist[], int n, int parent[], vector<string> names) 
{ 
    int biggestDis = dist[0];
    int src = 0; 
    int index = 0;

    for(int i = 0; i < n; i++) {
        if(biggestDis < dist[i]) {
            biggestDis = dist[i];
            index = i;
        }
    }

    cout << names[src] << " ";
    printp(parent, index, names);
    cout << biggestDis << endl;
} 

//algorithm from the book and adapted to account for pred[], some help from link in README
void shortestPath(int vertex, int size, vector<vector<int> > weights, vector<string> names) {
    int smallestWeight[size]; //this holds the value of the shortest distances from the start postion to any other postion 
    int pred[size]; //this holds the actual path to each postion
    bool weightFound[size]; //this just holds a bool if a postion is in a shortest path 
    
    //this loop sets up all the values with a default value
    for(int j = 0; j < size; j++) {
        smallestWeight[j] = INT_MAX;
        weightFound[j] = false;
        pred[0] = -1;
    }
    smallestWeight[vertex] = 0; //distance of the start postion to the start postion is zero
    
    //this is the loop that is supposed to loop through the undertermined positions, find their distances and remove them from the set 
    for(int i = 0; i < size - 1; i++) {
        int minWeight = INT_MAX;
        int v;

        //this loop finds the vertex with the smallest distance and is also undetermined, also finds that vertex's predecessor 
        for(int j = 0; j < size; j++) 
            if(!weightFound[j]) 
                if(smallestWeight[j] < minWeight) {
                    v = j;
                    minWeight = smallestWeight[v];
                }

        //marks that postion as processed 
        weightFound[v] = true;

        //this updates the neighbors if necessary
        for(int j = 0; j < size; j++)
            if(!weightFound[j] && weights[v][j])
                if(smallestWeight[v] + weights[v][j] < smallestWeight[j]) {
                     smallestWeight[j] = minWeight + weights[v][j];
                     pred[j] = v;
                }
        
    }
    
    print(smallestWeight, size, pred, names);
}


int main() {
    int num = 0; //this is going to set the number of strings to be inputted and the size of the matirx
    int test_cases_num = 0; //this determines the amount of times the program is going to run
    string name = " "; //this is value that the inputs are set to before added to the names vector

    //this takes in the inputs for the number of times the program is going to run
    cin >> test_cases_num;

    //it takes in the number of inputs, the actual inputs, and the distances between them, and then runs the shortestPath function
    while(test_cases_num > 0) {
        cin >> num;

        vector<vector<int> > dis_matrix(num, vector<int>(num)); 
        vector<string> names;

        for(int i = 0; i < num; i++) {
            cin >> name;
            names.push_back(name);
        }

        for(int i = 0; i < num; i++) {
            for(int j = 0; j < num; j++) {
                cin >> dis_matrix[i][j];
            }
        }
    
        shortestPath(0, num, dis_matrix, names);

        test_cases_num--;
    }
    return 0;
}