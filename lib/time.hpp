/**
 *@file time.h
 *@brief Classe Time Permet d'utiliser un chronomètre.
 *-Marche du Chrono.
 *-Pause du Chrono.
 *-Arret du Chrono.
*/

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
        void start();///Marche du Chrono.
        void stop();/// Arret du Chrono.
        float GetSec();/// Obtenir le temps en seconde.
        void pause();/// Pause le Chronometre.


};

#endif // TIME_HPP
