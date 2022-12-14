
/*******************************************************************************/
 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
 
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
//----------------------------------------------------------------------------------------------------
void list_add_element_as_first(list_head* list, list_element_data_type data);
void list_remove_element_first(list_head* list);
 
void list_add_element_as_last(list_head* list, list_element_data_type data);
void list_remove_element_last(list_head* list);

//Indeksacja elementów tak jak w tablicach: 0:[rozmiar-1] 
//dodawanie elementów wykonuje się za danym indeksem
//pozycja na minusie np. (-1) skutkuje wpisaniem elementu na poczatek listy
void list_add_element_by_index(list_head* list, list_element_data_type data, int position);
void list_remove_element_by_index(list_head* list, unsigned int position);

//-----------------------------------------------------------------------------------------------------
//Operacje zmiany kolejności elementów listy
//-----------------------------------------------------------------------------------------------------
void list_bubblesort(list_head* list);

//void list_switch_elements(list_head* list, unsigned int element1_pos, unsigned int element2_pos);



//-----------------------------------------------------------------------------------------------------
//Inne operacje na listach
//----------------------------------------------------------------------------------------------------- 
//zwrócenie długosci listy
unsigned int list_count_elements(list_head* list);
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
void list_print_all_elements(list_head* list);
void list_info_print(list_head* list);  //wypisuje elementy oraz rozmiar jako ostatnią liczbę

void list_create_random(list_head* head, unsigned int size);
/******************************************************************************
FUNKCJE KOD
*******************************************************************************/

/******************************************************************************
OPERACJE NA POCZĄTKU LISTY
*******************************************************************************/

void list_add_element_as_first(list_head* list, list_element_data_type data)
{

    list_element*  new_element = (list_element*) malloc(sizeof(list_element));
    new_element->data = data;
    
    new_element->next = (*list);
    (*list) = new_element;

}
/*************************************************************************************/

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

/******************************************************************************
OPERACJE NA KOŃCU LISTY
*******************************************************************************/

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
/*************************************************************************************/

