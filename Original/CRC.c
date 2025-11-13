#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

// Global arrays and variables
char generator_input[MAX_LEN];
int gen[30], frame[100], temp[130], rem[130] ;
int gen_len = 0, frame_len = 0;



/*
 * Global Variables Overview:
 *
 * gen[]         - Stores the generator polynomial bits (e.g., 1100000001111 for CRC-12).
 *                 Length is determined by gen_len.
 *
 * frame[]       - Stores the original input frame bits entered by the user (e.g., 1101011011).
 *                 Length is determined by frame_len.
 *
 * rem[]         - Stores the remainder after performing modulo-2 division (XOR).
 *                 Also used to check for errors in the received frame.
 *
 * temp[]        - Temporary working array:
 *                 - Holds the frame with appended zeros before division.
 *                 - Later holds the transmitted frame (original + CRC bits).
 *
 * gen_len       - Stores the length of the generator polynomial (number of bits in gen[]).
 *
 * frame_len     - Stores the length of the input frame (number of bits in frame[]).
 *
 * generator_input[] - Temporarily holds the generator polynomial as a string
 *                     (e.g., "1100000001111") before converting it to gen[].
 */

/*
 * 🧮 CRC Division Concepts:
 *
 * - The divisor in CRC is the generator polynomial.
 *   👉 In your program, this is stored in gen[].
 *
 * - The dividend is the frame data with zeros appended.
 *   👉 In your program, this is stored in temp[] and copied to rem[] for division.
 *
 * - CRC-12 means the generator polynomial is of degree 12.
 *   👉 So it has 13 bits (from x^12 down to x^0).
 *   👉 Example: "1100000001111" is a 13-bit polynomial for CRC-12.
 *
 * - It does NOT mean 12 characters are stored.
 *   👉 The number "12" refers to the length of the CRC remainder (in bits), not the frame size.
 *
 * Summary:
 *   - gen[] = divisor (generator polynomial)
 *   - temp[] / rem[] = dividend (frame + zeros)
 *   - CRC-12 = 12-bit remainder, using a 13-bit generator
 */


// Function declarations
void select_generator();
void input_frame();
void load_generator();
void append_zeros();
void copy_temp_to_rem();
void perform_crc_check();
void print_array(int arr[], int start, int end);

int main() {
    int i, error_flag = 0;

    // Step 1: Select CRC type and load generator polynomial
    select_generator();
    load_generator();

    // Step 2: Input frame bits
    input_frame();

    // Step 3: Append zeros to frame
    append_zeros();
    printf("\nFrame after appending zeros: ");
    print_array(temp, 0, frame_len + gen_len - 2);

    // Step 4: Copy temp to remainder and perform CRC division
    copy_temp_to_rem();   //After this, gen ->divisor and rem->dividend
    perform_crc_check();

    printf("\nRemainder after division: ");
    print_array(rem, frame_len, frame_len + gen_len - 2);  //Last (n-1) bits is crc remainder,so print remainder from frameLength

    // Step 5: Transmit frame (original + CRC remainder)
    printf("\nTransmitting frame...\n");
    for (i = frame_len; i < frame_len + gen_len - 1; i++)
        temp[i] = rem[i];  //1 to framle_len-1, we already data bits

    printf("Transmitted frame: ");
    print_array(temp, 0, frame_len + gen_len - 2);

    // Step 6: Simulate receiving and checking for errors
    printf("\nReceiving frame and checking for errors...\n");
    printf("Received frame: ");
    // temp[3] = 0;   // To simulate error in received code
    print_array(temp, 0, frame_len + gen_len - 2);

    copy_temp_to_rem();
    perform_crc_check();

    printf("Remainder after checking received frame: ");
    print_array(rem, frame_len, frame_len + gen_len - 2);

    for (i = frame_len; i < frame_len + gen_len - 1; i++) {
        if (rem[i] != 0) {
            error_flag = 1;
            break;
        }
    }

    if (error_flag)
        printf("\n Error detected in received frame!\n");
    else
        printf("\n No error detected. Data sent successfully.\n");

    return 0;
}

// Prompt user to select CRC type
void select_generator() {
    int choice;
    printf("Select CRC type:\n");
    printf("1. CRC-12\n");
    printf("2. CRC-16\n");
    printf("3. CRC-CCITT\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(generator_input, "1100000001111"); // CRC-12
            printf("\n*** CYCLIC REDUNDANCY CHECK - CRC-12 ***\n\n");
            break;
        case 2:
            strcpy(generator_input, "1000000000000101"); // CRC-16
            printf("\n*** CYCLIC REDUNDANCY CHECK - CRC-16 ***\n\n");
            break;
        case 3:
            strcpy(generator_input, "10001000000100001"); // CRC-CCITT
            printf("\n*** CYCLIC REDUNDANCY CHECK - CRC-CCITT ***\n\n");
            break;
        default:
            printf("Invalid choice.\n");
            exit(1);
    }
}

