#include "Prj3header.h"

using namespace std;



int* generateRandomNumbers (const int maxLimit);

void mergeSort (int* numberArray, const int left, const int right);
void merge (int* numberArray, const int left, const int middle, const int right);

void printNumbers (const int* numberArray);

void startWithTwoThread (int* numberArray, int length);
void startWithThreeThread (int* numberArray, int length);



#define SAMPLE_LENGTH       2000000
#define RANDOM_RANGE_MAX    100000





int main() {
	int* numbers_A;
    int* numbers_B;


    numbers_A = generateRandomNumbers(RANDOM_RANGE_MAX); // 0 ve istenilen değer arasında sayılar üretiliyor.

    numbers_B = new int[SAMPLE_LENGTH];
    for (int i = 0; i < SAMPLE_LENGTH; i++) // Aynı veriler yeni bir diziye kopyalanıyor ki aynı adres üzerinden sıralanmış diziye ulaşılıp süre konusunda yanılmayalım.
        numbers_B[i] = numbers_A[i];

    cout << "Please press a button on the keyboard to start the process with 2 threads.";
    getchar(); cout << endl;

    startWithTwoThread(numbers_A, SAMPLE_LENGTH); // 2 adet thread ile sıralama yapılır.

    cout << endl << endl << "--------------------------------------------------------------------------" << endl << endl << endl;

    cout << "Please press a button on the keyboard to start the process with 3 threads.";
    getchar(); cout << endl;

    startWithThreeThread(numbers_B, SAMPLE_LENGTH); // 3 adet thread ile sıralama yapılır.

	
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


// 2 tane thread ile işlem yapma.
void startWithTwoThread (int* numberArray, int length) {
    int mainLeft;
    int mainMiddle;
    int mainRight;

    clock_t t1; // Başlangıç zamanı için.
    clock_t t2; // Bitiş zamanı için.



    mainLeft    = 0; // Dizinin başlangıcı indexi.
    mainMiddle  = (length / 2) - 1; // Dizinin orta nokta indexi.
    mainRight   = length - 1; // Dizinin son indexi. 

	printNumbers(numberArray); // Array sırasız halde yazdırılıyor.

    t1 = clock(); // Sıralama başlamadan zaman alınıyor.

	thread threadMergeSort1(mergeSort, numberArray, mainLeft, mainMiddle); // Dizinin ilk yarısını sıralamak için kullanılan thread.
    thread threadMergeSort2(mergeSort, numberArray, mainMiddle + 1, mainRight); // Dizinin ikinci yarısını sıralamak için kullanılan thread.

	threadMergeSort1.join(); // Thread bekleniyor.
    threadMergeSort2.join(); // Thread bekleniyor.

    merge(numberArray, mainLeft, mainMiddle, mainRight); // Dizinin ilk ve ikinci yarısı birbiri arasında sıralanıyor.

    t2 = clock(); // Sıralama bitince zaman alınıyor.

	printNumbers(numberArray); // Array sıralı halde yazdırılıyor.

    cout << endl << "ARRAY LENGTH: " << length << endl; // Arrayin eleman sayısı yazdırılıyor.

    cout << "Sorting finished. Time taken: " << (t2 - t1) / (double)CLOCKS_PER_SEC << endl; // Toplam geçen süre yazdırılıyor.
}


// 2 tane thread ile işlem yapma.
void startWithThreeThread (int* numberArray, int length) {
    int eachArrayLenght;
    int mod;

    int leftStart;
    int leftEnd;
    int middleStart;
    int middleEnd;
    int rightStart;
    int rightEnd;

    clock_t t1; // Başlangıç zamanı için.
    clock_t t2; // Bitiş zamanı için.



    eachArrayLenght = length / 3; // 3 tane threade böleceğim için, arrayin her bir parçasının kaç elemanlı olacağını hesapalr.
    mod             = length % 3; // Tam bölünmediği durumlarda son kısma eklenmek üzere mod.

    leftStart   = 0;                                        // Dizinin ilk parçası için başlangıç indexi.
    leftEnd     = leftStart + (eachArrayLenght - 1);        // Dizinin ilk parçası için bitiş indexi.
    middleStart = leftEnd + 1;                              // Dizinin ortanca parçası için başlangıç indexi.
    middleEnd   = middleStart + (eachArrayLenght - 1);      // Dizinin ortanca parçası için bitiş indexi.
    rightStart  = middleEnd + 1;                            // Dizinin son parçası için başlangıç indexi.
    rightEnd    = rightStart + (eachArrayLenght - 1) + mod; // Dizinin son parçası için bitiş indexi.

	printNumbers(numberArray); // Array sırasız halde yazdırılıyor.

    t1 = clock(); // Sıralama başlamadan zaman alınıyor.

	thread threadMergeSort1(mergeSort, numberArray, leftStart, leftEnd);        // Dizinin ilk kısmını sıralamak için kullanılan thread.
    thread threadMergeSort2(mergeSort, numberArray, middleStart, middleEnd);    // Dizinin ikinci kısmını sıralamak için kullanılan thread.
    thread threadMergeSort3(mergeSort, numberArray, rightStart, rightEnd);      // Dizinin üçüncü kısmını sıralamak için kullanılan thread.

	threadMergeSort1.join(); // İlk kısmın sıralanmasının bitmesi bekleniyor.
    threadMergeSort2.join(); // İkinci kısmın sıralanmasının bitmesi bekleniyor.

    merge(numberArray, leftStart, leftEnd, middleEnd); // Dizinin ilk ve ikinci kısmı birbiri arasında sıralanıyor.

    threadMergeSort3.join(); // Üçüncü kısmın sıralanmasının bitmesi bekleniyor.

    merge(numberArray, leftStart, middleEnd, rightEnd); // Dizinin ilk ve ikinci kısmının kendi arasındaki sıralı hali ile üçüncü kısmı birbiri arasında sıralanıyor.

    t2 = clock(); // Sıralama bitince zaman alınıyor.

	printNumbers(numberArray); // Array sıralı halde yazdırılıyor.

    cout << endl << "ARRAY LENGTH: " << length << endl; // Arrayin eleman sayısı yazdırılıyor.

    cout << "Sorting finished. Time taken: " << (t2 - t1) / (double)CLOCKS_PER_SEC << endl; // Toplam geçen süre yazdırılıyor.
}