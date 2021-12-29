#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#define GUS_VIS "visitor"
#define GUS_CALL "phone caller"
#define GUS_PAR "delivery person"

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