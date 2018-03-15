#include <iostream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <list>
#include <climits>
int main()
{
	std::vector<double> v1; //maszyna A
	std::vector<double> v2; //maszyna B
	std::vector<double>::iterator i; //Iterator dla pêtli
	std::list<int>::iterator z; //Iterator dla listy

	int j = 0; //zmienna do wyznaczania indeksu
	double min = INT_MAX; //w tej zmiennej przechowywamy najmniejsza wartosc
	int index = 0; //w tej zmiennej zapamietujemy indeks maszyny z najmniejszym czasem
	bool czy_maszyna_1 = false; //zmienna boolowska do stwierdzenia w ktorej maszynie znalezlismy najmniejszy czas
	bool czy_maszyna_2 = false; //the same
	int koniec = 0; //zmienna do zewnetrznej petli 

	/*£adujemy do maszyny 1*/
	v1.push_back(10);
	v1.push_back(9);
	v1.push_back(8);
	v1.push_back(8);
	

	/*£adujemy do maszyny 2*/
	v2.push_back(8);
	v2.push_back(7);
	v2.push_back(9);
	v2.push_back(12);

	std::vector<double>v3 = v1;
	std::vector<double>v4 = v2;
	
	double *tab = new double[5]; //tablica wyjsciowa
	int maxIndeks = v1.size() - 1; //indeksy dla maszyny drugiej, czyli ³adowania na koniec
	int minIndeks = 0; //indeksy dla maszyny pierwszej, czyli ³adowania na pocz¹tek
	double makeSpan = 0.0;

	/*Zewnêtrzna pêtla koñczy siê wtedy jeœli lista wyjœciowa ma taki sam rozmiar jak maszyna A oraz maszyna B, czyli w tym wypadku 5*/
	while (koniec != v1.size()) {
		/*Pêtla wewnêtrzna maj¹ca za zadanie znaleŸæ najmniejszy element w obu maszynach i zapisaæ indeks tej maszyny w zmiennej "index"*/
		for (i = v1.begin(); i != v1.end() ; ++i) {
			if (v1[j] < min) {
				min = v1[j];
				index = j;
				czy_maszyna_1 = true;
				czy_maszyna_2 = false;
			}
			if (v2[j] < min) {
				min = v2[j];
				index = j;
				czy_maszyna_1 = false;
				czy_maszyna_2 = true;
			}
			j++;
		}

		/*Gdy pêtla znalaz³a nam najmniejszy element to ustawiamy tam MAX wartosci sugerujace ze dany indeks juz wystapil i zeby nie brac go pod uwage bo jest juz zapisany w liscie wyjœciowej*/
		v1[index] = INT_MAX;
		v2[index] = INT_MAX;
		
		/*Jesli element z II maszyny to na koniec, jesli zas z I maszyny to na poczatek*/
		if (czy_maszyna_2) {
			tab[maxIndeks] = index + 1;
			maxIndeks--;
		}
		else {
			tab[minIndeks] = index + 1;
			minIndeks++;
		} 
		
		min = INT_MAX; //ustawiamy ponownie wartosc min na MAX tak aby znalezc nowy najmniejszy element
		j = 0; //zmienna kontrolujaca przebiegi petli musi byc ponownie wyzerowana aby mozna bylo poprawnie przypisac j¹ do zmiennej index
		index = 0;

		koniec++;
		
	}

	for(int i = 0 ; i < 4 ;++i)
		std::cout << tab[i] << '\t';
	
	double tab1[4] = { 0,0,0,0 };
	double tab2[4] = { 0,0,0,0 };

	
	int nr_indeksu = tab[0];
	if (v3[nr_indeksu] < v4[nr_indeksu]) 
		tab2[0] += v3[nr_indeksu];
	else 
		tab1[0] += v4[nr_indeksu];
	
	

	for (int i = 0; i < v3.size(); ++i)
	{
		int nr_indeksu = tab[i] - 1;
		if (v3[nr_indeksu] < v4[nr_indeksu]) {
			tab1[0] += v3[nr_indeksu];
			tab2[0] += v4[nr_indeksu];
		}
		else {
			tab2[0] += v4[nr_indeksu];
			tab1[0] += v3[nr_indeksu];
		}

	}

	int suma1 = 0;
	int suma2 = 0;

	for (int i = 0; i < v3.size(); ++i)
	{
		suma1 += tab1[i];
		suma2 += tab2[i];
	}
	std::cout << std::endl;
	/*std::cout << suma1 << std::endl;
	std::cout << suma2 << std::endl;
*/
	if (suma1 > suma2)
	{
		
		std::cout <<"Makespan: "<<suma1<<std::endl;
	}
		else
	{
		std::cout << "Makespan: "<<suma2<<std::endl;
	}
	_getch();

}