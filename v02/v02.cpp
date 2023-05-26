// v02.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm> 
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>

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
string output(data& temp);
string headerAverage();
string headerMedian();
double average(vector<int> mark);
double median(vector<int> mark);
void calculation(vector<data>& list, int averageMedian);

//validation
bool decimal(int n);
int type();
bool YN();

//random
int number();
void randomMark(int k, data& temp);

//file
void read(string file, vector<data>& list);
int marks(std::ifstream& in);

//print
void toScreen(vector<data> list, int averageMedian);
void toFile(vector<data> list, int averageMedian, string file);

//sort
bool byName(data a, data b);
bool bySurname(data a, data b);

int main()
{

    vector<data> list;
    string inputFile = "..\\studentai.txt";
    string outputFile = "..\\kursiokai.txt";

    cout << "jei norite duomenis rasyti ranka, spauskite 1, jei skaityti is failo 0" << std::endl;
    bool handOrFile = YN();

    cout << " jei norite galutini pazymi skaiciuoti su vidurkiu, spauskite 1, jei mediana, 0" << std::endl;
    int averageMediana = YN();

    cout << "jei norite rusiuoti apgal varda, spauskite 1, jei pagal pavarde, 0" << std::endl;
    bool nameSurname = YN();

    if (!handOrFile)
    {

        read(inputFile, list);

        if (nameSurname)
        {

            sort(list.begin(), list.end(), byName);

        }

        else
        {

            sort(list.begin(), list.end(), bySurname);

        }

        calculation(list, averageMediana);
        toFile(list, averageMediana, outputFile);

    }

    else
    {

        while (true)
        {

            cout << "jei norite ivesti studento duomenis, spauskite 1, jei baigete iveskite 0" << std::endl;
            bool yn = YN();

            if (!yn)
            {

                break;

            }

            else
            {

                data T;
                output(T);
                list.push_back(T);

            }

        }

        if (nameSurname)
        {

            sort(list.begin(), list.end(), byName);

        }

        else
        {

            sort(list.begin(), list.end(), bySurname);

        }

        calculation(list, averageMediana);
        toScreen(list, averageMediana);

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

string output(data& temp)
{

    std::stringstream x;
    double ans = 0.40 * temp.result + 0.60 * temp.egz;

    x << std::setiosflags(std::ios_base::left) << std::setw(20) << temp.name <<
        std::setiosflags(std::ios_base::left) << std::setw(20) << temp.surname <<
        std::setiosflags(std::ios_base::left) << std::setw(20) << std::fixed <<
        std::setprecision(2) << ans << std::endl;

    return x.str();

}

string headerAverage()
{

    std::stringstream temp;

    temp << std::setiosflags(std::ios_base::left) << std::setw(20) << "vardas" <<
        std::setiosflags(std::ios_base::left) << std::setw(20) << "pavarde" <<
        std::setiosflags(std::ios_base::left) << std::setw(20) << "galutinis (vid.)" <<
        std::endl << "----------------------------------------------------------" << std::endl;

    return temp.str();

}

string headerMedian()
{

    std::stringstream temp;

    temp << std::setiosflags(std::ios_base::left) << std::setw(20) << "vardas" <<
        std::setiosflags(std::ios_base::left) << std::setw(20) << "pavarde" <<
        std::setiosflags(std::ios_base::left) << std::setw(20) << "galutinis (med.)" <<
        std::endl << "----------------------------------------------------------" << std::endl;

    return temp.str();
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

void calculation(vector<data>& list, int averageMedian)
{

    for (auto& el : list)
    {

        if (averageMedian == 1)
        {

            el.result = average(el.mark);

        }

        else
        {

            el.result = median(el.mark);

        }

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

    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed1);
    std::uniform_int_distribution<int> dist(1, 10);
    int x = dist(generator);
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

void read(string file, vector<data>& list)
{

    std::ifstream in(file);

    if (in)
    {

        int lenght = marks(in);

        while (!in.eof())
        {

            int p;
            data temp;
            in >> temp.name >> temp.surname;

            for (int i = 0; i < lenght; i++)
            {

                in >> p;
                temp.mark.push_back(p);

            }

            in >> temp.egz;
            list.push_back(temp);

        }

    }

    in.close();

}

int marks(std::ifstream& in)
{

    int ans = 0;
    string t;

    while ((in.peek() != '\n') && (in >> t))
    {

        ans++;

    }

    return ans - 3;

}

void toScreen(vector<data> list, int averageMedian)
{

    if (averageMedian == 1)
    {

        cout << headerAverage();

    }

    else
    {

        cout << headerMedian();

    }

    for (int i = 0; i < list.size(); i++)
    {

        cout << output(list[i]);

    }

}

void toFile(vector<data> list, int averageMedian, string file)
{

    std::ofstream out(file);

    if (averageMedian == 1)
    {

        out << headerAverage();

    }

    else
    {

        out << headerMedian();

    }

    for (auto& el : list)
    {

        out << output(el);

    }

    out.close();

}

bool byName(data a, data b)
{

    return a.name < b.name;

}

bool bySurname(data a, data b)
{

    return a.surname < b.surname;

}