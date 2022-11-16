/*******************************************************************************/
 
#include <stdio.h>
#include <stdbool.h>
 
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
void list_add_element_first(list_head* list, list_element_data_type data);
void list_remove_element_first(list_head* list);
 
void list_add_element_last(list_head* list, list_element_data_type data);
void list_remove_element_last(list_head* list);
 
//dodawanie elementów wykonuje się przed danym indeksem
void list_add_element_byindex(list_head* list, list_element_data_type data, unsigned int position);
void list_remove_element_byindex(list_head* list, unsigned int position);
 
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

void list_add_element_first(list_head* list, list_element_data_type data)
{
    list_element* new_element;
    new_element = (list_element*)malloc(sizeof(list_element));
    
    new_element->data = data;
    new_element->next = (*list);

}


int main()
{
    list_head mylist = NULL;
    return 0;
}
