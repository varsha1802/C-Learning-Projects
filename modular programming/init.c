#include "receptionist.h"
#include "employee.h"
#include <stdio.h>
#include <string.h>

void main () {
    int num_emp, id, num_serv, ser;
    char name[10], services[5][20];
    struct employee *emp_ptr;
    printf("\n\n**********************************************************************************************");
    printf("\n                               Allocate Employees                                             \n");
    printf("**********************************************************************************************\n");
    printf("\nEnter the number of employees you want to add : ");
    scanf("%d",&num_emp);
    for(int i = 0; i < num_emp; i++) {
        printf("\nEnter the details for Employee %d \n",i+1);
        printf("\nId : ");
        scanf("%d",&id);
        printf("\nName : ");
        scanf("%s", name);
        printf("\nNumber of services : ");
        scanf("%d",&num_serv);
        for(int j=0; j<num_serv; j++) {
            printf("\nService %d for employee %s ",j+1,name);
            printf("(1 - Visitor, 2 - Caller, 3 - Parcel delivery) : ");
            scanf("%d",&ser);
            switch(ser) {
                case 1:
                    strcpy(services[j], GUS_VIS);
                    break;
                case 2:
                    strcpy(services[j], GUS_CALL);
                    break;
                case 3:
                    strcpy(services[j], GUS_PAR);
                    break;
                default:
                    printf("\nInvalid choice. Please choose again");
                    j--;
                    break;
            }
        }  
        emp_ptr = add_employee(id, name, num_serv, services, false);
        register_employee(emp_ptr);
    }
    interact();
}