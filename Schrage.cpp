#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <conio.h>

class RPQ {
public:
	int p, r, q;
	RPQ(int r, int p, int q) : r(r), p(p), q(q) {}
	RPQ() { p = r = q = 0; }
};

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
	std::priority_queue<RPQ, std::vector<RPQ>, Q> wektorG; //zbi�r zada� gotowych do uszeregowania
	std::priority_queue<RPQ, std::vector<RPQ>, R> wektorN; //zbi�r zada� nieuszeregowanych
	std::ifstream plik;
	plik.open("in10.txt");
	int liczbaDanych = 0;
	int r, p, q;
	int t = 0, k = 0, cMax = 0;
	plik >> liczbaDanych;
	plik >> r;

	for (int i = 0; i < liczbaDanych; ++i)
	{
		plik >> r >> p >> q;
		std::cout << r << "   " << p << "   " << q << std::endl;
		RPQ Dane(r, p, q);
		wektorN.push(Dane);
	}

	while (wektorG.empty() == false || wektorN.empty() == false) { //dop�ki wektor G lub wektor N nie s� puste
		/*p�tla wewn�trzna s�u�y do budowania zbioru zada� gotowych do uszeregowania*/
		while (wektorN.empty() == false && wektorN.top().r <= t) { //dop�ki wektor N nie jest pusty oraz czas przygotowania pierwszego zadania jest mniejszy badz rowny czasowi t
			wektorG.push(wektorN.top()); //do wektora G �adujemy pierwszy element z wektora N
			wektorN.pop(); //usuwamy pierwszy element z wektora N
		}
		/*je�li nie ma zada� do uszeregowania to aktualizujemy czas 't', jesli za� nie jest pusty to aktualizujemy 't' o czas przygotowania*/
		if (wektorG.empty() == true) 
			t = wektorN.top().r;
		else {
			RPQ dane;
			dane = wektorG.top();
			wektorG.pop();
			k += 1;
			t += dane.p;
			cMax = max(cMax, t + dane.q);
		}
	}
	std::cout << "\nCmax: " << cMax << std::endl;
	_getch();
}
