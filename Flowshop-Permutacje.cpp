#include <iostream>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <climits>

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


int main()
{
	std::vector<double> v1; //maszyna A
	std::vector<double> v2; //maszyna B
	std::vector<int> wynikowy;
	std::vector<double>v3 = v1;
	std::vector<double>v4 = v2;
	double makeSpan = 0.0;

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
	v1.push_back(8);

	/*£adujemy do maszyny 2*/
	v2.push_back(8);
	v2.push_back(7);
	v2.push_back(9);
	v2.push_back(12);
	v2.push_back(8);
	
	for (int i = 0; i < v1.size(); ++i)
		wynikowy.push_back(i+1);

	std::vector<std::vector<int> > permutacje = PermutacjeBezPowtorzen(wynikowy);

	for (std::vector<std::vector<int> >::size_type i = 0; i < permutacje.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j < permutacje[i].size(); j++)
		{
			std::cout << permutacje[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	

	
	_getch();

}