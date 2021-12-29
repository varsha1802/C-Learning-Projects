#include <stdio.h>  
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "employee.h"

struct employee *add_employee(int emp_id, char emp_name[10], int num_serv, char services[5][20], bool busy) {
    struct employee *ptr;
    ptr = (struct employee*) malloc(1 * sizeof(struct employee));
    ptr->emp_id = emp_id;
    strcpy(ptr->emp_name, emp_name);
    for(int i=0; i<num_serv; i++) {
        strcpy(ptr->services[i], services[i]);
    }
    ptr->busy = busy;
    return ptr;
}

void disp_all_employees(struct employee **emp, int count) {
    printf("\n-----------------------------Employees List-------------------------\n");
    printf("\n--------------------------------------------------------------------");
    printf("\nSno\tId\tName\t\tServices");
    printf("\n--------------------------------------------------------------------");
    for(int i=0; i<count; i++) {
        struct employee *employee = *(emp+i);
        printf("\n%d\t",i+1);
        printf("%d\t",employee->emp_id);
        printf("%s\t\t",employee->emp_name);
        char service[20];
        int j=0;
        strcpy(service, employee->services[j]);
        while((strcmp(service, "")) != 0) {
            printf("%s, ",service);
            j++;
            strcpy(service, employee->services[j]);
        }
    }
    printf("\n--------------------------------------------------------------------\n");
}

void serve_parcel_req(struct parcel *pcl, int parcel_num, struct employee *emp) {
    emp->busy = true;
    for(int i=0; i<parcel_num; i++) {
        sleep(3);
        printf("\nPARCEL has been successfully received from %s, %s\n",pcl->sender_name,pcl->from_place);
        pcl++;
    }   
}

void serve_visitor(struct visitor visi, struct employee *emp) {
    emp->busy = true;
    sleep(3);
    printf("\nRequest from the guest %s, %s has been sucessfully processed\n", visi.vis_name,visi.come_from);
}

void serve_caller(struct phone_call call, struct employee *emp) {
    emp->busy = true;
    sleep(3);
    printf("\nRequest from the caller %s, %s has been sucessfully processed\n", call.caller_name, call.calling_from);
}