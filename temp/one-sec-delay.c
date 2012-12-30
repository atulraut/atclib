#include <stdio.h>
#include <time.h>
#include <math.h>
int main() {
/*        int p = system("date +%S");
        clock_t start_time = clock();
        printf("systime=%ld, star_time: %ld\n", p,  start_time);
        clock_t end_time = 1* 1000 + start_time;
        while(clock() != end_time) {
          printf("systime=%d, end_time : %d\n", system("date +%S"),  end_time);
        }
*/	
    int p = system("date +%S");
    clock_t start_time = clock();
    printf("Start Time In Second =%ld, star_time: %ld\n", p,  start_time); 
    time_t seconds = 60;   	
    delay (seconds);
    p = system("date +%S");
    clock_t end_time = clock();
    printf("End Time In Second =%ld, star_time: %ld\n", p,  end_time);

    return 0;
}
 
void delay(time_t seconds)
{
    time_t start=time(NULL);
    time_t end=0;
    seconds++;  /* account for partial second  */
    for(;;)
    {
      end=time(NULL);
      if(seconds + end >= start) break;       
    }
}
