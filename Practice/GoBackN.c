#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void main(){
    printf("-------- GO BACK N ---------\n");
    int totalFrames;
    printf("Enter total no. of frames : ");
    scanf("%d",&totalFrames);

    int windowSize;
    printf("Enter window Size: ");
    scanf("%d",&windowSize);

    srand(time(0));

    int sent = 0;
    while(sent<totalFrames){
        printf("\nSending Frames[%d-%d]...\n",sent,(sent+windowSize-1)<totalFrames ? sent+windowSize-1:totalFrames-1);

        if(rand()%100 < 40)
        {
            int lostFrame = sent + (rand()%windowSize);
            if(lostFrame >= totalFrames) lostFrame = totalFrames-1;
            printf("Reciever : Frame-%d lost,Go Back and Resend from Frame-%d\n\n",lostFrame,lostFrame);
            sent = lostFrame;
        }
        else
        {
            int ack = sent + windowSize;
            if(ack>totalFrames) ack=totalFrames;
            printf("Reciever : Acknowledged upto Frame-%d....\n\n",ack-1);
            sent = ack;
        }
    }
    printf("All %d Frames Sent Successfully\n\n",totalFrames);
}

