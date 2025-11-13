#include<stdio.h>
#include<string.h>

void main(){
    char data[100];
    printf("Enter Data String(10010100) :");
    scanf("%s",data);

    char stuffedData[200];
    int j=0,count=0;
    for(int i=0;i<strlen(data);i++)
    {
        stuffedData[j++]=data[i];  //Make a note
        if(data[i]=='1')
        {
            count++;        //Make a note
            if(count==5)
            {
                stuffedData[j++] = '0';
                count=0;
            }

        }
        else
        {
            count=0;
        }
    }
    stuffedData[j]='\0';

    printf("Stuffed Data : %s",stuffedData);
}
