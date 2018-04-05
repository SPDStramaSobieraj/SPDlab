#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <conio.h>

class RPQ {
public:
	int r, p, q, nr;
	RPQ(int r, int p, int q, int nr) : r(r), p(p), q(q), nr(nr) {}
	RPQ() { p = r = q = nr = 0; }
	friend std::ostream & operator << (std::ostream & os, const RPQ & r);
};

std::ostream & operator << (std::ostream & os, const RPQ & r)
{
	os << r.nr + 1 << "  ";
	//os << r.r << "  " << r.p << "  " << r.q << "  kolejnosc - " << r.nr << std::endl;
	return os;
}

struct R { bool operator ()(const RPQ & a, const RPQ & b) { return a.r > b.r; } };
struct Q { bool operator ()(const RPQ & a, const RPQ & b) { return a.q < b.q; } };

int max(int a, int b)
{
	if (a < b) return b;
	else
		return a;
}

int main()
{
	std::priority_queue<RPQ, std::vector<RPQ>, Q> wektorG; //zbiór zadañ gotowych do uszeregowania
	std::priority_queue<RPQ, std::vector<RPQ>, R> wektorN; //zbiór zadañ nieuszeregowanych

	std::ifstream plik;
	plik.open("in50.txt");
	int liczbaDanych = 0;
	int r, p, q;
	int kolejnosc = 0;
	int t = 0, k = 0, cMax = 0;
	plik >> liczbaDanych;
	plik >> r;
	

	for (int i = 0; i < liczbaDanych; ++i)
	{
		plik >> r >> p >> q;
		std::cout << r << "   " << p << "   " << q << std::endl;
		RPQ Dane(r, p, q, kolejnosc);
		wektorN.push(Dane);
		kolejnosc++;
	}
	std::cout << "\n\n";
	std::cout << "Kolejnosc : ";

	while (wektorG.empty() == false || wektorN.empty() == false) { //dopóki wektor G lub wektor N nie s¹ puste
		/*pêtla wewnêtrzna s³u¿y do budowania zbioru zadañ gotowych do uszeregowania*/
		while (wektorN.empty() == false && wektorN.top().r <= t) { //dopóki wektor N nie jest pusty oraz czas przygotowania pierwszego zadania jest mniejszy badz rowny czasowi t
			wektorG.push(wektorN.top()); //do wektora G ³adujemy pierwszy element z wektora N
			wektorN.pop(); //usuwamy pierwszy element z wektora N
		}
		/*jeœli nie ma zadañ do uszeregowania to aktualizujemy czas 't', jesli zaœ nie jest pusty to aktualizujemy 't' o czas przygotowania*/
		if (wektorG.empty() == true) 
			t = wektorN.top().r;
		else {
			RPQ dane;
			dane = wektorG.top();
			std::cout << dane;
			wektorG.pop();
			k += 1;
			t += dane.p;
			cMax = max(cMax, t + dane.q);
		}
	}
	std::cout << "\nCmax: " << cMax << std::endl;
	_getch();
}


