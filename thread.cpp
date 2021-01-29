#include <iostream>
#include "thread.h"

using namespace std;
template <typename Typ, size_t N>
Thread<Typ, N>::Thread() : elem(N)
{
    cout << "Pracuje konstruktor domyslny dla Thread\n";
}

template <typename Typ, size_t N>
void Thread<Typ, N>::run()
{
    if(running == true)
    {
        cout << "Watek pracuje\n";
        return;
    }
    cout << "Wlanczam watek\n";
    running = true;
    leddy.on();
}

template <typename Typ, size_t N>
void Thread<Typ, N>::stop()
{
    if(running == false)
    {
        return;
    }
    running = false;
    leddy.off();
}

