#include <iostream>

namespace arr
{
	template <class T>
	class Vector
	{

	public:
		T &operator[](size_t id)
		{
			if (id >= size_)
			{
				std::cout << "Array index out of range\n\n";
				throw "Array index out of range";
			}

			return tabs[id];
		}

		void push_back(T obj)
		{
			if (size_ == 0)
			{
				tabs = new T[1];
				tabs[size_] = obj;
				size_++;
				return;
			}

			T *tab_new = new T[size_ + 1];
			for (size_t i = 0; i < size_; i++)
			{
				tab_new[i] = tabs[i];
			}
			tab_new[size_] = obj;
			delete[] tabs;
			tabs = tab_new;
			size_++;
		}

		~Vector()
		{
			if (tabs != nullptr)
			{
				delete[] tabs;
			}
		}

		void clear()
		{
			if (tabs != nullptr)
			{
				delete[] tabs;
				tabs = nullptr;
				size_ = 0;
			}
		}
		size_t size()
		{
			return size_;
		}
		void set_size(size_t size)
		{
			size_ = size;
		}

	private:
		T *tabs{nullptr};
		size_t size_{0};
	};
}
