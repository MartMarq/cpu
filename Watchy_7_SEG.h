#ifndef WATCHY_7_SEG_H
#define WATCHY_7_SEG_H

#ifdef WATCHY_SIM
    #include "..\..\Watchy.h"
#else // WATCHY_SIM
    #include <Watchy.h>
#endif // WATCHY_SIM


#include "icons.h"
#include "cpu16pt7b.h"
#include "cpu10pt7b.h"

class Watchy7SEG : public Watchy{
    using Watchy::Watchy;
    public:
        void drawWatchFace();
        void drawTime();
        };

#endif