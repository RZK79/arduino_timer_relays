#ifndef _TIMER_H_
#define _TIMER_H_

class Timer{
  unsigned long timeout;
  unsigned long startMillis;

  void (*callback)(Timer* timer);

  bool paused;
public:
  Timer();
  virtual ~Timer();

  void update();

  void start(unsigned long t, void (*callback)(Timer* timer));
  void stop();
  void pause();
  void resume();
  void reset();
  bool isPaused();
};

#endif