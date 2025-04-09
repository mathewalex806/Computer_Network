#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int costMatrix[20][20];
int n;

struct routers{
    int distance[20];
    int adjacent[20];
}node[20];

int main()
{
    printf("Enter the number of nodes.\n");
    scanf("%d",&n);

   
    printf("Enter the cost Matrix\n");

    for (int i= 0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            scanf("%d",&costMatrix[i][j]);
            if (i==j)
            {
                costMatrix[i][j] = 0;
            }

            //set the distance and the adjacent values.

            node[i].distance[j] = costMatrix[i][j];
            node[i].adjacent[j] = j;
        }
    }

    //Calculating shortest distance

    int k, i=0, j=0;

    for(k=0; k<n; ++k)
    {
        for (i=0; i<n ; ++i)
        {
            for(j=0 ; j<n ; ++j)
            {
                if(node[i].distance[j] > node[i].distance[k] + node[k].distance[j])
                {
                    node[i].distance[j] = node[i].distance[k] + node[k].distance[j];
                    node[i].adjacent[j] = node[i].adjacent[k];
                }
            }
        }
    }

    for (i=0; i < n; i++)
    {
        printf("Router %d\n",i+1);
        for(j =0; j< n; j++)
        {
            printf("Distance to node %d through %d : %d\n", j+1,node[i].adjacent[j]+1, node[i].distance[j]);
        }
    }
    
}