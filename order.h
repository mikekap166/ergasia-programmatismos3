#ifndef ORDER_H
#define ORDER_H

typedef struct {
	int requests;
	int sold;
	int canceled[5];
} order;

#endif // ORDER_H

