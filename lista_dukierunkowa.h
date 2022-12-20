// typ danych struktury, tutaj zwykły int

#ifndef LIST_H 
#define LIST_H 


typedef char list_element_data_type;
 
//struktura pojedynczego elementu listy dwukierunkowej
typedef struct list_element
{
    list_element_data_type data;
    struct list_element* next;
    struct list_element* prev;
    
}list_element;
 
 //struktura listy, zawiera wskażnik na pierwszy element, ostatni element oraz ilość elementów;
 typedef struct list_head
 {
        list_element* head_ptr; 
        list_element* tail_ptr;
        int cnt;
        
 }list_head;
 
 
//typ pomocniczy, wskaznik na element listy, do nazwania listy i wskazania na jej pierwszy element z poziomu programu

/******************************************************************************
FUNKCJE PROTOTYPY
*******************************************************************************/
 void list_init(list_head* head);
 
 
//funkcje dodawania/usuwania elementów listy
//----------------------------------------------------------------------------------------------------
void list_add_first(list_head* head, list_element_data_type data);
void list_remove_first(list_head* head);
 
void list_add_last(list_head* head, list_element_data_type data);
void list_remove_last(list_head* head);

void list_add_element(list_head* head, list_element_data_type data, unsigned int position);
void list_remove_element(list_head* head, unsigned int position);


// zwracanie wskaznika na element o numerze cnt
list_element* list_get_element(list_head* head, unsigned int cnt);

// liczenie ilości elementów
unsigned int list_count(list_head* head);

// przeniesienie części jednej listy na początek drugiej (zadanie ze stosami)
void  list_transfer(list_head* head_src, list_head* head_dst, unsigned int cnt);

//funkcje wyświetlające/inne
void list_print_head(list_head head);
void list_print_tail(list_head head);

void list_print_cnt(list_head head);
void list_info_print(list_head* head); 
void list_print_all(list_head* head);
void print_element_data(list_element_data_type data);
list_element_data_type get_head_data(list_head* head);


#endif
