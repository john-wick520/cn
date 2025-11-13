//CheckSum
#include<stdio.h>

void main(){
    int n;
    printf("Enter length of data: ");
    scanf("%d",&n);

    int arr[n];
    int senderSideSum=0;
    printf("Enter %d numbers(Integers) :",n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        senderSideSum += arr[i];
    }

    int checkSum = ~senderSideSum;
    printf("\nSender Side(Sum) : %d\n",senderSideSum);
    printf("CheckSum(Sender Side) : %d\n\n",checkSum);

    int receiverSideSum=0;
    //arr[1] = 30; //To demonstrate error
    for(int i=0;i<n;i++)
        receiverSideSum += arr[i];

    receiverSideSum += checkSum;
    printf("Receiver Side(Sum) : %d\n\n",~receiverSideSum);

    if(~receiverSideSum == 0)
        printf("Data Received Successfully,No Error Occured\n");
    else
        printf("Error Occured in data\n");
}
