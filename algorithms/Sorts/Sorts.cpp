#include "./includes/BinaryHeap.cpp"
#include <iomanip>
#include <iostream>
#include <random>
#include <time.h>

template <typename T>
void BubbleSort(stnd::Vector<T> &vec) {

    for (int i = 0; i < vec.size(); i++)
        for (int j = i + 1; j < vec.size(); j++)
            if (vec[j] < vec[i])
                stnd::Swap<T>(vec[i], vec[j]);
}

template <typename T>
void BucketSort(stnd::Vector<T> &vec) {
    int n = floor(sqrt(vec.size()));
    auto *buckets = new stnd::Vector<T>[n];

    int min = vec[0];
    for (auto &i : vec) {
        if (i < min)
            min = i;
    }

    int max = 0;
    for (auto &i : vec) {
        if (i > max)
            max = i;
    }

    int gap = max / (n - 1);

    for (int i = 0; i < vec.size(); i++) {
        buckets[((vec[i] - min) / gap)].push_back(vec[i]);
    }
    for (int i = 0; i < n; i++)
        BubbleSort(buckets[i]);
    int ind = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < buckets[i].size(); j++) {
            vec[ind] = (buckets[i][j]);
            ind++;
        }
    delete[] buckets;
}

void CountingSort(stnd::Vector<int> &vec) {
    stnd::Vector<int> tab;

    int max = 0;
    for (auto &i : vec) {
        if (i > max)
            max = i;
    }

    for (int i = 0; i < max + 1; i++) {
        tab.push_back(0);
    }

    for (int i = 0; i < vec.size(); i++) {

        tab[vec[i]]++;
    }

    int ind = 0;
    for (int i = 0; i < max + 1; i++) {
        for (int j = 1; j <= tab[i]; j++) {
            vec[ind++] = i;
        }
    }
}

int main(int argc, char const *argv[]) {

    clock_t start1, start2, start3, end1, end2, end3;
    double time1, time2, time3;
    stnd::Vector<int> tab1;
    stnd::Vector<int> tab2;
    stnd::Vector<int> tab3;

    std::random_device random_device;
    std::mt19937_64 engine(random_device());
    std::uniform_int_distribution<uint64_t> dist(1, 1000000);

    for (int i = 0; i < 1000000; i++) {
        tab1.push_back(dist(engine));
        tab2.push_back(tab1[i]);
        tab3.push_back(tab2[i]);
    }

    start1 = clock();
    CountingSort(tab1);
    end1 = clock();

    time1 = double(end1 - start1) / double(CLOCKS_PER_SEC);

    start2 = clock();
    BucketSort(tab2);
    end2 = clock();

    time2 = double(end2 - start2) / double(CLOCKS_PER_SEC);

    start3 = clock();
    cnt::BinaryHeap<int> test(tab3);
    test.sort(tab3);
    end3 = clock();

    time3 = double(end3 - start3) / double(CLOCKS_PER_SEC);

    std::cout << "Counting sort: " << time1 << std::setprecision(5) << std::endl;
    std::cout << "Bucket sort: " << time2 << std::setprecision(5) << std::endl;
    std::cout << "Heap sort: " << time3 << std::setprecision(5) << std::endl;

    return 0;
}

// odmierzanie czasu
