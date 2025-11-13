
#include<stdio.h>
#define INF 999
#define MAX 20 //Max no. of routers

struct RoutingTable
{
    int dist[MAX];
    int nextHop[MAX];  //Holds the index of next router to forward packets toward each destination.
};

void main()
{
    int n;
    int cost[MAX][MAX];
    char nodes[MAX][20]; //20(MAX) no. of strings each of 20 characters length.
    struct RoutingTable rt[MAX];
    int i,j,k;

    printf("Enter Number of nodes(hosts/routers): ");
    scanf("%d",&n);

    printf("Enter node names (e.g., H1, H2, ...):\n");
    for(i=0; i<n; i++)
    {
        printf("Node %d: ",i+1);
        scanf("%s",nodes[i]);
    }

    /* ADJACENCY MATRIX CREATION
         Delay cost represents the time or cost to travel
           from one node to another in a network graph.
         In the adjacency matrix:
            - A positive number indicates the delay between nodes.
            - A high value like 999 (INF) means no direct connection.
            - A value of 0 means no delay (self-loop).
    */
    printf("\nEnter adjacency matrix (delay cost, INF=999, 0 for self): \n");
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            scanf("%d", &cost[i][j]);
    }

    //Initialize routing tables
    for(i=0; i<n; i++)
    {
            for(j=0; j<n; j++)
            {
                rt[i].dist[j] = cost[i][j];

                //If there is a direct edge and no self loop
                if(cost[i][j] != INF && i!=j)
                    rt[i].nextHop[j] = j;
                else
                    rt[i].nextHop[j]= -1;
            }
    }

    int updated;  // Flag to track if any routing table was updated in the current iteration

    do {
        updated = 0;  // Reset update flag at the start of each iteration

        // Loop through each router 'i'
        for (i = 0; i < n; i++)
        {   // Loop through each possible destination 'j'
            for (j = 0; j < n; j++)
            {   // Loop through each possible intermediate router 'k'
                for (k = 0; k < n; k++)
                {

                    // Check if going from 'i' to 'j' via 'k' is shorter than current known path
                    if (rt[i].dist[j] > cost[i][k] + rt[k].dist[j])
                    {
                        rt[i].dist[j] = cost[i][k] + rt[k].dist[j];  // Update distance to shorter path
                        rt[i].nextHop[j] = k;  // Update next hop to go through router 'k'
                        updated = 1;  // Mark that an update occurred
                    }
                }
            }
        }
    } while (updated);  // Repeat until no updates are made (routing tables have converged)

    //Printing Routing Tables
    for(i=0; i<n; i++)
    {
        printf("\nRouting Table for Node %s:\n",nodes[i]);
        printf("Destination\tCost\t\tNextHop\n");
        for(j=0; j<n; j++)
        {
            //if(i==j) continue;
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
