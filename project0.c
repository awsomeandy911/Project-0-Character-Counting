#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE 1112064

//struct that stores unicode objects
struct UnicodeElement 
{
    //variables for size and frequency of unicode characters 
    int size, frequency;

    //variables for the bits of unicode characters
    unsigned char byte_1, byte_2, byte_3, byte_4;
};

//swap function that allows us to swap 2 unicode characters
void swap(struct UnicodeElement *X, struct UnicodeElement *Y)
{
    //temporary variables for size and frequency
    int temp_size, temp_frequency;

    //temporary variables that hold bytes
    unsigned char temp_1, temp_2, temp_3, temp_4;

    //assign temp bits to first unicode character
    temp_1 = X->byte_1;
    temp_2 = X->byte_2;
    temp_3 = X->byte_3;
    temp_4 = X->byte_4;

    //assign temp size & frequency to first unicode character
    temp_size = X->size;
    temp_frequency = X->frequency;

    //swap first bits with second
    X->byte_1 = Y->byte_1;
    X->byte_2 = Y->byte_2;
    X->byte_3 = Y->byte_3;
    X->byte_4 = Y->byte_4;

    //swap first size & frequency with second
    X->size = Y->size;
    X->frequency = Y->frequency;

    //swap second bits with first
    Y->byte_1 = temp_1;
    Y->byte_2 = temp_2;
    Y->byte_3 = temp_3;
    Y->byte_4 = temp_4;

    //swap second size & frequency with first
    Y->size = temp_size;
    Y->frequency = temp_frequency;
}

//prints and sorts out unicode characters
void print(struct UnicodeElement element[], int size)
{
    //prints out unicode object values
    for (int i  = 0; i < size; i++)
    {
        unsigned char arr[4];

        arr[0] = element[i].byte_1;
        arr[1] = element[i].byte_2;
        arr[2] = element[i].byte_3;
        arr[3] = element[i].byte_4;

        unsigned char *str = &arr[0];
        printf("%s", str);
        printf("->");
        printf("%d\n", element[i].frequency);
    }
    int maximum;

    //sorts unicode from greatest to least by frequency of characters 
    for(int i = 0; i < size - 1; i++)
    {
        maximum = i;
        for(int j = i + 1; j < size; j++)
        {
            if(element[j].frequency > element[maximum].frequency)
            {
                maximum = j;
            }
        }
            if(maximum != i)
            {
                swap(&element[i],&element[maximum]);
            }
    }
}

int main(int argc, char **argv)
{
    //struct that points to unicode objects
    struct UnicodeElement *Unicode = malloc(MAX_SIZE * sizeof(struct UnicodeElement));

    //varaiables to store 1st, 2nd, 3rd, and 4th byte of unicode characters
    unsigned char firstChar, secondChar, thirdChar, fourthChar;

    //variable that acess struct elements from unicode and tracks count
    int count = 0;

    //varaiable that compares two unicode characters
    int compare = 0;

    //variable that stores the byte size result
    int result;

    //gets first byte by reading first unicode character
    firstChar = fgetc(stdin);

    //get first bytes of characters until it reaches EOF
    while(firstChar != EOF)
    {
        //read certain # of bits depending on four leading bits
        if (firstChar < 192)
            result = 1;

        if (firstChar >= 192 & firstChar < 224)
            result = 2;

        if (firstChar >= 224 & firstChar < 240)
            result = 3;

        if (firstChar >= 240)
            result = 4;

        //if bit size is 2, read 2nd unicode character
        if(result == 2)
        {
            secondChar = fgetc(stdin);
        }

        //if bit size is 3, read 2nd & 3rd unicode character
        if(result == 2)
        {
            secondChar = fgetc(stdin);
            thirdChar = fgetc(stdin);
        }

        //if bit size is 4, read 2nd, 3rd, & 4th unicode character
        if(result == 2)
        {
            secondChar = fgetc(stdin);
            thirdChar = fgetc(stdin);
            fourthChar = fgetc(stdin);
        }

        //check to see if given unicode was read in or not
        for(int i = 0; i < count; i++)
        {
            if (result == 1)
                    compare = (Unicode[i].byte_1 == firstChar);

                if (result == 2)
                    compare = ((Unicode[i].byte_1 == firstChar) & ((Unicode[i].byte_2) == secondChar));

                if (result == 3) 
                    compare = (Unicode[i].byte_1 == firstChar) & (Unicode[i].byte_2 == secondChar) & (Unicode[i].byte_3 == thirdChar);
               
                if (result == 4) 
                    compare = (Unicode[i].byte_1 == firstChar) & (Unicode[i].byte_2 == secondChar) & (Unicode[i].byte_3 == thirdChar) & (Unicode[i].byte_4 == fourthChar);

                if (compare == 1)
                    break;
        }

        int i;
        if (compare == 1)
        //increases frequency of unicode character
        Unicode[i].frequency++;

        else 
        {
                //changes NULL values of unicode character
                Unicode[count].frequency++;
                if (result == 1)
                    Unicode[count].byte_1 = firstChar;

                if (result == 2) 
                {
                    Unicode[count].byte_1 = firstChar;
                    Unicode[count].byte_2 = secondChar;
                }

                if (result == 3)
                {
                    Unicode[count].byte_1 = firstChar;
                    Unicode[count].byte_2 = secondChar;
                    Unicode[count].byte_3 = thirdChar;
                }

                if (result == 4)
                {
                    Unicode[count].byte_1 = firstChar;
                    Unicode[count].byte_2 = secondChar;
                    Unicode[count].byte_3 = thirdChar;
                    Unicode[count].byte_4 = fourthChar;
                }
                Unicode[count].size = Unicode[count].byte_1 + Unicode[count].byte_2 + Unicode[count].byte_3 + Unicode[count].byte_4;
                count++;
        }

        compare = 0;
        firstChar = fgetc(stdin);
    }

    //print out unicode character and the count
    print(Unicode, count);
    return 0;
}
