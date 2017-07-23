#include "time.h"



using namespace kalsengi;
using namespace std;

chrono::time_point<chrono::system_clock> Time::currentTime = chrono::system_clock::now ();
chrono::time_point<chrono::system_clock> Time::previousTime = chrono::system_clock::now ();
chrono::time_point<chrono::system_clock> Time::startTime = chrono::system_clock::now ();

float Time::getAbsTime ()
{
    chrono::duration<float> elapsedTime = currentTime - startTime;
    return elapsedTime.count();
}

float Time::getDeltaTime ()
{
    chrono::duration<float> elapsedTime = currentTime - previousTime;
    return elapsedTime.count();
}

void Time::update ()
{
    previousTime = currentTime;
    currentTime = chrono::system_clock::now ();
}
