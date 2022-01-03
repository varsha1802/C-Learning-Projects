#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#define CUS_SER "customer service"
#define PAR_DEL "parcel deliver"
#define BOTH "both requests"

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

#endif