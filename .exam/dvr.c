#include <stdio.h>
#include <stdlib.h>

int costMatrix[20][20];
int n;
struct routers
{
    int distance[20];
    int adjacent[20];
}node[20];

int main()
{
    printf("Enter the number of nodes : \n");
    scanf("%d",&n);

    for (int i=0; i<n ; i++)
    {
        for (int j=0; j<n; j++)
        {
            scanf("%d",&costMatrix[i][j]);
            costMatrix[i][i] = 0;
            // Initializing the node and the adjacency
            node[i].distance[j] = costMatrix[i][j];
            node[i].adjacent[j] = j;         
        }
    }
int k, i=0, j=0;
    //calculating routing table.
    for ( k=0 ; k<n ; ++k)
    {
        for ( i=0; i<n; ++i)
        {
            for( j=0; j< n; j++)
            {
                if (node[i].distance[j] > node[i].distance[k] + node[k].distance[j])
                {
                    node[i].distance[j] = node[i].distance[k] + node[k].distance[j];
                    node[i].adjacent[j] = node[i].adjacent[k];
                }
            }
        }
    }

    i =0, j=0; 
    for (i = 0; i < n; ++i) {
        printf("\nRouter %d\n", i + 1);
        for (j = 0; j < n; ++j) {
            printf("Node %d via %d : Distance %d\n", j + 1, node[i].adjacent[j] + 1, node[i].distance[j]);
        }
        printf("\n");
    }
}


