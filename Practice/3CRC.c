#include<stdio.h>

int genLength,frameLength;
int temp[512],rem[512];

void copy_temp_to_rem();
void compute_crc_check(int[]);
void print_array(int[],int,int);

void main()
{
    // Example generator polynomials
    int gen12[] = {1,1,0,0,0,0,0,0,0,1,1,1,1};          // CRC-12
    int gen16[] = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1};  // CRC-16
    int genCCITT[] = {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1}; // CRC-CCITT


    // Choose generator here
    int *gen = genCCITT;
    genLength = 17;


    char data[512];
    printf("Enter data String : ");
    scanf("%s",data);

    int input[512];
    frameLength=0;
    for(int i=0;i<strlen(data);i++)
    {
        for(int j=7;j>=0;j--)
        {
            input[frameLength++]=(data[i] >> j) & 1;
        }
    }

    for(int i=0;i<frameLength;i++)
        temp[i]=input[i];
    for(int i=frameLength;i<frameLength+genLength-1;i++)
        temp[i]=0;

    copy_temp_to_rem();
    compute_crc_check(gen);

    for(int i=frameLength;i<frameLength+genLength-1;i++)
        temp[i]=rem[i];

    printf("Transmitted Frame : ");
    print_array(temp,0,frameLength+genLength-1);

    printf("Enter Received Data :");
    for(int i=0;i<frameLength+genLength-1;i++)
        scanf("%d",&temp[i]);

    copy_temp_to_rem();
    compute_crc_check(gen);

    int error=0;
    for(int i=frameLength;i<frameLength+genLength-1;i++)
    {
        if(rem[i]!=0)
            error=1;
    }

    if(error)
        printf("Error Occured\n");
    else
        printf("Data Received Correctly\n");
}

void copy_temp_to_rem(){
    for(int i=0;i<frameLength+genLength-1;i++)
        rem[i] = temp[i];
}

void compute_crc_check(int gen[]){
    for(int i=0;i<frameLength;i++)
    {
        if(rem[i]==1)
        {
            for(int j=0;j<genLength;j++)
            {
                rem[i+j] = (rem[i+j]!=gen[j])?1:0;
            }
        }
    }
}

void print_array(int arr[],int start,int end){
    for(int i=start;i<end;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
