#include<stdio.h>
#include<math.h>

int dataBitsLength,parityBitsLength=0,totalLength;
int hammingCode[32];
int calculateParity(int);

void main(){
    printf("Enter length of data : ");
    scanf("%d",&dataBitsLength);

    int dataBits[dataBitsLength];
    printf("Enter Data (LSB to MSB): ");
    for(int i=0;i<dataBitsLength;i++)
        scanf("%d",&dataBits[i]);

    while((int)pow(2,parityBitsLength) < dataBitsLength+parityBitsLength+1)
        parityBitsLength++;

    totalLength = dataBitsLength+parityBitsLength;

    int dataIndex=0,parityIndex=0;
    for(int i=0;i<totalLength;i++)
    {
        if(i == (int)pow(2,parityIndex)-1)
        {
            hammingCode[i] = 0;
            parityIndex++;
        }
        else{
            hammingCode[i] = dataBits[dataIndex++];
        }
    }

    for(int i=0;i<parityBitsLength;i++)
    {
        int position = (int)pow(2,i);
        int value = calculateParity(position);
        hammingCode[position-1]=value;
    }

    printf("Calculated Code(Sender side , LSB to MSB) : ");
    for(int i=0;i<totalLength;i++)
        printf("%d ",hammingCode[i]);
    printf("\n\n");


    printf("Enter Received code(LSB to MSB) : ");
    for(int i=0;i<totalLength;i++)
        scanf("%d",&hammingCode[i]);

    int errorPosition=0;
    for(int i=0;i<parityBitsLength;i++)
    {
        int position = (int)pow(2,i);
        int value = calculateParity(position);
        if(value!=0)
            errorPosition += position;
    }
    if(errorPosition == 0)
        printf("\n\nData Received Correctly\n");
    else{
        printf("\n\nError caught at position-%d\n\n",errorPosition);

        hammingCode[errorPosition-1] ^= 1;

        printf("After Correction hamming Code(LSB to MSB) : ");
        for(int i=0;i<totalLength;i++)
            printf("%d ",hammingCode[i]);
        printf("\n");
    }
}

int calculateParity(int parityPosition)
{
    int count=0;
    for(int i=parityPosition-1;i<totalLength;i+=2*parityPosition)
    {
        for(int j=i;j<i+parityPosition && j<totalLength;j++)
        {
            if(hammingCode[j]==1)
                count++;
        }
    }
    if(count%2==0)
        return 0;
    else
        return 1;
}
