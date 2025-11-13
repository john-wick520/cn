//Stop And Wait Protocol
//The sender waits for an acknowledgment after sending each frame before sending the next.
//Sir Has taken a choice variable(input from the user either 0 or 1) instead of ack=rand()%2;
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void main()
{
    int totalFrames;

    printf("=== Stop-and-Wait Protocol Simulation ===\n");
    printf("Enter total number of frames to send : ");
    scanf("%d",&totalFrames);
    printf("\n");

    sender(totalFrames);
}

void sender(int totalFrames)
{
    int i,ack;
    srand(time(0));  //To generate a random number everytime.

    for(i = 1; i <= totalFrames ; i++)
    {
        printf("Sender : Sending Frame %d\n",i);
        ack = rand()%2; //Generates binary number(o or 1)

        //Frame Received by the receiver
        if(ack == 1)
        {
            receiver(i);
            printf("Sender : ACK %d received \n\n",i);
        }
        else
        {
            printf("Sender : ACK %d lost. Retransmitting...\n",i);
            i--;
        }
    }
    printf("\nAll %d frames sent successfully!\n",totalFrames);
}

void receiver(int frame)
{
    printf("\nReceiver : Frame %d received.Send ACK %d...\n",frame,frame);
}
