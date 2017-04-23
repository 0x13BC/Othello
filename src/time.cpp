#include "../lib/time.hpp"

/*------------CONSTRUCTORS-&-DESTRUCTORS------------*/
time::time()
    :m_pause(false)
{
    //ctor
}

time::~time()
{
    //dtor
}

time::time(const time& other)
{
    //copy ctor
}
/*-------------------------------------------------*/

/*----------------------METHODS--------------------*/
void time::start()
/**Demarre le timer **/
{
    //cout<<"Start timer."<<endl;
    m_inittime=clock();
}
void time::stop()
/** Arrete le timer **/
{
    //cout<<"End timer."<<endl;
    m_endtime=clock()-m_inittime; // DT= Temps actuel - Temps initial (AB= B-A)
    m_sec=(float)m_endtime/CLOCKS_PER_SEC;// Cast en float et divise par la fréquence
}
float time::GetSec()
/**Donne le timer en secondes**/
{
    cout<<"Secondes: "<<m_sec<<endl;
    return m_sec;
}
void time::pause()
/** Met le timer en pause **/
{
    if(!m_pause)
    {
        cout<<"Pause timer on"<<endl;
        m_pause=true;
        m_pstime=clock();
        cout<<"timer at: "<<(float)(clock()-m_inittime)/CLOCKS_PER_SEC<<" secondes."<<endl;
    }
    else
    {
        m_pause=false;

        m_inittime=clock()-m_pstime;// Temps initial= Temps Actuel-Duree de la pause
        cout<<"Pause timer for: "<<(float)(clock()-m_pstime)/CLOCKS_PER_SEC<<" secondes."<<endl;
    }
}
/*-------------------------------------------------*/
