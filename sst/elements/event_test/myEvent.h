
#ifndef _MYEVENT_H
#define _MYEVENT_H

#include <sst/core/compEvent.h>


class MyEvent : public SST::CompEvent {
    public:
    MyEvent() : SST::CompEvent() { }

        int count;
}; 

    
#endif
