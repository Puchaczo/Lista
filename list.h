// typ danych struktury, tutaj zwykły int

#ifndef LIST_H 
#define LIST_H 


typedef int list_element_data_type;
 
//struktura pojedynczego elementu listy
typedef struct list_element
{
    list_element_data_type data;
    struct list_element* next;
    
}list_element;
 
 //struktura listy, zawiera wskażnik na pierwszy element oraz dodatkowe informacje;
 typedef struct list_head
 {
        list_element* head_ptr; 
        int element_cnt;
        
 }list_head;
 
 
//typ pomocniczy, wskaznik na element listy, do nazwania listy i wskazania na jej pierwszy element z poziomu programu

/******************************************************************************
FUNKCJE PROTOTYPY
*******************************************************************************/
 void list_init(list_head* head);
 
 
//funkcje dodawania/usuwania elementów listy
//----------------------------------------------------------------------------------------------------
void list_add_first(list_head* list, list_element_data_type data);
void list_remove_first(list_head* list);
 
void list_add_last(list_head* list, list_element_data_type data);
void list_remove_last(list_head* list);

//Indeksacja elementów tak jak w tablicach: 0:[rozmiar-1] 
//dodawanie elementów wykonuje się za danym indeksem
//pozycja na minusie np. (-1) skutkuje wpisaniem elementu na poczatek listy
void list_add_index(list_head* list, list_element_data_type data, int position);
void list_remove_index(list_head* list, unsigned int position);

//-----------------------------------------------------------------------------------------------------
//Operacje zmiany kolejności elementów listy
//-----------------------------------------------------------------------------------------------------
void list_bubblesort(list_head* list);

//void list_switch_elements(list_head* list, unsigned int element1_pos, unsigned int element2_pos);



//-----------------------------------------------------------------------------------------------------
//Inne operacje na listach
//----------------------------------------------------------------------------------------------------- 
//zwrócenie długosci listy
//zwrócenie wskażnika na n-ty element listy
list_element* list_return_element_ptr_byindex(list_head* list, unsigned int position);
//zwrócenie wartości ntego elementu listy
list_element_data_type list_return_element_byindex(list_head* list, unsigned int position);

//void list_connect_elements(list_head* list, unsigned int position, list_element* element);

//-----------------------------------------------------------------------------------------------------
//funkcje wyswietlania/pomocnicze
//----------------------------------------------------------------------------------------------------- 
list_element* swap_list_elements(list_element* element1, list_element* element2);

void print_element_data(list_element_data_type);

void list_print_element_byindex(list_head* list, unsigned int position);
void list_print_all(list_head head);
void list_info_print(list_head head);  //wypisuje elementy oraz rozmiar jako ostatnią liczbę

unsigned int list_count(list_head head);

void list_create_random(list_head* head, unsigned int size);

#endif
