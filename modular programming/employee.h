#include<stdbool.h>
#include "participants.h"

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

struct employee {
	int emp_id;
	char emp_name[10];
	char services[5][20];
	bool busy;
};

void serve_parcel_req(struct parcel *pcl, int parcel_num, struct employee *emp);
void serve_caller(struct phone_call call, struct employee *emp);
void serve_visitor(struct visitor vis, struct employee *emp);
struct employee *add_employee(int emp_id, char emp_name[10], int num_serv, char services[5][20], bool busy);
void disp_all_employees(struct employee **emp, int count);
struct employee *get_all_employees(struct employee *emp);
void set_busy(struct employee *emp);

#endif