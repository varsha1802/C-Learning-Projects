#include<stdbool.h>
#include "participants.h"
#include "employee.h"

#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

#define CUS_SERVICE "customer service"
#define PAR_DEL "parcel delivery"
#define BOTH_REQ "both requests"

void interact();

struct parcel *get_del_det();
struct phone_call get_call_det();
struct visitor get_vis_det();

void fwd_parcel_req(struct parcel *prcl, int no_of_parcels);
void fwd_caller_req(struct phone_call ph_call);
void fwd_visitor_req(struct visitor visi);

void register_employee(struct employee *emp);
int find_employee(char req_type[20] );
void free_all_emp();
struct employee *return_employee(int index);

#endif