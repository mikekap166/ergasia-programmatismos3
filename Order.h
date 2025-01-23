#ifndef ORDER_H
#define ORDER_H

typedef struct {
	int requests;
	int sold;
	int canceled[5];
} Order;

#endif // ORDER_H

