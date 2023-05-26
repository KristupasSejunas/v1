// v011.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <iomanip>


using std::cout;
using std::cin;
using std::string;

struct data
{

    string name;
    string surname;
    int n = 0;
    int egz;
    int* mark = nullptr;
    double result = 0;

};

void input(data& temp);
void output(data& temp);
void headerAverage();
void headerMedian();
double average(int* mark, int k);
double median(int* mark, int k);
void sort(int* mark, int k);
void addMark(int p, data& temp);
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

    data* list = nullptr;
    int K = 0;
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

            K++;
            data T;
            input(T);

            data* temp = new data[K - 1];

            for (int i = 0; i < K - 1; i++)
            {

                temp[i] = list[i];

            }

            delete[] list;

            list = new data[K];

            for (int i = 0; i < K - 1; i++)
            {

                list[i] = temp[i];

            }

            list[K - 1] = T;
            delete[] temp;

        }

    }

    cout << "jei norite galutini reezulta skaiciuoti vidurkiu spauskite 1, jei mediana 0" << std::endl;
    yn = YN();

    for (data* i = list; i < list + K; i++)
    {

        if (yn)
        {

            i->result = average(i->mark, i->n);

        }

        else
        {

            i->result = median(i->mark, i->n);

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

    for (int i = 0; i < K; i++)
    {

        output(list[i]);

    }

    delete[] list;
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

                addMark(p, temp);

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

double average(int* mark, int k)
{

    double sum = 0;

    if (k == 0)
    {

        return 0;

    }

    for (int i = 0; i < k; i++)
    {

        sum += mark[i];

    }

    sum /= k * 1.0;
    return sum;

}

double median(int* mark, int k)
{

    if (k == 0)
    {

        return 0;

    }

    sort(mark, k);

    if (k % 2 != 0)
    {

        return mark[k / 2];

    }

    else
    {

        double answer = mark[k / 2] + mark[k / 2 - 1];
        return answer / 2.0;

    }

}

void sort(int* mark, int k)
{

    int i = 0;
    bool yn = true;

    while (yn)
    {

        yn = false;

        for (int j = k - 1; j > i; j--)
        {

            if (mark[j] <= mark[j - 1])
            {

                yn = true;
                int temp = mark[j];
                mark[j] = mark[j - 1];
                mark[j - 1] = temp;

            }

        }

        i++;

    }

}

void addMark(int p, data& temp)
{

    temp.n++;
    int* x = new int[temp.n];

    for (int i = 0; i < temp.n - 1; i++)
    {

        x[i] = temp.mark[i];

    }

    delete[] temp.mark;

    temp.mark = new int[temp.n];

    for (int i = 0; i < temp.n - 1; i++)
    {

        temp.mark[i] = x[i];

    }

    temp.mark[temp.n - 1] = p;
    delete[] x;

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
        addMark(x, temp);

    }

}