#include <iostream>
#include <math.h>

namespace arr {
template <class T>
class Vector {

public:
    Vector(std::initializer_list<T> list)
        : tabs(new T[list.size()]) {
        std::copy(list.begin(), list.end(), tabs);
        size_ = list.size();
        float capacityHandler = log2(size_);
        capacity_ = pow(2, ceil(capacityHandler));
    }
    Vector(){};
    T &operator[](size_t id) {
        if (id >= size_) {
            throw std::out_of_range("Out of Range");
        }

        return tabs[id];
    }
    const T *begin() const { return tabs ? tabs : nullptr; }
    const T *end() const { return &tabs[size_]; }

    void resize() {
        T *tab_new = new T[capacity_ * 2];
        for (size_t i = 0; i < capacity_; i++) {
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
