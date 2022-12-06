

#include <stdio.h>
#include <stdbool.h>




#include "lista.h"
/******************************************************************************
FUNKCJE KOD
*******************************************************************************/

// inicjalizuje klase listy zerami, bez niej wskaźniki wylatują w kosmos
void list_init(list_head* head)
{
     head->head_ptr = NULL;
     head->tail_ptr = NULL;
     head->cnt = 0;
}
     

/******************************************************************************
OPERACJE NA POCZĄTKU LISTY
*******************************************************************************/

void list_add_first(list_head* head, list_element_data_type data)
{
    list_element*  new_element = (list_element*)malloc(sizeof(list_element));
    new_element->data = data;
    
    new_element->prev = NULL;
    new_element->next = head->head_ptr;
  
    if(head->head_ptr != NULL)
    {      
          head->head_ptr->prev = new_element;       
    }
    else
    {
        head->tail_ptr = new_element;
    }
    
    head->head_ptr = new_element;
    head->cnt +=1;
}


void list_add_last(list_head* head, list_element_data_type data)
{
  
    list_element*  new_element = (list_element*) malloc(sizeof(list_element));
    new_element->data = data;
    
    new_element->next = NULL;
    new_element->prev = head->tail_ptr;
    
    if(head->tail_ptr != NULL)
    {      
          head->tail_ptr->next = new_element;       
    }
        else
    {
        head->head_ptr = new_element;
    }
    
    head->tail_ptr = new_element;
    head->cnt +=1;
}





void list_remove_element(list_head* head, unsigned int position)
{
  if((position <= (head->cnt))&&(position!=0))
  {
       
       list_element* temp_ptr; 
       int incr = 0;
       
       
       
       if(position <= ((head->cnt)>>1))
       {
            temp_ptr = head->head_ptr;       
            while(position > 1) // pierwszy element ma pozycje 1, liczac od poczatku porónujemy pozycje do 1
            {
                 temp_ptr = temp_ptr->next;
                 position--;
                 incr++;              
            }
       }
       else
       {
           position = head->cnt - position;
           temp_ptr = head->tail_ptr;
           while(position > 0) // ostatni element ma pozycje równą ilosci(cnt), wiec liczac od konca porównujemy pozycje do 0
           {
                temp_ptr = temp_ptr->prev;
                position--; 
                incr++;             
           }         
       }
       
       if((temp_ptr->prev == NULL) && (temp_ptr->next == NULL))
       {
          head->head_ptr = NULL;
          head->tail_ptr = NULL;
       }
       
       else
       {
           if(temp_ptr->prev != NULL)
           {
              temp_ptr->prev->next =  temp_ptr->next;           
           }
           else
           {         
               temp_ptr->next->prev =  NULL;
               head->head_ptr = temp_ptr->next;
           }
       
       
           if(temp_ptr->next != NULL)
           {
               temp_ptr->next->prev =  temp_ptr->prev;           
           }
           else
           {
               temp_ptr->prev->next =  NULL;
               head->tail_ptr = temp_ptr->prev;
           }
        }                    
       
       free(*temp_ptr);             
       head->cnt -=1;
       printf("kroki: %d  \n\r", incr);
  }
  else
  {
      printf("Nie ma takiej pozycji \n\r");
  }
   
 
}



void list_print_fval(list_head head)
{
     if(head.head_ptr != NULL)
         print_element_data(head.head_ptr->data);
     else
         printf("Lista jest pusta \n\r");
}


void list_print_lval(list_head head)
{
     if(head.tail_ptr != NULL)
          print_element_data(head.tail_ptr->data);
     else
         printf("Lista jest pusta \n\r");
}

void list_print_cnt(list_head head)
{
     printf("%d \n\r", head.cnt);
}




/*************************************************************************************/

/*

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
*******************************************************************************


/*************************************************************************************

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
*******************************************************************************

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

/*************************************************************************************

void list_remove_element_byindex(list_head* list, unsigned int position)
{
    if((*list) != NULL) //usuwamy tylko gdy lista ma elementy
    {
       if(position == 0) /*pierwszy element nie ma poprzedniego, przypadek pozycji 0 jest traktowany specjalnie, tak jak usuniecie elementu z poczatku listy
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

/*************************************************************************************

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

/*************************************************************************************

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
*******************************************************************************

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
************************************************************************************
//Funkcja zamiany zwraca wskaźnik na nowy pierwszy element
list_element* swap_list_elements(list_element* element1, list_element* element2)
{
           element1->next = element2->next;
           element2->next = element1;
           
           return element2;
}

/*************************************************************************************/

unsigned int list_count(list_head head)
{
    int count = 0;
    list_element* temp_pointer = head.head_ptr;
   
   
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
void list_info_print(list_head head) 
{
    list_print_all(head);
    printf(" rozmiar: %d \n\r", list_count(head));
}



/*************************************************************************************/

void list_print_all(list_head head)
{
    list_element* temp_pointer = head.head_ptr;
   
    if(temp_pointer == NULL)
     printf("lista jest pusta");
   
    while(temp_pointer != NULL)
    {
        print_element_data(temp_pointer->data);
        temp_pointer = temp_pointer->next;
    }
    
    printf("\n\r");
     
}

/*************************************************************************************/

void print_element_data(list_element_data_type data)
{
    printf("%d ", data);
}

/*************************************************************************************

void list_create_random(list_head* head, unsigned int size)
{
    srand(time(NULL));
    int i = 0;
    
    for (i; i < size; i++)
    {
        list_add_element_as_first(head, (rand() % 100));
    }
	
}
*/
