// alarm.h
//	Data structures for a software alarm clock.
//
//	We make use of a hardware timer device, that generates
//	an interrupt every X time ticks (on real systems, X is
//	usually between 0.25 - 10 milliseconds).
//
//	From this, we provide the ability for a thread to be
//	woken up after a delay; we also provide time-slicing.
//
//	NOTE: this abstraction is not completely implemented.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef ALARM_H
#define ALARM_H

#include "copyright.h"
#include "utility.h"
#include "callback.h"
#include "timer.h"
#include "thread.h"
#include <list>

class ThreadQueue
{
public:
    ThreadQueue() : _current_interrupt(0){};
    void push(Thread*, int);
    bool ready();
    bool isEmpty();

private:
    struct ThreadWrapper
    {
        ThreadWrapper(Thread* thread, int n) : sleeper(thread), when(n) { };
        Thread* sleeper;
        int when;
    };
    int _current_interrupt;
    std::list<ThreadWrapper> threadList;
};

// The following class defines a software alarm clock.
class Alarm : public CallBackObj
{
public:
    Alarm(bool doRandomYield);
    ~Alarm() { delete timer; }

    void WaitUntil(int x);

private:
    Timer *timer;
    ThreadQueue slist;
    void CallBack();
};

#endif // ALARM_H
