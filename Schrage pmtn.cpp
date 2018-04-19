#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <conio.h>
#include <climits>

/* Porównanie czasów z algorytmem bez przerwañ
6 zadañ - 32 z przerwaniami - 32 bez przerwañ
10 zadañ - 641 z przerwaniami - 687 bez przerwañ
20 zadañ - 1257 z przerwaniami - 1299 bez przerwañ
50 zadañ - 1492 z przerwaniami - 1513 bez przerwañ
100 zadañ - 3070 z przerwaniami - 3076 bez przerwañ
200 zadañ - 6398 z przerwaniami - 6416 bez przerwañ
500 zadañ - 14785 z przerwaniami - 14822 bez przerwañ */

/*Komentarze w programie omawiaj¹ algorytm poprzez porównanie go ze zwyk³ym algorytmem Schrage*/

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
	std::priority_queue<RPQ, std::vector<RPQ>, Q> wektorG; 
	std::priority_queue<RPQ, std::vector<RPQ>, R> wektorN; 

	std::ifstream plik;
	plik.open("in10.txt");
	int liczbaDanych = 0;
	int r, p, q;
	int kolejnosc = 0;
	int t = 0, cMax = 0;
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

	/*Zmienna posiadaj¹ca bardzo du¿¹ wartoœæ (czyt. nieskoñczon¹) podstawiana
	do zmiennej 'q' w celu zabezpieczenia zadania przed przerwaniem*/
	int liczba_zabezpieczajaca_przerwanie = INT_MAX;

	RPQ Maszyna(0, 0, liczba_zabezpieczajaca_przerwanie, 0);
	while (wektorG.empty() == false || wektorN.empty() == false) {

		while (wektorN.empty() == false && wektorN.top().r <= t) {
			RPQ tmp = wektorN.top();
			wektorG.push(wektorN.top());
			wektorN.pop();
			
			/*Algorytm Schrage z przerwaniami ró¿ni siê od algorytmu Schrage
			zasadniczo jednym krokiem. Za ka¿dym razem gdy do zbioru zadañ gotowych
			jest dodawane zadanie to sprawdzane jest czy ma wiêkszy czas dostarczania
			od zadania aktualnie przebywaj¹cego na maszynie. Je¿eli tak to wykonywanie zadania
			natychmiast jest przerywane, a pozosta³a czêœæ zadania tj. o czasie
            trwania t - tmp.r ponownie wk³adana jest do zbioru zadañ gotowych do realizacji.*/
			
	
			if (tmp.q > Maszyna.q)
			{
				Maszyna.p = t - tmp.r;
				t = tmp.r;
				wektorG.push(Maszyna);
			}

		}
		if (wektorG.empty() == true) {
			t = wektorN.top().r;
			continue;
		}
		else {
			RPQ Dane1(0, 0, 0, 0);
			Dane1 = wektorG.top();
			std::cout << Dane1;
			wektorG.pop();
			Maszyna = Dane1;
			t = t + Dane1.p;
			cMax = max(cMax, t + Dane1.q);
		}
	}
	std::cout << "\nCmax: " << cMax << std::endl;
	_getch();
}


