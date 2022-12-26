// ChyrunSofialab11.2.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Lab_11_2.cpp
// < Чирун Софія >
// Лабораторна робота № 11.2.2
// Послідовний пошук у бінарному файлі 
// Варіант 18

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> 
using namespace std;
enum Student { KN, IT, ME, FI, TN };
string studentStr[] = { "Комп’ютерні науки", "Інформатика", "Матем. та екон.", "Фізика та інформ.", "Трудове навчання" };
struct Specialist
{
	string prizv;
	int course;
	Student student;
	double fizyk;
	double matem;
	union
	{
		double progr;
		double numbm;
		double pedag;
	};
	double serbl;
};

void Create(Specialist* p, const int N);
void Print(Specialist* p, const int N);
void Serbal(Specialist* p, const int N);
double MinSerbal(Specialist* p, const int N);
int Dobre(Specialist* p, int j, const int N, int d);
void CreateBIN(char* fname, Specialist* p, const int N) 
{
	ofstream fout(fname, ios::binary); 
	string s; 
	fout << "==============================================================================================================================="
		<< endl;
	fout << "| № | Прізвище | Курс |   Спеціальність   | Фізика | Математика | Програмування | Чисельні методи | Педагогіка | Середній бал |"
		<< endl;
	fout << "-------------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		fout << "|" << setw(2) << right << i + 1 << " ";
		fout << "| " << setw(9) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].course << " "
			<< "| " << setw(17) << left << studentStr[p[i].student] << " "
			<< "| " << setw(6) << setprecision(2) << fixed << right << p[i].fizyk << " "
			<< "| " << setw(10) << setprecision(2) << fixed << right << p[i].matem << " ";
		switch (p[i].student)
		{
		   case KN:
			  fout << "| " << setw(13) << setprecision(2) << fixed << right << p[i].progr << " |" << setw(18) << right << "|" << setw(14) << right << "| ";
			  break;
		   case IT:
			  fout << "| " << setw(15) << " |" << setw(16) << setprecision(2) << fixed << right << p[i].numbm << " |" << setw(14) << right << "| ";
			  break;
		   case ME:
			  fout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		   case FI:
			  fout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		   case TN:
			  fout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		}
		fout << setw(12) << setprecision(2) << fixed << right << p[i].serbl << " | " << endl;
	}
	fout << "===============================================================================================================================" << endl;
	fout << endl;
	fout << endl;
}

void CreateBIN1(char* fname, Specialist* p, const int N) 
{
	ofstream fout(fname, ios::binary); 
	string s; 
	fout << endl << "Кількість оцінок добре: ";
	fout << endl << "Фізика: " << Dobre(p, 1, N, 0);
	fout << endl << "Математика: " << Dobre(p, 2, N, 0);
	fout << endl << "Програмування: " << Dobre(p, 3, N, 0);
	fout << endl << "Чисельні методи: " << Dobre(p, 4, N, 0);
	fout << endl << "Педагогіка: " << Dobre(p, 5, N, 0);
	fout << endl << endl;
}

void PrintBIN(char* fname) 
{
	ifstream fin(fname, ios::binary); 
	char c; 
	while (fin.read((char*)&c, sizeof(c))) 
	{
		cout << c; 
	}
	cout << endl;
}

int main()
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 
	int N;
	cout << "Введіть N: "; cin >> N;
	Specialist* p = new Specialist[N];
	Create(p, N);
	Serbal(p, N);
	Print(p, N);
	char fname[100]; 
	cout << "enter file name 1: "; cin >> fname;
	cout << endl << "Мінімaльний середній бал: " << MinSerbal(p, N) << endl;
	CreateBIN(fname, p, N); 
	cout << "\nВивід результату з файлу 1: " << endl;
	PrintBIN(fname); 
	char gname[100]; 
	cout << "enter file name 2: "; cin >> gname;
	CreateBIN1(gname, p, N);
	cout << "\nВивід результату з файлу 2: " << endl;
	PrintBIN(gname); 
	return 0;
}

