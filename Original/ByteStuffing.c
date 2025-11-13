#include <stdio.h>
#include <string.h>
#define FLAG '$'
#define ESC  '&'

void characterStuffing(char data[])
{
    char stuffed[200];
    int i, j = 0;

    // Add starting FLAG
    stuffed[j++] = FLAG;

    for (i = 0; i < strlen(data); i++)
    {
        if (data[i] == FLAG || data[i] == ESC)
        {
            stuffed[j++] = ESC;  // Add escape character
        }
        stuffed[j++] = data[i];  // Add actual data
    }

    // Add ending FLAG
    stuffed[j++] = FLAG;
    stuffed[j] = '\0';
    printf("Stuffed Frame: %s\n", stuffed);
}

int main()
{
    char data[100];

    printf("Enter input data (e.g., AEFG): ");
    scanf("%s", data);
    characterStuffing(data);
    return 0;
}

//This program treats only $ and & as special characters
//Space refers to end of string

