/*********************************************************************************************************/
/*Algorytm Carliera zosta³ czêœciowo zaimplementowany w poprawny sposób. Brakuje w nim rekurencji        
jeœli warunki w ifach zostan¹ spe³nione i te miejsca w programie pozosta³y puste. Przy zastosowaniu	     
jej poprzez bezsensowne kopiowanie kodu pojawia³ nam siê b³¹d. Program nale¿a³oby przerobiæ obiektowo na 
funkcje i za pomoc¹ jednej linijki wywo³ywaæ rekurencje.*/
/*********************************************************************************************************/


#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <queue>
#include <climits>

class RPQ {
public:
	int r, p, q, nr;
	RPQ(int r, int p, int q, int nr) : r(r), p(p), q(q), nr(nr) {}
	RPQ() { p = r = q = nr = 0; }
};

struct R { bool operator ()(const RPQ & a, const RPQ & b) { return a.r > b.r; } };
struct Q { bool operator ()(const RPQ & a, const RPQ & b) { return a.q < b.q; } };


int main()
{
	std::priority_queue<RPQ, std::vector<RPQ>, Q> wektorG;
	std::priority_queue<RPQ, std::vector<RPQ>, R> wektorN;
	std::ifstream plik;
	plik.open("in50.txt");
	int liczbaDanych = 0;
	int kolejnosc = 0;
	int r, p, q;
	int t = 0, cMax = 0, k = 0, e = 0;
	plik >> liczbaDanych;
	plik >> r;
	std::vector <RPQ> tablicaPi;
	std::cout << liczbaDanych << std::endl;
	int a = 0, b = 0, c = 0;

	for (int i = 0; i < liczbaDanych; i++)
	{
		plik >> r >> p >> q;
		std::cout << r << "  " << p << "  " << q << std::endl;
		RPQ Dane(r, p, q, kolejnosc);
		wektorN.push(Dane);
		kolejnosc++;
	}

	while (wektorG.empty() == false || wektorN.empty() == false) {
		while (wektorN.empty() == false && wektorN.top().r <= t) {
			wektorG.push(wektorN.top());
			wektorN.pop();

		}
		if (wektorG.empty() == true) {
			t = wektorN.top().r;
			continue;
		}
		else
		{
			RPQ Dane1;
			Dane1 = wektorG.top();
			wektorG.pop();
			k = k + 1;
			tablicaPi.push_back(Dane1);
			t = t + Dane1.p;
			if (cMax <= t + Dane1.q)
			{
				cMax = t + Dane1.q;
				b = k;
			}
		}

	}

	int U = cMax;
	int UB = INT_MAX;

	if (U < UB) {                                                    
		UB = U;
	}

	int sum = 0;

	for (int j = b; j > 0; j--)
	{
		sum = 0;
		for (int s = j; s <= b; s++)
			sum += tablicaPi[s - 1].p;
		sum += tablicaPi[b - 1].q + tablicaPi[j - 1].r;
		//std::cout << sum << std::endl;
		if (cMax == sum)
			a = j;
	}

	for (int j = a; j <= b; j++)
		if (tablicaPi[j - 1].q < tablicaPi[b - 1].q)
			c = j;


	std::cout << std::endl;
	std::cout << "C_max po Schrage zwyklym: " << cMax << " " << "a: " << a << " b: " << b << " c: " << c << std::endl;

	if (c == 0) { //jesli c nie istnieje                           
		std::cout << "C nie istnieje" << std::endl;
		std::cout << "C_max po Schrage zwyklym = " << cMax << std::endl;
	}

	int minR = INT_MAX;
	for (int j = c + 1; j <= b; j++) {
		if (tablicaPi[j].r < minR)
			minR = tablicaPi[j].r;
	}
	std::cout << "Minimum r = " << minR << std::endl;

	int minQ = INT_MAX;
	for (int j = c + 1; j <= b; j++) {
		if (tablicaPi[j].q < minQ)
			minQ = tablicaPi[j].q;
	}
	std::cout << "Minimum q = " << minQ << std::endl;

	
	int prim = 0;
	for (int j = c + 1; j <= b; j++) {
		prim += tablicaPi[j].p;
	}
	
	std::cout << "Pprim = " << prim << std::endl;

	int rpic = tablicaPi[c].r;
	std::cout << "rpic= " << rpic << std::endl;

	tablicaPi[c].r = std::max(tablicaPi[c].r, prim + minR);
	std::cout << "rpic= " << tablicaPi[c].r << std::endl;

	int LB = 0;
	t = 0;
	cMax = 0;

	for (int i = 0; i < liczbaDanych; ++i)
		wektorN.push(tablicaPi[i]);

	int liczba_zabezpieczajaca_przerwanie = INT_MAX;

	RPQ Maszyna(0, 0, liczba_zabezpieczajaca_przerwanie, 0);
	while (wektorG.empty() == false || wektorN.empty() == false) {

		while (wektorN.empty() == false && wektorN.top().r <= t) {
			RPQ tmp = wektorN.top();
			wektorG.push(wektorN.top());
			wektorN.pop();

			
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
			wektorG.pop();
			Maszyna = Dane1;
			t = t + Dane1.p;
			cMax = std::max(cMax, t + Dane1.q);
		}
	}
	//std::cout << "Cmax po 1-szym podziale schraga: " << cMax << std::endl;

	LB = cMax;
	if (LB < UB)
	{
		//rekurencja
	}

	tablicaPi[c].r = rpic;
	int qpic = tablicaPi[c].q;
	tablicaPi[c].q = std::max(tablicaPi[c].q, minR + prim);
	

	LB = 0;
	t = 0;
	cMax = 0;
	Maszyna.r = Maszyna.p = Maszyna.q = Maszyna.nr = 0;

	for (int i = 0; i < liczbaDanych; ++i)
		wektorN.push(tablicaPi[i]);

	liczba_zabezpieczajaca_przerwanie = INT_MAX;

	while (wektorG.empty() == false || wektorN.empty() == false) {

		while (wektorN.empty() == false && wektorN.top().r <= t) {
			RPQ tmp = wektorN.top();
			wektorG.push(wektorN.top());
			wektorN.pop();


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
			wektorG.pop();
			Maszyna = Dane1;
			t = t + Dane1.p;
			cMax = std::max(cMax, t + Dane1.q);
		}
	}
	//std::cout << "Cmax po 2-gim podziale schraga: " << cMax << std::endl;

	LB = cMax;
	if (LB < UB) {                                       
		//rekurencja
	}

	tablicaPi[c].q = qpic;                    
	std::cout << "Cmax po podzia³ach schraga i rekurencjach: " << cMax << std::endl;
	

	_getch();
}

