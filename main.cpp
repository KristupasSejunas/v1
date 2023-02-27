#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

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
void outputAverage();
void outputMedian();
double average(int* mark, int k);
void sorting(int* mark, int k);
double median(int* mark, int k);
void addMark(int p, data& temp);

bool decimal(int n);
int type();
bool yes_no();

int number();
void random_mark (int k, data& temp);

int main()
{

    srand(time(NULL));

    data* lst = nullptr;
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

            amount++;
            data T;
            input(T);

            data* temp = new data[amount - 1];

            for (int i = 0; i < amount - 1; i++)
            {

                temp[i] = lst[i];

            }

            delete[] lst;
            lst = new data[amount];

            for (int i = 0; i < amount - 1; i++)
            {

                lst[i] = temp[i];

            }

            lst[amount - 1] = T;
            delete[] temp;

        }

    }

    cout << "jei norite rezultata skaiciuoti su vidurkiu, spauskite 1, jei norite skaiciuoti su mediana, spauskite 0" << endl;
    bool ans = yes_no();

    for (data* i = lst; i < lst + amount; i++)
    {

        if (ans)
        {

            i -> result = average(i -> mark, i -> n);

        }

        else
        {

            i -> result = median(i -> mark, i -> n);

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

    for (int i = 0; i < amount; i++)
    {

        output(lst[i]);

    }

    delete[] lst;
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

                addMark(p, temp);

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

    sum /= k *1.0;
    return sum;

}

void sorting(int* mark, int k)
{

    int i = 0;
    bool y_n = true;

    while (y_n)
    {

        y_n = false;

        for (int j = k - 1; j > i; j--)
        {

            if (mark[j] <= mark[j - 1])
            {

                y_n = true;
                mark[j] += mark[j - 1];
                mark[j - 1] = mark[j] - mark[j - 1];
                mark[j] = mark[j] - mark[j - 1];

            }

        }

        i++;

    }

}

double median(int* mark, int k)
{

    if (k == 0)
    {

        return 0;

    }

    sorting(mark, k);

    if (k % 2 != 0)
    {

        return mark[k/2];

    }

    else
    {

        double ans = mark[k / 2] + mark[k / 2 - 1];
        return ans / 2.0;

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
        addMark(x, temp);

    }

}
