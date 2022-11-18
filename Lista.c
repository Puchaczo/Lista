
/*******************************************************************************/
 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
 
/******************************************************************************
TYPEDEF/STRUKTURY
*******************************************************************************/
// typ danych struktury, tutaj zwykły int
typedef int list_element_data_type;
 
//struktura pojedynczego elementu listy
typedef struct list_element
{
    list_element_data_type data;
    struct list_element* next;
    
}list_element;
 
//typ pomocniczy, wskaznik na element listy, do nazwania listy i wskazania na jej pierwszy element z poziomu programu
typedef list_element* list_head;
 
 
/******************************************************************************
FUNKCJE PROTOTYPY
*******************************************************************************/
 
//funkcje dodawania/usuwania elementów listy
void list_add_element_as_first(list_head* list, list_element_data_type data);
void list_remove_element_first(list_head* list);
 
void list_add_element_as_last(list_head* list, list_element_data_type data);
void list_remove_element_last(list_head* list);
 
//dodawanie elementów wykonuje się przed danym indeksem
void list_add_element_by_index(list_head* list, list_element_data_type data, unsigned int position);
void list_remove_element_by_index(list_head* list, unsigned int position);
 
//zwrócenie długosci listy
int list_count_elements(list_head* list);
 
//funkcje wyswietlania/pomocnicze
list_element* list_return_element_byindex(list_head* list, unsigned int position);

void list_print_all_elements(list_head* list);
void list_info_print(list_head* list);  //wypisuje elementy oraz rozmiar jako ostatnią liczbę
void list_element_set_free(list_element* element); //zeruje dane elementu usuwanego z listy
 
 
/******************************************************************************
FUNKCJE KOD
*******************************************************************************/

void list_add_element_as_first(list_head* list, list_element_data_type data)
{

    list_element*  new_element = (list_element*) malloc(sizeof(list_element));
    new_element->data = data;
    
    new_element->next = (*list);
    (*list) = new_element;

}


void list_remove_element_first(list_head* list)
{
    if((*list) != NULL) //usuwamy tylko gdy lista ma elementy
    {
        //zapamiętujemy adres drugiego elementu
        list_element* temp_pointer = (*list)->next;
        free((*list));
        
        (*list) = temp_pointer;
    }
    else
    {
        printf("nie ma co usuwać\n\r");
    }   
}


void list_add_element_as_last(list_head* list, list_element_data_type data)
{
 
// Tworzymy nowy obiekt, jako ostatni next = NULL       
    list_element*  new_element = (list_element*) malloc(sizeof(list_element));
    new_element->data = data;
    new_element->next = NULL;
    
//oddzielny przypadek gdy lista jest pusta, inaczej segmentation fault
    if((*list) == NULL)
    {
        (*list) = new_element;
    }
    
    else
    {
        list_element* temp_pointer = (*list);
        while(temp_pointer->next != NULL)
        {
            temp_pointer = temp_pointer->next;
        }
        temp_pointer->next = new_element;
    }
}


void list_remove_element_last(list_head* list)
{
    if((*list) != NULL) //usuwamy tylko gdy lista ma elementy
    {
        if(((*list)->next) == NULL)
        {
            free(*list);
            (*list) = NULL;
        }
        else
        {
            list_element* temp_pointer = (*list);
            //szukamy przedostatniego elementu
            while((temp_pointer->next->next) != NULL)
            {
                temp_pointer = temp_pointer->next;
            }
            free(temp_pointer->next);
            temp_pointer->next = NULL;
        }
    }
    else
    {
        printf("nie ma co usuwać\n\r");
    }   
}



int list_count_elements(list_head* list)
{
    int count = 0;
    list_element* temp_pointer = (*list);
   
   
    while(temp_pointer != NULL)
    {
        count++;
        temp_pointer = temp_pointer->next;
    }
   
    return count;
}


void list_print_all_elements(list_head* list)
{
    list_element* temp_pointer = (*list);
   
    if(temp_pointer == NULL)
     printf("lista jest pusta");
   
    while(temp_pointer != NULL)
    {
        printf("%d ", temp_pointer->data);
        temp_pointer = temp_pointer->next;
    }
     
}

// format: [wartośc elementu #0] [wartośc elementu #1] ... [wartośc elementu #n-1] rozmiar: n
void list_info_print(list_head* list) 
{
    list_print_all_elements(list);
    printf(" rozmiar: %d \n\r", list_count_elements(list));
}


int main()
{
    
    list_head mylist = NULL;
    list_info_print(&mylist);
    list_add_element_as_last(&mylist, 5);
    list_info_print(&mylist);
    list_add_element_as_first(&mylist, 3);
    list_info_print(&mylist);
    list_add_element_as_last(&mylist, 4);
    list_info_print(&mylist);
    list_remove_element_first(&mylist);
    list_info_print(&mylist);
    list_remove_element_first(&mylist);
    list_info_print(&mylist);
    list_remove_element_first(&mylist);
    list_info_print(&mylist);
    list_remove_element_first(&mylist);
    list_info_print(&mylist);
    
    list_add_element_as_last(&mylist, 5);
    list_info_print(&mylist);
    list_add_element_as_first(&mylist, 3);
    list_info_print(&mylist);
    list_add_element_as_last(&mylist, 4);
    list_info_print(&mylist);
    list_remove_element_last(&mylist);
    list_info_print(&mylist);
    list_remove_element_last(&mylist);
    list_info_print(&mylist);
    list_remove_element_last(&mylist);
    list_info_print(&mylist);
    list_remove_element_last(&mylist);
    list_info_print(&mylist);
    
    return 0;
}
