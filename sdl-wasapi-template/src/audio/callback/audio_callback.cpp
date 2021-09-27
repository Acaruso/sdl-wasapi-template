#include "audio_callback.hpp"

#include "../audio_util.hpp"

#include <cmath>
#include <iostream>
#include <limits>
#include <stdlib.h>

double getRand()
{
    return rand() / (RAND_MAX + 1.);
}

double Env::get(bool trig, double holdTime, double t)
{
    double out = 0.0;
    unsigned holdTimeSamps = mstosamps(holdTime);

    if (trig) {
        on = true;
        timer = 0;
    }

    if (timer < holdTimeSamps) {
        out = 1.0;
    }

    timer += 1;

    return out;
}

double AHREnv::get(bool trig, double a, double h, double r, double t)
{
    unsigned attackSamps = mstosamps(a);
    unsigned holdSamps = mstosamps(h);
    unsigned releaseSamps = mstosamps(r);

    double attackDelta = 1.0 / (double)attackSamps;
    double releaseDelta = 1.0 / (double)releaseSamps;

    if (trig) {
        sig = 0.0;
        timer = 0;
    }

    if (timer < attackSamps) {
        sig += attackDelta;
    } else if (timer < attackSamps + holdSamps) {
        sig = 1.0;
    } else if(timer < attackSamps + holdSamps + releaseSamps) {
        sig -= releaseDelta;
    } else {
        sig = 0.0;
    }

    timer += 1;

    return sig;
}

Env env;

AHREnv ahrEnv;

AHREnv modEnv;

double freq = 120;

double r = 0.0;

bool trig = false;

// callback gets called per-sample
double audioCallback(PlaybackSystemContext& context)
{
    trig = context.trig;

    double t = context.getTime();
    double period = 500.0;
    // trig = context.sampleCounter % mstosamps(period) == 0;

    if (trig) {
        r = getRand();
    }

    double w = twoPi * freq;

    double theta = sin(w * t * 0.5) * modEnv.get(trig, 1, 50, 200, t) * 8 * r;

    double sinSig = sin((w * t) + theta);

    double envSig = ahrEnv.get(trig, 1, 200, 500, t);

    double sig = sinSig * envSig * 0.5;

    return sig;
}
