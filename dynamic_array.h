
#pragma once
#include<iostream>
using namespace std;

///////////////////////////////////////////////////////DYNAMIC ARRAY////////////////////////////////////////////////////////////////////

template <typename T>
class DynamicArray
{
 private:
    int m_size; //used
    int m_capacity; //available
    T * m_data;

 public:
    DynamicArray() {};

    DynamicArray(const DynamicArray<T> & a) //copy constructor works with lvalue
    {
        m_size = a.m_size;
        m_capacity = m_size;
        m_data = NULL;
        if (m_size != 0)
            m_data = new T[m_size];
        else
            m_data = 0;
        for (int i = 0; i < m_size; ++i)
            m_data[i] = a.m_data[i];
        cout << "copy constructor" << endl;
    }
    
    DynamicArray(DynamicArray<T> && other) //move constructor works with rvalue
    {
        m_data = other.m_data;
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        cout << "move constructor" << endl;
    }

    DynamicArray(int size) //create DA of size
    {
        m_size = size;
        m_capacity = size;
        if (size != 0)
            m_data = new T[size];
        else
            m_data = 0;
    }

   DynamicArray(T* items, int count) //copy elements from given data
   {
       m_size = count;
       m_capacity = m_size;
       if (m_size != 0)
       {
        m_data = new T[count];
        for (int i = 0; i < count; i++)
            m_data[i] = items[i];
       }
       else
            m_data = 0;
   }
 
    ~DynamicArray() //destructor
    {
        if (m_data)
            delete[] m_data;
    }

    const T& Get(int index)
    {
        if ((index > m_size - 1)||(index < 0))
        {
            throw "Index out of range";
        }
        else
        {
            return m_data[index];
        }
    }

    void Set(const T& value, int index)
    {
        if ((index > m_size - 1)||(index < 0))
        {
            throw "Index out of range";
        }
        else
        {
            m_data[index] = value;
        }
    }

    void Resize(int size)
    {
        if (size > m_capacity)
        {
            int new_capacity = max(size, m_size * 2);
            T * new_data = new T[new_capacity];
            for (int i = 0; i < m_size; ++i)
                new_data[i] = m_data[i];
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_size = size;
    }

    void Push_back(const T& val)
    {
        Resize(m_size + 1);
        m_data[m_size - 1] = val;
    }

    int GetSize()
    {
        return m_size;
    }

    T & operator[] (int i) //operator overloading
    {
        return m_data[i];
    }

    void GetArray() 
    {
        for (int i = 0; i < m_size; i++)
        cout << m_data[i] << " ";
        cout << "\n";
    }

    void PrintArrayElement(int index)
    {
        if ((index > m_size - 1)||(index < 0))
        {
            throw "Index out of range";
        }
        else
        {
            cout << m_data[index] << " ";
        }
    }

    DynamicArray<T>& operator=(DynamicArray<T> &b)
    {
        m_size = b.m_size;
        m_capacity = b.m_capacity;
        m_data = b.m_data;

        return *this;
    }

    /////////////////////iterator//////////////

    class Iterator {
		friend class DynamicArray;
	private:
		T* some_element;
		Iterator(T* new_element) : some_element(new_element) {};
		Iterator() : some_element(nullptr) {};
	public:
		Iterator& operator++() {
            ++some_element;
            return (*this);
        }

		Iterator operator++(int) {
            Iterator result = *this;
            ++(*this);
            return result;
        }

		Iterator& operator--() {
            --some_element;
            return (*this);
        }

		Iterator operator--(int) {
            Iterator result = *this;
            --(*this);
            return result;
        }

		bool operator!=(Iterator it) {
            return (some_element != it.some_element);
        }

		bool operator==(Iterator it) {
            return (some_element == it.some_element);
        }

		bool operator<(Iterator it){
            return (some_element < it.some_element);
        }

		bool operator<=(Iterator it) {
            return (some_element <= it.some_element);
        }

		const T& operator*() {
            return *(some_element);
        }
	};

    Iterator begin() {
        return Iterator(m_data);
    }

	Iterator end() {
        return Iterator(m_data + m_size - 1);
    }

	Iterator advance_forward(int amount) {
        Iterator result = *this;
        for (int i = 0; i < amount; i++)
            ++(*this);
        return result;
    }

	Iterator advance_back(int amount) {
        Iterator result = *this;
        for (int i = 0; i < amount; i++)
            --(*this);
        return result;
    }

	int real_index(Iterator it) {
        int counter = 0;
        for (Iterator ptr = m_data; ptr <= end(); ++ptr) {
            if (ptr == it)
                return counter - 1;
            ++counter;
        }
        return -1;
    }

    Iterator find_middle(Iterator beginning, Iterator ending) {
        if (beginning == nullptr)
            return nullptr;
        Iterator slow = beginning, fast = beginning;
        ++fast;
        if (beginning == ending)
            return ending;
        while (fast != ending) {
            ++fast;
            if (fast != ending) {
                ++slow;
                ++fast;
            }
            else ++slow;
        }
        return slow;
    }

	Iterator binary_search(Iterator beginning, Iterator ending, const T& key, bool(*comparator_ascending_order)(const T&, const T&)) {
        Iterator tmp = nullptr;
        while (beginning <= ending) {
            Iterator middle = find_middle(beginning, ending);
            if (key == middle.operator*())
                return middle;
            else if (comparator_ascending_order(middle.operator*(), key)) {
                tmp = middle;
                ++tmp;
                beginning = tmp;
            }
            else {
                tmp = middle;
                --tmp;
                ending = tmp;
            }
        }
        return beginning;
    }

    //////////////////sorting algorithms////////////////
    //////////////////quick sort///////////////////////

    Iterator partition(Iterator beginning, Iterator ending, bool(*comparator_ascending_order)(const T&, const T&)) {
        T pivot = ending.operator*();
        Iterator i = beginning;
        --i;
        while (beginning < ending) {
            if (comparator_ascending_order(beginning.operator*(), pivot)) {
                ++i;
                T tmp = i.operator*();
                *(i.some_element) = beginning.operator*();
                *(beginning.some_element) = tmp;
            }
            ++beginning;
        }
        Iterator i_plus_one = i;
        ++i_plus_one;
        T tmp = i_plus_one.operator*();
        *(i_plus_one.some_element) = pivot;
        *(ending.some_element) = tmp;
        return i_plus_one;
    }

	void Quick_Sort(Iterator beginning, Iterator ending, bool(*comparator_ascending_order)(const T&, const T&)) {
        if (beginning < ending) {
            Iterator index = partition(beginning, ending, comparator_ascending_order);
            Iterator ind_prev = index, ind_post = index;
            --ind_prev;
            ++ind_post;
            Quick_Sort(beginning, ind_prev, comparator_ascending_order);
            Quick_Sort(ind_post, ending, comparator_ascending_order);
        }
    }

	void Quick_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) {
        Quick_Sort(begin(), end(), comparator_ascending_order);
    }

