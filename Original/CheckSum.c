#include <stdio.h>
void main()
{
    int data[100], length, i, sum = 0, checksum;

    // Sender Side
    printf("Enter length of data: ");
    scanf("%d", &length);
    printf("Enter %d data integers:\n", length);
    for(i = 0; i < length; i++)
    {
        scanf("%d", &data[i]);
        sum += data[i]; // Sum of data
    }
    printf("\nSum(sender side) : %d\n",sum);

    checksum = ~sum; // One's complement
    printf("Checksum (sender side): %d\n\n", checksum);

    // Receiver Side
    int receivedSum = 0;

    //data[2]=82; //Modifiying the data , to caught the error

    for(i = 0; i < length; i++)
    {
        receivedSum += data[i];
    }
    printf("Sum(receiver side) : %d\n",receivedSum);

    receivedSum += checksum;    //Adding sender checksum(1's complement) to Receiver Sum
    printf("Checksum (receiver side): %d\n\n", ~receivedSum);

    if(~receivedSum == 0)
        printf("No error: Data received correctly.\n");
    else
        printf("Error detected in received data.\n");
}

//1's Complement may vary from compiler to compiler
