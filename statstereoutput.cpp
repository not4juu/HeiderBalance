#include "statstereoutput.h"

StatStereOutput::StatStereOutput()
{
    for(unsigned i=0; i<9; ++i)
    {
        this->fromStere[i]=0;
    }
    this->allPoints = 0;
    this->percentage = 0.;
    this->reachPoints = 0;
}
