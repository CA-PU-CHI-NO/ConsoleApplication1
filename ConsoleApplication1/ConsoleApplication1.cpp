#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

// Функция для чтения массива из файла
std::vector<int> readArrayFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<int> array;
    int number;

    while (file >> number) {
        array.push_back(number);
    }

    return array;
}

// Функция для записи массива в файл
void writeArrayToFile(const std::string& filename, const std::vector<int>& array) {
    std::ofstream file(filename);

    for (int number : array) {
        file << number << " ";
    }
}

// Функция для вывода массива на консоль
void printArray(const std::vector<int>& array) {
    for (int number : array) {
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

// Функция для выполнения шейкерной сортировки
void shakerSort(std::vector<int>& array, int& comparisons, int& swaps) {
    int left = 0;
    int right = array.size() - 1;
    bool swapped = false;

    do {
        // Проход слева направо
        swapped = false;
        for (int i = left; i < right; i++) {
            comparisons++;
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                swapped = true;
                swaps++;
            }
        }
        right--;

        // Проход справа налево
        if (!swapped) {
            break;
        }
        swapped = false;
        for (int i = right; i > left; i--) {
            comparisons++;
            if (array[i] < array[i - 1]) {
                std::swap(array[i], array[i - 1]);
                swapped = true;
                swaps++;
            }
        }
        left++;
    } while (swapped);
}

// Функция для выполнения сортировки по убыванию с подсчетом перестановок
void descendingSort(std::vector<int>& array, int& comparisons, int& swaps) {
    std::sort(array.rbegin(), array.rend());
    comparisons = array.size() * (array.size() - 1) / 2;
    swaps = array.size() * (array.size() - 1) / 2;
}

int main() {
    std::string filename = "input.txt";
    setlocale(LC_ALL, "Russian");

    // Чтение массива из файла
    std::vector<int> randomArray = readArrayFromFile(filename);

    std::cout << "Случайный массив: ";
    printArray(randomArray);

    // Сортировка массива по возрастанию
    std::vector<int> ascendingArray = randomArray;
    int comparisons = 0;
    int swaps = 0;
    auto startTime = std::chrono::steady_clock::now();
    shakerSort(ascendingArray, comparisons, swaps);
    auto endTime = std::chrono::steady_clock::now();

    std::cout << "Отсортированный массив (по возрастанию): ";
    printArray(ascendingArray);
    std::cout << "Количество сравнений: " << comparisons << std::endl;
    std::cout << "Количество перестановок: " << swaps << std::endl;
    std::cout << "Затраченное время: " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << " microseconds" << std::endl;
    // Сортировка массива по убыванию с подсчетом перестановок
    std::vector<int> descendingArray = randomArray;
    comparisons = 0;
    swaps = 0;
    startTime = std::chrono::steady_clock::now();
    descendingSort(descendingArray, comparisons, swaps);
    endTime = std::chrono::steady_clock::now();

    std::cout << "Отсортированный массив (по убыванию): ";
    printArray(descendingArray);
    std::cout << "Количество сравнений: " << comparisons << std::endl;
    std::cout << "Количество перестановок: " << swaps << std::endl;
    std::cout << "Затраченное время: " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << " microseconds" << std::endl;

    return 0;
}
