#include "audio_util.hpp"


unsigned scaleSignal(double sig)
{
    double f = ((sig * 0.5) + 0.5) * scale;
    unsigned u = (unsigned)f << 8;
    return u;
}

unsigned mstosamps(double ms)
{
    return (unsigned)(ms * 44.1);
}
