#include<stdio.h>

void main()
{
    printf("---LEAKY BUCKET ALGORITHM----\n\n");

    int bucketCapacity,outputRate,no_of_time_slots;
    int incoming,stored=0;
    printf("Enter bucket Capacity : ");
    scanf("%d",&bucketCapacity);

    printf("Enter Output Rate: ");
    scanf("%d",&outputRate);  //Must be less than bucketCapacity

    printf("Enter No.of time Slots :");
    scanf("%d",&no_of_time_slots);

    for(int i=1;i<=no_of_time_slots;i++)
    {
        printf("\n\nTime Slot-%d\nEnter no.of incoming packets : ",i);
        scanf("%d",&incoming);

        if(stored+incoming>bucketCapacity)
        {
            int dropped = (stored+incoming) - bucketCapacity;
            stored = bucketCapacity;
            printf("Bucket Overflow!Dropped: %d packets\n",dropped);
        }
        else
            stored = stored+incoming;

        if(stored>outputRate)
        {
            stored = stored-outputRate;
            printf("Transmitted : %d packets,Left in bucket : %d packets\n",outputRate,stored);
        }
        else
        {
            printf("Transmitted : %d packets,Left in Bucket : 0 packets\n",stored);
            stored=0; //Make a note
        }
    }

    while(stored>0)
    {
        if(stored>outputRate)
        {
            stored = stored-outputRate;
            printf("Transmitted : %d packets,Left in bucket : %d packets\n",outputRate,stored);
        }
        else
        {
            printf("Transmitted : %d packets,Left in Bucket : 0 packets\n",stored);
            stored=0;   //Make a note
        }
    }

    printf("\n\nAll Packets Transmitted Successfully...\n");
}
