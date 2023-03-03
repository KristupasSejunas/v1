#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>

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
string output(data& temp);
string outputAverage();
string outputMedian();
double average(vector<int> mark);
double median(vector<int> mark);
void counting(vector<data>& lst, bool y_n);

//cheking functions
bool decimal(int n);
int type();
bool yesNo();

//random generating
int number();
void random_mark (int k, data& temp);

//working with files
void read(string stud, vector<data>& lst);
int markCounter(ifstream& in);

//printing
void toScreen(vector<data> lst, bool y_n);
void toFile(vector<data> lst, bool y_n, string result);

//sorting
bool sortWithName(data a, data b);
bool sortWithSirname(data a, data b);

int main()
{

    vector<data> lst;
    string stud = "studentai.txt";
    string result = "kursiokai.txt";

    cout << "Jei norite duomenis rasyti ranka, spauskite 1, jei noriste skaityti is failo, spauskite 0" << endl;
    bool reedFromFile = yesNo();

    cout << "Jei norite skaiciuoti su vidurkiu, spauskite 1, jei norite skaiciuoti su mediana, spauskite 0" << endl;
    bool y_n = yesNo();

    cout << "Jei norite rusiuoti per varda, spauskite 1, jei norite rusiuoti pagal pavarde, spauskite 0" << endl;
    bool nameSirname = yesNo();

    if (!reedFromFile)
    {

        read(stud, lst);

        if (nameSirname)
        {

            sort(lst.begin(), lst.end(), sortWithName);

        }

        else
        {

            sort(lst.begin(), lst.end(), sortWithSirname);

        }

        counting(lst, y_n);
        toFile(lst, y_n, result);

    }

    else
    {

        while (true)
        {

            cout << "Norint ivesti studento duomenis, spauskite 1, jei norite baigti duomenu ivedima, spauskite 0" << endl;
            bool ans = yesNo();

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

        if (nameSirname)
        {

            sort(lst.begin(), lst.end(), sortWithName);

        }

        else
        {

            sort(lst.begin(), lst.end(), sortWithSirname);

        }

        counting(lst, y_n);
        toScreen(lst, y_n);

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
    y_n = yesNo();

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
    y_n = yesNo();

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

string output(data& temp)
{

    stringstream x;
    x << setiosflags(ios_base::left) << setw(20) << temp.name << setiosflags(ios_base::left) << setw(20) << temp.surname <<
        setiosflags(ios_base::left) << setw(20) << fixed << setprecision(2) << 0.4 * temp.result + 0.6 * temp.egz << endl;
    return x.str();

}

string outputAverage()
{

    stringstream x;
    x << setiosflags(ios_base::left) << setw(20) << "Vardas" << setiosflags(ios_base::left) << setw(20) << "Pavarde" <<
        setiosflags(ios_base::left) << setw(20) << "Galutinis (Vid.)" << endl
        << "--------------------------------------------------" << endl;
    return x.str();

}

string outputMedian()
{

    stringstream x;
    x << setiosflags(ios_base::left) << setw(20) << "Vardas" << setiosflags(ios_base::left) << setw(20) << "Pavarde" <<
        setiosflags(ios_base::left) << setw(20) << "Galutinis (Med.)" << endl
        << "--------------------------------------------------" << endl;
    return x.str();

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

bool yesNo()
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

    unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed1);
    uniform_int_distribution<int> dist(1, 10);
    int x = dist(generator);

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

void read(string stud, vector<data>& lst)
{

    ifstream in(stud);

    if (in)
    {

        int lenght = markCounter(in);

        while(!in.eof())
        {

            int m;
            data temp;
            in >> temp.name >> temp.surname;

            for (int i = 0; i < lenght; i++)
            {

                in >> m;
                temp.mark.push_back(m);

            }

            in >> temp.egz;
            lst.push_back(temp);

        }

    }

    in.close();

}

int markCounter(ifstream& in)
{

    int ans = 0;
    string t;

    while ((in.peek() != '\n') && (in >> t))
    {

        ans++;

    }

    return ans - 3;

}

void toScreen(vector<data> lst, bool y_n)
{

    if (y_n)
    {

        cout << outputAverage();

    }

    else
    {

       cout << outputMedian;

    }

    for (int i = 0; i < lst.size(); i++)
    {

        cout << output(lst[i]);

    }

}

void toFile(vector<data> lst, bool y_n, string result)
{

    ofstream out(result);

    if (y_n)
    {

        out << outputAverage();

    }

    else
    {

        out << outputMedian();

    }

    for (auto& el : lst)
    {

        out << output(el);

    }

    out.close();

}

void counting(vector<data>& lst, bool y_n)
{

    for (auto& el : lst)
    {

        if (y_n)
        {

            el.result = average(el.mark);

        }

        else
        {

            el.result = median(el.mark);

        }

    }

}

bool sortWithName(data a, data b)
{

    return a.name < b.name;

}

bool sortWithSirname(data a, data b)
{

    return a.surname < b.surname;

}
