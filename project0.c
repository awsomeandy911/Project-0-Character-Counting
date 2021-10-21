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

//swap function that is used by built-in c function (quick sort)
int swap(const void *X, const void *Y)
{
    int xCount, yCount;

    xCount = ((struct UnicodeElement *)X)->frequency;
    yCount = ((struct UnicodeElement *)Y)->frequency;

    if(yCount > xCount)
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
    int count = 1;

    //varaiable that marks if character exists
    int marker = 0;

    //gets first byte by reading first unicode character
    firstChar = fgetc(stdin);

    //get first bytes of characters until it reaches EOF
    while(firstChar != EOF)
    {
        //read certain # of bits depending on four leading bits
        if (firstChar < 192)
        {
            result = 1;
        }
        else if (firstChar >= 192 & firstChar < 224)
        {
            result = 2;
            //if bit size is 2, read 2nd unicode character
            secondChar = (unsigned char)fget(stdin);
        }
        else if (firstChar >= 224 & firstChar < 240)
        {
            result = 3;
            //if bit size is 3, read 2nd & 3rd unicode character
            secondChar = (unsigned char)fget(stdin);
            thirdChar = (unsigned char)fget(stdin);
        }
        else if (firstChar >= 240)
        {
            result = 4;
            //if bit size is 4, read 2nd, 3rd, & 4th unicode character
            secondChar = (unsigned char)fget(stdin);
            thirdChar = (unsigned char)fget(stdin);
            fourthChar = (unsigned char)fget(stdin);
        }

         int i;

        //check to see if given unicode was already read in or not
        for(i = 0; i < count; i++)
        {
            //uses bitwise operators to check the byte correctness
            //if it matches all conditons it'll equal 1
           if((result == 1) && (firstChar == UnicodeArr[i].byte_1))
           {
               UnicodeArr[i].frequency += 1;
               marker = 1;
               break;
           }
           else if((result == 2) && (firstChar == UnicodeArr[i].byte_1) && (secondChar == UnicodeArr[i].byte_2))
           {
               UnicodeArr[i].frequency += 1;
               marker = 1;
               break;
           }
           else if((result == 3) && (firstChar == UnicodeArr[i].byte_1) && (secondChar == UnicodeArr[i].byte_2) &&
                           (thirdChar == UnicodeArr[i].byte_3))
           {
               UnicodeArr[i].frequency += 1;
               marker = 1;
               break;
           }
           else if((result == 4) && (firstChar == UnicodeArr[i].byte_1) && (secondChar == UnicodeArr[i].byte_2)
                            (thirdChar == UnicodeArr[i].byte_3) && (fourthChar == UnicodeArr[i].byte_4))
           {
               UnicodeArr[i].frequency += 1;
               marker = 1;
               break;
           }
           else
           {
               i++;
           }

        }

       
       

        if(marker = 0)
        {
                //changes NULL values of unicode character
                UnicodeArr[count].frequency++;
                if (result == 1)
                {
                    UnicodeArr[count].byte_1 = (unsigned char)firstChar;

                    UnicodeArr[i].frequency += 1;
                }
                else if (result == 2) 
                {
                    UnicodeArr[count].byte_1 = (unsigned char)firstChar;
                    UnicodeArr[count].byte_2 = (unsigned char)secondChar;

                    UnicodeArr[i].frequency += 1;
                }

                else if (result == 3)
                {
                    UnicodeArr[count].byte_1 = (unsigned char)firstChar;
                    UnicodeArr[count].byte_2 = (unsigned char)secondChar;
                    UnicodeArr[count].byte_3 = (unsigned char)thirdChar;

                    UnicodeArr[i].frequency += 1;
                }

                else if (result == 4)
                {
                    UnicodeArr[i].byte_1 = (unsigned char)firstChar;
                    UnicodeArr[i].byte_2 = (unsigned char)secondChar;
                    UnicodeArr[i].byte_3 = (unsigned char)thirdChar;
                    UnicodeArr[i].byte_4 = (unsigned char)fourthChar;

                    UnicodeArr[i].frequency += 1;
                }
                
                count++;
        }

        
        firstChar = fgetc(stdin);
    }

    //quick sort function 
    qsort(UnicodeArr, count, sizeof(UnicodeElement), swap);

    //print out unicode character and the count
    print(UnicodeArr, count);
    return 0;
}
