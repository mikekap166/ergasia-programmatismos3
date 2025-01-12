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
	pid_t pid ; //Main variable that we hold the id of the proccess to separate father from child processes 
	int i,k,b; // general use counters
	
	int CP1[2], CP2[2], CP3[2], CP4[2], CP5[2];// 'C'Child to 'P'Parent pipe
	
        int PC1[2], PC2[2], PC3[2], PC4[2], PC5[2];// 'P'Parent to 'C'Child pipe
       
	pipe(CP1); //Creating Pipes for Child to Parent communication
	pipe(CP2);
	pipe(CP3);
	pipe(CP4);
	pipe(CP5);
	
	pipe(PC1); //Creating Pipes for Parent to Child communcation
	pipe(PC2);
	pipe(PC3);
	pipe(PC4);
	pipe(PC5);
	
	char a; //Used in child processes to recieve a character that informs the child if the purchase was complete
	
	//initialization of counters for the final report
	int orders=0;		
	int canceled=0;
	int completed=0;
	int income=0;

	//Creation of arrays of structs Product and order that contain information about each product and order requests respectively
	Product array1[10];
	order array2[10];

	//initialization of products descriptions in array1
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

	//Initialization of Products prices in array1
	array1[0].price=650;
	array1[1].price=120;
	array1[2].price=80;
	array1[3].price=12;
	array1[4].price=65;
	array1[5].price=49;
	array1[6].price=2350;
	array1[7].price=350;
	array1[8].price=750;
	array1[9].price=75;

	//Initialization of item count for each product to 2 in array1
	for (i =0 ; i<10; i++){
		array1[i].item_count=2;
	}



	//Initialization of array2 requests/sold counters and the canceled list of denied clients 
	for (i =0 ; i<10; i++){
                array2[i].requests=0;
		array2[i].sold=0;
		for(k=0;k<5;k++){ 
		  array2[i].canceled[k]=0;
		}
        }
	
	
	
		                                      /// 1st Child Execution ///
	
	pid=fork(); //First Childs Birth
	if (pid>0){ //Only Parant Process goes in
		pid=fork(); // second child's birth
	} else {
	      for(k=0; k<10; k++){  // 10 loops for 10 requests
		close(PC1[1]); //closing write descriptor of PC pipe
	        read(PC1[0], &i, sizeof(int)); //Waits to read an integer from PC pipe so it proceeds
	        i=0 + rand() % 10 ; //use of rand to decide 1 of 10 products 
		close(CP1[0]); //Closing read descriptor of CP pipe
	        write(CP1[1], &i, sizeof(int)); //writes integer i to CP to send the random product to parent process
	        close(PC1[1]);  //close write descriptor of PC pipe
	        read(PC1[0], &a, 1);  //read character a from parent process to inform if purchase was complete with a Y or N
	        sleep(1); //program waits 1 second
	      }  
	      exit(1); //terminates child process 
	}
	
	
	
		                                      /// 2nd Child Execution ///
	
	if (pid>0){//Only Parant Process goes in
                pid=fork(); // third child's birth
        }else {
              for(k=0; k<10; k++){ // 10 loops for 10 requests
	        close(PC2[1]); //closing write descriptor of PC pipe
	        read(PC2[0], &i, sizeof(int)); //Waits to read an integer from PC pipe so it proceeds
		rand();  //extra rand to force more random numbers 
	        i=0 + rand() % 10 ; //use of rand to decide 1 of 10 products 
		close(CP2[0]); //Closing read descriptor of CP pipe
	        write(CP2[1], &i, sizeof(int)); //writes integer i to CP to send the random product to parent process
	        close(PC2[1]); //close write descriptor of PC pipe
	        read(PC2[0], &a, 1);  //read character a from parent process to inform if purchase was complete with a Y or N
	        sleep(1); //program waits 1 second
	      }  
	      exit(1);  //terminates child process 
	}



	                                      /// 3rd Child Execution ///
	
	if (pid>0){//Only Parant Process goes in
                pid=fork(); // fourth child's birth
        }else {
              for(k=0; k<10; k++){ // 10 loops for 10 requests
	        close(PC3[1]); //closing write descriptor of PC pipe
	        read(PC3[0], &i, sizeof(int)); //Waits to read an integer from PC pipe so it proceeds
		rand();  //extra rand to force more random numbers 
		rand();
	        i=0 + rand() % 10 ; //use of rand to decide 1 of 10 products 
		close(CP3[0]); //Closing read descriptor of CP pipe
	        write(CP3[1], &i, sizeof(int)); //writes integer i to CP to send the random product to parent process
	        close(PC3[1]); //close write descriptor of PC pipe
	        read(PC3[0], &a, 1);  //read character a from parent process to inform if purchase was complete with a Y or N
	        sleep(1); //program waits 1 second
	      }  
	      exit(1);  //terminates child process 
	}



	                                      /// 4th Child Execution ///
	
	if (pid>0){//Only Parant Process goes in
                pid=fork(); // fifth child's birth
        }else {
              for(k=0; k<10; k++){ // 10 loops for 10 requests
	        close(PC4[1]); //closing write descriptor of PC pipe
	        read(PC4[0], &i, sizeof(int)); //Waits to read an integer from PC pipe so it proceeds
		rand();  //extra rand to force more random numbers 
		rand();
		rand();
	        i=0 + rand() % 10 ; //use of rand to decide 1 of 10 products 
		close(CP4[0]); //Closing read descriptor of CP pipe
	        write(CP4[1], &i, sizeof(int)); //writes integer i to CP to send the random product to parent process
	        close(PC4[1]); //close write descriptor of PC pipe
	        read(PC4[0], &a, 1);  //read character a from parent process to inform if purchase was complete with a Y or N
	        sleep(1); //program waits 1 second
	      }  
	      exit(1);  //terminates child process 
	}



	                                      /// 5th Child Execution ///
	
	 if (pid>0){//Only Parant Process goes in
		//no more forks required 5 child processes where created
        }else {          
              for(k=0; k<10; k++){ // 10 loops for 10 requests
	        close(PC5[1]); //closing write descriptor of PC pipe
	        read(PC5[0], &i, sizeof(int)); //Waits to read an integer from PC pipe so it proceeds
		rand();  //extra rand to force more random numbers 
		rand();
		rand();
		rand();
	        i=0 + rand() % 10 ; //use of rand to decide 1 of 10 products 
		close(CP5[0]); //Closing read descriptor of CP pipe
	        write(CP5[1], &i, sizeof(int)); //writes integer i to CP to send the random product to parent process
	        close(PC5[1]); //close write descriptor of PC pipe
	        read(PC5[0], &a, 1);  //read character a from parent process to inform if purchase was complete with a Y or N
	        sleep(1); //program waits 1 second
	      }  
	      exit(1);  //terminates child process 
	}
	 
	 

	
        /// parent process ///
	 if (pid>0){ //only parent goes in
	    int x=0, j; //general use counters 
	    i=0; // used to send an integer to child processes so they proceed
	    
	    
	    
	    
	                                            /// FOR CHILD 1 ///
	    int t; //t will contain the random product. It will be read from CP
	    for(x=0;x<10; x++){ //10 loops for 10 requests
	      close(PC1[0]); //close read descriptor of PC pipe
	      write(PC1[1], &i, sizeof(int)); //writes an integer to the PC pipe so the child process proceeds
	      close(CP1[1]); //close write descriptor of CP pipe
	      read(CP1[0], &t, sizeof(j)); //reads t (random product) from the CP pipe 
	      orders+=1; //Adds 1 to orders counter for total orders
	      j= funky(array1, array2, t); //calls function funky gives us parameters the two arrays of structs and t (the random product)
	      if(j==0){ //Checks if the purchase was completed
	          close(PC1[0]); //Closes read descriptor of PC pipe 
	          j= array1[t].price; //assigns the price of the product to j
	          income+=j; //adds j to total income
	          char ch = 'Y'; //with this variable Parent will inform child if order can be done with a Y
	          write(PC1[1], &ch, 1); //Writes character Y to PC pipe
	          completed+=1; //adds 1 to total completed orders 
	          printf("Client 1: Purchase complete! Your total is: %d €\n", j); 
	        }
	        else{ //Purchase Denied
	          char ch='N'; //with this variable Parent will inform child if order coundnt be done with a N
	          close(PC1[0]); //close read descriptor of PC pipe
	          j=0; 
	          array2[t].canceled[0]=1; /*accesses canceled array (list of unserved customers )in array2(stuct order) and assigns 
					   1 to the respective spot in the array for the customer that wasnt served*/
			
	          write(PC1[1], &ch, sizeof(char)); //writes character N to PC pipe
	          canceled+=1;  //adds one to total canceled orders
	          printf("Client 1: Products unavailable sorry have a nice day. Request Denied!!!!\n" );
	        }
	        sleep(1);
	    }
	    
	    
	    
	    
	                                      /// FOR CHILD 2 ///	
		 
	    for(x=0;x<10; x++){ //10 loops for 10 requests								
	      close(PC2[0]); //close read descriptor of PC pipe
	      write(PC2[1], &i, sizeof(int)); //writes an integer to the PC pipe so the child process proceeds
              close(CP2[1]); //close write descriptor of CP pipe
	      read(CP2[0], &t, sizeof(t)); //reads t (random product) from the CP pipe 
	      orders+=1; //Adds 1 to orders counter for total orders
	      j= funky(array1, array2, t); //calls function funky gives us parameters the two arrays of structs and t (the random product)
	      if(j==0){   //Checks if the purchase was completed
	          close(PC2[0]); //close read descriptor of PC pipe
	          j= array1[t].price;  //assigns the price of the product to j
	          income+=j; //adds j to total income
	          char ch = 'Y'; //Parent informs child if order can be done with a Y
	          write(PC2[1], &ch, 1);  //Writes character Y to PC pipe
	          completed+=1; //adds 1 to total completed orders 
	          printf("Client 2: Purchase complete! Your total is: %d €\n", j);
	        }
	        else{ //Purchase Denied
	          char ch='N'; //with this variable Parent will inform child if order coundnt be done with a N
	          close(PC2[0]); //close read descriptor of PC pipe
	          j=0;
	          array2[t].canceled[1]=1;  /*accesses canceled array (list of unserved customers )in array2(stuct order) and assigns 
					    1 to the respective spot in the array for the customer that wasnt served*/
			
	          write(PC2[1], &ch, sizeof(char));  //Writes character N to PC pipe
	          canceled+=1;   //adds one to total canceled orders
	          printf("Client 2: Products unavailable sorry have a nice day. Request Denied!!!!\n" );
	        }
	        sleep(1);
	    }
	    
	    
	    
	    
	                                      /// FOR CHILD 3 ///
		 
	    for(x=0;x<10; x++){ //10 loops for 10 requests
	      close(PC3[0]); //close read descriptor of PC pipe
	      write(PC3[1], &i, sizeof(int)); //writes an integer to the PC pipe so the child process proceeds
	      close(CP3[1]); //close write descriptor of CP pipe
	      read(CP3[0], &t, sizeof(t)); //reads t (random product) from the CP pipe 
	      orders+=1; //Adds 1 to orders counter for total orders
	      j= funky(array1, array2, t); //calls function funky gives us parameters the two arrays of structs and t (the random product)
	      if(j==0){    //Checks if the purchase was completed
	          close(PC3[0]); //close read descriptor of PC pipe
	          j= array1[t].price;  //assigns the price of the product to j
	          income+=j; //adds j to total income
	          char ch = 'Y'; //Parent informs child if order can be done with a Y
	          write(PC3[1], &ch, 1);  //Writes character Y to PC pipe
	          completed+=1; //adds 1 to total completed orders 
	          printf("Client 3: Purchase complete! Your total is: %d €\n", j);
	        }
	        else{ //Purchase Denied
	          char ch='N'; //with this variable Parent will inform child if order coundnt be done with a N
	          close(PC3[0]); //close read descriptor of PC pipe
	          j=0;
	          array2[t].canceled[2]=1;  /*accesses canceled array (list of unserved customers )in array2(stuct order) and assigns 
					   1 to the respective spot in the array for the customer that wasnt served*/
			
	          write(PC3[1], &ch, sizeof(char)); //Writes character N to PC pipe
	          canceled+=1;   //adds one to total canceled orders
	          printf("Client 3: Products unavailable sorry have a nice day. Request Denied!!!!\n" );
	        }
	        sleep(1);
	    }
	    
	    
	    
	    
	                                      /// FOR CHILD 4 ///	
		 
	    for(x=0;x<10; x++){ //10 loops for 10 requests   
	      close(PC4[0]); //close read descriptor of PC pipe
	      write(PC4[1], &i, sizeof(int)); //writes an integer to the PC pipe so the child process proceeds
	      close(CP4[1]); //close write descriptor of CP pipe
	      read(CP4[0], &t, sizeof(j)); //reads t (random product) from the CP pipe 
	      orders+=1; //Adds 1 to orders counter for total orders
	      j= funky(array1, array2, t); //calls function funky gives us parameters the two arrays of structs and t (the random product)
	      if(j==0){ //Checks if the purchase was completed
	          close(PC4[0]); //close read descriptor of PC pipe
	          j= array1[t].price;  //assigns the price of the product to j
	          income+=j; //adds j to total income
	          char ch = 'Y'; //Parent informs child if order can be done with a Y
	          write(PC4[1], &ch, 1);  //Writes character Y to PC pipe
	          completed+=1; //adds 1 to total completed orders 
	          printf("Client 4: Purchase complete! Your total is: %d €\n", t);
	        }
	        else{ //Purchase Denied
	          char ch='N'; //with this variable Parent will inform child if order coundnt be done with a N
	          close(PC4[0]); //close read descriptor of PC pipe
	          j=0;
	          array2[t].canceled[3]=1;  /*accesses canceled array (list of unserved customers )in array2(stuct order) and assigns 
					   1 to the respective spot in the array for the customer that wasnt served*/
			
	          write(PC4[1], &ch, sizeof(char)); //Writes character N to PC pipe
	          canceled+=1;    //adds one to total canceled orders
	          printf("Client 4: Products unavailable sorry have a nice day. Request Denied!!!!\n" );
	        }
	        sleep(1);
	    }
	    
	    
	    
	    
	                                      /// FOR CHILD 5 ///
		 
	    for(x=0;x<10;x++){ //10 loops for 10 requests
	      close(PC5[0]); //close read descriptor of PC pipe
	      write(PC5[1], &i, sizeof(int)); //writes an integer to the PC pipe so the child process proceeds
	      close(CP5[1]); //close write descriptor of CP pipe
	      read(CP5[0], &t, sizeof(t)); //reads t (random product) from the CP pipe 
	      orders+=1; //Adds 1 to orders counter for total orders
	      j= funky(array1, array2, t);
	      if(j==0){  //Checks if the purchase was completed
	          close(PC5[0]); //close read descriptor of PC pipe
	          j= array1[t].price;
	          income+=j;
	          char ch = 'Y'; //Parent informs child if order can be done with a Y
	          write(PC5[1], &ch, 1);  //Writes character Y to PC pipe
	          completed+=1; //adds 1 to total completed orders 
	          printf("Client 5: Purchase complete! Your total is: %d €\n", j);
	        }
	        else{ //Purchase Denied
	          char ch='N'; //with this variable Parent will inform child if order coundnt be done with a N
	          close(PC5[0]); //close read descriptor of PC pipe
	          j=0;
	          array2[t].canceled[4]=1;  /*accesses canceled array (list of unserved customers )in array2(stuct order) and assigns 
					   1 to the respective spot in the array for the customer that wasnt served*/
			
	          write(PC5[1], &ch, sizeof(char)); //Writes character N to PC pipe
	          canceled+=1;    //adds one to total canceled orders
	          printf("Client 5: Products unavailable sorry have a nice day. Request Denied!!!!\n" );
	        }  
	        sleep(1);
	    }
	    
	    
	    
	    
	                                      /// PRODUCT REPORT ///
	    waitpid(-1, NULL, 0); //ennforces waiting for child processes to finish

	    //for loop for 10 products to output a report for each product	  
	    for(t=0;t<10;t++){ //
	      b=0; 
	      printf("\n\n\n%d.The item with the description %s had:\n",t+1,array1[t].desc); //output description for each product from array1
	      printf("%d requests for purchase \n",array2[t].requests); //outputs number of requests for each product from array2
	      printf("%d sales\n",array2[t].sold); //outputs times item was sold from array2
	     
	      //for loop to print list of unserved clients for each product	    
	      printf("the clients that could not be served are:\n");  //Outputs	      
	      for(k=0;k<5;k++){ //5 loops for the 5 spots in array canceled
	        if(array2[t].canceled[k]==1){//checks if each spot in array canceled is 1 meaning client was denied his request at least once
	          printf(" Client %d\n",k+1); //outputs list of clients
	        }else 
	          b= b+1; //counter to confirm we are in the last loop 
	      }
	      if(b==5){ //For this product the array cancelled was all 0 so no client was denied his request
	        printf("None");
	      }
	    }



	                                      /// FINAL REPORT ///
		 
	    printf("\n\n\nTotal Orders were: %d\n", orders); //outputs number of total requests made 
	    printf("Total Completed Orders were: %d\n", completed); //outputs number of total completed purchases
	    printf("Total Canceled Orders were: %d\n", canceled); //outputs number of total canceled purchases 
	    printf("Total Income is: %d\n", income); //outputs total income 
	    
	 }

}
