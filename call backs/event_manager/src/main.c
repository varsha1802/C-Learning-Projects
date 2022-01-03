#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "receptionist.h"
#include "employee.h"
#include "participants.h"

#define VISITOR 1
#define CALLER 2
#define DELIVERY 3

void handle_parc_req(int parc_num, void (*forward_req)(int, char *, char *))
{
    struct parcel *parcels = malloc(sizeof(struct parcel) * parc_num);
    for (int i = 0; i < parc_num; i++) {
        printf("\nParcel %d :\n",i+1);
        printf("\nWho have sent this parcel? ");
        scanf("%s",parcels[i].sender_name);
        printf("\nWhere did the parcel come from? ");
        scanf("%s",parcels[i].from_place);
    }
    for (int i = 0; i < parc_num; i++) {
        printf("\n---------------------------------------------------------\n");
        printf("\nParcel delivery request %d\n",i+1);
        (*forward_req)(DELIVERY, parcels[i].sender_name, parcels[i].from_place);
    }
}

void main()
{
    int evt_num, emp_cnt, ch_req, no_of_parcels;
    struct phone_call call;
    struct visitor vis;
    printf("\n---------------------------------------------------------");
    printf("\n                 Allocate Employees");
    printf("\n---------------------------------------------------------\n");
    printf("\nEnter the number of Employees to be added (Maximum count is 5) : ");
    scanf("%d",&emp_cnt);
    add_employees(emp_cnt);
    show_empls();
    printf("\n---------------------------------------------------------");
    printf("\n                 Receptionist mode");
    printf("\n---------------------------------------------------------\n");
    while(1)
    {
        printf("\nReady to serve guests......!\n");
        printf("\nEnter the guest type ");
        printf("(1 - Visitor, 2 - Caller, 3 - Delivery person) : ");        
        scanf("%d",&evt_num);
        switch(evt_num) {
            case 1 : 
                printf("\ncould you please tell me your name? ");
                scanf("%s",vis.vis_name);
                printf("\nWhere are you coming from? ");
                scanf("%s",vis.come_from);
                printf("\n1 - customer service ** 2 - Deliver parcel(s) ** 3 - Both the requests : ");
                scanf("%d",&ch_req);
                printf("\n---------------------------------------------------------\n");
                printf("\n              Request from a visitor\n");
                switch(ch_req) {
                    case 1:
                        strcpy(vis.req_type, CUS_SER);
                        forward_req(VISITOR, vis.vis_name, vis.come_from);
                        break;
                    case 2:
                        strcpy(vis.req_type, PAR_DEL);
                        printf("\nCould you please tell me the number of parcels that you need to deliver? ");
                        scanf("%d",&no_of_parcels);
                        handle_parc_req(no_of_parcels, forward_req);
                        break;
                    case 3:
                        strcpy(vis.req_type, BOTH);
                        forward_req(VISITOR, vis.vis_name, vis.come_from);
                        printf("\nCould you please tell me the number of parcels that you need to deliver? ");
                        scanf("%d",&no_of_parcels);
                        handle_parc_req(no_of_parcels, forward_req);
                        break;
                    default:
                            printf("\nYou've entered an INVALID choice\n");
                            break;
                }
                break;
            case 2 :
                printf("\ncould you please tell me your name? ");
                scanf("%s",call.caller_name);
                printf("\nWhere are you calling from? ");
                scanf("%s",call.calling_from);
                printf("\n1 - Customer service ** 2 - Deliver parcel(s) ** 3 - Both the requests : ");
                scanf("%d",&ch_req); 
                printf("\n---------------------------------------------------------\n");
                printf("\n                  Phone call arrived\n");
                switch(ch_req) {
                    case 1:
                            strcpy(call.req_type, CUS_SER);
                            forward_req(CALLER, call.caller_name, call.calling_from);
                            break;
                    case 2:
                            strcpy(call.req_type, PAR_DEL);
                            printf("\nCould you please tell me the number of parcels that you need to deliver? ");
                            scanf("%d",&no_of_parcels);
                            handle_parc_req(no_of_parcels, forward_req);
                            break;
                    case 3:
                            strcpy(call.req_type, BOTH);
                            forward_req(CALLER, call.caller_name, call.calling_from);
                            printf("\nCould you please tell me the number of parcels that you need to deliver? ");
                            scanf("%d",&no_of_parcels);
                            handle_parc_req(no_of_parcels, forward_req);
                            break;
                    default:
                            printf("\nYou've entered an INVALID choice\n");
                            break;
                }
                break;
            case 3 :
                printf("\nCould you please tell me the number of parcels that you need to deliver? ");
                scanf("%d",&no_of_parcels);
                handle_parc_req(no_of_parcels, forward_req);
                break;
            default :
                printf("\nInvalid choice\n");
        }
    }
}