    //////////////////merge sort///////////////////////

    void Merge(Iterator beginning, Iterator& middle, Iterator ending, bool(*comparator_ascending_order)(const T&, const T&)) {
        Iterator middle_plus_1 = middle;
        int real = real_index(middle);
        ++middle_plus_1;
        Iterator length_of_first_subarray = middle;
        Iterator length_of_second_subarray = ending;
        Iterator index_of_first_subarray = beginning, index_of_second_subarray = middle_plus_1;
        int index_of_merged_array = 0;
        T* merged_array = new T[real_index(ending) + 1];

        while ((index_of_first_subarray <= length_of_first_subarray) && (index_of_second_subarray <= length_of_second_subarray)) {
            if (comparator_ascending_order(index_of_second_subarray.operator*(), index_of_first_subarray.operator*())) {
                *(merged_array + index_of_merged_array) = index_of_second_subarray.operator*();
                ++index_of_second_subarray;
            }
            else {
                *(merged_array + index_of_merged_array) = index_of_first_subarray.operator*();
                ++index_of_first_subarray;
            }
            ++index_of_merged_array;
        }
        while (index_of_first_subarray <= length_of_first_subarray) {
            *(merged_array + index_of_merged_array) = index_of_first_subarray.operator*();
            ++index_of_first_subarray;
            ++index_of_merged_array;
        }
        while (index_of_second_subarray <= length_of_second_subarray) {
            *(merged_array + index_of_merged_array) = index_of_second_subarray.operator*();
            ++index_of_second_subarray;
            ++index_of_merged_array;
        }
        int counter = 0;
        for (Iterator ptr = beginning; ptr <= ending; ++ptr) {
            *(ptr.some_element) = *(merged_array + counter);
            ++counter;
        }
    }

	void Merge_Sort(Iterator beginning, Iterator ending, bool(*comparator_ascending_order)(const T&, const T&)) {
        if (beginning < ending) {
            Iterator middle = find_middle(beginning, ending);
            Iterator tmp = middle;
            ++tmp;
            Merge_Sort(beginning, middle, comparator_ascending_order);
            Merge_Sort(tmp, ending, comparator_ascending_order);
            Merge(beginning, middle, ending, comparator_ascending_order);
        }
    }
	void Merge_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) {
	    Merge_Sort(begin(), end(), comparator_ascending_order);
    }

    //////////////////binary insertion sort///////////////////////
    void Binary_Insertion_Sort(bool(*comparator_ascending_order)(const T&, const T&)) {
        Iterator j = nullptr, location = nullptr, i = begin(), j_tmp = nullptr, tmp = nullptr;
        T key;
        ++i;
        for (; i <= end(); ++i) {
            j = i;
            --j;
            key = i.operator*();
            location = binary_search(begin(), j, key, comparator_ascending_order);
            while (location <= j) {
                j_tmp = j;
                ++j_tmp;
                *(j_tmp.some_element) = j.operator*();
                --j;
            }
            j_tmp = j;
            ++j_tmp;
            *(j_tmp.some_element) = key;
        }
    }

    void Binary_Insertion_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) {
        Binary_Insertion_Sort(comparator_ascending_order);
    }

};