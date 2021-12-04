#include <iostream>

namespace arr {
template <class T>
class Vector {

public:
    T &operator[](size_t id) {
        if (id >= size_) {
            std::cout << "Array index out of range\n\n";
            throw "Array index out of range";
        }

        return tabs[id];
    }
    void resize() {
        T *tab_new = new T[capacity_ * 2];
        for (size_t i = 0; i < capacity_ / 2; i++) {
            tab_new[i] = tabs[i];
        }
        delete[] tabs;
        tabs = tab_new;
        capacity_ *= 2;
    }

    void push_back(T obj) {
        if (capacity_ == 0) {
            tabs = new T[1];
            tabs[capacity_] = obj;
            size_++;
            capacity_++;
            return;
        }
        if (size_ == capacity_)
            resize();

        tabs[size_] = obj;
        size_++;
    }

    ~Vector() {
        if (tabs != nullptr) {
            delete[] tabs;
        }
    }

    void clear() {
        if (tabs != nullptr) {
            delete[] tabs;
            tabs = nullptr;
            size_ = 0;
        }
    }
    size_t size() {
        return size_;
    }
    size_t capacity() const {

        return capacity_;
    }
    void set_size(size_t size) {
        size_ = size;
    }
    T *get_ptr() {
        return tabs;
    }

private:
    T *tabs{nullptr};
    size_t size_{0};
    size_t capacity_{0};
};
} // namespace arr
