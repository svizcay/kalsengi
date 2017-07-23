#ifndef TIME_H
#define TIME_H 

#include <chrono>

namespace kalsengi
{
    class Time
    {
        public:
            static float getAbsTime ();
            static float getDeltaTime ();
            static void update ();

        protected:
            Time ();        // do not allow users to construct an instance
            static std::chrono::time_point<std::chrono::system_clock> currentTime;
            static std::chrono::time_point<std::chrono::system_clock> previousTime;
            static std::chrono::time_point<std::chrono::system_clock> startTime;

    };
}
#endif /* TIME_H */