void list_remove_element_last(list_head* list)
{
    if((*list) != NULL) //usuwamy tylko gdy lista ma elementy
    {
        //lista jednoelementowa nie ma przedostatniego elementu, przypadek specjalny
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

/******************************************************************************
OPERACJE NA INDEKSIE LISTY
Indeksacja elementów tak jak w tablicy: 0:[rozmiar-1]
*******************************************************************************/

void list_add_element_byindex(list_head* list, list_element_data_type data, int position)
{

    if(position < 0)
    {
        list_add_element_as_first(list, data);
    }
    else
    {
         list_element* temp_pointer = list_return_element_ptr_byindex(list, position);
         
         if((temp_pointer) != NULL)
         {
             
            list_element*  new_element = (list_element*) malloc(sizeof(list_element));
            new_element->data = data;
            
            new_element->next = temp_pointer->next;
            temp_pointer->next = new_element;
         }
         
         else
             printf("element listy o indeksie %d nie istnieje \n\r", position);

    }
}

/*************************************************************************************/

void list_remove_element_byindex(list_head* list, unsigned int position)
{
    if((*list) != NULL) //usuwamy tylko gdy lista ma elementy
    {
       if(position == 0) /*pierwszy element nie ma poprzedniego, przypadek pozycji 0 jest traktowany specjalnie, tak jak usuniecie elementu z poczatku listy*/
        {
                list_remove_element_first(list);
        }
        else
        {
            //Znajdujemy poprzednik usuwanego pliku (dlatego -1)
            list_element* temp_pointer = list_return_element_ptr_byindex(list, position-1);
         
            if(((temp_pointer) != NULL)&&((temp_pointer->next) != NULL))
            {
                list_element*  temp_pointer_to_delete = temp_pointer->next;
            
                temp_pointer->next = temp_pointer_to_delete->next;
                free(temp_pointer_to_delete);
            }
         
         else
             printf("element listy o indeksie %d nie istnieje \n\r", position);
        }
    }
    else
    {
        printf("nie ma co usuwać\n\r");
    }   
}

/*************************************************************************************/

list_element* list_return_element_ptr_byindex(list_head* list, unsigned int position)
{
    unsigned int count = 0;
    list_element* temp_pointer = (*list);
   
   
    while((temp_pointer != NULL)&&(count < position)) //koniec petli w przypadku znalezienia elementu lub konca listy
    {
        count++;
        temp_pointer = temp_pointer->next;
    }
   
    return temp_pointer;
}

/*************************************************************************************/

list_element_data_type list_return_element_data_byindex(list_head* list, unsigned int position)
{
    unsigned int count = 0;
    list_element* temp_pointer = (*list);
   
   
    while((temp_pointer != NULL)&&(count < position)) //koniec petli w przypadku znalezienia elementu lub konca listy
    {
        count++;
        temp_pointer = temp_pointer->next;
    }
    
    printf("element listy o indeksie %d ma wartość: ", position);
    print_element_data(temp_pointer->data);
    printf(" \n\r");
    return temp_pointer->data;

}

/******************************************************************************
OPERACJE INNE
*******************************************************************************/

void list_bubblesort(list_head* list)
{
    bool swap_flag = 0;     //flaga informująca o wykonaniu przemieszczenia
    int moves = 0;          //licznik wykonanych przemieszczeń
 
    if((*list) != NULL)     //nie sortujemy pustej tablicy
    {
        //sprawdzenie uporzadkowania na podstawie wykonanych przemieszczeń, gdy ich nie wykona lista jest gotowa
        do                  
        {  
            //dwa elementy pomocnicze: wskaźnik na element obecny oraz poprzedni
            list_element* element_ptr = (*list);
            list_element* element_previous_ptr = (*list);
            swap_flag = 0;
            
            //pojedyncze przejście przez listę
            while((element_ptr->next) != NULL) 
            {
                //porównanie wartości elementów obecnego oraz poprzedniego
                if((element_ptr->data) > (element_ptr->next->data))
                {
                    //osobny przypadek gdy zamieniamy pierwszy element listy
                    if(element_ptr == (*list))
                    {
                        //zamieniamy elementy i zamienione podpinamy je pod head listy
                        //przesuwamy wskażnik na kolejny element, previous zostaje na head
                        (*list) = swap_list_elements(element_ptr, element_ptr->next);
                        element_ptr = (*list)->next;
                        element_previous_ptr = (*list);
                    }
                    else
                    {
                        //gdy nie zamieniamy pierwszego elementu listy, zamienione wartości podpinamy pod next poprzedniego elementu
                        //przesuwamy ptr na nastepny
                        element_previous_ptr->next = swap_list_elements(element_ptr, element_ptr->next); 
                        element_ptr = element_previous_ptr->next;
                    }
                    swap_flag = 1;
                    moves++;
                }
                else
                {
                    //gdy nie było zamainy inkrementujemy dwa wskaźniki
                    element_previous_ptr = element_ptr;
                    element_ptr = element_ptr->next; 
                }
            }
                       // list_info_print(list) ;
        }
        while(swap_flag == 1); 
        
        printf("Posortowano listę wykonując: %d zamian \n\r", moves);
    }
    else
    {
        printf("nie mozna posortować pustej listy \n\r");
    }
}

/************************************************************************************

//zamianiany jest element z zadanej pozycji oraz następny
void list_swap_elements(list_head* list, unsigned int element_pos)
{
    
    if(((*list) != NULL)&& (((*list)->next) != NULL)) //lista musi mieć co najmniej dwa elementy aby wykonać zamianę
    {
        
        list_element* element_pointer = list_return_element_ptr_byindex(list, element_pos);
        
        if(element_pointer == NULL)
        {
            printf("na danej pozycji nie mozna dokonać zamiany \n\r");
        }
        else
        {   
            
            if(element_pos == 0)
            {
                (*list) = swap_list_elements(element_pointer, element_pointer->next);
            }
            else
            {
                list_element* temp_pointer = list_return_element_ptr_byindex(list, element_pos-1);
                temp_pointer->next = swap_list_elements(element_pointer, element_pointer->next);
            }
            
        }
    }
    else
    {
        printf("zbyt mało elementów do zamiany \n\r");
    }   
}

************************************************************************************/
//Funkcja zamiany zwraca wskaźnik na nowy pierwszy element
list_element* swap_list_elements(list_element* element1, list_element* element2)
{
           element1->next = element2->next;
           element2->next = element1;
           
           return element2;
}

/*************************************************************************************/

unsigned int list_count_elements(list_head* list)
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


/******************************************************************************
    WYSWIETLANIE LISTY/INNE
*******************************************************************************/


// format: [wartośc elementu #0] [wartośc elementu #1] ... [wartośc elementu #n-1] rozmiar: n
void list_info_print(list_head* list) 
{
    list_print_all_elements(list);
    printf(" rozmiar: %d \n\r", list_count_elements(list));
}



/*************************************************************************************/

void list_print_all_elements(list_head* list)
{
    list_element* temp_pointer = (*list);
   
    if(temp_pointer == NULL)
     printf("lista jest pusta");
   
    while(temp_pointer != NULL)
    {
        print_element_data(temp_pointer->data);
        temp_pointer = temp_pointer->next;
    }
     
}

/*************************************************************************************/

void print_element_data(list_element_data_type data)
{
    printf("%d ", data);
}

/*************************************************************************************/

void list_create_random(list_head* head, unsigned int size)
{
    srand(time(NULL));
    
    for (int i = 0; i < size; i++)
    {
        list_add_element_as_first(head, (rand() % 100));
    }
	
}

/*************************************************************************************/

int main()
{
    
    list_head mylist = NULL;
    
    list_create_random(&mylist, 30);
    list_info_print(&mylist);  

    
    list_bubblesort(&mylist);
    list_info_print(&mylist);  
    return 0;
}
