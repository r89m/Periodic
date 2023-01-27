#ifndef PERIODIC_LIB_BACKOFF_H
#define PERIODIC_LIB_BACKOFF_H

class BackoffStrategy {
   protected:
    unsigned long _minDelay;
    unsigned long _jitterMinMax;

    BackoffStrategy(unsigned long minDelay, unsigned long jitterMinMax = 0)
        : _minDelay(minDelay), _jitterMinMax(jitterMinMax) {}

    long getJitter() const { return (_jitterMinMax > 0) ? random(-_jitterMinMax, _jitterMinMax) : 0; }

    virtual unsigned long getPlainWaitDuration(unsigned long attempt) const = 0;

   public:
    unsigned long getWaitDuration(unsigned long attempt) const {
        unsigned long plain = getPlainWaitDuration(attempt);
        long jitter = getJitter();
        // Check for instances where the negative jitter is greater than the plain wait duration
        // cppcheck-suppress oppositeExpression
        if (jitter < 0 && abs(jitter) > plain) {
            return 0;
        }
        return plain + jitter;
    };
};

class NoBackoff : public BackoffStrategy {
   public:
    explicit NoBackoff(unsigned long minDelay, unsigned long jitterMinMax = 0) : BackoffStrategy(minDelay, jitterMinMax) {}
    unsigned long getPlainWaitDuration(unsigned long attempt) const override {
        return _minDelay;
    };
};

class IncreasingDelayBackoff : public BackoffStrategy {
   protected:
    unsigned long _maxDelay;

    IncreasingDelayBackoff(unsigned long minDelay, unsigned long maxDelay, unsigned long jitterMinMax = 0)
        : BackoffStrategy(minDelay, jitterMinMax), _maxDelay(maxDelay) {}

    virtual unsigned long getUnclampedWaitDuration(unsigned long attempt) const = 0;

    unsigned long getPlainWaitDuration(unsigned long attempt) const override {
        return std::min(_maxDelay, getUnclampedWaitDuration(attempt));
    }
};

class LinearBackoff : public IncreasingDelayBackoff {
   protected:
    unsigned long getUnclampedWaitDuration(unsigned long attempt) const override { return (_minDelay * (attempt + 1)); }

   public:
    LinearBackoff(unsigned long minDelay, unsigned long maxDelay, unsigned long jitterMinMax = 0)
        : IncreasingDelayBackoff(minDelay, maxDelay, jitterMinMax) {}
};

class ExponentialBackoff : public IncreasingDelayBackoff {
   protected:
    unsigned long getUnclampedWaitDuration(unsigned long attempt) const override {
        double exponentialComponent = pow(2, attempt);
        if (exponentialComponent == INFINITY) {
            // Exponential component is huge, just return the max delay
            return _maxDelay;
        }
        return _minDelay * (unsigned long)exponentialComponent;
    }

   public:
    ExponentialBackoff(unsigned long minDelay, unsigned long maxDelay, unsigned long jitterMinMax = 0)
        : IncreasingDelayBackoff(minDelay, maxDelay, jitterMinMax) {}
};

#endif // PERIODIC_LIB_BACKOFF_H