#include <stdio.h>
#include <stdbool.h>

#include "list.h"
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

/******************************************************************************
*******************************************************************************/

void list_remove_first(list_head* head)
{
     if(head->head_ptr != NULL)
     {                 
          list_element* temp_ptr; 
          if(head->head_ptr->next == NULL)
          {
               temp_ptr  =   head->head_ptr;  
               head->head_ptr = NULL;
               head->tail_ptr = NULL;
          }
          else
          {
               temp_ptr = head->head_ptr;
               head->head_ptr->next->prev = NULL;
               head->head_ptr = head->head_ptr->next;
          }
          head->cnt -= 1;
          free(temp_ptr);
    }                                         
 }

/******************************************************************************
OPERACJE NA KONCU LISTY
*******************************************************************************/

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

/******************************************************************************
*******************************************************************************/
void list_remove_last(list_head* head)
{
     if(head->tail_ptr != NULL)
     {                 
          list_element* temp_ptr; 
          if(head->tail_ptr->prev == NULL)
          {
               temp_ptr  =   head->head_ptr;  
               head->head_ptr = NULL;
               head->tail_ptr = NULL;
               head->cnt = 0;
          }
     else
     {
          temp_ptr = head->tail_ptr;
          head->tail_ptr->prev->next = NULL;
          head->tail_ptr = head->tail_ptr->prev;
      }
      head->cnt -=1;
      free(temp_ptr);
    }                     
 }

/******************************************************************************
OPERACJE NA DOWOLNYM ELEMENCIE LISTY
*******************************************************************************/

void list_add_element(list_head* head, list_element_data_type data, unsigned int position)
{
     
     if(position == head->cnt)
     {
          list_add_last(head,data);    
       }
     else if(position == 0)
     {
          list_add_first(head,data);    
      }
     else
     {
         list_element* temp_ptr;
         if((temp_ptr = list_get_element(head,position)) != NULL)
         {
              list_element*  new_element = (list_element*) malloc(sizeof(list_element));
              new_element->data = data;
              
              new_element->next = temp_ptr->next;
              temp_ptr->next = new_element;
              
              new_element->prev = temp_ptr;
              temp_ptr->next->prev = new_element;
              
              
             head->cnt++; 
          }
          else
          {
              printf("ostatni element ma numer: %d\n\r",head-> cnt);
          }      
     } 
 }
 
/******************************************************************************
*******************************************************************************/
  
 void list_remove_element(list_head* head, unsigned int position)
{
     
     if(position == head->cnt)
     {
          list_remove_last(head);    
       }
     else if(position == 1)
     {
          list_remove_first(head);    
      }
     else if(position >0)
     {
         list_element* temp_ptr;
         if((temp_ptr = list_get_element(head,position)) != NULL)
         {
               temp_ptr->prev->next =  temp_ptr->next;
               temp_ptr->next->prev =  temp_ptr->prev;      
              
              free(temp_ptr);
              
             head->cnt--; 
          }
          else
          {
              printf("ostatni element ma numer: %d\n\r",head-> cnt);
          }      
     } 
 } 
 
 
/******************************************************************************
POBRANIE ADRESU DOWOLNEGO ELEMENTU
*******************************************************************************/

  list_element* list_get_element(list_head* head, unsigned int cnt)
{
              
       list_element* temp_ptr; 
       
       //funkcja sprawdza, czy szukany element jest bliżej końca czy poczatkku listy, i szuka od tej strony
       if((((head->cnt)/2) < cnt)&&(cnt <= head->cnt))
       {
          temp_ptr = head->head_ptr;       
            while(cnt > 1)
            {
                 temp_ptr = temp_ptr->next;  
                 cnt--;          
            }   
        }
        else if(cnt <= head->cnt)
        {
            cnt = head->cnt - cnt;
            temp_ptr = head->tail_ptr;       
            while(cnt > 0) 
            {
                 temp_ptr = temp_ptr->prev;
                 cnt--;             
            }   
        }
        else
        {
             printf("Nie ma takiego elementu \n\r");
             temp_ptr = NULL;
        }

            
         return temp_ptr;
  }
/******************************************************************************
PRZENIESIENIE CZESCI JEDNEJ LISTY NA POCZATEK DRUGIEJ (zadanie ze stosami)
brak zabezpieczeń krańcowych list
*******************************************************************************/

void  list_transfer(list_head* head_src, list_head* head_dst, unsigned int cnt)
{
     
       list_element* element_ptr = list_get_element(head_src, cnt);
       list_element* head_ptr = head_src->head_ptr;
       
       if(element_ptr != head_src->tail_ptr)
       {
            head_src->head_ptr = element_ptr->next;
            element_ptr->next->prev = NULL;
       }
       else
       {
            head_src->head_ptr = NULL;
            head_src->tail_ptr = NULL;                            
       }
           head_src->cnt -=cnt;
       
       if(head_dst->head_ptr != NULL)
       {    
       head_dst->head_ptr->prev = element_ptr;
       element_ptr->next = head_dst->head_ptr;
       head_dst->head_ptr = head_ptr;
       }
       else
       {
            element_ptr->next = NULL;
            head_dst->head_ptr = head_ptr;
            head_dst->tail_ptr = element_ptr;
           }
       head_dst->cnt +=cnt;       
 }





/******************************************************************************
FUNKCJE WYSWIETLAJĄCE
*******************************************************************************/


void list_print_head(list_head head)
{
     if(head.head_ptr != NULL)
         print_element_data(head.head_ptr->data);
     else
         printf("Lista jest pusta \n\r");
}


void list_print_tail(list_head head)
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
void list_swap_elements(list_head* head, unsigned int element_pos)
{
    
    if(head->cnt >=2) //lista musi mieć co najmniej dwa elementy aby wykonać zamianę
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

/************************************************************************************
//Funkcja zamiany zwraca wskaźnik na nowy pierwszy element
list_element* swap_list_elements(list_element* element1, list_element* element2)
{
           element1->next = element2->next;
           element2->next = element1;
           
           return element2;
}

/*************************************************************************************/

unsigned int list_count(list_head* head)
{
    int count = 0;
    list_element* temp_pointer = head->head_ptr;
   
   
    while(temp_pointer != NULL)
    {
        count++;
        temp_pointer = temp_pointer->next;
    }
   
    return count;
}

/*************************************************************************************/

void list_info_print(list_head* head) 
{
    list_print_all(head);
    printf(" rozmiar: %d \n\r", list_count(head));
}

/*************************************************************************************/

void list_print_all(list_head* head)
{
    list_element* temp_pointer = head->head_ptr;
   
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
    printf("%c ", data);
}


list_element_data_type get_head_data(list_head* head)
{
    return head->head_ptr-> data;
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