void Create(Specialist* p, const int N)
{
	int student;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync(); 
		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].course;
		cout << " спеціальність (0 - Комп’ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
		cin >> student;
		p[i].student = (Student)student;
		cout << " фізика: "; cin >> p[i].fizyk;
		cout << " математика: "; cin >> p[i].matem;
		switch (p[i].student)
		{
		   case KN:
			  cout << " програмування : "; cin >> p[i].progr; 
			  break;
		   case IT:
			  cout << " чисельні методи : "; cin >> p[i].numbm;
			  break;
		   case ME:
			  cout << " педагогіка : "; cin >> p[i].pedag; 
			  break;
		   case FI:
			  cout << " педагогіка : "; cin >> p[i].pedag; 
			  break;
		   case TN:
			  cout << " педагогіка : "; cin >> p[i].pedag; 
			  break;
		}
		cout << endl;
	}
}

void Serbal(Specialist* p, const int N)
{
	double s = 0;
	for (int i = 0; i < N; i++)
	{
		s = p[i].fizyk + p[i].matem;
		switch (p[i].student)
		{
		   case KN:
			  s += p[i].progr;
			  break;
		   case IT:
			  s += p[i].numbm;
			  break;
		   case ME:
			  s += p[i].pedag;
			  break;
		   case FI:
			  s += p[i].pedag;
			  break;
		   case TN:
			  s += p[i].pedag;
			  break;
		}
		p[i].serbl = s / 3;
		s = 0;
	}
}

double MinSerbal(Specialist* p, const int N)
{
	double s = 1000;
	for (int i = 0; i < N; i++)
	{
		if (p[i].serbl < s)
		   s = p[i].serbl;
	}
	return s;
}

int Dobre(Specialist* p, int j, const int N, int d)
{
	double s = 4;
	for (int i = 0; i < N; i++)
		switch (j)
		{
		   case 1:
			  if (p[i].fizyk == s)
				 d++;
			  break;
		   case 2:
			  if (p[i].matem == s)
				 d++;
			  break;
		   case 3:
		      if (p[i].progr == s)
				 d++;
			  break;
		   case 4:
			  if (p[i].numbm == s)
				 d++; 
			  break;
		   case 5:
			  if (p[i].pedag == s)
				 d++; 
			  break;
		}
	return d;
}

void Print(Specialist* p, const int N)
{
	cout << "===============================================================================================================================" << endl;
	cout << "| № | Прізвище | Курс |   Спеціальність   | Фізика | Математика | Програмування | Чисельні методи | Педагогіка | Середній бал |" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|" << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << p[i].prizv
			<< "| " << setw(4) << right << p[i].course << " "
			<< "| " << setw(17) << left << studentStr[p[i].student] << " "
			<< "| " << setw(6) << setprecision(2) << fixed << right << p[i].fizyk << " "
			<< "| " << setw(10) << setprecision(2) << fixed << right << p[i].matem << " ";
		switch (p[i].student)
		{
		   case KN:
			  cout << "| " << setw(13) << setprecision(2) << fixed << right << p[i].progr << " |" << setw(18) << right << "|" << setw(14) << right << "| ";
			  break;
		   case IT:
			  cout << "| " << setw(15) << " |" << setw(16) << setprecision(2) << fixed << right << p[i].numbm << " |" << setw(14) << right << "| ";
			  break;
		   case ME:
			  cout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		   case FI:
			  cout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		   case TN:
			  cout << "| " << setw(15) << right << "|" << " " << setw(17) << right << "|" << " " << setw(10) << right << p[i].pedag << " | ";
			  break;
		}
		cout << setw(12) << setprecision(2) << fixed << right << p[i].serbl << " | " << endl;
	}
	cout << "===============================================================================================================================" << endl;
	cout << endl;
}