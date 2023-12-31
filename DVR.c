#include <stdio.h>
struct router
{
    unsigned cost[20];
    unsigned from[20];
} routingTable[10];

int main()
{
    int costmat[20][20];
    int routers, i, j, k;
    printf("\nEnter the number of routers : ");
    scanf("%d", &routers); // Enter the routers
    printf("\nEnter the cost matrix :\n");
    for (i = 0; i < routers; i++)
    {
        for (j = 0; j < routers; j++)
        {
            scanf("%d", &costmat[i][j]);
            costmat[i][i] = 0;
            routingTable[i].cost[j] = costmat[i][j]; // initialise the distance equal to cost matrix
            routingTable[i].from[j] = j;
        }
    }

    int otherShorterPathExists;
    do
    {
        otherShorterPathExists = 0;
        for (i = 0; i < routers; i++) // We choose arbitary vertex k and we calculate the direct distance from the router i to k using the cost matrix and add the distance from k to router j
            for (j = 0; j < routers; j++)
                for (k = 0; k < routers; k++)
                    if (routingTable[i].cost[j] > costmat[i][k] + routingTable[k].cost[j])
                    { // We calculate the minimum distance
                        // note: routingTable[i].cost[k] = costmat[i][k]
                        routingTable[i].cost[j] = routingTable[i].cost[k] + routingTable[k].cost[j];
                        routingTable[i].from[j] = k;
                        otherShorterPathExists = 1;
                    }
    } while (otherShorterPathExists != 0);

    for (i = 0; i < routers; i++)
    {
        printf("\n\n For router %d\n", i + 1);
        for (j = 0; j < routers; j++)
        {
            printf("\t\nRouter %d via %d distance %d ", j + 1, routingTable[i].from[j] + 1, routingTable[i].cost[j]);
        }
    }
    printf("\n\n");
}
