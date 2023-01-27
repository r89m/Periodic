#ifndef PERIODIC_LIB_H
#define PERIODIC_LIB_H

#include <Arduino.h>

#include "backoff.h"

class IPeriodicCallback {
   public:
    virtual bool periodicCallback(unsigned long attempts) = 0;
};

template <class TCallback, class TBackoff>
class _Periodic {
   private:
    TCallback _callback;
    TBackoff _backoffStrategy;
    unsigned long _lastCallTimestamp = 0;
    unsigned long _attempt = 0;

   protected:
    virtual unsigned long getTimestamp() { return millis(); }

   public:
   // cppcheck-suppress passedByValue - Copying the backoff strategy prevents segfaults in the below Periodic functions
    _Periodic(TCallback callback, TBackoff backoffStrategy)
        : _callback(callback), _backoffStrategy(backoffStrategy) {}

    void loop() {
        unsigned long currentCallTimestamp = getTimestamp();
        if (currentCallTimestamp - _lastCallTimestamp >= _backoffStrategy.getWaitDuration(_attempt)) {
            _lastCallTimestamp = currentCallTimestamp;
            auto callbackSuccess = _callback.periodicCallback(_attempt);
            if (callbackSuccess) {
                _attempt = 0;
            } else {
                _attempt++;
            }
        }
    }
};

template <class TCallback, class TBackoff>
class _PeriodicMicros : _Periodic<TCallback, TBackoff> {
   protected:
    unsigned long getTimestamp() override { return micros(); }

   public:
    using _Periodic<TCallback, TBackoff>::_Periodic;
};

// TOOD: Are these wrapperes needed? Can Backoffs have a Template parameter that indicats the return type? Or wraps the calling of the callback.
using PeriodicCallbackFunction = bool (*)(unsigned long attempt);
class PeriodicCallbackWrapper : public IPeriodicCallback {
   private:
    PeriodicCallbackFunction _callbackFunction;

   public:
    // cppcheck-suppress noExplicitConstructor
    PeriodicCallbackWrapper(PeriodicCallbackFunction callbackFunction) : _callbackFunction(callbackFunction) {}

    bool periodicCallback(unsigned long attempts) override { return _callbackFunction(attempts); }
};

using SimplePeriodicCallback = void (*)();
class SimplePeriodicCallbackWrapper : IPeriodicCallback {
   private:
    SimplePeriodicCallback _callback;

   public:
    // cppcheck-suppress noExplicitConstructor
    SimplePeriodicCallbackWrapper(SimplePeriodicCallback callback) : _callback(callback) {}

    bool periodicCallback(unsigned long attempts) override {
        _callback();
        return true;
    }
};

_Periodic<SimplePeriodicCallbackWrapper, NoBackoff> Periodic(SimplePeriodicCallback callback, unsigned long delay) {
    return _Periodic<SimplePeriodicCallbackWrapper, NoBackoff>(callback, NoBackoff(delay));
}

_Periodic< PeriodicCallbackWrapper, ExponentialBackoff> Periodic(PeriodicCallbackFunction callback, unsigned long minimumDelay, unsigned long maximumDelay) {
    return _Periodic< PeriodicCallbackWrapper, ExponentialBackoff>(callback, ExponentialBackoff(minimumDelay, maximumDelay));
}

_Periodic< PeriodicCallbackWrapper, ExponentialBackoff> Periodic(PeriodicCallbackFunction callback, unsigned long minimumDelay, unsigned long maximumDelay, unsigned long jitter = 0) {
    return _Periodic< PeriodicCallbackWrapper, ExponentialBackoff>(callback, ExponentialBackoff(minimumDelay, maximumDelay, jitter));
}

template <class TBackoff>
_Periodic<PeriodicCallbackWrapper, TBackoff> Periodic(PeriodicCallbackFunction callback, TBackoff backoffStrategy) {
    return _Periodic<PeriodicCallbackWrapper, TBackoff>(callback, backoffStrategy);
}

_PeriodicMicros<SimplePeriodicCallbackWrapper, NoBackoff> PeriodicMicros(SimplePeriodicCallback callback, unsigned long delay) {
    return _PeriodicMicros<SimplePeriodicCallbackWrapper, NoBackoff>(callback, NoBackoff(delay));
}

_PeriodicMicros< PeriodicCallbackWrapper, ExponentialBackoff> PeriodicMicros(PeriodicCallbackFunction callback, unsigned long minimumDelay, unsigned long maximumDelay) {
    return _PeriodicMicros< PeriodicCallbackWrapper, ExponentialBackoff>(callback, ExponentialBackoff(minimumDelay, maximumDelay));
}

_PeriodicMicros< PeriodicCallbackWrapper, ExponentialBackoff> PeriodicMicros(PeriodicCallbackFunction callback, unsigned long minimumDelay, unsigned long maximumDelay, unsigned long jitter = 0) {
    return _PeriodicMicros< PeriodicCallbackWrapper, ExponentialBackoff>(callback, ExponentialBackoff(minimumDelay, maximumDelay, jitter));
}

template <class TBackoff>
_PeriodicMicros<PeriodicCallbackWrapper, TBackoff> PeriodicMicros(PeriodicCallbackFunction callback, TBackoff backoffStrategy) {
    return _PeriodicMicros<PeriodicCallbackWrapper, TBackoff>(callback, backoffStrategy);
}

#endif  // PERIODIC_LIB_H