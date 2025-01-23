

#include <stdio.h>
#include "Product.h"
#include "Order.h"
#include <string.h>
#include <stdlib.h>


int funky(Product products[], Order orders[], int i) {
    if (products[i].item_count > 0) { 
        products[i].item_count -= 1;   
        orders[i].requests += 1;      
        orders[i].sold += 1;         
        return 0;  
    } else {
        orders[i].requests += 1;          
        return 1;
    }
}
  
  