// Load generator polynomial into gen[] integer array
void load_generator() {
    int i;
    gen_len = strlen(generator_input);
    for (i = 0; i < gen_len; i++) {
        if (generator_input[i] == '0')
            gen[i] = 0;
        else if (generator_input[i] == '1')
            gen[i] = 1;
        else {
            printf("Invalid generator input! Only '0' and '1' allowed.\n");
            exit(1);
        }
    }
}

// Input frame bits from user
void input_frame() {
    int i;
    char input[MAX_LEN];
    printf("Enter the frame bits (e.g. 1101011011): ");
    scanf("%s", input);

    frame_len = strlen(input);
    for (i = 0; i < frame_len; i++) {
        if (input[i] == '0')
            frame[i] = 0;
        else if (input[i] == '1')
            frame[i] = 1;
        else {
            printf("Invalid input! Only '0' and '1' are allowed.\n");
            exit(1);
        }
    }
}

// Append zeros to frame (length = gen_len - 1)
void append_zeros() {
    int i;
    for (i = 0; i < frame_len; i++)
        temp[i] = frame[i];
    for (i = frame_len; i < frame_len + gen_len - 1; i++)
        temp[i] = 0;
}

// Copy temp array to remainder array
void copy_temp_to_rem() {
    int i;
    int len = frame_len + gen_len - 1;
    for (i = 0; i < len; i++)
        rem[i] = temp[i];
}

// Perform modulo-2 division (XOR-based)
void perform_crc_check() {
    int i, j;
    int len = frame_len + gen_len - 1;

    for (i = 0; i <= len - gen_len; i++) {
        if (rem[i] == 1) {
            for (j = 0; j < gen_len; j++)
                rem[i + j] = (rem[i + j] != gen[j]) ? 1 : 0;
        }
    }
}

// Print array from start to end index
void print_array(int arr[], int start, int end) {
    int i;
    for (i = start; i <= end; i++)
        printf("%d", arr[i]);
    printf("\n");
}

/*
 * 🔁 Sequence of Events in Your Program:
 *
 * 1. User enters frame bits → stored in frame[]
 *    👉 This is the message to be protected. No division happens yet.
 *
 * 2. User selects CRC type or enters generator polynomial → stored in gen[]
 *    👉 This becomes the divisor used for modulo-2 division.
 *
 * 3. Zeros are appended to the frame → stored in temp[]
 *    👉 Prepares the dividend for division.
 *
 * 4. Division begins → rem[] is initialized from temp[], and divided by gen[]
 *    👉 Now the divisor (gen[]) is used to compute the CRC remainder.
 */
/*
 * 🧮 Manual CRC Calculation: Step-by-Step
 *
 * Example: CRC-12
 *
 * Given:
 * - Frame (data bits): 1101011011
 * - Generator Polynomial (CRC-12): 1100000001111 (13 bits, degree 12)
 *
 * Step 1: Append Zeros to the Frame
 * - Since the generator is degree 12, append 12 zeros to the frame.
 * - Original frame:         1101011011
 * - Appended zeros:         000000000000
 * - Dividend (temp[]):      110101101100000000000
 *
 * Step 2: Perform Modulo-2 Division (XOR)
 * - Align the generator with the leftmost 1 of the dividend.
 * - XOR the generator with that section of the dividend.
 * - Bring down the next bit and repeat until all bits are processed.
 * - The remainder after the last XOR is the CRC.
 *
 * Example of first XOR step:
 *   110101101100000000000   ← dividend
 *   1100000001111           ← divisor (generator)
 *   -------------------
 *   000101101011100000000   ← result after XOR (only first 13 bits affected)
 *
 * Step 3: Extract the Remainder
 * - After the final XOR, the last 12 bits of the result are the CRC remainder.
 * - Example CRC-12: 011011001101
 *
 * Step 4: Transmit Frame + CRC
 * - Final transmitted frame: 1101011011 + 011011001101
 * - Result: 1101011011011011001101
 *
 * Step 5: Receiver Repeats the Division
 * - Receiver receives the full frame (data + CRC).
 * - Performs the same modulo-2 division using the same generator.
 * - If the remainder is all zeros → data is error-free.
 * - If not → error is detected.
 *
 * Key Concepts:
 * - frame[]       → Original data (message)
 * - gen[]         → Generator polynomial (divisor)
 * - temp[]/rem[]  → Dividend (frame + zeros)
 * - CRC-12        → 12-bit remainder, using a 13-bit generator
 */

 /*
 * perform_crc_check()
 * -------------------
 * Step-by-step explanation:
 *
 * 1. rem[] contains the frame bits with zeros appended (the dividend).
 * 2. gen[] contains the generator polynomial bits (the divisor).
 * 3. For each bit in rem[] from left to right:
 *    - If the current bit is 1:
 *      a. XOR the next gen_len bits of rem[] with gen[].
 *      b. This simulates binary division using XOR (modulo-2).
 *    - If the current bit is 0:
 *      a. Skip to the next bit (no division needed).
 * 4. After the loop, the last (gen_len - 1) bits of rem[] hold the CRC remainder.
 * 5. This remainder is used for error detection or appended to the frame for transmission.
 */

