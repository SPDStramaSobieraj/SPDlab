#include <iostream>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

std::vector<std::vector<int> >PermutacjeBezPowtorzen(std::vector<int> tmp) {
	std::sort(tmp.begin(), tmp.end());
	std::vector<std::vector<int> > t;
	if (tmp.empty()) {
		return t;
	}
	do {
		t.push_back(tmp);
	} while (std::next_permutation(tmp.begin(), tmp.end()));
	return t;
}



class RPQ
{

public:
	int r, p, q; //przygotowanie, wykonanie, dostarczenie
	int nr; //numer zadania
	RPQ(int p, int r, int q, int nr);
	RPQ() { p = r = q = nr = 0; }
};

RPQ::RPQ(int r, int p, int q, int nr) : r(r), p(p), q(q), nr(nr)
{

}


int main()
{
	srand(time(NULL));
	std::ifstream plik;
	std::vector<RPQ> v1;
	std::vector<RPQ>::iterator i; //Iterator dla pêtli
	int liczbazadan = 0;
	int x, y, z;

	plik.open("in6.txt");
	if (!plik.is_open())
	{
		std::cout << "Plik nie udalo sie otworzyc!";
		_getch();
		exit(EXIT_FAILURE);
	}

	plik >> liczbazadan;
	plik >> x;

	for (int i = 0; i < liczbazadan; ++i)
	{
		plik >> x;
		plik >> y;
		plik >> z;
		std::cout << x << "  " << y << "  " << z << std::endl;
		RPQ zadanie(x, y, z, i);
		v1.push_back(zadanie);
	}


	std::cout << std::endl << std::endl;


	/*SORTOWANIE PO R*/
	/*int k = v1.size();
	bool zamiana;

	do {
	zamiana = false;
	for (int i = 0; i < k - 1; ++i)
	{
	if (v1[i].r > v1[i + 1].r)
	{
	swap(v1[i].r, v1[i + 1].r);
	swap(v1[i].p, v1[i + 1].p);
	swap(v1[i].q, v1[i + 1].q);
	zamiana = true;
	}

	}

	} while (zamiana);

	for (int i = 0; i < v1.size(); i++)
	std::cout << v1[i].r << "  " << v1[i].p << "  " << v1[i].q << std::endl;*/

	/*PRZEGLAD ZUPELNY*/

	int ilePermutacji = 0;
	std::vector<int> wynikowy;

	for (int i = 0; i < liczbazadan; ++i)
	{
		wynikowy.push_back(i);
	}

	std::vector<std::vector<int> > permutacje = PermutacjeBezPowtorzen(wynikowy);
	
	int Cmax = 0;
	int S = 0;
	int C = 0;
	int a = 0;

	for (std::vector<std::vector<int> >::size_type i = 0; i < permutacje.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j < permutacje[i].size(); j++)
		{

		}
		ilePermutacji++;

	}
	//std::cout << "Ilosc permutacji: " << ilePermutacji << std::endl;
	std::vector<RPQ> tmp;

	for (int z = 0; z < ilePermutacji; z++)
	{
		for (int j = 0; j < v1.size(); ++j) {
			int indeks = permutacje[z][j];
			RPQ zadanie(v1[indeks].r, v1[indeks].p, v1[indeks].q, z);
			tmp.push_back(zadanie);
			std::cout << tmp[indeks].r << "  " << tmp[indeks].p << "  " << tmp[indeks].q << std::endl;
		}


		while (a < liczbazadan)
		{
			if (tmp[a].r <= S)  //moment rozpoczecia wykonywania zadania musi byc wiekszy badz rowny czasowi przygotowania zadania, a jesli nie jest...
			{
				S = S + tmp[a].p;  //moment zakonczenia zadania to suma momentu rozpoczecia zadania i wykonywania sie zadania       
				Cmax = S + tmp[a].q;  //funkcja celu czyli czas zakonczenia zadania + czas dostarczenia zadania  
				a++;
			}
			else //... to naliczamy czas dopoki zadanie bedzie mozna wykonac
				S++;
		}
		for (int d = 0; d < tmp.size(); ++d)
			tmp.pop_back();
		
		std::cout << std::endl;
		std::cout << "Cmax to : " << Cmax;
		std::cout << std::endl;
		std::cout << std::endl;
		Cmax = 0;
		S = 0;
		a = 0;

	}




	_getch();


}