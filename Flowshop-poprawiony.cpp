#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <climits>


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


int main()
{
	std::ifstream plik;
	std::vector<double> w1; //maszyna A
	std::vector<double> w2; //maszyna B
	plik.open("dane10.txt");
	if (!plik.is_open())
	{
		std::cout << "Plik nie udalo sie otworzyc!\n";
		exit(EXIT_FAILURE);
	}
	double value, value2;
	std::string line;
	int count;
	plik >> count;

	for (int i = 0; i < count; ++i) {
		plik >> value;
		w1.push_back(value);
		plik >> value;
		w2.push_back(value);
	}
		
		
	
	std::vector<int> wynikowy;
	double makeSpan = 0.0;

	int j = 0; //zmienna do wyznaczania indeksu
	double min = INT_MAX; //w tej zmiennej przechowywamy najmniejsza wartosc
	int index = 0; //w tej zmiennej zapamietujemy indeks maszyny z najmniejszym czasem
	bool czy_maszyna_1 = false; //zmienna boolowska do stwierdzenia w ktorej maszynie znalezlismy najmniejszy czas
	bool czy_maszyna_2 = false; //the same
	int koniec = 0; //zmienna do zewnetrznej petli 

	
	for (int i = 0; i < w1.size(); ++i)
		wynikowy.push_back(i);

	int suma = 0;
	for (int i = 0; i < w1.size(); ++i)
		suma += w2[i];

	int ilePermutacji = 0;

	std::vector<std::vector<int> > permutacje = PermutacjeBezPowtorzen(wynikowy);

	for (std::vector<std::vector<int> >::size_type i = 0; i < permutacje.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j < permutacje[i].size(); j++)
		{
			//std::cout << permutacje[i][j] << ' ';
		}
		//std::cout << std::endl;
		ilePermutacji++;
	}
	std::cout << "Ilosc permutacji: " << ilePermutacji << std::endl;


	int czas_po_ktorym_mozna = 0;
	int makespan = 0;
	int makespan2 = 0;
	int nr_indeksu = 0;
	int najmniejszy_makespan = INT_MAX;

	for (int z = 0; z < ilePermutacji; z++)
	{
		for (int j = 0; j < w1.size(); ++j) {
			int nr_indeksu = permutacje[z][j];
			czas_po_ktorym_mozna += w1[nr_indeksu];

			for (int i = 0; i < w1[nr_indeksu]; ++i)
				makespan++;

			if (makespan2 < czas_po_ktorym_mozna)
			{
				int roznica = czas_po_ktorym_mozna - makespan2;
				for (int i = 0; i < roznica; ++i)
					makespan2++;
			}

			for (int j = 0; j < w2[nr_indeksu]; ++j)
				makespan2++;
		}
		for (int k = 0; k < w1.size(); ++k)
			std::cout << permutacje[z][k] << ' ';
		if (najmniejszy_makespan > makespan2)
			najmniejszy_makespan = makespan2;
		std::cout << "  " << suma;
		std::cout << "  " << makespan2;
		std::cout << std::endl;
		makespan = 0;
		makespan2 = 0;
		czas_po_ktorym_mozna = 0;



	}
	std::cout << "\nNajmniejszy makespan : " << najmniejszy_makespan;
	const int size = w1.size();
	double *tab = new double[size]; //tablica wyjsciowa
	int maxIndeks = w1.size() - 1; //indeksy dla maszyny drugiej, czyli ³adowania na koniec
	int minIndeks = 0; //indeksy dla maszyny pierwszej, czyli ³adowania na pocz¹tek
	std::vector<double>::iterator i; //Iterator dla pêtli

					   /*Zewnêtrzna pêtla koñczy siê wtedy jeœli lista wyjœciowa ma taki sam rozmiar jak maszyna A oraz maszyna B, czyli w tym wypadku 5*/
	while (koniec != w1.size()) {
		/*Pêtla wewnêtrzna maj¹ca za zadanie znaleŸæ najmniejszy element w obu maszynach i zapisaæ indeks tej maszyny w zmiennej "index"*/
		for (i = w1.begin(); i != w1.end(); ++i) {
			if (w1[j] < min) {
				min = w1[j];
				index = j;
				czy_maszyna_1 = true;
				czy_maszyna_2 = false;
			}
			if (w2[j] < min) {
				min = w2[j];
				index = j;
				czy_maszyna_1 = false;
				czy_maszyna_2 = true;
			}
			j++;
		}

		/*Gdy pêtla znalaz³a nam najmniejszy element to ustawiamy tam MAX wartosci sugerujace ze dany indeks juz wystapil i zeby nie brac go pod uwage bo jest juz zapisany w liscie wyjœciowej*/
		w1[index] = INT_MAX;
		w2[index] = INT_MAX;

		/*Jesli element z II maszyny to na koniec, jesli zas z I maszyny to na poczatek*/
		if (czy_maszyna_2) {
			tab[maxIndeks] = index;
			maxIndeks--;
		}
		else {
			tab[minIndeks] = index;
			minIndeks++;
		}

		min = INT_MAX; //ustawiamy ponownie wartosc min na MAX tak aby znalezc nowy najmniejszy element
		j = 0; //zmienna kontrolujaca przebiegi petli musi byc ponownie wyzerowana aby mozna bylo poprawnie przypisac j¹ do zmiennej index
		index = 0;

		koniec++;

		
	}

	std::cout << "\n\nWyznaczone algorytmem Johnsona:  ";
	for (int i = 0; i < w1.size(); ++i)
		std::cout << tab[i] << '\t';

	
	_getch();

}