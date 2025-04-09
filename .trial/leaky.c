#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void main()
{
    int bucket_capacity, leak_rate, num_packets;
    
    printf("Enter the bucket capacity: ");
    scanf("%d", &bucket_capacity);

    printf("Enter the leak rate: ");
    scanf("%d", &leak_rate);

    printf("Enter the number of packets: ");
    scanf("%d", &num_packets);

    int packets[num_packets];
    printf("Enter the size of each incoming packet:\n");
    for (int i = 0; i < num_packets; i++) {
        scanf("%d", &packets[i]);
    }

    printf("\nLeaky Bucket Simulation:\n");

    int bucket = 0;
    for(int i=0; i<num_packets; i++)
    {
        printf("Incomming packet size: %d\n", packets[i]);
        bucket += packets[i];
        if (bucket> bucket_capacity)
        {
            printf("Overflowed : Dropped %d packets\n", bucket - bucket_capacity);
            bucket = bucket_capacity;
        }

        bucket -= leak_rate;
        if (bucket < 0) {
            bucket = 0;
        }
    }
}