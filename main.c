#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include "Product.h"
#include "funky.h"
#include "order.h"

void main() {
	pid_t pid ;
	int i, k;
	
	int CP1[2], CP2[2], CP3[2], CP4[2], CP5[2];// 'C'Child to 'P'Parent pipe
	
        int PC1[2], PC2[2], PC3[2], PC4[2], PC5[2];// 'P'Parent to 'C'Child pipe
       
	pipe(CP1);
	pipe(CP2);
	pipe(CP3);
	pipe(CP4);
	pipe(CP5);
	
	pipe(PC1);
	pipe(PC2);
	pipe(PC3);
	pipe(PC4);
	pipe(PC5);
	char a;
	int orders=0;
	int canceled=0;
	int completed=0;
	int income=0;
	Product array1[10];
	order array2[10];
	strcpy(array1[0].desc , "tv 4k 55inch");
	strcpy(array1[1].desc , "gaming keyboard");
	strcpy(array1[2].desc , "gaming mouse");
	strcpy(array1[3].desc , "mousepad");
	strcpy(array1[4].desc , "gaming headphones");
	strcpy(array1[5].desc , "f175 carlos sainz 1/43 car model");
	strcpy(array1[6].desc , "gaming computer");
	strcpy(array1[7].desc , "gaming monitor");
	strcpy(array1[8].desc , "ps5 pro");
	strcpy(array1[9].desc , "ps5 controller dualsense");
	array1[0].price=650;
	array1[1].price=120;
	array1[2].price=80;
	array1[3].price=12;
	array1[4].price=65;
	array1[5].price=49;
	array1[6].price=2350;
	array1[7].price=350;
	array1[8].price=750;
	array1[9].price=80;
	for (i =0 ; i<10; i++){
		array1[i].item_count=2;
	}
	for (i =0 ; i<10; i++){
                array2[i].requests=0;
		array2[i].sold=0;
		array2[i].canceled=0;
        }
	pid=fork(); // first child's birth
	if (pid>0){
		pid=fork(); // second child's birth
	} else {
	      for(k=0; k<10; k++){
	        close(PC1[1]); // first child's process
	        read(PC1[0], &i, sizeof(int));
	        i=0 + rand() % 10 ;
		close(CP1[0]);
	        write(CP1[1], &i, sizeof(int));
	        close(PC1[1]);
	        read(PC1[0], &i, 4);
	        sleep(1);
	      }  
	      exit(1);
	}
      
	if (pid>0){
                pid=fork(); // third child's birth
        }else {
              for(k=0; k<10; k++){
	        close(PC2[1]); // second child's process
	        read(PC2[0], &i, sizeof(int));
	        i=0 + rand() % 10 ;
		close(CP2[0]);
	        write(CP2[1], &i, sizeof(int));
	        close(PC2[1]);
	        read(PC2[0], &i, 4);
	        sleep(1);
	      }  
	      exit(1);
	}
	if (pid>0){
                pid=fork(); // fourth child's birth
        }else {
              for(k=0; k<10; k++){
	        close(PC3[1]);  // third child's process
	        read(PC3[0], &i, sizeof(int));
	        i=0 + rand() % 10 ;
		close(CP3[0]);
	        write(CP3[1], &i, sizeof(int));
	        close(PC3[1]);
	        read(PC3[0], &i, 4);
	        sleep(1);
	      }  
	      exit(1);
	}
	if (pid>0){
                pid=fork(); // fifth child's birth
        }else {
              for(k=0; k<10; k++){
	        close(PC4[1]); // fourth child's process
	        read(PC4[0], &i, sizeof(int));
	        i=0 + rand() % 10 ;
		close(CP4[0]);
	        write(CP4[1], &i, sizeof(int));
	        close(PC4[1]);
	        read(PC4[0], &i, 4);
	        sleep(1);
	      }  
	      exit(1);
	}
	 if (pid>0){
                i=7;
        }else {          
              for(k=0; k<10; k++){
	        close(PC5[1]); // fifth child's process
	        read(PC5[0], &i, sizeof(int));
	        i=0 + rand() % 10 ;
		close(CP5[0]);
	        write(CP5[1], &i, sizeof(int));
	        close(PC5[1]);
	        read(PC5[0], &i, 4);
	        sleep(1);
	      }  
	      exit(1);
	}
	 
	 
	            
        /// parent process ///
	 if (pid>0){ 
	    int x=0, j;
	    int customer;
	    i=0;
	    
	    
	    
	    
	    int t;                                  /// FOR CHILD 1 ///
	    for(x=0;x<10; x++){
	      close(PC1[0]);
	      write(PC1[1], &i, sizeof(int));
	      read(CP1[0], &t, sizeof(j));
	      orders+=1;
	      j= funky(array1, array2, t);
	      int l;
	      if(j==0){  
	          close(PC1[0]);
	          j= array1[t].price;
	          income+=j;
	          char ch = 'Y'; //Parent informs child if order can be done with a Y
	          write(PC1[1], &ch, 1); 
	          completed+=1;
	          printf("Client 1: Purchase complete! Your total is: %d €\n", j);
	        }
	        else{
	          char ch='N';
	          close(PC1[0]);
	          j=0;
	          write(PC1[1], &ch, sizeof(char));
	          canceled+=1; 
	          printf("Client 1: Products unavailable sorry have a nice day. Request Denied!!!!\n" );
	        }
	        sleep(1);
	    }
	    
	    
	    
	    
	                                      /// FOR CHILD 2 ///	    
	    for(x=0;x<10; x++){
	      close(PC2[0]);
	      write(PC2[1], &i, sizeof(int));
	      read(CP2[0], &t, sizeof(t));
	      orders+=1;
	      j= funky(array1, array2, t);
	      if(j==0){  
	          close(PC2[0]);
	          j= array1[t].price;
	          income+=j;
	          char ch = 'Y'; //Parent informs child if order can be done with a Y
	          write(PC2[1], &ch, 1); 
	          completed+=1;
	          printf("Client 2: Purchase complete! Your total is: %d €\n", j);
	        }
	        else{
	          char ch='N';
	          close(PC2[0]);
	          j=0;
	          write(PC2[1], &ch, sizeof(char));
	          canceled+=1; 
	          printf("Client 2: Products unavailable sorry have a nice day. Request Denied!!!!\n" );
	        }
	        sleep(1);
	    }
	    
	    
	    
	    
	                                      /// FOR CHILD 3 ///	    
	    for(x=0;x<10; x++){
	      close(PC3[0]);
	      write(PC3[1], &i, sizeof(int));
	      read(CP3[0], &t, sizeof(t));
	      orders+=1;
	      j= funky(array1, array2, t);
	      if(j==0){  
	          close(PC3[0]);
	          j= array1[t].price;
	          income+=j;
	          char ch = 'Y'; //Parent informs child if order can be done with a Y
	          write(PC3[1], &ch, 1); 
	          completed+=1;
	          printf("Client 3: Purchase complete! Your total is: %d €\n", j);
	        }
	        else{
	          char ch='N';
	          close(PC3[0]);
	          j=0;
	          write(PC3[1], &ch, sizeof(char));
	          canceled+=1; 
	          printf("Client 3: Products unavailable sorry have a nice day. Request Denied!!!!\n" );
	        }
	        sleep(1);
	    }
	    
	    
	    
	    
	                                      /// FOR CHILD 4 ///	    
	    for(x=0;x<10; x++){	    
	      close(PC4[0]);
	      write(PC4[1], &i, sizeof(int));
	      read(CP4[0], &t, sizeof(j));
	      orders+=1;
	      j= funky(array1, array2, t);
	      if(j==0){  
	          close(PC4[0]);
	          j= array1[t].price;
	          income+=j;
	          char ch = 'Y'; //Parent informs child if order can be done with a Y
	          write(PC4[1], &ch, 1); 
	          completed+=1;
	          printf("Client 4: Purchase complete! Your total is: %d €\n", t);
	        }
	        else{
	          char ch='N';
	          close(PC4[0]);
	          j=0;
	          write(PC4[1], &ch, sizeof(char));
	          canceled+=1; 
	          printf("Client 4: Products unavailable sorry have a nice day. Request Denied!!!!\n" );
	        }
	        sleep(1);
	    }
	    
	    
	    
	    
	                                      /// FOR CHILD 5 ///	    
	    for(x=0;x<10;x++){
	      close(PC5[0]);
	      write(PC5[1], &i, sizeof(int));
	      read(CP5[0], &t, sizeof(t));
	      orders+=1;
	      j= funky(array1, array2, t);
	      if(j==0){  
	          close(PC5[0]);
	          j= array1[t].price;
	          income+=j;
	          char ch = 'Y'; //Parent informs child if order can be done with a Y
	          write(PC5[1], &ch, 1); 
	          completed+=1;
	          printf("Client 5: Purchase complete! Your total is: %d €\n", j);
	        }
	        else{
	          char ch='N';
	          close(PC5[0]);
	          j=0;
	          write(PC5[1], &ch, sizeof(char));
	          canceled+=1; 
	          printf("Client 5: Products unavailable sorry have a nice day. Request Denied!!!!\n" );
	        }  
	        sleep(1);
	    }
	    
	    
	    
	    
	                                      /// FINAL REPORT ///
	    waitpid(-1, NULL, 0);
	    for(t=0;t<10;t++){
	      printf("\n\n\n%d.The item with the description %s had:\n",t,array1[t].desc);
	      printf("%d requests for purchase \n",array2[t].requests);
	      printf("%d sales\n",array2[t].sold);
	      printf("%d requests not served",array2[t].canceled);
	    }
	    printf("\n\n\nTotal Orders were: %d\n", orders);
	    printf("Total Completed Orders were: %d\n", completed);
	    printf("Total Canceled Orders were: %d\n", canceled);
	    printf("Total Income is: %d\n", income);
	    
	 }


}
