#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

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
void outputAverage();
void outputMedian();
double average(vector<int> mark);
double median(vector<int> mark);

bool decimal(int n);
int type();
bool yes_no();

int number();
void random_mark (int k, data& temp);

int main()
{

    srand(time(NULL));

    vector<data> lst;
    int amount = 0;

    while (true)
    {

        cout << "Norint ivesti studento duomenis, spauskite 1, jei norite baigti duomenu ivedima, spauskite 0" << endl;
        bool ans = yes_no();

        if (ans == false)
        {

            break;

        }

        else
        {

            data T;
            input(T);
            lst.push_back(T);
        }

    }

    cout << "jei norite rezultata skaiciuoti su vidurkiu, spauskite 1, jei norite skaiciuoti su mediana, spauskite 0" << endl;
    bool ans = yes_no();

    for (auto& el : lst)
    {

        if (ans)
        {

            el.result = average(el.mark);

        }

        else
        {

            el.result = median(el.mark);

        }

    }

    if (ans)
    {

        outputAverage();

    }

    else
    {

        outputMedian();

    }

    for (int i = 0; i < lst.size(); i++)
    {

        output(lst[i]);

    }

    system("pause");

}

void input(data& temp)
{

    bool y_n;
    int p;

    cout << "studento vardas: ";
    cin >> temp.name;
    cout << endl;

    cout << "studento pavarde: ";
    cin >> temp.surname;
    cout << endl;

    cout << "jei norite pazymius generuoti atsitiktinius, spauskite 1, jei norite vesti ranka, spauskite 0" << endl;
    y_n = yes_no();

    if (y_n)
    {

        cout << "kiek pazymiu norite sugeneruoti? " << endl;
        p = type();
        random_mark(p, temp);

    }

    else
    {

        cout << "iveskite namu darbu pazymius. Baigus, paspauskite 0" << endl;

        while (true)
        {

            p = type();

            if (p == 0)
            {

                break;

            }

            else if (decimal(p))
            {

                temp.mark.push_back(p);

            }

        }

    }

    cout << "jei norite egzamino rezultata generuoti atsitiktinai, spauskite 1, jei norite ivesti ranka spauskite 0" << endl;
    y_n = yes_no();

    if (y_n)
    {

        temp.egz = number();

    }

    else
    {

        cout << "iveskite egzamino rezultata: ";

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

    cout << left << setw(15) << temp.surname << left << setw(15) << temp.name << left <<
    setw(15) << fixed << setprecision(2) << 0.4 * temp.result + 0.6 * temp.egz << endl;

}

void outputAverage()
{

    cout << left << setw(15) << "Pavarde" << left << setw(15) << "Vardas" <<
    left << setw(15) << "Galutinis (Vid.)" << endl;
    cout << "--------------------------------------------------" << endl;

}

void outputMedian()
{

    cout << left << setw(15) << "Pavarde" << left << setw(15) << "Vardas" <<
    left << setw(15) << "Galutinis (Med.)" << endl;
    cout << "--------------------------------------------------" << endl;


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

    sum /= mark.size() *1.0;
    return sum;

}

double median(vector<int> mark)
{

    if (mark.size() == 0)
    {

        return 0;

    }

    sort (mark.begin(), mark.end());

    if (mark.size() % 2 != 0)
    {

        return mark[mark.size() / 2];

    }

    else
    {

        double ans = mark[mark.size() / 2] + mark[mark.size() / 2 - 1];
        return ans / 2.0;

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

        cout << "prasome ivesti skaiciu nuo 1 iki 10" << endl;
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

            cout << "iveskite sveikaji skaiciu" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');

        }

        else
        {

            return x;

        }

    }

}

bool yes_no()
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

            cout << "iveskite 1 arba 0" << endl;

        }

    }

}

int number()
{

    int x = rand() % 10 + 1;
    return x;

}

void random_mark(int k, data& temp)
{

    int x;

    for (int i = 0; i < k; i++)
    {

        x = number();
        temp.mark.push_back(x);

    }

}
