#include "includes/vector.cpp"
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
    void insert(T value) {
        Node<T> *obj = new Node<T>(value);
        tab.push_back(obj);
        if (tab.size() >= 2) {
            bottomToTop(tab.size(), cmp);
        }
    }

    int print() {
        if (tab.get_ptr() == nullptr)
            return 1;

        for (int i = 0; i < tab.size(); i++) {

            std::cout << "[ ID : " << tab[i]->get_id() << ", "
                      << "Data: " << tab[i]->get_data() << " ]"
                      << ", ";
            if (i == 0)
                std::cout << "{ Parent: "
                          << "None"
                          << ", ";
            else
                std::cout << "{ Parent: " << floor(tab[(i - 1) / 2]->get_id()) << ", ";

            if (2 * i + 1 >= tab.size())
                std::cout << "Left: "
                          << "None"
                          << ", ";
            else
                std::cout << "Left: " << tab[2 * i + 1]->get_id() << ", ";

            if (2 * i + 2 >= tab.size())
                std::cout << "Right: "
                          << "None"
                          << " }" << std::endl;
            else
                std::cout << "Right: " << tab[2 * i + 2]->get_id() << " }" << std::endl;
        }
        return 0;
    }

    void clear() {
        tab.clear();
    }

private:
    arr::Vector<Node<T> *> tab;

private:
    void topToBottom(const int n, bool (*cmp)(Node<T> *obj1, Node<T> *obj2)) {

        if (n == tab.size())
            return;

        if (cmp(tab[n - 1], tab[n - 2]))
            return;
        else {
            Node<T> *temp = tab[n - 2];
            tab[n - 2] = tab[n - 1];
            tab[n - 1] = temp;
        }

        topToBottom(n + 1, cmp);
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
};

} // namespace stnd

int main(int argc, char const *argv[]) {

    stnd::BinaryHeap<int> Bh;

    Bh.insert(10);
    Bh.insert(8);
    Bh.insert(31);
    Bh.insert(40);
    Bh.print();
    //Bh.print();

    return 0;
}