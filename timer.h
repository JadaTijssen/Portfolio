#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

#define SECONDS      1000000
#define MILLISECONDS    1000

class Timer
{
 private:
   struct timeval start;
   struct timeval stop;
   bool running;
 public:
   // Constructor
   Timer() {
     running = false;
   }
   
   // user functions
   void startTimer() {
     running = true;
     gettimeofday(&start, NULL);
   }
   
   void stopTimer() {
     running = false;
     gettimeofday(&stop, NULL);
   }
   
   double seconds() {
     if (running) {
       std::cerr << "Abort on error: timer is still runing. You need to stop the timer first\n";
       exit(-1);
     }
     double tm = stop.tv_sec*SECONDS + stop.tv_usec
       - (start.tv_sec*SECONDS + start.tv_usec);
     return tm/SECONDS;
   }
   
   int milliseconds() {
     return (int)(seconds()*1000);
   }
};

#endif
