#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <ctime>

using namespace std;

class time
{
    private:
        //ATTRIBUTS
        time_t m_inittime,m_endtime,m_pstime;
        float m_sec;
        bool m_pause;

    public:

        //CONSTRUCTOR & DESTRUCTOR
        time();
        ~time();
        time(const time& other);

        //METHODS
        void start();
        void stop();
        float GetSec();
        void pause();


};

#endif // TIME_HPP
