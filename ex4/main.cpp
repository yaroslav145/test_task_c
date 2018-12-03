#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    ifstream file;

    file.open("input.txt");

    if(!file.is_open())
    {
        cout << "Can't open file" << endl;
        return 0;
    }

    string str;
    size_t pos;

    while(!file.eof())
    {
        str.clear();

        getline(file, str);

        pos = str.find(':');

        if(pos == string::npos)
        {
            cout << "Invalid string" << endl;
            continue;
        }

        str.replace(pos, 1, " Value: ");
        cout << "Key: " + str << endl;
    }

    file.close();

    return 0;
}
