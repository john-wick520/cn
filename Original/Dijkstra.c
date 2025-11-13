#include <stdio.h>

#define INFINITY 9999
#define MAX 10

void dijkstra(int G[MAX][MAX], int n, int startnode);
void printPath(int pred[], int node);

int main() {
    int G[MAX][MAX], n, v;
    printf("Enter number of vertices (max %d): ", MAX);
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &G[i][j]);

    printf("Enter starting node (0 to %d): ", n - 1);
    scanf("%d", &v);

    dijkstra(G, n, v);
    return 0;
}

void dijkstra(int G[MAX][MAX], int n, int startnode) {
    int cost[MAX][MAX], distance[MAX], pred[MAX];
    int visited[MAX], count, mindistance, nextnode;
    //distance[] stores the cost[sourcevertex][destinationvertex]
    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far


    // Initialize cost matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cost[i][j] = (G[i][j] == 0) ? INFINITY : G[i][j];

    // Initialize distances and predecessors
    for (int i = 0; i < n; i++) {
        distance[i] = cost[startnode][i];
        //Intially for all nodes,predecessor node is source node (or) -1
        pred[i] = (cost[startnode][i] != INFINITY) ? startnode : -1;
        visited[i] = 0;
    }

    distance[startnode] = 0; //distance of source vertex is zero (source vertex to source vertex)
    visited[startnode] = 1;
    count = 1;

    while (count < n - 1) {
        mindistance = INFINITY;
        nextnode = -1;

        //To identify the minimum distance and next node of the corresponding node
        for (int i = 0; i < n; i++) {
            if (!visited[i] && distance[i] < mindistance) {
                mindistance = distance[i];
                nextnode = i;
            }
        }

        if (nextnode == -1) break; // No reachable unvisited node

        visited[nextnode] = 1;

        //To find if a better path exists through next node for all remaining from source vertex.
        for (int i = 0; i < n; i++) {

            if (!visited[i]) {
                if (cost[nextnode][i] != INFINITY) {
                    //mindistance is the distance from source node to next node i.e cost[source][nextnode]
                    if (mindistance + cost[nextnode][i] < distance[i]) {
                        distance[i] = mindistance + cost[nextnode][i];
                        pred[i] = nextnode; //pred=nextnode,since from source node we reach destination node(i) through next node
                    }
                }
            }
        }
        count++;
    }

    // Print results
    printf("\n%-10s %-10s %-30s\n", "Vertex", "Distance", "Path");
    printf("--------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        if (i != startnode) {
            printf("%-10d", i);
            if (distance[i] == INFINITY) {
                printf("%-10s %-30s\n", "INF", "No path");
            } else {
                printf("%-10d ", distance[i]);
                printPath(pred, i);
                printf("\n");
            }
        }
    }
}

// Recursive path printer
void printPath(int pred[], int node) {
    if (pred[node] == -1) {
        printf("%d", node);
        return;
    }
    printPath(pred, pred[node]);
    printf(" -> %d", node);
}
