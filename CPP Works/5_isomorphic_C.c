/*
Grafların İzomorfizmini Kontrol Eden C Programı:
Bu C programı, verilen iki grafın izomorfik olup olmadığını kontrol eden basit bir örnektir. Program, iki komşuluk matrisini karşılaştırarak 
ve grafiklerin özelliklerini analiz ederek izomorfizmi belirler.

Programın Çalışma Prensibi:
Program, grafların izomorfizmini kontrol etmek için aşağıdaki adımları izler:

İlk olarak, her iki grafın düğüm (node) sayısını karşılaştırır. Eğer düğüm sayıları eşit değilse, graflar izomorfik değildir.

Daha sonra, her iki grafın kenar (edge) sayısını karşılaştırır. Kenar sayıları eşit değilse, graflar izomorfik değildir.

Son olarak, her iki grafın düğümlerinin derecelerini karşılaştırır. Düğümlerin dereceleri eşit değilse, graflar izomorfik değildir.

Eğer yukarıdaki üç koşul da sağlanıyorsa, program grafların izomorfik olduğunu belirtir.
*/

#include<stdio.h>

//Graflardaki düğüm sayıları aşağıda tanımlanır.Tanımlanan değerler aynı zamanda komşuluk matrislerinin boyutunu belirler.
//iki grafın izomorfik olması için bu değerler aynı olmalıdır.
#define V 4 //rapor 2.ekran çıktısı için : V 5 olarka tanımlanmış ve addOneForFirstAdjMatrix(adjMatrix, 0, 4);addOneForFirstAdjMatrix(adjMatrix, 4, 0); fonksiyonları eklenmiştir.
#define V2 4


//kenar karşılaştırılması için kullanılacak
int EdgeCounterForFirstAdjMatrix = 0;
int EdgeCounterForSecondAdjMatrix = 0;


//derece karşılaştırması için kullanılacak
int col, col1, row, row1;


void init(int arr[][V])
//matrisin tüm elemanlarını '0' olarak atayan fonksiyon
//daha sonra ilgili yerler addOne fonksiyonları ile '1' olarak değiştirilecek
{
	int i, j;
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			arr[i][j] = 0;
}


void addOneForFirstAdjMatrix(int arr[][V], int col, int row)
{
	arr[col][row] = 1;
	EdgeCounterForFirstAdjMatrix++;

}

void addOneForSecondAdjMatrix(int arr[][V], int col1, int row1)
{
	arr[col1][row1] = 1;
	EdgeCounterForSecondAdjMatrix++;
}

void notIsomorphic()
{
	printf("\nBU GRAFLAR IZOMORFIK DEGILDIR !\n\n");
}

void printAdjMatrix(int arr[][V])
{
	int i, j;

	for (i = 0; i < V; i++)
	{
		for (j = 0; j < V; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

void printSecAdjMatrix(int arr[][V2])
{
	int i, j;

	for (i = 0; i < V2; i++)
	{
		for (j = 0; j < V2; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}


int main()
{

	int adjMatrix[V][V];
	printf("Ilk Komsuluk Matrisi:\n\n");
	init(adjMatrix);
	//ilk komşuluk matrisinin düzenlemeleri aşağıda yapılmıştır (0 yerine 1 yazılması).
	addOneForFirstAdjMatrix(adjMatrix, 0, 1);
	addOneForFirstAdjMatrix(adjMatrix, 0, 2);
	addOneForFirstAdjMatrix(adjMatrix, 1, 0);
	addOneForFirstAdjMatrix(adjMatrix, 1, 3);
	addOneForFirstAdjMatrix(adjMatrix, 2, 0);
	addOneForFirstAdjMatrix(adjMatrix, 2, 3);
	addOneForFirstAdjMatrix(adjMatrix, 3, 1);
	addOneForFirstAdjMatrix(adjMatrix, 3, 2);
	//rapordaki 3.ekran çıktısını elde etmek için  addOneForFirstAdjMatrix(adjMatrix, 0, 3);	addOneForFirstAdjMatrix(adjMatrix, 3, 0); eklenmelidir
	printAdjMatrix(adjMatrix);

	printf("\n\nIkinci Komsuluk Matrisi:\n\n");
	int adjMatrix2[V2][V2];
	init(adjMatrix2);
	//İkinci komşuluk matrisinin düzenlemeleri aşağıda yapılmıştır (0 yerine 1 yazılması). 
	addOneForSecondAdjMatrix(adjMatrix2, 0, 2);
	addOneForSecondAdjMatrix(adjMatrix2, 0, 3);
	addOneForSecondAdjMatrix(adjMatrix2, 1, 2);
	addOneForSecondAdjMatrix(adjMatrix2, 1, 3);
	addOneForSecondAdjMatrix(adjMatrix2, 2, 0);
	addOneForSecondAdjMatrix(adjMatrix2, 2, 1);
	addOneForSecondAdjMatrix(adjMatrix2, 3, 0);
	addOneForSecondAdjMatrix(adjMatrix2, 3, 1);
	printSecAdjMatrix(adjMatrix2);

	printf("\n\nKomsuluk matrisi verilen iki grafin izomorfik olup olmadigini anlamak icin: \n\n1-) Graflardaki dugum(node) sayilari esit olmalidir\n2-) Graflardaki kenar(edge) sayisi esit olmalidir.\n");
	printf("3-) Her iki grafinda dugumleri ayni derecelere sahip olmalidir.");
	printf("\n\nYukarida verilen komsuluk matrisleri icin:\n");
	//Grafların İzomorfik olup olmadığı burada 3 adımda kontrol edilir.
	//1-) Grafların dugum sayısı esit olmalıdır
	if (V == V2) {
		printf("\nGraflarin dugum sayisi esit.  (1/3)");

		//2-) Grafların kenar sayısı esit olmalıdır
		if (EdgeCounterForFirstAdjMatrix == EdgeCounterForSecondAdjMatrix) {
			printf("\nGraflarin kenar kenar sayisi esit.Yukaridaki graflarin %d kenari vardir.  (2/3)", EdgeCounterForSecondAdjMatrix / 2);
			//her kenar matrisde iki defa gösterildiği için sayac ikiye bölünmelidir.(0,2) ve (2,0) gibi

			//3-) graflardaki düğümlerin dereceleri eşit olmalıdır.
			if (col == col1 && row == row1) {
				printf("\nGraflardaki dugumlarin dereceleri esittir. (3/3)\n");
				printf("\nBU GRAFLAR IZOMORFIKTIR !\n");
			}
			else {
				printf("\nGrafdaki duğumlerin derecesi esit degil.\n");
				notIsomorphic();
			}

		}
		else {
			printf("\nHata:Graflarin kenar sayisi esit degil.\n");
			printf("ilk grafin kenar sayisi:%d ikinci grafin kenar sayisi:%d \n\n", EdgeCounterForFirstAdjMatrix / 2, EdgeCounterForSecondAdjMatrix / 2);

			//her kenar matrisde iki defa gösterildiği için sayac ikiye bölünmelidir.
			notIsomorphic();
		}
	}

	else {
		printf("\nHata:Graflarin dugum sayisi esit degildir.\n");
		notIsomorphic();
	}

	return 0;
}

