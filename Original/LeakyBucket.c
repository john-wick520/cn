//Leaky Bucket Algorithm
//Bucket can be router or switch
#include<stdio.h>
#include<stdlib.h>

void main()
{
    int bucketSize,outputRate,n,incoming;
    int stored = 0,i;

    printf("=== Leaky Bucket Algorithm Simulation ===\n");
    //Bucket Capacity = No Of Packets a bucket can hold.
    printf("Enter bucket capacity (in packets): ");
    scanf("%d",&bucketSize);

    //Output Rate = No. of packets that a bucket transfer outward.
    printf("Enter output rate (packets transfer per second): ");
    scanf("%d",&outputRate);

    //No of times the packets are inserting into bucket.
    printf("Enter number of incoming packets (time slots): ");
    scanf("%d",&n);

    //Iterate over all time slots
    for(i = 1; i <= n; i++)
    {
        //No of packets coming into the bucket for that particular time slot
        printf("\nTime %d: Enter number of incoming packets: ",i);
        scanf("%d",&incoming);
        printf("Incoming packets: %d\n",incoming);
        //If bucket(stored+incoming) cannot accomdate incoming packets,
        //then drop some packets(incoming).
        if(incoming + stored > bucketSize)
        {
            int dropped = (incoming + stored) - bucketSize;
            stored = bucketSize;
            printf("Bucket Overflow! Dropped packets : %d\n",dropped);
        }
        else
            stored = stored+incoming;

        //No. of Stored Packets > No. of Outgoing packets
        if(stored > outputRate)
        {
            stored = stored-outputRate;
            printf("Transmitted: %d | Packets left in bucket: %d\n",outputRate,stored);
        }
        else
        {
            printf("Transimitted: %d | Packets left in bucket : 0\n",stored);
            stored = 0;
        }
    }

    //If all time slots completed but there are left over packets in the bucket,
    //then Drain remaining packets
    while(stored > 0){
        if(stored > outputRate)
        {
            stored = stored - outputRate;
            printf("\nTransmitted: %d | Packets left in bucket: %d\n",outputRate,stored);
        }
        else
        {
            printf("\nTransimitted: %d | Packets left in bucket : 0\n",stored);
            stored = 0;
        }
    }
    printf("\nAll packets transmitted successfully\n");
}
