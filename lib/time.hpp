#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <ctime>

using namespace std;

class Time
{
    private:
        //ATTRIBUTS
        time_t m_initTime,m_endTime,m_psTime;
        float m_sec;
        bool m_pause;

    public:

        //CONSTRUCTOR & DESTRUCTOR
        Time();
        ~Time();
        Time(const Time& other);

        //METHODS
        void start();
        void stop();
        float GetSec();
        void pause();


};

#endif // TIME_HPP
