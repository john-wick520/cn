#include<stdio.h>
#include<string.h>

#define ESC '&'
#define FLAG '$'

void main(){
    char data[100];
    printf("Enter input data(E.g:Hello) : ");
    scanf("%s",&data);

    char stuffedData[200];
    int j=0;

    stuffedData[j++] = FLAG;
    for(int i=0;i<strlen(data);i++)
    {
        if(data[i]==ESC || data[i]==FLAG)
            stuffedData[j++] = ESC;

        stuffedData[j++]=data[i];
    }
    stuffedData[j++]= FLAG;
    stuffedData[j]='\0';

    printf("Stuffed Data : %s",stuffedData);
}
