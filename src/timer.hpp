

#ifndef TIMER_HPP
#define TIMER_HPP

class Timer
{
    public:
        Timer();
        void start();
        void stop();
        void togglePause();
        int getTicks();
        bool isStarted();
        bool isPaused();
        virtual ~Timer();
    private:
        int startTicks;
        int pausedTicks;
        bool started;
        bool paused;
};

#endif
