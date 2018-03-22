#include <iostream>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;


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
	std::vector<RPQ>::iterator i; //Iterator dla p�tli
	int liczbazadan = 0;
	int x, y, z;

	plik.open("in10.txt");
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
	int k = v1.size();
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
		std::cout << v1[i].r << "  " << v1[i].p << "  " << v1[i].q << std::endl;

	/*FUNKCJA CELU*/
	
	int Cmax = 0;
	int S = 0;
	int C = 0;
	int a = 0;


	while (a < liczbazadan)
	{
		if (v1[a].r <= S)  //moment rozpoczecia wykonywania zadania musi byc wiekszy badz rowny czasowi przygotowania zadania, a jesli nie jest...
		{
			S = S + v1[a].p;  //moment zakonczenia zadania to suma momentu rozpoczecia zadania i wykonywania sie zadania       
			Cmax = S + v1[a].q;  //funkcja celu czyli czas zakonczenia zadania + czas dostarczenia zadania  
			a++;
		}
		else //... to naliczamy czas dopoki zadanie bedzie mozna wykonac
			S++;	
	}


	std::cout << std::endl;
	std::cout << Cmax;


	_getch();


}