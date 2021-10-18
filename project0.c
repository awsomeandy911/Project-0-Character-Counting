#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//making a Linked List
struct LinkedList
{
    //character frequency
    int frequency;

    //next pointer
    struct LinkedList *next;

    //array that holds the bytes
    char c_arr[5];
};
typedef struct LinkedList LinkedList;

//comparing list frequency
int comparelist(LinkedList *list_1, LinkedList *list_2)
{
    return list_1->frequency - list_2->frequency;
}

//sorting the linked list by using merge sort
LinkedList *sortlist(LinkedList *list)
{
    //pointer variables
    LinkedList *temp, *a, *element, *tail;

    //variables that hold the number of merges and the sizes of list, temp, and a
    int size_list, merge_num, size_temp, size_a;

    //check if list exists, if not return NULL
    if(!list)
    {
        return NULL;
    }
    
    /* assume the list size is at least 1 since 
       there must be at least one element
    */
    size_list = 1;

    //infinite loop
    while(1)
    {
        //set temp to the head of list
        temp = list;
        list = NULL;
        tail = NULL;

        //count the number of merges
        merge_num = 0;

        while(temp)
        {
            //increment the number of merges everytime it loops
            merge_num++;

            //set a to the head of list
            a = temp;
            size_temp = 0;

            //loop a by the list size
            for(int i = 0; i < size_list; i++)
            {
                size_temp++;
                a = a -> next;

                //break if a doesn't exist
                if(!a) 
                    break;
            }

            //merge the two lists
            size_a = size_list;

            /* conditions ok if size_a and size_temp are 
               not empty and "a" points to something
            */
           while((size_a > 0 && a) || size_temp > 0)
           {
               //if "a" is empty, element comes from temp
               if(size_a == 0 || !a)
               {
                   element = temp;
                   temp = temp->next;
                   size_temp--;
               }

                    //if temp is empty, element comes from "a"
                    else if(size_temp == 0)
                    {
                        element = a;
                        a = a->next;
                        size_a--;
                    }

                    //compare the frequencies of the lists
                    else if(comparelist(temp, a) >= 0)
                    {
                        //first element of "a" is lower
                        element = a;
                        a = a->next;
                        size_a--;
                    }

                        else
                        {   
                            //first element of temp is lower
                            element = temp;
                            temp = temp->next;
                            size_temp--;
                        }

                //add the next element to list       
                if(tail)
                {
                    tail->next = element;
                }
                    else
                    {
                        list = element;
                    }
                        tail = element;
            }
            
            //"a" and temp done interating through list
            temp = a;
        }
            
            tail->next = NULL;

            //for only one merge sort
            if(merge_num <= 1)
            {
                return list;
            }

            size_list *= 2;
    }
}
/* insert the array of bytes for a character to the linked list
   counts the number of occurences of each character
*/
void insert_list(LinkedList **head, const char *to_insert)
{
        //if the linked list is null, then we see the 1st character 
        if ((*head) == NULL) 
        {
            (*head) = (struct LinkedList*) malloc(sizeof(struct LinkedList *));

            //set the next list to null in case it's populated
            (*head)->next = NULL;

            //set the frequency to 1 because it's the first instance
            (*head)->frequency = 1;

            //copy the character we have to the linked list's character
            strcpy((*head)->c_arr, to_insert);      
        } 

            //if character is same then increment the occurence
            else if(strcmp((*head)->c_arr, to_insert) == 0) 
            {
                (*head)->frequency++;
            } 
                else 
                {
                    /*recursion to keep going until we won't be receiving any more
                      first byte of character
                    */
                    insert_list(&(*head)->next, to_insert);
                }

}

/*while there are elements to head, print out the character with its
  frequency. Then set it to next and keep repeating until head is null.
*/
void print_list(LinkedList *head) 
{
    while (head != NULL) 
    {
        printf("%s->%d\n", head->c_arr, head->frequency);
        head = head->next;
    }
}


int main(int argc, char *argv[])
{
  
    //set first byte to 0
    int byte = 0;

    struct LinkedList *LinkedList = NULL;

	//get the first byte of characters until it reaches EOF
    while((byte = fgetc(stdin)) != EOF) 
    {
        //compare first byte to hex values to determine how many more bytes to read
        int byte_exta = 0;

        if (byte >= 0xF0) 
        { 	
            //the case for [11110]
            byte_exta = 3;
        } 
        else if (byte >= 0xE0) 
        {  
            //the case for [1110]
            byte_exta = 2;
        } 
        else if (byte >= 0xC0) 
        {  
            //the case for [110]
            byte_exta = 1;
        }						

        //create an array to hold bytes
        unsigned char arr_byte[5];

        //pointer to the byte array
        unsigned char *byte_pointer = arr_byte;

		//byte pointer will hold the first byte
        byte_pointer += sprintf(byte_pointer, "%c", byte);

        //iterate through the number of byte_exta we have and set it to the pointer
        for (int i = 0; i < byte_exta; ++i) 
        {
            byte = fgetc(stdin);

			//byte pointer will now hold all the bytes for each character
            byte_pointer += sprintf(byte_pointer, "%c", byte);
        }

        //set the array of bytes to the linked list
        insert_list(&LinkedList, arr_byte);
    }

    //sort the list
    struct LinkedList *list = listsort(LinkedList);

    //print the list
    print_list(list);

    //free the list
    free(list);

    return EXIT_SUCCESS;

}
