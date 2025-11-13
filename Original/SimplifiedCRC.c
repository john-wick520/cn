#include<stdio.h>
#include<string.h>

int frameLength,genLength;
int temp[32],rem[32];

void copy_temp_to_rem();
void compute_crc_check();
void print_array(int[],int,int);

void main()
{
    //gen[] values are not properly
    int gen[] = {1,1,0,0,0,0,0,0,0,1,1,1,1}; //CRC-12
    //int gen[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1}; //CRC-16
    //int gen[] = {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1}; //CRC-CCITT

    genLength = 13; //CRC-12  , 16 FOR CRC-16 & CRC-CCITT

    //Take frame data input
    printf("Enter no.of data bits : ");
    scanf("%d",&frameLength);

    int input[frameLength];
    printf("Enter %d data bits :",frameLength);
    for(int i=0;i<frameLength;i++)
        scanf("%d",&input[i]);

    //Append (genLength-1) zeroes to input data
    for(int i=0;i<frameLength;i++)
        temp[i] = input[i];
    for(int i=frameLength;i<frameLength+genLength-1;i++)
        temp[i]=0;

    copy_temp_to_rem();
    compute_crc_check(gen);

    //Adding rem(crc code)at end of frame(data)
    //temp[] is already having data input from 0 to frameLength-1
    for(int i=frameLength;i<frameLength+genLength-1;i++)
        temp[i] = rem[i];

    printf("Transmitted Frame : ");
    print_array(temp,0,frameLength+genLength-1);

    //Receiver Side
    printf("Enter Received Frame : ");
    for(int i=0;i<frameLength+genLength-1;i++)
        scanf("%d",&temp[i]);

    copy_temp_to_rem();
    compute_crc_check(gen);

    printf("Remainder at receiver side : ");
    print_array(rem,frameLength,frameLength+genLength-1);

    int error=0; //Flag variable
    for(int i=frameLength;i<frameLength+genLength-1;i++)
    {
        if(rem[i]!=0)
        {
            error = 1;
        }
    }

    if(error)
        printf("Error Occured...!\n");
    else
        printf("Data Received Correctlyyy....!");
}

void copy_temp_to_rem(){
    for(int i=0;i<frameLength+genLength-1;i++)
        rem[i]=temp[i];
}

void compute_crc_check(int gen[]){
    for(int i=0;i<frameLength;i++)
    {
        if(rem[i]==1)
        {
            for(int j=0;j<genLength;j++)
            {
                rem[i+j] = rem[i+j]!=gen[j]?1:0;  //XOR Operation
            }
        }
    }
}

void print_array(int arr[],int start,int end){
    for(int i=start;i<end;i++)
        printf("%d ",arr[i]);
    printf("\n");
}
