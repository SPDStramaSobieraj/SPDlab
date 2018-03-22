# SPDlab
Sprawozdanie z laboratorium nr 1.

Flowshop:
Przygotowano trzy zestawy testowe dla wariantu z dwiema maszynami:
I		II		III
11  8		4   8		5  3
3   5   	9   1		6  4
10  3   	3   4		2  6 	
3   5   	10  2		3  10
5   7		6   7		9  8
		2   5		7  5
		1   12		5  11
		5   6		8  4
				5  4
				3  8

Metodą przeglądu zupełnego wygenerowano wszystkie możliwe kombinacje ułożenia zadań, dla zestawu 5 prac uzyskano 5!, czyli 120 możliwości,
dla zestawu 8 prac 8!, czyli 40320 możliwości, a dla zestawu 10 zadań otrzymano 10!, czyli 3628800 możliwości.
Dzięki temu można zauważyć, że najlepszy makespan uzyskały:
Dla zestawu I: Kombinacje z wynikiem 35
Dla zestawu II: Kombinacje z wynikiem 46
Dla zestawu III: Kombinacje z wynikiem 66

Algorytm Jonhsona wyznaczył następujące kolejności zadań:
Dla zestawu I: 2 4 5 1 3
Dla zestawu II: 7 6 3 1 8 5 4 2
Dla zestawu III: 3 4 10 9 7 5 6 8 2 1

Wyniki otrzymane za pomocą obu metod się pokrywają, ponieważ kombinacje wyznaczone przez Algorytm Johnsona są jednymi z tych, które osiągały najniższy makespan.
Algorytm Johnsona jest jednak korzystniejszym rozwiązaniem, ponieważ przy dużej ilości zadań jak np. w zestawie III, wygenerowanie wszystkich permutacji zajmuje dużo czasu.


Problem RPQ:
Przygotowano zestawy testowe składające się z 6, 10, 20, 50, 100 i 200 prac do wykonania.
Korzystając z metody przeglądu zupełnego generujemy wszystkie możliwe kombinacje kolejności zadań.
Pozwala to na porównanie i wybór najkorzystniejszego rozwiązania. Dla podanych zestawów testowych otrzymano następujące wartości makespan:
Dla zestawu 6 prac - 32
Dla zestawu 10 prac - 927
 

Metoda SortR
Metoda SortR wyznacza rozwiązanie sortując czasy przygotowania zadania.
Za pomocą tej metody uzyskano następujące wyniki
Dla zestawu 6 prac - 34
Dla zestawu 10 prac - 599
Dla zestawu 20 prac - 1103
Dla zestawu 50 prac - 1790
Dla zestawu 100 prac - 3789
Dla zestawu 200 prac - 7703
Dla zestawu 500 prac - 13952

Zestawienie optymalnych wyników dla powyższych zestawów:
6 prac - 32
10 prac - 641
20 prac - 1267
50 prac - 1492
100 prac - 3070
200 prac - 6398
500 prac - 14785

Przegląd Zupełny pozwala na wgląd do wszystkich możliwych rozwiązań, jednak przy dużych sporych wejściowych zajmuje dużo czasu.
Metoda SortR nie zawsze podaje nam rozwiązanie o najlepszym makespan, jednak czas jej wykonywania jest o wiele krótszy niż w przypadku przeglądu zupełnego.

