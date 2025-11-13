#include <stdio.h>
#include <math.h>

int dataBits[32];
int hammingCode[32];

int calculateParity(int parityPosition, int totalLength);

void main()
{
    int dataBitsCount, bitIndex, parityBitsCount = 0,
    totalCodeLength, dataIndex, parityIndex;

    printf("Please enter the length of the Data Word: ");
    scanf("%d", &dataBitsCount);

    printf("Please enter the Data Word(LSB to MSB):");
    for (int i = 0; i < dataBitsCount; i++)
    {
        scanf("%d", &dataBits[i]);
    }

     // Calculate the required number of parity bits
    // Formula: 2^r >= m + r + 1  (m = data bits, r = parity bits)
    parityBitsCount = 0;
    while ( (int)pow(2, parityBitsCount) < (dataBitsCount + parityBitsCount + 1) )
    {
        parityBitsCount++;
    }

    // Calculate total length of the Hamming code
    totalCodeLength = parityBitsCount + dataBitsCount;

    //Insert data bits into code positions and leave parity positions as 0
    dataIndex = parityIndex = 0;
    for (int i = 0; i < totalCodeLength; i++)
    {
        // If current position is a power of 2 → parity bit position
        if (i == ((int)pow(2, parityIndex) - 1))
        {
            hammingCode[i] = 0; // Placeholder for parity
            parityIndex++;
        }
        else
        {
            hammingCode[i] = dataBits[dataIndex]; // Place data bit
            dataIndex++;
        }
    }

    // Calculate actual parity bit values and update code
    for (int i = 0; i < parityBitsCount; i++)
    {
        int position = (int)pow(2, i);
        int value = calculateParity(position, totalCodeLength);
        hammingCode[position - 1] = value;
    }

    printf("\nThe calculated Code Word (LSB to MSB) is: ");
    for (int i = 0; i < totalCodeLength; i++)
        printf("%d ", hammingCode[i]);
    printf("\n");

    printf("Please enter the received Code Word (LSB to MSB):");
    for (int i = 0; i < totalCodeLength; i++)
        scanf("%d", &hammingCode[i]);

    int errorPosition = 0;
    for (int i = 0; i < parityBitsCount; i++)
    {
        int position = (int)pow(2, i);
        int value = calculateParity(position, totalCodeLength);
        if (value != 0) //means the parity check failed — the number of 1s is wrong.
            errorPosition += position; // Add position of error
    }

    if (errorPosition == 0)
        printf("\nThe received Code Word is correct.\n");
    else
    {
        printf("\nError at bit position: %d\n", errorPosition);

        // Correct the error (flip the bit)
        hammingCode[errorPosition - 1] ^= 1;

        printf("Corrected Code Word (LSB to MSB): ");
        for (int i = 0; i < totalCodeLength; i++)
            printf("%d ", hammingCode[i]);
        printf("\n");

    }
}


// Function to calculate parity for a specific position
int calculateParity(int parityPosition, int totalLength)
{
    int count = 0, i, j;

    // Loop through blocks: count '1's in each block of size = parityPosition(Refer below comments)
    for (i = parityPosition - 1; i < totalLength; i += 2 * parityPosition)
    {
        for (j = i; j < i + parityPosition && j < totalLength; j++)
        {
            if (hammingCode[j] == 1)
                count++;
        }
    }

    // Even count → parity bit = 0, Odd count → parity bit = 1
    if (count % 2 == 0)
        return 0;
    else
        return 1;
}


/*
 p1 ante 2^0 =1 so each block ki 1 element untadhi and next 1 element skip chestam (1,3,5,7,...)
 p2 ante 2^1 =2 so each block ki 2 elements untai and next 2 elements skip chestam (2,3,6,7,...)
 p3 ante 2^2 =4 so each block ki 4 elements untai and next 4 skip chestam(4,5,6,7,12,13,...)
    Outer loop → next block reach avvadaniki
    Inner loop → block lo bits iterate cheyyadaniki
*/
