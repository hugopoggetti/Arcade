#pragma once

#include <chrono>

class CountdownTimer {
public:
    CountdownTimer() {}

    void start() {
        _startTime = std::chrono::steady_clock::now();
        _running = true;
    }

    void reset(int seconds) {
        _duration = seconds;
        start();
    }

    int remainingSeconds() const {
        if (!_running) return _duration;

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - _startTime).count();
        int remaining = _duration - (int)elapsed;
        return (remaining > 0) ? remaining : 0;
    }

    bool isFinished() const {
        return remainingSeconds() <= 0;
    }

private:
    int _duration;
    bool _running = false;
    std::chrono::steady_clock::time_point _startTime;
};
