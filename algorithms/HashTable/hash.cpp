#include <iostream>
#include "includes/vector.cpp"
#include <math.h>
#include <time.h>

namespace stnd
{

    template <class K, class T>
    struct Pair
    {

        Pair(){};
        K key;
        T data;
        Pair(K _key, T _value)
        {
            key = _key;
            data = _value;
        }

        friend std::ostream &operator<<(std::ostream &out, const Pair *pr)
        {

            out << pr->key << ": " << pr->data;

            return out;
        }
    };

    template <class K, class T>
    class Map
    {

    public:
        Map()
        {
            _array = new arr::Vector<Pair<K, T> *>[capacity];
        }

        ~Map()
        {
            if (_array != nullptr)
                delete[] _array;
        }

        int insert(K key, T value)
        {
            Pair<K, T> *test = find(key);
            if (test != nullptr)
            {
                if (test->data == value && test->key == key)
                    return 1;

                else if (test != nullptr && test->key == key)
                {
                    test->data = value;
                    return 0;
                }
            }

            int index = hash_index(value);
            Pair<K, T> *node = new Pair<K, T>(key, value);
            _array[index].push_back(node);
            size++;
            if (size == capacity * 0.75)
            {
                rehash();
            }

            return 0;
        }

        arr::Vector<Pair<K, T>> &operator[](size_t id)
        {
            if (id >= capacity)
            {
                std::cout << "Array index out of range\n\n";
                throw "Array index out of range";
            }

            return _array[id];
        }

        void print()
        {

            std::cout << "Ilość elementów: " << size << "\n";
            std::cout << "Pojemność tablicy: " << capacity << "\n\n";
            int empty = 0;
            for (int i = 0; i < capacity; i++)
            {
                if (_array[i].size() > 0)
                {
                    std::cout << i << ": ";

                    for (int j = 0; j < _array[i].size(); j++)
                    {

                        std::cout << "{" << _array[i][j] << "}";
                        if (j < _array[i].size() - 1)
                            std::cout << ", ";
                        else
                            std::cout << "\n";
                    }
                }
                else
                {
                    empty++;
                }
            }
            std::cout << "\nEmpty: " << empty;
        }

        int del(K key)
        {
            for (int i = 0; i < capacity; i++)
            {
                if (_array[i].size() > 0)
                {
                    for (int j = 0; j < _array[i].size(); j++)
                    {

                        if (_array[i][j]->key == key)
                        {
                            for (j; j < _array[i].size() - 1; j++)
                            {
                                delete _array[i][j];
                                _array[i][j] = _array[i][j + 1];
                            }

                            _array[i].set_size(_array[i].size() - 1);
                            size--;
                            return 0;
                        }
                    }
                }
            }
            return 1;
        }

        void clear()
        {
            for (int i = 0; i < capacity; i++)
            {
                if (_array[i].size() > 0)
                {

                    for (int j = 0; j < _array[i].size(); j++)
                    {
                        delete _array[i][j];
                        _array[i].set_size(0);
                        size = 0;
                        capacity = 4;
                    }
                }
            }
        }

        Pair<K, T> *find(K key)
        {
            for (int i = 0; i < capacity; i++)
            {
                if (_array[i].size() > 0)
                {
                    for (int j = 0; j < _array[i].size(); j++)
                    {
                        if (_array[i][j]->key == key)
                        {
                            return _array[i][j];
                        }
                    }
                }
            }
            return nullptr;
        }

    private:
        int hash_index(T value)
        {
            int index = 0;
            int q = value.size();
            int pow_ = 0;
            int numb = 0;
            int p = 0;
            for (int i = 0; i < q; i++)
            {
                numb = static_cast<int>(value[i]);
                p = q - (i + 1);
                pow_ = pow(numb, p);
                index += pow_;
            }
            return abs(index % capacity);
        }
        void rehash()
        {
            capacity *= 2;
            arr::Vector<Pair<K, T> *> *temp = new arr::Vector<Pair<K, T> *>[capacity];

            for (int i = 0; i < (capacity / 2); i++)
            {
                if (_array[i].size() > 0)
                {

                    for (int j = 0; j < _array[i].size(); j++)
                    {
                        int index = hash_index(_array[i][j]->data);
                        Pair<K, T> *new_obj = new Pair<K, T>(_array[i][j]->key, _array[i][j]->data);
                        temp[index].push_back(new_obj);
                    }
                }
            }
            delete[] _array;
            _array = temp;
        }

    private:
        arr::Vector<Pair<K, T> *> *_array{nullptr};
        static int size;
        static int capacity;
    };
}
template <class K, class T>
int stnd::Map<K, T>::size;

template <class K, class T>
int stnd::Map<K, T>::capacity{4};

std::string str_generator()
{
    const char str_tablep[] = {"ABCDEFGHIJKLMNOUPRSTUVXYZabcdefghijklmnouperstuwxyz"};
    std::string data;
    for (int i = 0; i < (rand() % 100); i++)
    {

        data += str_tablep[rand() % 50];
    }
    return data;
}
int main(int argc, char const *argv[])
{
    srand(time(NULL));
    stnd::Map<int, std::string>
        mapa;
    for (int i = 0; i < 10000; i++)
    {
        std::string data = str_generator();
        mapa.insert(i, data);
    }

    mapa.print();
    return 0;
}