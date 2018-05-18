#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <climits>

class NEH {
public:
	int nr;
	int czas;
	std::vector<int> czasyNaMaszynie;
	bool operator < (const NEH & zad) const { return (czas < zad.czas); }
	void wyliczCzasCalkowity();	
};

void::NEH::wyliczCzasCalkowity()
{
	czas = 0;
	for (int i = 0; i < czasyNaMaszynie.size(); i++) 
		czas += czasyNaMaszynie[i];
}

int obliczCmax(std::vector<NEH> wektorZadan, std::vector<int> tablicaPi, int liczbaZadan, int liczbaMaszyn);

int main()
{
	std::vector<NEH> wektorZadan;
	std::ifstream plik;
	plik.open("in10.txt");
	int liczbaZadan = 0;
	int liczbaMaszyn = 0;
	int sumaCzasow = 0;

	/*1) £adujemy dane do dwóch wektorów - 1: czasyNaMaszynie 2: wektoraZadan oraz podliczamy czas na ka¿dej maszynie*/
	plik >> liczbaZadan >> liczbaMaszyn;
	
	for (int i = 0; i < liczbaZadan; i++)
	{
		NEH tmp;
		for (int j = 0; j < liczbaMaszyn; j++)
		{
			int czastmp;
			plik >> czastmp;
			tmp.czasyNaMaszynie.push_back(czastmp);
			sumaCzasow += czastmp;
		}
		tmp.nr = i;
		tmp.wyliczCzasCalkowity();
		wektorZadan.push_back(tmp);
	}

	/*2) Sortujemy zadania nierosn¹co po sumie czasów wszystkich operacji na wszystkich maszynach dla danego zadania */
	sort(wektorZadan.rbegin(), wektorZadan.rend());

	std::vector<int> tablicaPi;
	std::vector<int> tablicaPiTmp;
	tablicaPi.push_back(0);
	int cMax = 0;
	
	/*3) Wybieramy zadanie o najwiêkszym 'w', czyli przechodzimy przez pêtle od pocz¹tku*/
	for (int i = 1; i < wektorZadan.size(); i++)
	{
		cMax = INT_MAX; //ustawiamy Cmax maksymalny po to, aby znaleŸæ najmniejszy
		/*4) Wstawiamy zadanie k na k pozycjach*/
		for (int j = 0; j < i + 1; j++)
		{
			tablicaPi.insert(tablicaPi.begin() + j, i);
			int c = obliczCmax(wektorZadan, tablicaPi, liczbaZadan, liczbaMaszyn);
			/*5) Sprawdzamy czy aktualny Cmax jest mniejszy od poprzedniego.*/
			if (c < cMax)
			{
				cMax = c;
				tablicaPiTmp = tablicaPi;
			}
			tablicaPi.erase(tablicaPi.begin() + j);
		}
		tablicaPi = tablicaPiTmp;
	}

	std::cout << "Cmax = " << cMax << std::endl;
	
	for(int z = tablicaPi.size() - 1 ; z >= 0; z--)
		std::cout << tablicaPi[z] + 1 << "  ";
	_getch();
	return 0;
}

int obliczCmax(std::vector<NEH> wektorZadan, std::vector<int> tablicaPi, int liczbaZadan, int liczbaMaszyn)
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