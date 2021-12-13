#include "../../Vector/Vector.cpp"
#include "../../swap/swap.cpp"
#include <iostream>
#include <math.h>

template <class T>
class Node {
public:
    Node() {}
    Node(T data__) {
        id = rand() % 150;
        data = data__;
    }
    int get_id() const {
        return id;
    }
    T get_data() const {
        return data;
    }
    void set_data(T data_) {
        data = data_;
    }

private:
    int id;
    T data;
};
template <class T>
bool cmp(Node<T> *obj1, Node<T> *obj2) {
    return obj1->get_data() >= obj2->get_data();
}

namespace cnt {

template <class T>
class BinaryHeap {

public:
    BinaryHeap(stnd::Vector<T> &_tab) {
        for (int i = 0; i < _tab.size(); i++) {

            HeapToTop(i, _tab, _tab.size());
        }
    }

    int print() {
        if (tab.get_ptr() == nullptr)
            return 1;

        for (int i = 0; i < tab.size(); i++) {

            std::cout << "[ ID : " << tab[i] << " ]"
                      << ", ";
            if (i == 0)
                std::cout << "{ Parent: "
                          << "None"
                          << ", ";
            else
                std::cout << "{ Parent: " << tab[floor((i - 1) / 2)] << ", ";

            if (2 * i + 1 >= tab.size())
                std::cout << "Left: "
                          << "None"
                          << ", ";
            else
                std::cout << "Left: " << tab[2 * i + 1] << ", ";

            if (2 * i + 2 >= tab.size())
                std::cout << "Right: "
                          << "None"
                          << " }" << std::endl;
            else
                std::cout << "Right: " << tab[2 * i + 2] << " }" << std::endl;
        }
        return 0;
    }

    void clear() {
        tab.clear();
    }
    void sort(stnd::Vector<T> &_tab) {

        for (int i = _tab.size(); i > 0; i--) {
            stnd::Swap<T>(_tab[0], _tab[i - 1]);
            HeapToBottom(_tab, 0, i - 1);
        }
    }

private:
    stnd::Vector<T>
        tab;

private:
    void HeapToTop(const int i, stnd::Vector<T> &_tab, const int n) {

        if (n == 0 || i <= 0)
            return;

        int dziecko = i;
        int rodzic = (dziecko - 1) / 2;
        if (_tab[dziecko] > _tab[rodzic]) {
            stnd::Swap<T>(_tab[dziecko], _tab[rodzic]);
            HeapToTop(rodzic, _tab, n - 1);
        }
    }

    void HeapToBottom(stnd::Vector<T> &_tab, int n, int size) {

        if (2 * n + 1 >= size)
            return;

        int left = 2 * n + 1 == size ? 0 : _tab[2 * n + 1];
        int right = 2 * n + 2 == size ? 0 : _tab[2 * n + 2];

        if (left > right) {
            if (_tab[n] > _tab[2 * n + 1])
                return;
            stnd::Swap<T>(_tab[n], _tab[2 * n + 1]);
            HeapToBottom(_tab, 2 * n + 1, size);

        } else {
            if (_tab[n] > _tab[2 * n + 2])
                return;
            stnd::Swap<T>(_tab[n], _tab[2 * n + 2]);
            HeapToBottom(_tab, 2 * n + 2, size);
        }
    }
};
} // namespace cnt
