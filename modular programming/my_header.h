#include<stdbool.h>

#define CUS_SERVICE "customer service"
#define PAR_DEL "parcel delivery"
#define BOTH_REQ "par and cus"
#define GUS_VIS "visitor"
#define GUS_CALL "phone caller"
#define GUS_PAR "delivery person"

struct employee {
	int emp_id;
	char emp_name[10];
	char services[5][20];
	bool busy;
};

struct parcel {
	char sender_name[20];
	char from_place[10];
};

struct phone_call {
	char caller_name[20];
	char calling_from[10];
	char req_type[20];
};

struct visitor {
	char vis_name[20];
	char come_from[10];
	char req_type[20];
};

void interact();
void fwd_parcel_req(struct parcel *prcl);
void fwd_caller_req(struct phone_call ph_call);
void fwd_visitor_req(struct visitor visi);
void serve_parcel_req(struct parcel *pcl, struct employee *emp);
void serve_caller(struct phone_call call, struct employee *emp);
void serve_visitor(struct visitor vis, struct employee *emp);
struct phone_call get_call_det();
struct visitor get_vis_det();
struct parcel *get_del_det();


	
 