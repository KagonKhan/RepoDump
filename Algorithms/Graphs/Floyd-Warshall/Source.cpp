#include <iostream>
#include <limits.h>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
int nodes, edges;
#define INF 999999

int outputNumber = 1, iterations = 0;

void printSolution(const std::vector<std::vector<int>>& graph, const std::vector<std::vector<int>>& routes);


void load(std::string filename);
void floydWarshall(const std::vector<std::vector<int>>& graph) {


    std::vector<std::vector<int>> dist(edges, std::vector<int>(edges)), routes(edges, std::vector<int>(edges));
    int i, j, k;

    for (i = 0; i < nodes; i++)
        for (j = 0; j < nodes; j++) {
            dist[i][j] = graph[i][j];
            if (i != j)
                routes[i][j] = j + 1;
        }


    for (k = 0; k < nodes; k++) 
        for (i = 0; i < nodes; i++) 
            for (j = 0; j < nodes; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    routes[i][j] = routes[i][k];
                }
                iterations++;
            }

    printSolution(dist, routes);
}

void printSolution(const std::vector<std::vector<int>>& graph, const std::vector<std::vector<int>>& routes) {
    int numroute = 0;

    std::string outputName = "floyd_out_" + std::to_string(outputNumber) + ".txt";
    ofstream output(outputName);

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (graph[i][j] > 0.9 * INF)
                output << "INF" << "\t";
            else
                output << graph[i][j] << "\t";
        }
        output << endl;
    }

    output << endl;

    if (output.is_open()) {
        int k;
        for (int i = 0; i < nodes; i++) 
            for (int j = 0; j < nodes; j++) 

                if (i != j) {
                    output << "d[" << i + 1 << "][" << j + 1 << "] = " << graph[i][j] << "\t";
                    numroute++;
                  
                    output << "Path: " << i + 1;
                    k = i + 1;
                    do {
                        k = routes[k - 1][j];  
                        output << "->" << k;
                    }  while (k != j + 1);
                    output << "\n";
                }
            
        
    }
    output.close();
    std::cout << outputName << "\t" << nodes << "\t" << edges << "\t" << numroute << "\t" << iterations << std::endl;
}


int main() {
    load("floyd1.txt"), outputNumber++;
    load("floyd2.txt"), outputNumber++;
    load("floyd3.txt"), outputNumber++;
    load("floyd4.txt"), outputNumber++;
    load("floyd5.txt"), outputNumber++;
  //  system("Pause"), system("CLS");
    return 0;
}


void load(std::string filename) {
    std::ifstream inFile(filename);
    inFile >> nodes >> edges;

    std::vector<std::vector<int>> graph(edges, std::vector<int>(edges, INF));
    int node, edge, weight;
    //Read data

    for (int i = 0; i < edges; i++) {
        for (int j = 0; j < edges; j++) {
            if (j == i) {
                graph[i][j] = 0;
                continue;
            }
            inFile >> node >> edge >> weight;
            graph[node - 1][edge - 1] = weight;
        }
    }
    std::cout << filename << "\t";
    floydWarshall(graph);
}