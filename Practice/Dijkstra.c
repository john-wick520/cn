#include<stdio.h>

#define INFINITY 9999
#define MAX 50

void dijkstra(int[MAX][MAX],int,int);
void printPath(int[],int);

void main(){
    int n;
    printf("Enter no.of Vertices : ");
    scanf("%d",&n);

    int graph[MAX][MAX];
    printf("Enter Adjacency Matrix(0 for no-edge) :\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&graph[i][j]);
        }
    }

    int src;
    printf("Enter source vertex : ");
    scanf("%d",&src);

    dijkstra(graph,src,n);
}

void dijkstra(int graph[MAX][MAX],int startnode,int n)
{
    int cost[n][n],distance[n],pred[n];
    int visited[n];

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cost[i][j] = (graph[i][j]!=0)?graph[i][j]:INFINITY;
        }
    }

    for(int i=0;i<n;i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = (cost[startnode][i]!=INFINITY) ? startnode : -1;
        visited[i]=0;
    }

    distance[startnode] = 0;
    pred[startnode] = -1;
    visited[startnode] =1;

    int count=1;
    while(count<n-1)
    {
        int minDist = INFINITY;
        int nextNode = -1;
        for(int i=0;i<n;i++)
        {
            if(!visited[i] && distance[i]<minDist)
            {
                minDist = distance[i];
                nextNode = i;
            }
        }

        if(nextNode == -1) break;

        visited[nextNode] = 1;

        for(int i=0;i<n;i++)
        {
            if(!visited[i])
            {
                if(minDist+cost[nextNode][i] < distance[i])
                {
                    distance[i] = minDist + cost[nextNode][i]; //Make a note
                    pred[i] = nextNode;
                }
            }
        }
        count++;
    }


    printf("\n%s %-10s %-10s\n","VERTEX","COST","PATH");
    printf("---------------------------------\n");
    for(int i=0;i<n;i++)
    {
        if(i!=startnode)
        {
            printf("%-10d",i);
            if(distance[i]==INFINITY)
                printf("%-10s %-10s","INF","NO PATH\n");
            else
            {
                printf("%-10d",distance[i]);
                printPath(pred,i);
                printf("\n");
            }
        }
    }
}

void printPath(int pred[],int node)
{
    if(pred[node]==-1){
        printf("%d",node);
        return;
    }
    printPath(pred,pred[node]);
    printf("->%d",node);
}

