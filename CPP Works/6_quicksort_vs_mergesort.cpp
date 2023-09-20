#include <iostream>
#include <vector>

// MergeSort Algoritması
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// QuickSort Algoritması
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    std::vector<int> numbers;

    std::cout << "Kaç tane sayı gireceksiniz? ";
    int count;
    std::cin >> count;

    std::cout << "Lütfen " << count << " sayı girin:\n";
    for (int i = 0; i < count; ++i) {
        int num;
        std::cin >> num;
        numbers.push_back(num);
    }

    // MergeSort kullanarak sıralama
    mergeSort(numbers, 0, count - 1);
    std::cout << "MergeSort ile sıralanmış dizi: ";
    for (int i = 0; i < count; ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    // Diziyi yeniden sıfırlayın
    numbers.clear();
    std::cout << "Lütfen " << count << " sayıyı tekrar girin:\n";
    for (int i = 0; i < count; ++i) {
        int num;
        std::cin >> num;
        numbers.push_back(num);
    }

    // QuickSort kullanarak sıralama
    quickSort(numbers, 0, count - 1);
    std::cout << "QuickSort ile sıralanmış dizi: ";
    for (int i = 0; i < count; ++i) {
        std::cout << numbers[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
/*

# Sıralama Algoritmaları ile Sıralama Programı:
Bu kod, Merge Sort ve Quick Sort sıralama algoritmalarını içerir ve her iki algoritmanın çalışma sürelerini ölçerek karşılaştırır. 
Kullanıcıdan bir dizi sayı girişi alır ve sonuçları ekrana yazar. Süre ölçümü için <chrono> kullanır.

Sıralama Algoritmaları ve Karmaşıklıkları:
Programda kullanılan iki sıralama algoritması şunlardır:

- **MergeSort**: Zaman karmaşıklığı O(n log n) olan etkili bir sıralama algoritmasıdır.
- **QuickSort**: En iyi durumda O(n log n) zaman karmaşıklığına sahiptir, ancak kötü durumda O(n^2) olabilir.

*/