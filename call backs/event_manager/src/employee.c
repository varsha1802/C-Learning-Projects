#include <stdlib.h>
#include <stdio.h>
#include "receptionist.h"
#include "employee.h"

#define set_bit(map, pos) ((map) |= 1<<(pos-1))

void emp1()
{ 
  printf("\nEmployee 1 - I have sucessfully received the request\n");
  printf("\n----------------started to process-----------------------\n");
  printf("\n---------------------------------------------------------\n");
}

void emp2()
{
  printf("\nEmployee 2 - I have sucessfully received the request\n");
  printf("\n----------------started to process-----------------------\n");
  printf("\n---------------------------------------------------------\n");
}

void emp3()
{
  printf("\nEmployee 3 - I have sucessfully received the request\n");
  printf("\n----------------started to process-----------------------\n");
  printf("\n---------------------------------------------------------\n");
}

void emp4()
{
  printf("\nEmployee 4 - I have sucessfully received the request\n");
  printf("\n----------------started to process-----------------------\n");
  printf("\n---------------------------------------------------------\n");
}

void emp5()
{
  printf("\nEmployee 5 - I have sucessfully received the request\n");
  printf("\n----------------started to process-----------------------\n");
  printf("\n---------------------------------------------------------\n");
}

void (*reg_event[])() = {&emp1,&emp2,&emp3,&emp4,&emp5};

void add_employees(int num_emp)
{
  int evt_no, evt = 0, bit_map;
  char e_name[10];
  for (int i = 0; i < num_emp; i++)
  {
    bit_map = 0;
    printf("\nEnter the following details for employee %d \n",i+1);
    printf("\nEmployee Name : ");
    scanf("%s",e_name);
    printf("\nNumber of events served : ");
    scanf("%d",&evt_no);
    printf("\n1 - Visitor, 2 - Caller, 3 - Parcel\n");
    for (int j = 0; j < evt_no; j++)
    {
      printf("\nEvent %d : ",j+1);
      scanf("%d",&evt); 
      set_bit(bit_map, evt);
    }    
    register_employee(i+1,e_name,bit_map,reg_event[i]);
  }    
}


