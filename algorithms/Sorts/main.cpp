#include "./includes/BinaryHeap.cpp"
#include <iostream>

template <class T>
void CountingSort(arr::Vector<T> &tab) {

    int *numbs[tab.size()];
    int *counts[tab.size()];
    for (int i = 0; i < tab.size(); i++) {
        counts[i] = 0;
    }
    for (int j = 0; j < tab.size(); j++) {
        numbs[j] = &tab[j];
    }

    for (int i = 0; i < tab.size(); i++) {
        std::cout << "[ " << counts[i] << ", " << numbs[i] << "]";
    }
}

int main(int argc, char const *argv[]) {

    arr::Vector<int> tab{9, 7, 4, 3, 6, 5, 1, 2, 8, 11};
    std::cout << "Przed sortowaniem:\n";
    for (auto &i : tab) {
        std::cout << i << " ";
    }

    stnd::BinaryHeap<int> BinaryHeap(tab);

    std::cout << "\n\nPo Kopcowaniu:\n";
    for (auto &i : tab) {
        std::cout << i << " ";
    }
    BinaryHeap.sort(tab, tab.size());

    std::cout << "\n\nPo Sortowaniu:\n";
    for (auto &i : tab) {
        std::cout << i << " ";
    }

    return 0;
}
