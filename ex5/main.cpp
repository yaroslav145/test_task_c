#include <iostream>
#include <limits>
#include <cmath>

using namespace std;

class Point
{
    public:
        int x;
        int y;
};


int checkFailAndClear()
{
    int flag = 0;

    flag = cin.fail();

    cin.clear();
    while(cin.get() != '\n')
    {}

    return flag;
}


const int pointCount = 3;


int main()
{
    Point point[pointCount];
    double k[2];

    for(int i = 0; i < pointCount; ++i)
    {
        while(1)
        {
            cout << "Enter the coordinates of the " << i + 1 << " point (x y)" << endl;

            cin >> point[i].x >> point[i].y;

            if(!checkFailAndClear())
                break;

            cout << "Incorrect value, try again" << endl;
        }
    }

    std::cout.setf(std::ios::fixed);
    std::cout.precision(4);

    int minX = point[0].x;
    int maxX = point[0].x;

    for(int i = 0; i < pointCount; ++i)
    {
        if(minX > point[i].x)
            minX = point[i].x;

        if(maxX < point[i].x)
            maxX = point[i].x;
    }

    double b = (point[1].x - point[0].x) * 2;
    double a = point[2].x - 2*point[1].x + point[0].x;
    double a2 = a*2;

    for(; minX <= maxX; minX++)
    {
        double c = point[0].x - minX;

        double d = b*b - 4*a*c;
        d = sqrt(d);
        k[0] = (-b + d)/(a2);
        k[1] = (-b - d)/(a2);


        for(int i = 0; i < 2; ++i)
        {
            double t = k[i];

            if((t >= 0) && (t <= 1))
            {
                double y = t*t*(point[0].y - 2*point[1].y + point[2].y) + t*2*(point[1].y - point[0].y) + point[0].y;

                cout << "X: " << minX << "   Y: " << y << endl;
            }
        }
    }

    return 0;
}
