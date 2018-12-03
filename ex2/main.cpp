#include <iostream>
#include <ctime>

using namespace std;


int randAnyInt(int seed)
{
    return (int)((unsigned int)seed * 1746973713 + 7676697);
}

const int N = 100;

int main()
{
    int arr[N];

    int seed = time(NULL);

    for(int i = 0; i < N; ++i)
    {
        seed = randAnyInt(seed);
        arr[i] = seed;
    }


    int maxElement = arr[0];
    int minElement = arr[0];
    double mid = 0;
    int buf;


    for(int i = 0; i < N; ++i)
    {
        buf = arr[i];

        if(buf > maxElement)
            maxElement = buf;

        if(buf < minElement)
            minElement = buf;

        mid += buf;
    }

    mid /= N;

    cout << "Max: " << maxElement << endl;
    cout << "Min: " << minElement << endl;
    cout.setf(ios::fixed);
    cout.precision(4);
    cout << "Mid: " << mid << endl;


    return 0;
}
