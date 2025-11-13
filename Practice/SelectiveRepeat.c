#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void main()
{
    int totalFrames;
    printf("Enter total no. of frames : ");
    scanf("%d",&totalFrames);

    int windowSize;
    printf("Enter window size : ");
    scanf("%d",&windowSize);

    int frameStatus[totalFrames];
    for(int i=0;i<totalFrames;i++)
        frameStatus[i]=0;

    srand(time(0));

    int sent=0;
    while(sent<totalFrames)
    {
        printf("\nSending Frames[%d-%d]...\n",sent,sent+windowSize-1<totalFrames?sent+windowSize-1:totalFrames-1);

        for(int i=sent;i<sent+windowSize && i<totalFrames;i++)
        {
            if(frameStatus[i]==0)
                printf("Sender : Sent Frame-%d\n",i);
        }

        for(int i=sent;i<sent+windowSize && i<totalFrames;i++)
        {
            if(frameStatus[i]==0)
            {
                int ack = rand()%2;
                if(ack==1)
                {
                    printf("Receiver : Recieved Frame-%d\n",i);
                    frameStatus[i]=1;
                }
                else
                {
                    printf("Receiver : Lost Frame - %d, Resend Frame - %d\n",i,i);
                }
            }
        }

        for(int i=sent;i<sent+windowSize && i<totalFrames;i++)
        {
            if (frameStatus[i] == 0)
            {
                printf("Sender : Resending frame %d...\n", i);
                printf("Receiver: Recieved Frame-%d\n", i);
                frameStatus[i] = 1;
            }

        }

        while(sent < totalFrames && frameStatus[sent]==1)
            sent++;
    }
    printf("\n\nAll %d frames sent successfully..\n",totalFrames);
}
