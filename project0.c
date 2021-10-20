#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//maximum size of all unicode characters
#define MAX_SIZE 1112064

//struct that stores unicode objects
struct UnicodeElement 
{
    //variables for size and frequency of unicode characters 
    int size, frequency;

    //variables for the bits of unicode characters
    unsigned char byte_1, byte_2, byte_3, byte_4;
};
typedef struct UnicodeElement UnicodeElement;

//swap function that uses built-in c function (quick sort)
void swap(const void *X, const void *Y)
{
    int xCount, yCount;

    xCount = ((struct UnicodeElement *)X)->frequency;
    yCount = ((struct UnicodeElement *)Y)->frequency;

    if(yCount < xCount)
    {
        return 1;
    }
        else
        {
            return -1;
        }

}

//prints and sorts out unicode characters
void print(struct UnicodeElement element[], int size)
{
    //prints out unicode object values
    for (int i  = 0; i < size; i++)
    {
        unsigned char arr[4];
        
        //copy array of UnicodeArr elements
        arr[0] = element[i].byte_1;
        arr[1] = element[i].byte_2;
        arr[2] = element[i].byte_3;
        arr[3] = element[i].byte_4;

        unsigned char *str = &arr[0];

        //print out in correct format
        printf("%s", str);
        printf("->");
        printf("%d\n", element[i].frequency);
    }
    
}

int main(int argc, char **argv)
{
    //struct that points to unicode objects
    struct UnicodeElement *UnicodeArr = malloc(MAX_SIZE * sizeof(struct UnicodeElement));

    //varaiables to store 1st, 2nd, 3rd, and 4th byte of unicode characters
    unsigned char firstChar, secondChar, thirdChar, fourthChar;

    //set all values of Unicode array to 0 in memory
    memset(UnicodeArr, 0, sizeof(UnicodeArr));

    //variable that stores the byte size result
    int result;

    //variable that acess struct elements from unicode and tracks count
    int count = 0;

    //varaiable that compares two unicode characters
    int compare = 0;

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
                    compare = (UnicodeArr[i].byte_1 == firstChar);

                if (result == 2)
                    compare = ((UnicodeArr[i].byte_1 == firstChar) & ((UnicodeArr[i].byte_2) == secondChar));

                if (result == 3) 
                    compare = (UnicodeArr[i].byte_1 == firstChar) & (UnicodeArr[i].byte_2 == secondChar) & (UnicodeArr[i].byte_3 == thirdChar);
               
                if (result == 4) 
                    compare = (UnicodeArr[i].byte_1 == firstChar) & (UnicodeArr[i].byte_2 == secondChar) & (UnicodeArr[i].byte_3 == thirdChar) & (UnicodeArr[i].byte_4 == fourthChar);

                if (compare == 1)
                    break;
        }

        int i;
        if (compare == 1)
        //increases frequency of unicode character
        UnicodeArr[i].frequency++;

        else 
        {
                //changes NULL values of unicode character
                UnicodeArr[count].frequency++;
                if (result == 1)
                    UnicodeArr[count].byte_1 = firstChar;

                if (result == 2) 
                {
                    UnicodeArr[count].byte_1 = firstChar;
                    UnicodeArr[count].byte_2 = secondChar;
                }

                if (result == 3)
                {
                    UnicodeArr[count].byte_1 = firstChar;
                    UnicodeArr[count].byte_2 = secondChar;
                    UnicodeArr[count].byte_3 = thirdChar;
                }

                if (result == 4)
                {
                    UnicodeArr[count].byte_1 = firstChar;
                    UnicodeArr[count].byte_2 = secondChar;
                    UnicodeArr[count].byte_3 = thirdChar;
                    UnicodeArr[count].byte_4 = fourthChar;
                }
                UnicodeArr[count].size = UnicodeArr[count].byte_1 + UnicodeArr[count].byte_2 + UnicodeArr[count].byte_3 + UnicodeArr[count].byte_4;
                count++;
        }

        compare = 0;
        firstChar = fgetc(stdin);
    }

    qsort(UnicodeArr, count, sizeof(UnicodeElement), swap);

    //print out unicode character and the count
    print(UnicodeArr, count);
    return 0;
}
