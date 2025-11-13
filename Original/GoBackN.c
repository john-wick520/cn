#include<stdio.h>
#include <stdlib.h> // for rand(), srand()
#include <time.h>   // for time()

void main()
{
    int totalFrames,windowSize;
    int i,sent=0,lost_frame;

    srand(time(0)); // seed random number generator

    printf("\n===GO-Back-N ARQ Simulation ===\n");
    printf("Enter total number of frames to send: ");
    scanf("%d",&totalFrames);
    printf("Enter window size: ");
    scanf("%d",&windowSize);

    while(sent<totalFrames)
    {
        printf("\n--- Sending Window of Frames [%d - %d] ---\n",
               sent, (sent + windowSize - 1 < totalFrames) ? sent + windowSize - 1 : totalFrames - 1);

         // Randomly decide if a frame is lost in this window
        // 40% chance of loss, 60% chance all received
        if (rand() % 100 < 40)
        {
            lost_frame = sent + (rand() % windowSize); // random frame in window
            if (lost_frame >= totalFrames)
                lost_frame = totalFrames - 1;

            printf("Receiver: Frame %d lost! Go back and resend from %d\n", lost_frame, lost_frame);
            sent = lost_frame; // go back and resend from lost frame
        }
        else
        {
            int ack = sent + windowSize;
            if (ack > totalFrames) ack = totalFrames;
            printf("Receiver: Acknowledged up to frame %d\n", ack - 1);
            sent = ack; // slide window forward
        }
    }
    printf("\nAll frames sent successfully using GO-BACK-N!\n");

}

/*
    ---------------------------------- Explanation ----------------------------------

    1. rand() % 100 < 20
       - rand() generates a pseudo-random integer.
       - rand() % 100 gives a number between 0 and 99.
       - '< 20' means about 20% probability of frame loss, 80% probability of success.
       - This simulates a noisy channel where some frames are lost randomly.

    2. lost_frame = sent + (rand() % windowSize)
       - Selects a random frame inside the current window as the "lost" frame.
       - Example: if window is [3 - 5] and rand()%windowSize = 1, then lost_frame = 3 + 1 = 4.
       - Ensures that only frames within the current transmission window can be lost.

    Together:
       → With 20% probability, a random frame inside the current window is treated as lost.
       → Then Go-Back-N ARQ requires the sender to go back and retransmit from that lost frame.
*/
