#pragma once

#include "../playback_system/playback_system_context.hpp"

const double twoPi = 3.14159265359 * 2;

struct Env
{
    unsigned timer = 0;
    bool on = false;

    double get(bool trig, double holdTime, double t);
};

struct AHREnv
{
    unsigned timer = 0;
    bool on = false;
    double sig;

    double get(bool trig, double a, double h, double r, double t);
};


double audioCallback(PlaybackSystemContext& context);
