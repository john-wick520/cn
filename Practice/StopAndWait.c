#include<stdio.h>
#include<time.h>

void main(){
    int total_no_frames;

    printf("=== Stop-and-Wait Protocol Simulation ===\n");
    printf("Enter no.of frames : ");
    scanf("%d",&total_no_frames);


    sender(total_no_frames);
}

void sender(int totalFrames)
{
    int ack;
    srand(time(NULL));

    for(int i=0;i<totalFrames;i++)
    {
        printf("Sender : Sending Frame: %d\n",i+1);

        ack = rand()%2;
        if(ack==1)
        {
            receiver(i);
            printf("Sender : ACK %d received \n\n",i+1);
        }
        else
        {
            printf("Sender : ACK %d lost. Retransmitting...\n",i+1);
            i--;
        }
    }
    printf("All %d frames sent successfully\n",totalFrames);
}

void receiver(int frame)
{
    printf("\nReceiver : Frame %d received.Send ACK %d...\n",frame+1,frame+1);
}
