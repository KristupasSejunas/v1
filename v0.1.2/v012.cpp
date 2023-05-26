// v012.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::string;
using std::vector;

struct data
{

    string name;
    string surname;
    int egz;
    vector<int> mark;
    double result = 0;

};

void input(data& temp);
void output(data& temp);
void headerAverage();
void headerMedian();
double average(vector<int> mark);
double median(vector<int> mark);

//validation
bool decimal(int n);
int type();
bool YN();

//random
int number();
void randomMark(int k, data& temp);

int main()
{

    srand(time(NULL));

    vector<data> list;
    bool yn;

    while (true)
    {

        cout << "jei norite ivesti studento duomenis spauskite 1, jei baigete ivesti duomenis, spauskite 0" << std::endl;
        yn = YN();

        if (!yn)
        {

            break;

        }

        else
        {

            data T;
            input(T);
            list.push_back(T);

        }

    }

    cout << "jei norite galutini reezulta skaiciuoti vidurkiu spauskite 1, jei mediana 0" << std::endl;
    yn = YN();

    for (auto& el : list)
    {

        if (yn)
        {

            el.result = average(el.mark);

        }

        else
        {

            el.result = median(el.mark);

        }

    }

    if (yn)
    {

        headerAverage();

    }

    else
    {

        headerMedian();

    }

    for (int i = 0; i < list.size(); i++)
    {

        output(list[i]);

    }

    system("pause");
}

void input(data& temp)
{

    bool yn;
    int p;

    cout << "iveskite varda: ";
    cin >> temp.name;
    cout << "iveskite pavarde: ";
    cin >> temp.surname;

    cout << "Jei norite namu darbu pazymius generuoti automatiskai, spauskite 1, jei ranka 0" << std::endl;
    yn = YN();

    if (yn)
    {

        cout << "kiek norite pazymiu?" << std::endl;
        p = type();
        randomMark(p, temp);

    }

    else
    {

        cout << "iveskite pazymius po viena (norint baigti ivedima, iveskite '11'" << std::endl;

        while (true)
        {

            p = type();

            if (p == 11)
            {

                break;

            }

            else if (decimal(p))
            {

                temp.mark.push_back(p);

            }

        }

    }

    cout << "jei norite egzamino pazymi generuoti automatiskai spauskite 1, jei norite irasyti ranka 0" << std::endl;
    yn = YN();

    if (yn)
    {

        temp.egz = number();

    }
    else
    {

        cout << "iveskite pazymi: " << std::endl;

        while (true)
        {

            p = type();

            if (decimal(p))
            {

                temp.egz = p;
                break;

            }

        }

    }

}

void output(data& temp)
{

    cout << std::left << std::setw(15) << temp.surname << std::left <<
        std::setw(15) << temp.name << std::left << std::setw(15) <<
        std::fixed << std::setprecision(2) <<
        0.4 * temp.result + 0.6 * temp.egz << std::endl;
}

void headerAverage()
{

    cout << std::left << std::setw(15) << "pavarde" << std::left << std::setw(15) <<
        "vardas" << std::left << std::setw(15) << "galutinis (vid.)" << std::endl;
    cout << "--------------------------------------------------" << std::endl;

}

void headerMedian()
{

    cout << std::left << std::setw(15) << "pavarde" << std::left << std::setw(15) <<
        "vardas" << std::left << std::setw(15) << "galutinis (med.)" << std::endl;
    cout << "--------------------------------------------------" << std::endl;

}

double average(vector<int> mark)
{

    double sum = 0;

    if (mark.size() == 0)
    {

        return 0;

    }

    for (int i = 0; i < mark.size(); i++)
    {

        sum += mark[i];

    }

    sum /= mark.size() * 1.0;
    return sum;

}

double median(vector<int> mark)
{

    if (mark.size() == 0)
    {

        return 0;

    }

    sort(mark.begin(), mark.end());

    if (mark.size() % 2 != 0)
    {

        return mark[mark.size() / 2];

    }

    else
    {

        double answer = mark[mark.size() / 2] + mark[mark.size() / 2 - 1];
        return answer / 2.0;

    }

}

bool decimal(int n)
{

    if (n >= 1 && n <= 10)
    {

        return true;

    }

    else
    {

        cout << "skaicius turi buti nuo 1 iki 10" << std::endl;
        return false;

    }

}

int type()
{

    int x;

    while (true)
    {

        cin >> x;

        if (!cin.good())
        {

            cout << "iveskite sveikaji skaiciu " << std::endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n'); // isvalo buffer

        }

        else
        {

            return x;

        }

    }

}

bool YN()
{

    int x;

    while (true)
    {

        x = type();

        if (x == 0 || x == 1)
        {

            return x;

        }

        else
        {

            cout << "iveskite 1 arba 0" << std::endl;

        }

    }

}

int number()
{

    int x = rand() % 10 + 1;
    return x;

}

void randomMark(int k, data& temp)
{

    int x;

    for (int i = 0; i < k; i++)
    {

        x = number();
        temp.mark.push_back(x);

    }

}