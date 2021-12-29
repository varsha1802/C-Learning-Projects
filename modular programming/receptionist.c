#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "receptionist.h"

char guest_type[20];
int no_of_parcels = 0;
struct parcel *par;
static struct employee* employees[20];
static int k=0;
static int busy_cnt = 0;
int emp_cnt;

void interact() {
    emp_cnt = k; 
    disp_all_employees(employees, emp_cnt);
    printf("\n********************************************************************************************");
    printf("\n                                     I am the Receptionist\n");
    printf("********************************************************************************************\n");    
    while(true) {         
        int choice;  
        printf("\n-----------------------------------\n");
        printf("----Ready to serve the guests----");
        printf("\n-----------------------------------\n");        
        printf("\nEnter 1 if you are a VISITOR\nEnter 2 if you are a CALLER\nEnter 3 if you are a DELIVERY PERSON\n\n");
        scanf("%d",&choice);
        switch(choice) {
            case 1:
                strcpy(guest_type,GUS_VIS);
                printf("\nYou are a %s\n",guest_type);
                struct visitor visi = get_vis_det();
                if (strcmp(visi.req_type, PAR_DEL)==0) {
                    par = get_del_det();                    
                    fwd_parcel_req(par, no_of_parcels);  
                } else if (strcmp(visi.req_type, CUS_SERVICE)==0) {
                    fwd_visitor_req(visi);
                } else if (strcmp(visi.req_type, BOTH_REQ)==0) {
                    par = get_del_det();
                    fwd_visitor_req(visi);                    
                    fwd_parcel_req(par, no_of_parcels);  
                }
                break;
            case 2:
                strcpy(guest_type,GUS_CALL);
                printf("\nYou are a %s\n",guest_type);
                struct phone_call call = get_call_det();
                if (strcmp(call.req_type, PAR_DEL)==0) {
                    par = get_del_det();
                    fwd_parcel_req(par, no_of_parcels);
                } else if (strcmp(call.req_type, CUS_SERVICE)==0) {
                    fwd_caller_req(call);
                } else if (strcmp(call.req_type, BOTH_REQ)==0) {
                    par = get_del_det();
                    fwd_caller_req(call);                    
                    fwd_parcel_req(par, no_of_parcels);  
                }
                break;
            case 3:
                strcpy(guest_type, GUS_PAR);
                printf("\nYou are a %s\n",guest_type);
                par = get_del_det();
                fwd_parcel_req(par, no_of_parcels);          
                break;
            default:
                printf("\nYou've entered an INVALID choice. Please enter again.\n");
                break;
        }
    }
}

void register_employee(struct employee *emp) {
    employees[k] = emp;
    k++;
}

int find_employee(char req_type[20] ) {
    for(int i=0; i<emp_cnt; i++) {
        struct employee *emp_ptr = employees[i];
        if(!emp_ptr->busy) {
            int j=0;
            char service[20];
            strcpy(service, emp_ptr->services[j]);
            while((strcmp(service, "")) != 0) {
                if(strcmp(service, req_type) == 0) {
                    return i;
                }
                j++;
                strcpy(service, emp_ptr->services[j]);
            }
        }
    }
    busy_cnt++;
    if (busy_cnt > 1) {
        free_all_emp();
    }
    return -1;
}

void free_all_emp() {
    for(int i=0; i<emp_cnt; i++) {
        struct employee *emp_ptr = employees[i];
        if(emp_ptr->busy) {
            emp_ptr->busy = false;
        }
    }    
}

struct employee *return_employee(int index) {
    return employees[index];
}

struct visitor get_vis_det() {
    int ch,i;
    struct visitor vis;    
    printf("\ncould you please tell me your name? ");
    scanf("%s",vis.vis_name);
    printf("\nWhere are you coming from? ");
    scanf("%s",vis.come_from);
    printf("\nEnter 1 if you need customer service\nEnter 2 if you need to deliver parcel(s)\nEnter 3 if you have both the requests\n");
    scanf("%d",&ch);
    switch(ch) {
            case 1:
                strcpy(vis.req_type, CUS_SERVICE);
                break;
            case 2:
                strcpy(vis.req_type, PAR_DEL);
                break;
            case 3:
                strcpy(vis.req_type, BOTH_REQ);
                break;
            default:
                printf("\nYou've entered an INVALID choice\n");
                break;
        }
    
    return vis;
}

struct phone_call get_call_det(){
    int ch,i;
    struct phone_call ph_call;    
    printf("\ncould you please tell me your name? ");
    scanf("%s",ph_call.caller_name);
    printf("\nWhere are you calling from? ");
    scanf("%s",ph_call.calling_from);
    printf("\nEnter 1 if you need customer service\nEnter 2 if you need to deliver parcel(s)\nEnter 3 if you have both the requests\n");
    scanf("%d",&ch);
    switch(ch) {
            case 1:
                strcpy(ph_call.req_type, CUS_SERVICE);
                break;
            case 2:
                strcpy(ph_call.req_type, PAR_DEL);
                break;
            case 3:
                strcpy(ph_call.req_type, BOTH_REQ);
                break;
            default:
                printf("\nYou've entered an INVALID choice. Please enter again.\n");
                break;
        }    
    return ph_call;
}

struct parcel *get_del_det() {
    int i;
    printf("\nCould you please tell me the number of parcels that you need to deliver? ");
    scanf("%d",&no_of_parcels);
    struct parcel *parcels = malloc(sizeof(struct parcel) * no_of_parcels);
    for(i = 0; i < no_of_parcels; i++) {
        printf("\nParcel %d :\n",i+1);
        printf("\nWhere did the parcel come from? ");
        scanf("%s",parcels[i].from_place);
        printf("\nWho have sent this parcel? ");
        scanf("%s",parcels[i].sender_name);
    }
    return parcels;
}

void fwd_parcel_req(struct parcel *prcl, int no_of_parcels) {
    struct employee *emp;
    int emp_index = find_employee(GUS_PAR);
    if(emp_index != -1) {
        emp = return_employee(emp_index);
        printf("\nParcel delivery request has been started to process by our employee\n"); 
        printf("\nEmployee Id : %d Employee Name : %s\n", emp->emp_id, emp->emp_name);
        serve_parcel_req(prcl, no_of_parcels, emp);
    } else {
        printf("\nSorry for the inconvenience...! All our employees are busy now. Please come back after some time");
    }   
}

void fwd_visitor_req(struct visitor visi) {
    struct employee *emp;
    int emp_index = find_employee(GUS_VIS);
    if(emp_index != -1) {
        emp = return_employee(emp_index);
        printf("\nCustomer service request from the visitor %s has been started to process by our employee\n",visi.vis_name); 
        printf("\nEmployee Id : %d Employee Name : %s\n", emp->emp_id, emp->emp_name);
        serve_visitor(visi, emp);
    } else {
        printf("\nSorry for the inconvenience...! All our employees are busy now. Please come back after some time");
    }   
}

void fwd_caller_req(struct phone_call ph_call) {
    struct employee *emp;
    int emp_index = find_employee(GUS_CALL);
    if(emp_index != -1) {
        emp = return_employee(emp_index);
        printf("\nCustomer service request from the caller %s has been started to process by our employee\n",ph_call.caller_name); 
        printf("\nEmployee Id : %d Employee Name : %s\n", emp->emp_id, emp->emp_name);
        serve_caller(ph_call, emp);
    } else {
        printf("\nSorry for the inconvenience...! All our employees are busy now. Please come back after some time");
    }   
}