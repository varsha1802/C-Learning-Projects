#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "employee.h"
#include "participants.h"
#include "receptionist.h"

#define check_bit(map, pos) ((map) & (1<<(pos-1)))

typedef void(*func)();
static int f_cnt = 0;

struct employee {
  int emp_id;
  char emp_name[15];
  int events;
  bool busy;
  func cb;
  struct employee *next;
};

struct employee *head = NULL;
struct employee *tail = NULL;

void register_employee(int id,char e_name[10],int map,void(*cb_ptr)())
{ 
  struct employee* new_emp = (struct employee*)malloc(sizeof(struct employee));
  if (new_emp != NULL) 
  {
    new_emp->emp_id = id;
    strcpy(new_emp->emp_name, e_name);
    new_emp->events = map;
    new_emp->busy = false;
    new_emp->cb = cb_ptr;
    new_emp->next = NULL;
  }  
  if(head == NULL)
  {
    head = new_emp;
    tail = new_emp;
  } else
  {
    tail->next = new_emp;
    tail = new_emp;
  }
  printf("\nEmployee %d - %s registered successfully\n",id,new_emp->emp_name);
}

void forward_req(int evt_num, char *name, char *place)
{
  struct employee*  temp;
  bool success = false;
  temp = head;
  while (temp != NULL)
  {
    if(!temp->busy)
    {
      if (check_bit(temp->events, evt_num))
      {
        success = true;
        printf("\n---------------------------------------------------------\n");
        printf("\nRequester name : '%s'\tPlace : '%s'\n",name,place);
        printf("\nYour Request is forwarded to our employee\n");
        printf("\nEmployee Id : '%d'    Employee name : '%s'\n",temp->emp_id, temp->emp_name);
        temp->busy = true;
        temp->cb();
        break;
      }
    }
    temp = temp->next;
  }
  if(!success) {
    printf("\n----------------------------------------------------------------");
    printf("\nAll our employees are busy now. Please come back after some time");
    printf("\n----------------------------------------------------------------\n");
    f_cnt++;
    if (f_cnt > 1)
    {
      free_empls();
    }
  }
}

void free_empls() {
  struct employee* p;
  p = head;
  while (p != NULL) 
  {
    if(p->busy) 
    {
      p->busy = false;
    }
    p = p->next;  
  }
}

void show_empls() {
  struct employee* p;
  p = head;
  printf("\n--------------------Employees List-----------------------\n");
  printf("\n---------------------------------------------------------");
  printf("\nId\tName\t\tServices");
  printf("\n---------------------------------------------------------"); 
  while (p != NULL) 
  {
    printf("\n%d\t",p->emp_id);
    printf("%s\t\t",p->emp_name);
    switch(p->events)
    {
      case 1: printf("Visitor"); break;
      case 2: printf("Caller"); break;
      case 3: printf("Visitor, Caller"); break;
      case 4: printf("Delivery"); break;
      case 5: printf("Visitor, Delivery"); break;
      case 6: printf("Caller, Delivery"); break;
      case 7: printf("Visitor, Caller, Delivery"); break;
    }
    p = p->next;     
  }
  printf("\n---------------------------------------------------------\n");
}