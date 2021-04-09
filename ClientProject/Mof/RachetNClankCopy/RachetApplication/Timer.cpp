#include "Timer.h"

my::Timer::Timer() :
    _time(0.0f),
    _time_max(0.0f),
    _loop(true) {
}

my::Timer::~Timer() {
}

void my::Timer::Initialize(float max, bool loop) {
    _time = 0.0f;
    _time_max = max;
    _loop = loop;
}

#include <iostream>
bool my::Timer::Tick(float delta_time) {
    _time += delta_time;

    if (_loop && _time_max <= _time) {
        _time = 0.0f;
        return true;
    } // if
    return false;
}