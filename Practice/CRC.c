#include<stdio.h>
#include<string.h>

char gen_input[20];
int gen[20],data[50],temp[50],rem[50];
int data_length,gen_length;

void select_generator();
void set_genInput();
void set_frameInput();
void append_zeroes();
void print_array(int[],int,int);
void copy_temp_to_rem();
void compute_crc();


void main(){
    select_generator();
    set_genInput();

    set_frameInput();

    append_zeroes();
    printf("Frame(Input Data) after appending zeroes : ");
    print_array(temp,0,data_length+gen_length-1);

    copy_temp_to_rem();
    compute_crc();

    printf("Remainder After computing CRC :");
    print_array(rem,data_length,data_length+gen_length-1);

    printf("Transimitting data with CRC...\n");
    for(int i=data_length;i<data_length+gen_length-1;i++)
    {
        temp[i]=rem[i];
    }
    printf("Transmitted frame: ");
    print_array(temp, 0, data_length + gen_length - 1);

    printf("\nReceiving frame and checking for errors...\n");
    printf("Received frame: ");
    //temp[3]^=1; //To simulate error
    print_array(temp, 0, data_length + gen_length - 1);

    copy_temp_to_rem();
    compute_crc();

    printf("Remainder After computing CRC :");
    print_array(rem,data_length,data_length+gen_length-1);

    for(int i=data_length;i<data_length+gen_length-1;i++)
    {
        if(rem[i]!=0)
        {
            printf("\n\nERROR occured in received data\n\n");
            return;
        }
    }

    printf("\n\nData Received Successfully....\n\n");

}

void select_generator(){
    int choice;
    printf("Select a CRC\n");
    printf(" 1.CRC-12\n 2.CRC-16\n 3.CRC-CCITT\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice){
        case 1: strcpy(gen_input,"1100000001111");
                break;
        case 2: strcpy(gen_input,"1000000000000101");
                break;
        case 3: strcpy(gen_input,"10001000000100001");
                break;
        default:
                printf("Enter a valid input");
    }
}

//Divisor
void set_genInput(){
    gen_length = strlen(gen_input);
    for(int i=0;i<gen_length;i++)
    {
        if(gen_input[i]=='1')
            gen[i]=1;
        else
            gen[i]=0;
    }
}

//Dividend
void set_frameInput(){
    printf("Enter no. of data bits: ");
    scanf("%d",&data_length);

    printf("Enter data bits(E.g. 1011011): ");
    for(int i=0;i<data_length;i++)
        scanf("%d",&data[i]);
}

void append_zeroes(){
    for(int i=0;i<data_length;i++)
        temp[i] = data[i];
    for(int i=data_length;i<data_length+gen_length-1;i++)
        temp[i] = 0;
}

void print_array(int arr[],int start,int end){
    for(int i=start;i<end;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void copy_temp_to_rem(){
    for(int i=0;i<data_length+gen_length-1;i++)
        rem[i] = temp[i];
}

void compute_crc(){
    //****Iterate only upto the frame****
    for(int i=0;i<data_length;i++)
    {
        if(rem[i]==1)
        {
            for(int j=0;j<gen_length;j++)
            {
                rem[i+j] = rem[i+j]!=gen[j]?1:0;  //XOR operation
            }
        }
    }
}
