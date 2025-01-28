#pragma once

#include "hk/Types.h"
#include "hk/debug/Log.h"
#include "nn/svc/svc_Api.h"
#include "sead/time/seadTickSpan.h"

namespace hk::util {

inline void formatTickSpan(char* out, sead::TickSpan span)
{
    float secs = span.toSeconds<float>();
    float ms = span.toMilliSeconds<float>();
    float us = span.toMicroSeconds<float>();
    float ns = span.toNanoSeconds();

    if (secs >= 1)
        sprintf(out, "%2.2fs", secs);
    else if (ms >= 1)
        sprintf(out, "%2.2fms", ms);
    else if (us >= 1)
        sprintf(out, "%2.2fus", us);
    else if (ns >= 1)
        sprintf(out, "%2.2fns", ns);
}

template <TemplateString Name = "Clock">
class Clock {
    sead::TickSpan mTick = 0;

public:
    void start() { mTick = nn::svc::GetSystemTick(); }

    sead::TickSpan count() const { return sead::TickSpan(nn::svc::GetSystemTick()) - mTick; }

    void print() const
    {
        sead::TickSpan diff = count();

        char formatted[16];
        formatTickSpan(formatted, diff);

        hk::dbg::Log("Clock(%s): %s", Name.value, formatted);
    }
};

template <TemplateString Name = "Clock">
class ScopedClock : public Clock<Name> {
public:
    ScopedClock()
    {
        Clock<Name>::start();
    }

    ~ScopedClock()
    {
        Clock<Name>::print();
    }
};

} // namespace hk::util
