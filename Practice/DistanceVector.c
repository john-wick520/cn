#include<stdio.h>

#define INF 999
#define MAX 20

struct routingTable{
    int dist[MAX];
    int nextHop[MAX];
};

void main(){
    int n;
    char nodes[MAX][20];
    int cost[MAX][MAX];
    struct routingTable rt[MAX];

    printf("Enter no. of routers :");
    scanf("%d",&n);

    printf("Enter names of routers(E.g:A,B,C..) :");
    for(int i=0;i<n;i++)
        scanf("%s",&nodes[i]);

    printf("Enter adjacency matrix(delay cost,INF=999,loop=0):\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            scanf("%d",&cost[i][j]);
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            rt[i].dist[j] = cost[i][j];

            if(cost[i][j]!=INF && i!=j)
                rt[i].nextHop[j] = j;
            else
                rt[i].nextHop[j] = -1;

        }
    }

    int updated = 0;
    do{
        updated = 0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<n;k++)
                {
                    if(rt[i].dist[j] > cost[i][k]+rt[k].dist[j])
                    {
                        rt[i].dist[j] = cost[i][k]+rt[k].dist[j];
                        rt[i].nextHop[j] = k; //make a note
                        updated =1;
                    }
                }
            }
        }
    }while(updated);

    printf("FINAL ROUTING TABLES\n");
    for(int i=0;i<n;i++)
    {
        printf("Routing Table - %s\n",nodes[i]);
        printf("%-10s %-10s %-10s\n","Destination","Distance","Next Hop");
        for(int j=0;j<n;j++)
        {
            printf("%s\t\t",nodes[j]);


            if(rt[i].dist[j] == INF)
                printf("INF\t\t");
            else
                printf("%d\t\t",rt[i].dist[j]);

            if(rt[i].nextHop[j]!=-1)
                printf("%s\n",nodes[rt[i].nextHop[j]]);
            else
                printf("-\n");

        }
    }
}
