#include <iostream>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;


class RPQ
{
	
public:
	double r, p, q; //przygotowanie, wykonanie, dostarczenie
	RPQ(double p, double r, double q);
	RPQ() { p = r = q = 0; }
};

RPQ::RPQ(double r, double p, double q) : r(r), p(p), q(q)
{

}


int main()
{
	srand(time(NULL));
	std::vector<RPQ> v1;
	std::vector<RPQ>::iterator i; //Iterator dla pêtli
	
	
	
	for (int i = 0; i < 5; i++)
	{
		srand(time(NULL));
		double przygotowanie = 1 + rand() % 5;
		double wykonanie = 6 + rand() % 5;
		double dostarczenie = 1 + rand() % 5;
		RPQ Dane(przygotowanie, wykonanie, dostarczenie);
		v1.push_back(Dane);
		Sleep(1000);
	}

	for (int i = 0  ; i < v1.size() ; i++)
		std::cout << v1[i].r << "   " << v1[i].p << "   " << v1[i].q << std::endl;

	std::cout << std::endl << std::endl;
	
	
	int k = v1.size();
	bool zamiana;

	do {
		zamiana = false;
		for (int i = 0; i < k - 1; ++i)
		{
			if (v1[i].r > v1[i + 1].r)
			{
				swap(v1[i].r, v1[i+1].r);
				swap(v1[i].p, v1[i + 1].p);
				swap(v1[i].q, v1[i + 1].q);
				zamiana = true;
			}

		}

		} while (zamiana);


		double S[5];
		double C[5];
		for (int i = 0; i < 5; ++i) {
			S[i] = 0;
			C[i] = 0;
		}
		double Cmax = 0;


		
		for (int i = 0; i < v1.size(); i++)
			std::cout << v1[i].r << "   " << v1[i].p << "   " << v1[i].q << std::endl;

		S[0] = v1[0].r;

		for (int i = 0; i < 4; ++i)
		{
			C[i] = S[i] + v1[i].p;
			S[i + 1] = v1[i + 1].r + C[i];
		}

		for (int i = 0; i < 5; ++i)
			Cmax += (C[i] + v1[i].q);
	
		std::cout << std::endl;
		std::cout << Cmax;

	
	

	
	
	
	_getch();


}