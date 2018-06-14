#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <climits>

class TabuSearch {
public:
	int nr;
	int czas;
	std::vector<int> czasyNaMaszynie;
	bool operator < (const TabuSearch & zad) const { return (czas < zad.czas); }
	void wyliczCzasCalkowity();
};

void::TabuSearch::wyliczCzasCalkowity()
{
	czas = 0;
	for (int i = 0; i < czasyNaMaszynie.size(); i++)
		czas += czasyNaMaszynie[i];
}

int obliczCmax(std::vector<TabuSearch> wektorZadan, std::vector<int> tablicaPi, int liczbaZadan, int liczbaMaszyn);

int silnia(int n)
{
	if (n == 0) return 1;
	else return n * silnia(n - 1);
}

int main()
{
	srand(time(NULL));
	std::vector<TabuSearch> wektorZadan;
	std::ifstream plik;
	plik.open("in50.txt");
	int liczbaZadan = 0;
	int liczbaMaszyn = 0;
	int sumaCzasow = 0;

	/*£adujemy dane do wektora wektorZadan*/

	plik >> liczbaZadan >> liczbaMaszyn;

	for (int i = 0; i < liczbaZadan; i++)
	{
		TabuSearch tmp;
		for (int j = 0; j < liczbaMaszyn; j++)
		{
			int czastmp;
			plik >> czastmp;
			tmp.czasyNaMaszynie.push_back(czastmp);
		}
		tmp.nr = i;
		wektorZadan.push_back(tmp);
		wektorZadan[i].nr = i + 1;
	}
	
	
	std::vector<int> tablicaPi;
	std::vector<int> tablicaPiGwiazdka;
	tablicaPi.push_back(0);
	int cMax = 0;
	
	/*Znajdz rozwiazanie poczatkowe. Rozwiazanie poczatkowe
	jako pierwsza kombinacja z algorytmu NEG*/

	int j = 0;
	for (int i = 1; i < wektorZadan.size(); i++)
	{
		cMax = INT_MAX; //ustawiamy Cmax maksymalny po to, aby znaleŸæ najmniejszy
		tablicaPi.insert(tablicaPi.begin() + j, i);
		int c = obliczCmax(wektorZadan, tablicaPi, liczbaZadan, liczbaMaszyn);
		if (c < cMax)
		{
			cMax = c;
			tablicaPiGwiazdka = tablicaPi;
		}
		tablicaPi.erase(tablicaPi.begin() + j);
		tablicaPi = tablicaPiGwiazdka;
		j++;
	}

	for (int i = 0; i < tablicaPi.size(); i++)
		std::cout << tablicaPi[i] + 1 << "  ";
	std::cout << "\nCmax po rozwiazaniu poczatkowym = " << cMax << std::endl;

	/*Generujemy sasiedztwo na podstawie rozwiazania poczatkowego. Sasiedztwo generujemy na podstawie "ruchu" czyli zamiany kolejnosci dwoch elementow.
	Przyjmujemy tyle kombinacji ile mamy zadan. Przyjmujemy tez czas jak dlugo maja generowac sie sasiedztwa w postacii ilosci wykonan pêtli.
	Jesli algorytm wykonal wszystkie mozliwe permutacje to przerywamy algorytm i wychodzimy z pêtli. Tworzymy nowy wektor "WektorZabronien" do ktorego
	wk³adamy juz permutacje kolejnosci dla ktorych wartosc funkcji celu zostala juz policzona.*/
	
	std::vector <std::vector<int> > WektorZabronien;
	WektorZabronien.push_back(tablicaPi);
	int licznik = 0;

	for (int j = 0; j < 10; j++) {
		for (int i = 1; i < wektorZadan.size(); i++)
		{
			int ile = wektorZadan.size();
			int jakaSilnia = silnia(ile) - 1;
			if (licznik == jakaSilnia)
				break;
			int L1 = std::rand() % wektorZadan.size();
			int L2 = std::rand() % wektorZadan.size();
			while (L1 == L2)
				L2 = std::rand() % wektorZadan.size();
			std::swap(tablicaPi[L1], tablicaPi[L2]);
			
			if (std::find(WektorZabronien.begin(), WektorZabronien.end(), tablicaPi) != WektorZabronien.end()) {
				i--;
				continue;
			}

			WektorZabronien.push_back(tablicaPi);
			licznik++;
			int c = obliczCmax(wektorZadan, tablicaPi, liczbaZadan, liczbaMaszyn);
			if (c < cMax)
			{
				cMax = c;
				tablicaPiGwiazdka = tablicaPi;
			}
			/*for (int i = 0; i < tablicaPi.size(); i++)
				std::cout << tablicaPi[i] + 1 << "  ";*/
			std::cout << "Cmax = " << c;
			std::cout << std::endl;
		}

	}

	std::cout << "  Cmax OPTYMALNY = " << cMax;


	_getch();
	return 0;
}

int obliczCmax(std::vector<TabuSearch> wektorZadan, std::vector<int> tablicaPi, int liczbaZadan, int liczbaMaszyn)
{
	int *tablicaMaszyn = new int[liczbaMaszyn];
	for (int i = 0; i < liczbaMaszyn; i++)
		tablicaMaszyn[i] = 0;
	for (int i = 0; i < tablicaPi.size(); i++)
	{
		for (int j = 0; j < liczbaMaszyn; j++)
		{
			if (j > 0 && tablicaMaszyn[j - 1] > tablicaMaszyn[j])
				tablicaMaszyn[j] = tablicaMaszyn[j - 1];
			tablicaMaszyn[j] += wektorZadan[tablicaPi[i]].czasyNaMaszynie[j];
		}
	}
	int cMax = tablicaMaszyn[liczbaMaszyn - 1];
	delete[] tablicaMaszyn;
	return cMax;
}