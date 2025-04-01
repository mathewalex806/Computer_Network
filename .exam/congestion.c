#include <stdio.h>
#include <stdlib.h>

int main()
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

    //Leaky bucket algo

    int bucket = 0;
    for (int i=0; i<num_packets; i++)
    {
        printf("Incomming packet : %d\n", packets[i]);
        printf("Current bucket capacity : %d\n ", bucket);
        bucket+= packets[i];
        if (bucket>bucket_capacity)
        {
            printf("Overflow occured %d packets discarded\n", bucket - bucket_capacity);
            bucket = bucket_capacity;
        }
        //leak out rate
        int leaked  = (bucket>= leak_rate) ? leak_rate: bucket;
        bucket = bucket - leak_rate;
        printf("No of packets leaked : %d\n", leaked);
    }

    printf("Leaking out packets present in the bucket \n");
    while (bucket >0)
    {
        int leaked  = (bucket>= leak_rate) ? leak_rate: bucket;
        bucket = bucket - leak_rate;
        printf("No of packets leaked : %d\n", leaked);
    }

}