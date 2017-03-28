#ifndef MYLOCK_H
#define MYLOCK_H

//#include <wiringPi.h>
int openLock(void);
void init();
void setPowerPin23();
int closeLock(void);
#endif // MYLOCK_H
