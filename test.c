#include "prtfmt.h"

int main(void){
mini_printf ("hello, world\n"); 
mini_printf ("[%99% %T %d]\n", 20);
mini_printf ("[%d %x %X %b]\n", 15, 15, 15, 15); 
mini_printf ("[%+010ld]\n", 999l);  
mini_printf ("[%+010.005ld]\n", -999l); 
mini_printf ("[%10.6b]\n", 16);   

mini_printf ("[%.6s]\n", "hello, world");   
mini_printf ("[%10.6s]\n", "hello, world"); 
mini_printf ("[%4.6s]\n", "hello, world"); 
mini_printf ("[%4.0s]\n", "hello, world");  
mini_printf ("[%9s]\n", "hello, world");  
mini_printf ("[%-20s]\n", "hello, world");    
mini_printf ("[%20s]\n", "hello, world"); 
mini_printf ("[%~s]\n", "hello");     
mini_printf ("[%~20s]\n", "hello"); 
mini_printf ("[%~-20s]\n", "hello"); 
mini_printf ("[%~-20.3s]\n", "hello");  

mini_printf ("[%4.6c]\n", 'A');   
mini_printf ("[%4.0c]\n", 'A');   
mini_printf ("[%-20c]\n", 'A'); 
mini_printf ("[%+10x]\n", -1);       
	return 0;
}
