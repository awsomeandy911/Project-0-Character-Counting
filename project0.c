#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//maximum size of all unicode characters
#define MAX_SIZE 1112064

//struct that stores unicode objects
struct UnicodeElement 
{
    //variable for the bits of unicode characters
    unsigned char bytes[4];

    //variable for frequency of unicode characters 
    int frequency;

};
typedef struct UnicodeElement UnicodeElement;

//swap function that is used by built-in c function (quick sort)
int swap(const void *X, const void *Y)
{
    int xCount, yCount;

    //compares the two counts to the frequency of characters
    xCount = ((UnicodeElement *)X)->frequency;
    yCount = ((UnicodeElement *)Y)->frequency;

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
void print(UnicodeElement element[], int size)
{
    //prints out unicode object values
    for (int i  = 0; i < size; i++)
    {
        //byte array
        unsigned char arr[4];
        
        //copy array of Unicode array elements
        arr[0] = element[i].bytes[0];
        arr[1] = element[i].bytes[1];
        arr[2] = element[i].bytes[2];
        arr[3] = element[i].bytes[3];

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
    UnicodeElement *UnicodeArr = (malloc(MAX_SIZE * sizeof(UnicodeElement)));

    //variable for intialization of empty byte
    int emptyByte;

    //varaible for bytes in a chacter array
    unsigned char arr[4];
    
    //built in c function that sets all values of array to 0 in the memory
    memset(UnicodeArr, 0, sizeof(UnicodeArr));

    //variable that acess struct elements from unicode and tracks count
    int count = 0;

    //varaiable that marks if character exists
    int marker = 0;

    //variable that stores the byte size result
    int result = 0;

    //gets first byte by reading first unicode character
    emptyByte = fgetc(stdin);
    
    //get first bytes of characters until it reaches EOF
    while(emptyByte != EOF) 
    {
            //checker to see what kind of bytes it is
            if (emptyByte >= 240)
            { 		
                result = 4;
                arr[1] = (unsigned char)fgetc(stdin);
                arr[2] = (unsigned char)fgetc(stdin);
                arr[3] = (unsigned char)fgetc(stdin);
            } 
            else if (emptyByte >= 224) 
            {  
                result = 3;
                arr[1] = (unsigned char)fgetc(stdin);
                arr[2] = (unsigned char)fgetc(stdin);
            } 
            else if (emptyByte >= 192) 
            {  
                result = 2;
                arr[1] = (unsigned char)fgetc(stdin);
            }
            else
            {
                result = 1;
            }

        
        //check to see if given unicode was already read in or not
        for(int i = 0; i < count; i++)
        {

            //uses bitwise operators to check the byte correctness
            if(result == 4)
            {
                marker = (UnicodeArr[i].bytes[0] == (unsigned char) emptyByte) & (UnicodeArr[i].bytes[1] ==  arr[1]) & (UnicodeArr[i].bytes[2] ==  arr[2]) & (UnicodeArr[i].bytes[3] ==  arr[3]);
            }
            else if(result == 3)
            {
                marker = (UnicodeArr[i].bytes[0] == (unsigned char) emptyByte) & (UnicodeArr[i].bytes[1] ==  arr[1]) & (UnicodeArr[i].bytes[2] == arr[2]);
            }
            else if(result == 2)
            {
                marker = (UnicodeArr[i].bytes[0] == (unsigned char) emptyByte) & (UnicodeArr[i].bytes[1] == arr[1]);
            }
            else
            {
                marker = (UnicodeArr[i].bytes[0] == (unsigned char) emptyByte);
            }

            //break if character is found in array
            if(marker == 1)
            {
                UnicodeArr[i].frequency++;
                                            break;
            }
        }

        //if character is not found in array, add it and increase count by 1
        if(marker == 0)
        {
            //increment pointer by amount of characters
            UnicodeArr[count].frequency++;

            if(result == 1)
            {
                //case for result 1 means 1 byte
                UnicodeArr[count].bytes[0] = emptyByte;
            }
            if(result == 2)
            {
                //case for result 2 means 2 bytes
                UnicodeArr[count].bytes[0] = (unsigned char) emptyByte;
                UnicodeArr[count].bytes[1] = arr[1];
            }
            if(result == 3)
            {
                //case for result 3 means 3 bytes
                UnicodeArr[count].bytes[0] = (unsigned char) emptyByte;
                UnicodeArr[count].bytes[1] = arr[1];
                UnicodeArr[count].bytes[2] = arr[2];
            }
            if(result == 4)
            {
                //case for result 4 means 4 bytes
                UnicodeArr[count].bytes[0] = (unsigned char) emptyByte;
                UnicodeArr[count].bytes[1] = arr[1];
                UnicodeArr[count].bytes[2] = arr[2];
                UnicodeArr[count].bytes[3] = arr[3];
            }

           //increment count by 1
            count++;
        }
    }

    //built in c function quick sort, that sorts out all unicode characters
    qsort(UnicodeArr, count, sizeof(UnicodeElement), swap);

    //print out unicode character and the count
    print(UnicodeArr, count);
    
    return 0;
}
