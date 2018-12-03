#include <iostream>
#include <string>
#include <vector>


using namespace std;


char getDelimiter()
{
    string s;

    cout << "Enter delimiter" << endl;
    while(1)
    {
        getline(cin, s);

        if(s.length() == 1)
            return s.at(0);

        cout << "Not valid delimiter. Try again." << endl;
    }
}


void getSubstrings(string& str, char delimiter, vector<string>& substrVector)
{
    size_t pos = 0, prevPos = 0, len;

    while(pos != std::string::npos)
    {
        pos = str.find(delimiter, prevPos);

        len = pos - prevPos;

        if(pos == std::string::npos)
        {
            len = str.length() - prevPos;

            if(prevPos == 0)
                break;
        }

        if(len != 0)
            substrVector.push_back(str.substr(prevPos, len));

        prevPos = pos + 1;
    }
}


void printSubstrings(vector<string>& substrVector)
{
    for(vector<string>::iterator it = substrVector.begin(); it != substrVector.end(); it++)
    {
        cout << *it << endl;
    }
}


int main()
{
    string str;
    vector<string> substrings;
    char delimiter;

    cout << "Enter string" << endl;
    while(1)
    {
        getline(cin, str);

        if(str.length() != 0)
            break;

        cout << "Not valid string. Try again." << endl;
    }

    delimiter = getDelimiter();

    getSubstrings(str, delimiter, substrings);

    printSubstrings(substrings);

    return 0;
}
