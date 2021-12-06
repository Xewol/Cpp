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

namespace stnd {

template <class T>
class BinaryHeap {

public:
    BinaryHeap(arr::Vector<T> &_tab) {

        HeapToTop(_tab, _tab.size());
    }

    void insert(T value) {
        Node<T> *obj = new Node<T>(value);
        tab.push_back(obj);
        if (tab.size() >= 2) {
            bottomToTop(tab.size(), cmp);
        }
    }
    void pop_front() {
        const int numb = tab.size();
        delete tab[0];
        tab[0] = tab[numb - 1];
        tab.set_size(tab.size() - 1);
        topToBottom(0, cmp);
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
    void sort(arr::Vector<T> &_tab, int n) {

        for (int i = n; i > 0; i--) {
            stnd::Swap(_tab[0], _tab[i - 1]);
            HeapToBottom(_tab, 0, i - 1);
        }
    }

private:
    arr::Vector<T>
        tab;

private:
    void topToBottom(const int n, bool (*cmp)(Node<T> *obj1, Node<T> *obj2)) {

        if (n >= tab.size() - 2)
            return;

        //mniejszy od obu
        if (!cmp(tab[n], tab[2 * n + 1]) && !cmp(tab[n], tab[2 * n + 2])) {
            Node<T> *left = tab[2 * n + 1];
            Node<T> *right = tab[2 * n + 2];
            Node<T> *temp;
            if (cmp(right, left)) {
                temp = right;
                tab[2 * n + 2] = tab[n];
                tab[n] = temp;
                topToBottom(n + 2, cmp);

            } else {
                temp = left;
                tab[2 * n + 1] = tab[n];
                tab[n] = temp;

                topToBottom(n + 1, cmp);
            }
        } else
            return;
    }

    void bottomToTop(const int n, bool (*cmp)(Node<T> *obj1, Node<T> *obj2)) {

        if (n == 1)
            return;

        if (cmp(tab[n - 1], tab[n - 2])) {

            Node<T> *temp = tab[n - 2];
            tab[n - 2] = tab[n - 1];
            tab[n - 1] = temp;

        } else
            return;

        bottomToTop(n - 1, cmp);
    }

    void HeapToTop(arr::Vector<T> &_tab, const int n) {

        if (n == 0)
            return;
        int dziecko = _tab[n - 1];
        int rodzic = _tab[floor((n - 2) / 2)];
        if (dziecko > rodzic) {
            stnd::Swap(_tab[n - 1], _tab[floor((n - 2) / 2)]);
        }
        HeapToTop(_tab, n - 1);
    }

    void HeapToBottom(arr::Vector<T> &_tab, int n, int size) {

        if (2 * n + 1 >= size)
            return;

        int left = 2 * n + 1 == size ? 0 : _tab[2 * n + 1];
        int right = 2 * n + 2 == size ? 0 : _tab[2 * n + 2];

        if (left > right) {
            if (_tab[n] > _tab[2 * n + 1])
                return;
            stnd::Swap(_tab[n], _tab[2 * n + 1]);
            HeapToBottom(_tab, 2 * n + 1, size);

        } else {
            if (_tab[n] > _tab[2 * n + 2])
                return;
            stnd::Swap(_tab[n], _tab[2 * n + 2]);
            HeapToBottom(_tab, 2 * n + 2, size);
        }
    }
};
} // namespace stnd
