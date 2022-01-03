#ifndef RECEPTIONIST_H
#define RECEPTIONIST_H

void register_employee(int id,char e_name[10],int map,void(*cb_ptr)());
void forward_req(int evt_num, char *name, char *place);
void free_empls();
void show_empls();

#endif
