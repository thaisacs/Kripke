/******************************************************************************
 *
 * Routines for doing timing.
 *
 *****************************************************************************/

#include <Kripke/Timing.h>

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <mpi.h>

void Timing::start(std::string const &name){
  // get or create timer
  Timer &timer = timers[name];

  if(!timer.started){
    timer.started = true;
    timer.start_time = MPI_Wtime();
  }
}

void Timing::stop(std::string const &name){
  // get or create timer
  Timer &timer = timers[name];

  if(timer.started){
    timer.started = false;
    timer.total_time += MPI_Wtime() - timer.start_time;
    timer.count ++;
  }
}

void Timing::stopAll(void){
  for(TimerMap::iterator i = timers.begin();i != timers.end();++ i){
    stop((*i).first);
  }
}

void Timing::clear(void){
  timers.clear();
}

void Timing::print(void) const {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(rank != 0){
    return;
  }

  // build a sorted list of names
  std::vector<std::string> names;
  std::vector<Timer const *> ord_timers;
  for(TimerMap::const_iterator i = timers.begin();i != timers.end();++ i){
    names.push_back((*i).first);
    ord_timers.push_back(&(*i).second);
  }
  std::sort(names.begin(), names.end());

  // Display timers
  printf("\nTimers:\n");
  printf("  %-16s  %-12s  %-12s\n", "Timer", "Count", "Seconds");
  for(int i = 0;i < names.size();++ i){
    printf("  %-16s  %-12d  %12.5lf\n", names[i].c_str(), ord_timers[i]->count, ord_timers[i]->total_time);
  }
}
