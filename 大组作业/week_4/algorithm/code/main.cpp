#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <cmath>
#include <string>
#include <climits>

using namespace std;
using namespace std::chrono;

// 插入排序类
class InsertSort {
public:
    static void sort(vector<int>& arr) {
        for (int i = 1; i < arr.size(); ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
};

// 归并排序类
class MergeSort {
public:
    static void sort(vector<int>& arr) {
        if (arr.size() > 1) {
            int mid = arr.size() / 2;
            vector<int> left(arr.begin(), arr.begin() + mid);
            vector<int> right(arr.begin() + mid, arr.end());

            MergeSort::sort(left);
            MergeSort::sort(right);

            merge(arr, left, right);
        }
    }

private:
    static void merge(vector<int>& arr, const vector<int>& left, const vector<int>& right) {
        int i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                arr[k++] = left[i++];
            }
            else {
                arr[k++] = right[j++];
            }
        }
        while (i < left.size()) {
            arr[k++] = left[i++];
        }
        while (j < right.size()) {
            arr[k++] = right[j++];
        }
    }
};

// 快速排序类
class QuickSort {
public:
    static void sort(vector<int>& arr) {
        quickSort(arr, 0, arr.size() - 1);
    }

private:
    static void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

// 计数排序类
class CountSort {
public:
    static void sort(vector<int>& arr) {
        if (arr.empty()) return;

        int max_val = *max_element(arr.begin(), arr.end());
        int min_val = *min_element(arr.begin(), arr.end());
        int range = max_val - min_val + 1;

        vector<int> count(range, 0);
        vector<int> output(arr.size());

        for (int num : arr) {
            count[num - min_val]++;
        }

        for (int i = 1; i < range; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = arr.size() - 1; i >= 0; --i) {
            output[count[arr[i] - min_val] - 1] = arr[i];
            count[arr[i] - min_val]--;
        }

        arr = output;
    }
};

// 基数计数排序类
class RadixCountSort {
public:
    static void sort(vector<int>& arr) {
        if (arr.empty()) return;

        int max_val = *max_element(arr.begin(), arr.end());

        for (int exp = 1; max_val / exp > 0; exp *= 10) {
            countingSort(arr, exp);
        }
    }

private:
    static void countingSort(vector<int>& arr, int exp) {
        vector<int> output(arr.size());
        vector<int> count(10, 0);

        for (int num : arr) {
            count[(num / exp) % 10]++;
        }

        for (int i = 1; i < 10; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = arr.size() - 1; i >= 0; --i) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        arr = output;
    }
};

// 排序测试工具类
class SortTester {
public:
    static vector<int> generateTestData(int size, int min_val = 0, int max_val = 10000) {
        vector<int> data(size);
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min_val, max_val);

        for (int& num : data) {
            num = dis(gen);
        }
        return data;
    }

    static void saveToFile(const vector<int>& data, const string& filename) {
        ofstream outFile(filename);
        for (int num : data) {
            outFile << num << "\n";
        }
        outFile.close();
    }

    static vector<int> loadFromFile(const string& filename) {
        vector<int> data;
        ifstream inFile(filename);
        int num;

        while (inFile >> num) {
            data.push_back(num);
        }
        inFile.close();
        return data;
    }

    static double testSorting(void (*sortFunc)(vector<int>&), vector<int> data) {
        auto start = high_resolution_clock::now();
        sortFunc(data);
        auto end = high_resolution_clock::now();
        duration<double> elapsed = end - start;
        return elapsed.count();
    }

    static void runLargeDataTests() {
        vector<int> sizes = { 10000, 50000, 200000 };
        vector<pair<string, void (*)(vector<int>&)>> sorters = {
            {"InsertSort", InsertSort::sort},
            {"MergeSort", MergeSort::sort},
            {"QuickSort", QuickSort::sort},
            {"CountSort", CountSort::sort},
            {"RadixCountSort", RadixCountSort::sort}
        };

        cout << "大型数据集排序测试:\n";
        cout << "算法         10000数据     50000数据     200000数据\n";

        for (const auto& sorter : sorters) {
            cout << sorter.first;
            for (int size : sizes) {
                vector<int> data = generateTestData(size);
                double time_taken = testSorting(sorter.second, data);
                printf("     %.4fs  ", time_taken);
            }
            cout << "\n";
        }
    }

    static void runSmallDataRepeatedTests() {
        vector<pair<string, void (*)(vector<int>&)>> sorters = {
            {"InsertSort", InsertSort::sort},
            {"MergeSort", MergeSort::sort},
            {"QuickSort", QuickSort::sort},
            {"CountSort", CountSort::sort},
            {"RadixCountSort", RadixCountSort::sort}
        };

        vector<int> small_data = generateTestData(100);
        const int iterations = 100000;

        cout << "\n小型数据集重复排序测试 (100数据 × 100k次):\n";
        cout << "算法         总用时\n";

        for (const auto& sorter : sorters) {
            auto start = high_resolution_clock::now();
            for (int i = 0; i < iterations; ++i) {
                vector<int> data_copy = small_data;
                sorter.second(data_copy);
            }
            auto end = high_resolution_clock::now();
            duration<double> elapsed = end - start;
            printf("%-12s %.4fs\n", sorter.first.c_str(), elapsed.count());
        }
    }
};



int main() {
    // 生成测试数据并保存到文件
    vector<int> test_data = SortTester::generateTestData(1000);
    SortTester::saveToFile(test_data, "test_data.txt");

    // 从文件加载数据并排序
    vector<int> loaded_data = SortTester::loadFromFile("test_data.txt");
    cout << "\n从文件加载的数据前10个: ";
    for (int i = 0; i < 10 && i < loaded_data.size(); ++i) {
        cout << loaded_data[i] << " ";
    }
    cout << "\n";

    // 测试各种排序算法
    SortTester::runLargeDataTests();
    SortTester::runSmallDataRepeatedTests();

    return 0;
}