// alarm.cc
//	Routines to use a hardware timer device to provide a
//	software alarm clock.  For now, we just provide time-slicing.
//
//	Not completely implemented.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "alarm.h"
#include "main.h"
#include <list>
//----------------------------------------------------------------------
// Alarm::Alarm
//      Initialize a software alarm clock.  Start up a timer device
//
//      "doRandom" -- if true, arrange for the hardware interrupts to
//		occur at random, instead of fixed, intervals.
//----------------------------------------------------------------------

Alarm::Alarm(bool doRandom)
{
    timer = new Timer(doRandom, this);
}

void Alarm::CallBack()
{
    Interrupt *interrupt = kernel->interrupt;
    MachineStatus status = interrupt->getStatus();

    bool woke = this->slist.ready();
    bool isEmptyTash = !woke && this->slist.isEmpty();
    if (status == IdleMode && isEmptyTash)
    { // is it time to quit?
        if (!interrupt->AnyFutureInterrupts())
        {
            timer->Disable(); // turn off the timer
        }
    }
    else
    { // there's someone to preempt
        interrupt->YieldOnReturn();
    }
}

int i = 1;
void Alarm::WaitUntil(int x)
{
    IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff);
    Thread *thread = kernel->currentThread;
    cout << "Alarm::WaitUntil, time:" << i << endl;
    ++i;
    this->slist.push(thread, x);
    kernel->interrupt->SetLevel(oldLevel);
}

bool ThreadQueue::isEmpty()
{
    return this->threadList.empty();
}

void ThreadQueue::push(Thread *thread, int n)
{
    ASSERT(kernel->interrupt->getLevel() == IntOff);
    this->threadList.push_back(ThreadWrapper(thread, _current_interrupt + n));
    thread->Sleep(false);
}

bool ThreadQueue::ready()
{
    bool woken = false;
    ++this->_current_interrupt;
    std::list<ThreadWrapper>::iterator it = threadList.begin();
    for (; it != threadList.end();)
    {
        if (this->_current_interrupt >= it->when) {
            woken = true;
            kernel->scheduler->ReadyToRun(it->sleeper);
            it = this->threadList.erase(it);
        } else {
            ++it;
        }
    }
    return woken;
}
