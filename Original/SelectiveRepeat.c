/*
    Write a Program to implement Sliding window protocol for Selective repeat.
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>    //for srand(time(0))
#define MAX 50
void main()
{
    int totalFrames,windowSize;
    int frameStatus[MAX];
    int i,choice,resend;

    srand(time(0)); //To generate different sequence of random numbers

    printf("\n===Selective Repeat ARQ Simulation ===\n");
    printf("Enter total number of frames to send: ");
    scanf("%d",&totalFrames);
    printf("Enter window size: ");
    scanf("%d",&windowSize);

    for(i=0;i<totalFrames;i++)
        frameStatus[i]=0;

    int sent=0;
    while(sent<totalFrames)
    {
         printf("\n--- Sending Window of Frames [%d - %d] ---\n",
               sent, (sent + windowSize - 1 < totalFrames) ? sent + windowSize - 1 : totalFrames - 1);

        // send frames
        for(i=sent;i<sent+windowSize && i<totalFrames;i++)
        {
            if(frameStatus[i]==0)
                printf("Frame %d sent.\n",i);
        }
        // check ACK randomly
        for(i=sent;i<sent+windowSize && i<totalFrames;i++)
        {
            if(frameStatus[i]==0)
            {
                choice = rand()%2; // 0 = lost, 1 = received
                if(choice == 1)
                {
                    printf("ACK for frame %d received.\n",i);
                    frameStatus[i]=1;
                }
                else
                    printf("Frame %d lost / not acknowledge.\n",i);
            }
        }

        // resend lost frames automatically
        for (i = sent; i < sent + windowSize && i < totalFrames; i++)
        {
            if (frameStatus[i] == 0)
            {
                printf("Resending frame %d...\n", i);
                printf("ACK for frame %d received now.\n", i);
                frameStatus[i] = 1;
            }
        }

        // slide window
        while(sent<totalFrames && frameStatus[sent]==1)
            sent++;
    }
    printf("\nAll frames sent and acknowledged successfully!\n");
}

/*
    --------------------------------- Explanation ---------------------------------

    1. srand(time(0)):
       - srand() is used to "seed" the random number generator.
       - time(0) gives the current system time in seconds.
       - This ensures that each run of the program produces a different sequence of random numbers.
       - Without it, rand() would generate the same sequence every time the program is run.

    2. Random ACK simulation (choice = rand() % 2):
       - rand() generates a pseudo-random integer.
       - rand() % 2 will give either 0 or 1.
           -> 0 = ACK lost (frame not acknowledged).
           -> 1 = ACK received (frame successfully acknowledged).
       - This simulates an unreliable channel where frames can be randomly lost or received.

    Together, these make the program behave like a real Selective Repeat ARQ protocol
    with randomness in acknowledgments and retransmissions.
*/
