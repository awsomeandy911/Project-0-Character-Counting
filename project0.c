#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//maximum size of all unicode characters
#define MAX_SIZE 1112064

//struct that stores unicode objects
struct UnicodeElement 
{
    //variable for frequency of unicode characters 
    int frequency;

    //variables for the bits of unicode characters in an character array
    unsigned char bytes[4];
};


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
    struct UnicodeElement *UnicodeArr = (malloc(MAX_SIZE * sizeof(struct UnicodeElement)));

    //variable for intialization of empty byte
    int emptyByte;

    //varaible for bytes in a chacter array
    unsigned char arr[4];
    
    //set all values of Unicode array to 0 in memory
    memset(UnicodeArr, 0, sizeof(UnicodeArr));

   //variable that acess struct elements from unicode and tracks count
    int count = 0;

    //variable that stores the byte size result
    int result = 0;
        
    //gets first byte by reading first unicode character
    emptyByte = fgetc(stdin);

    //get first bytes of characters until it reaches EOF
    while(emptyByte !=EOF) 
    {

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
        
        
        //varaible for the index used in loops
        int i;

        //varaiable that marks if character exists
        int marker = 0;

        for(i = 0; i < count; i++)
        {

            if(result == 4)
            {
                marker = (UnicodeArr[i].bytes[0] == (unsigned char) emptyByte) & (UnicodeArr[i].bytes[1] ==  arr[1]) & (UnicodeArr[i].bytes[2] ==  arr[2]) 
                                                                & (UnicodeArr[i].bytes[3] ==  arr[3]);
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

            if(marker == 1)
            {
                UnicodeArr[i].frequency++;
                break;
            }
        }

        
        if(marker == 0)
        {
            UnicodeArr[count].frequency++;

            if(result == 1)
            {
                UnicodeArr[count].bytes[0] = emptyByte;
            }
            if(result == 2)
            {
                UnicodeArr[count].bytes[0] = (unsigned char) emptyByte;
                UnicodeArr[count].bytes[1] = arr[1];
            }
            if(result == 3)
            {
                UnicodeArr[count].bytes[0] = (unsigned char) emptyByte;
                UnicodeArr[count].bytes[1] = arr[1];
                UnicodeArr[count].bytes[2] = arr[2];
            }
            if(result == 4)
            {
                UnicodeArr[count].bytes[0] = (unsigned char) emptyByte;
                UnicodeArr[count].bytes[1] = arr[1];
                UnicodeArr[count].bytes[2] = arr[2];
                UnicodeArr[count].bytes[3] = arr[3];
            }
           
           //increment by 1 to the count of characters in character array
            count++;
        }
    }

    //quick sort function 
    qsort(UnicodeArr, count, sizeof(struct UnicodeElement), swap);

    //print out unicode character and the count
    print(UnicodeArr, count);
    
    return 0;
}
