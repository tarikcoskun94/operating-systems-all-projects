#include "Prj3header.h"

using namespace std;



int* generateRandomNumbers (const int maxLimit);
void mergeSort (int* numberArray, const int left, const int right);
void merge (int* numberArray, const int left, const int middle, const int right);
void printNumbers (const int* numberArray);



#define SAMPLE_LENGTH       2000000
#define RANDOM_RANGE_MAX    100000





int main() {
	int* numbers;

    clock_t t1; // Başlangıç zamanı için.
    clock_t t2; // Bitiş zamanı için.



	numbers = generateRandomNumbers(RANDOM_RANGE_MAX); // 0 ve istenilen değer arasında sayılar üretiliyor.

	printNumbers(numbers); // Array sırasız halde yazdırılıyor.

    t1 = clock(); // Sıralama başlamadan zaman alınıyor.

	thread threadMergeSort(mergeSort, numbers, 0, SAMPLE_LENGTH - 1); // Bir adet thread (varsayılan main threadi saymazsak) ile merge işlemi yapılıyor.

	threadMergeSort.join(); // Thread bekleniyor.

    t2 = clock(); // Sıralama bitince zaman alınıyor.

	printNumbers(numbers); // Array sıralı halde yazdırılıyor.

    cout << endl << "ARRAY LENGTH: " << SAMPLE_LENGTH << endl; // Arrayin eleman sayısı yazdırılıyor.

    cout << "Sorting finished. Time taken: " << (t2 - t1) / (double)CLOCKS_PER_SEC << endl; // Toplam geçen süre yazdırılıyor.


	
	return 0;
}





// Rastgele sayı üretici.
int* generateRandomNumbers (const int maxLimit) {
	int number;
	int* numbers = new int[SAMPLE_LENGTH]; // İstenilen eleman sayısına göre sayı arrayi yapılandırılıyor.



	srand(time(0)); // Rastgelelik zamana bağımlı yapılıyor.

	for (int i = 0; i < SAMPLE_LENGTH; i++) { // Maximum limite göre sayılar üretilip diziye dolduruluyor.
		number = (rand() % maxLimit) + 1;
		numbers[i] = number;
	}



	return numbers;
}


// Merge sort ana fonksiyonu.
void mergeSort (int* numberArray, const int left, const int right) {
	int middle;



    if (left < right) {
        middle = left + (right - left) / 2; // Orta nokta hesabı.
  
        mergeSort(numberArray, left, middle); // Sol taraf divide işlemi.
        mergeSort(numberArray, middle + 1, right); // Sağ taraf divide işlemi.
  
        merge(numberArray, left, middle, right); // Conquer aşaması.

    } 
}


// Merge sort için conquer aşaması fonksiyonu.
void merge (int* numberArray, const int left, const int middle, const int right) {
	int i;
	int j;
	int k;

    int n1 = middle - left + 1; 
    int n2 = right - middle; 
  
    int L[n1]; // Sol taraf için geçici array.
	int R[n2]; // Sağ taraf için geçici array.
  


    for (i = 0; i < n1; i++) // Sol tarafa veriler kopyalanıyor.
        L[i] = numberArray[left + i]; 
    for (j = 0; j < n2; j++) // Sağ tarafa veriler kopyalanıyor.
        R[j] = numberArray[middle + 1 + j]; 
  
    i = 0;
    j = 0;
    k = left; // Alt arrayın başlangıç indexini tutar.
    while (i < n1 && j < n2) // Birleştiriliyor.
    { 
        if (L[i] <= R[j]) 
        { 
            numberArray[k] = L[i]; 
            i++; 
        } 
        else
        { 
            numberArray[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 

    while (i < n1) // En son solda kalanlar varsa kopyalanıyor.
    { 
        numberArray[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) // En son sağda kalanlar varsa kopyalanıyor.
    { 
        numberArray[k] = R[j]; 
        j++; 
        k++; 
    } 
}


// Dizi yazdırma fonksiyonu.
void printNumbers (const int* numberArray) {
	cout << "[";
	for (int i = 0; i < SAMPLE_LENGTH; i++) {
		cout << numberArray[i];
		if (i != SAMPLE_LENGTH - 1)
			cout << ", ";
	}
	cout << "]" << endl;
}