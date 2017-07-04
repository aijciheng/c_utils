#include "system.h"

#include <stdio.h>  
#include <time.h>
#include <sys/time.h>

long get_current_time() {   
   struct timeval tv;  
   gettimeofday(&tv,NULL);  
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;  
}
