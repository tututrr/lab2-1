#include<iostream>
#include <iostream>
#include <cstdlib> 
#include <chrono>
#include <string>
#include <fstream>

#include "dynamic_array.h"
#include "linked_list.h"
#include "sequence_virtual.h"
#include "comparator.h"
#include "isorter.h"


using namespace std;

/*///////////////////////////////////////////////////////DYNAMIC ARRAY////////////////////////////////////////////////////////////////////

template <typename T>
class DynamicArray
{
 private:
    int m_size;
    int m_capacity;
    T * m_data;

 public:

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

    ~DynamicArray() //destructor
    {
        if (m_data)
            delete[] m_data;
    }

    const T& Get(int index)
    {
        if ((index > m_size - 1)||(index < 0))
        {
            cout << "Index out of range" << endl;
        }
        else
        {
            return m_data[index];
        }
    }    

    void Set(int index, const T& value)
    {
        if ((index > m_size - 1)||(index < 0))
        {
            cout << "Index out of range" << endl;
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

    void Push_back(T val)
    {
        Resize(m_size + 1);
        m_data[m_size - 1] = val;
    }

    int GetSize()
    {
        return m_size;
    }

    T & operator[] (int i)//operator overloading
    {
        return m_data[i];
    }

    void GetArray() 
    {
        for (int i = 0; i < m_size; i++)
        cout << m_data[i] << " ";
        cout << "\n";
    }
};
*/

/*////////////////////////////////////////////////////LINKED LIST/////////////////////////////////////////////////////////////////////

template <class T>
class Node {
public:
    T data;
    Node<T>* next;
};

template <class T>
class LinkedList {
private:
    Node<T>* head;
public:
    LinkedList(T* items, int count); //copy elements from given array

    LinkedList();

    LinkedList(const LinkedList<T>& old_version); //copy constructor

    const T& GetFirst(); //get first element in the list

    void Set(const T& item, int index); //set element index as item

    const T& GetLast(); //get last element in the list

    const T& Get(int index); //get "index" element in the list

    void PrintListElement(int index); //print index element

    LinkedList<T>* GetSubList(int startindex, int endindex); //get list from start to end

    int GetLength(); //get list length

    void Append(const T& item); //add element in the end

    void Prepend(const T& item); //add element in the beginning

    void InsertAt(const T& item, int index); //insert element at "index"

    LinkedList<T>* Concat(const LinkedList<T>& list); //concatenates two lists

    void GetList();
};

template <class T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <class T>
LinkedList<T>::LinkedList(T* items, int count) {
    if (count > 0) {
        Node<T>* node1 = new Node<T>;
        Node<T>* node2 = new Node<T>;
        node1->data = items[0];
        if (count == 1) {
            node1->next = nullptr;
            head = node1;
        }
        else {
            node1->next = node2;
            head = node1;
            for (int i = 1; i < count - 1; ++i) {
                Node<T>* node3 = new Node<T>;
                node2->data = items[i];
                node2->next = node3;
                node2 = node2->next;
            }
            node2->data = items[count - 1];
            node2->next = nullptr;
        }
    }
    else head = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& old_version) {
    int size = 0;
    Node<T>* cur_node = old_version.head;
    if (cur_node != nullptr) {
        while (cur_node->next != nullptr) {
            ++size;
            cur_node = cur_node->next;
        }
        ++size;
        Node<T>* node1 = new Node<T>;
        Node<T>* old_node = old_version.head;
        node1->data = old_node->data;
        old_node = old_node->next;
        if (size == 1) {
            node1->next = nullptr;
            head = node1;
        }
        else {
            node1->next = old_node;
            head = node1;
            node1 = node1->next;
            for (int i = 1; i < size - 1; ++i) {
                node1->data = old_node->data;
                old_node = old_node->next;
                node1->next = old_node;
                node1 = node1->next;
            }
            node1->data = old_node->data;
            node1->next = nullptr;
        }
    }
    else head = nullptr;
}

template <class T>
LinkedList<T>* LinkedList<T>::Concat(const LinkedList<T>& list) {
    LinkedList<T>* concat_list = new LinkedList<T>();
    Node<T>* node1 = head;
    Node<T>* node2 = list.head;
    while (node1 != nullptr)
    {
        concat_list->Append(node1->data);
        node1 = node1->next;
    }
    while (node2 != nullptr)
    {
        concat_list->Append(node2->data);
        node2 = node2->next;
    }
    return concat_list;
}

template <class T>
LinkedList<T>* LinkedList<T>::GetSubList(int startindex, int endindex) {
    Node<T>* node = head;
    int size = 0;
    while (node != nullptr) {
        node = node->next;
        ++size;
    }
    if ((startindex < 0) || (startindex >= size) || (endindex < 0) || (endindex >= size))
        cout << "Index out of range" << endl;
    LinkedList<T>* list = new LinkedList<T>();
    Node<T>* current = head;
    int k = 0;
    while (k != startindex) {
        current = current->next;
        ++k;
    }
    for (; k <= endindex; k++) {
        list->Append(current->data);
        current = current->next;
    }
    return list;
}

template <class T>
void LinkedList<T>::Prepend(const T& item) {
    Node<T>* new_node = new Node<T>;
    new_node->data = item;
    new_node->next = head;
    head = new_node;
}

template <class T>
void LinkedList<T>::Append(const T& item) {
    Node<T>* new_node = new Node<T>;
    new_node->data = item;
    new_node->next = nullptr;
    Node<T>* current = head;
    if (current != nullptr) {
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
    else
        head = new_node;
}

template <class T>
void LinkedList<T>::InsertAt(const T& item, int index) {
    Node<T>* node = head;
    int size = 0;
    while (node != nullptr) {
        node = node->next;
        ++size;
    }
    if ((index < 0) || (index > size))
        cout << "Index out of range" << endl;
    Node<T>* new_node = new Node<T>;
    new_node->data = item;
    new_node->next = nullptr;
    Node<T>* current = head;
    Node<T>* current1 = nullptr;
    int k = 0;
    if (index > 0) {
        while (k != index - 1) {
            current = current->next;
            ++k;
        }
        current1 = current->next;
        current->next = new_node;
        current = current->next;
        current->next = current1;
    }
    if (index == 0) {
        new_node->next = head;
        head = new_node;
    }
}

template <class T>
int LinkedList<T>::GetLength() {
    int size = 0, flag = 0;
    Node<T>* current = head;
    if (current->next == nullptr)
        flag = 1;
    while (current->next != nullptr) {
        current = current->next;
        ++size;
    }
    if (flag == 0)
        return size + 1;
    else
        return size;
}

template <class T>
const T& LinkedList<T>::Get(int index) {
    Node<T>* current = head;
    Node<T>* current1 = head;
    int size = 0;
    while (current != nullptr) {
        current = current->next;
        ++size;
    }
    if ((index < 0) || (index > size - 1))
        cout << "Index out of range" << endl;
    int k = 0;
    while (k != index) {
        current1 = current1->next;
        ++k;
    }
    return current1->data;
}

template <class T>
void LinkedList<T>::PrintListElement(int index) {
    Node<T>* current = head;
    Node<T>* current1 = head;
    int size = 0;
    while (current != nullptr) {
        current = current->next;
        ++size;
    }
    if ((index < 0) || (index > size - 1))
        cout << "Index out of range" << endl;
    int k = 0;
    while (k != index) {
        current1 = current1->next;
        ++k;
    }
    cout << current1->data << " ";
}

template <class T>
void LinkedList<T>::Set(const T& item, int index) {
    Node<T>* current = head;
    Node<T>* current1 = head;
    int size = 0;
    while (current != nullptr) {
        current = current->next;
        ++size;
    }
    if ((index < 0) || (index > size - 1))
        cout << "Index out of range" << endl;
    int k = 0;
    while (k != index) {
        current1 = current1->next;
        ++k;
    }
    current1->data = item;
}

template <class T>
const T& LinkedList<T>::GetLast() {
    Node<T>* current = head;
    if (current->next == nullptr)
        cout << "Index out of range" << endl;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current->data;
}

template <class T>
const T& LinkedList<T>::GetFirst() {
    Node<T>* current = head;
    if (current->next == nullptr)
        cout << "Index out of range" << endl;
    return current->data;
}

template <class T>
void LinkedList<T>::GetList() {
    Node<T>* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
*/

/*///////////////////////////////////////////////////////SEQUENCE//////////////////////////////////////////////////////////////////////

template <class T>
class Sequence {
public:
    virtual const T& GetFirst() = 0; //get first element

    virtual const T& GetLast() = 0; //get last element

    virtual const T& Get(int index) = 0; //get "index" element

    virtual int GetLength() = 0; //get length

    virtual void Append(const T& item) = 0; //add element at the end

    virtual void Prepend(const T& item) = 0; //add element at the beginning

    virtual void InsertAt(const T& item, int index) = 0; //add element at "index"

    virtual void Set(const T& item, int index) = 0; //set element at "index"

    virtual Sequence<T>* GetSubsequence(int startindex, int endindex) = 0; //get elements from "startindex" to "endindex"

    virtual void PrintElement(int index) = 0; //print index element 

    virtual void Print() = 0;
};

template <class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* Array;
public:
    ArraySequence(T* items, int count) : Array(new DynamicArray<T>(items, count)) {}; 

    ArraySequence() : Array(new DynamicArray<T>()) {}; 

    ArraySequence(const LinkedList<T>& old_version) : Array(new DynamicArray<T>(old_version)) {};

    ArraySequence(int size) : Array(new DynamicArray<T>(size)) {};
    
    virtual const T& GetFirst() override {
        if (this->Array->GetSize() == 0)
            throw "Index out of range";
        return this->Array->Get(0);
    }
    virtual const T& GetLast() override {
        if (this->Array->GetSize() == 0)
            throw "Index out of range";
        int last = this->Array->GetSize();
        return this->Array->Get(last - 1);
    }
    virtual const T& Get(int index) override {
        if ((index < 0) || (index >= this->Array->GetSize()))
            throw "Index out of range";
        return this->Array->Get(index);
    }
    virtual Sequence<T>* GetSubsequence(int startindex, int endindex) override {
        if ((startindex < 0) || (startindex >= this->Array->GetSize()) || (endindex < 0) || (endindex >= this->Array->GetSize()))
            throw "Index out of range";
        T* items = new T[endindex - startindex + 1];
        int count = startindex;
        for (int i = 0; i < (endindex - startindex + 1); i++) {
            items[i] = this->Array->Get(count);
            ++count;
        }
        ArraySequence<T> Arr(items, endindex - startindex + 1);
        Sequence<T>* seq = &Arr;
        return seq;
    }
    virtual int GetLength() override {
        return this->Array->GetSize();
    }
    virtual void Print() override {
        this->Array->GetArray();
    }
    virtual void PrintElement(int index) override {
        this->Array->PrintArrayElement(index);
    }
    virtual void Append(const T& item) override {
        this->Array->Push_back(item);
    }
    virtual void Prepend(const T& item) override {
        int arr_size = this->Array->GetSize();
        T* arr = new T[arr_size * 2];
        for (int i = 0; i < arr_size; i++) {
            arr[i] = this->Array->Get(i);
        }
        this->Array->Resize(arr_size + 1);
        for (int i = arr_size; i >= 1; i--) {
            this->Array->Set(i, arr[i - 1]);
        }
        this->Array->Set(0, item);
    }
    virtual void InsertAt(const T& item, int index) override {
        int arr_size = this->Array->GetSize();
        T* arr = new T[arr_size * 2];
        for (int i = 0; i < arr_size; i++) {
            arr[i] = this->Array->Get(i);
        }
        this->Array->Resize(arr_size + 1);
        for (int i = arr_size; i >= index + 1; i--) {
            this->Array->Set(i, arr[i - 1]);
        }
        this->Array->Set(index, item);
    }
    virtual void Set(const T& item, int index) override {
        this->Array->Set(item, index);
    }

    Sequence<T>* Concat(const ArraySequence<T>& list) {
        int k = this->Array->GetSize();
        int new_size = list.Array->GetSize();
        T* arr = new T[k + new_size];
        for (int i = 0; i < k; i++) {
            arr[i] = this->Array->Get(i);
        }
        int p = 0;
        for (int i = k; i < k + new_size; i++) {
            arr[i] = list.Array->Get(p);
            ++p;
        }
        ArraySequence<T> a_arr(arr, k + new_size);
        Sequence<T>* aa_arr = &a_arr;
        return aa_arr;
    }
    
};

template <class T>
class LinkedListSequence : public Sequence<T> {
private:
    LinkedList<T>* List;
public:
    LinkedListSequence(T* items, int count) : List(new LinkedList<T>(items, count)) {};
    LinkedListSequence() : List(new LinkedList<T>) {};
    LinkedListSequence(const LinkedList<T>& old_version) : List(new LinkedList<T>(old_version)) {};
    virtual const T& GetFirst() override {
        return this->List->GetFirst();
    }
    virtual const T& GetLast() override {
        return this->List->GetLast();
    }
    virtual const T& Get(int index) override {
        return this->List->Get(index);
    }
    virtual Sequence<T>* GetSubsequence(int startindex, int endindex) override {
        T* items = new T[endindex - startindex + 1];
        int count = startindex;
        for (int i = 0; i < (endindex - startindex + 1); i++) {
            items[i] = this->List->Get(count);
            ++count;
        }
        LinkedListSequence<T> list(items, endindex - startindex + 1);
        Sequence<T>* seq = &list;
        return seq;
    }
    virtual int GetLength() override {
        return this->List->GetLength();
    }
    virtual void Print() override {
        this->List->GetList();
    }
    virtual void PrintElement(int index) override {
        this->List->PrintListElement(index);
    }
    virtual void Append(const T& item) override {
        this->List->Append(item);
    }
    virtual void Prepend(const T& item) override {
        this->List->Prepend(item);
    }
    virtual void InsertAt(const T& item, int index) override {
        this->List->InsertAt(item, index);
    }
    virtual void Set(const T& item, int index) override {
        this->List->Set(item, index);
    }
    Sequence<T>* Concat(const LinkedList<T>& list) {
        LinkedList<T>* list1 = this->List->Concat(list);
        LinkedListSequence<T> l_list(*list1);
        Sequence<T>* ll_list = &l_list;
        return ll_list;
    }
};
*/

/*/////////////////////////////////////////////////MATRIX////////////////////////////////////////////////////////////////////////////

template <class T, class K = LinkedListSequence<T>>
class Matrix
{
private:
    Sequence<T>* rectangleMatrix;
    int rows;
    int columns;
    int counter;

public:
    Matrix(T* items, int _rows, int _columns) : rows(_rows), columns(_columns), counter(_rows*_columns)
    {
        this->rectangleMatrix = new K(items, rows*columns);

    }

    void out()
    {
        int i = 0;
        for (int n = 0; n < rows; n++)
        {
            for (int m = 0; m < columns; m++)
            {
                this->rectangleMatrix->PrintElement(i);
                i++;
            }
            cout << "\n" << endl;
        }
    }

    int GetLength()
    {
        return this->counter;
    }

    T Get (int index)
    {
        return this->rectangleMatrix->Get(index);
    }

    void Sum(Matrix<T, K>* matrix)
    {
        if ((matrix->rows = this->rows) && (matrix->columns = this->columns) && (matrix->counter != 0))
        {
            for (int q = 0; q < this->counter; q++)
            {
                this->rectangleMatrix->Set(this->rectangleMatrix->Get(q) + matrix->rectangleMatrix->Get(q), q);
            }
        } 
        else
        {
            throw "The dimensions of the matrices do not match";
        }
    }

    void MultiplyByScalar(T scalar)
    {

        for (int i = 0; i < this->counter; i++)
        {
            this->rectangleMatrix->Set(scalar* this->rectangleMatrix->Get(i), i);
        }
    }

    T Lnorm()
    {
        T maximum = 0;
        for (int i = 0; i < this->columns; i++)
        {
            T sum = 0;
            for (int j = i; j < this->rows*this->columns; j = j + columns)
            {
                sum = sum + this->rectangleMatrix->Get(j);

            }
            if (sum > maximum)
            {
                maximum = sum;
            }
        }
        return maximum;
    }

    void ElementScalarRows (int row, T scalar)
    {
        if (row < this->rows)
        {
            for (int i = row*columns; i < row*columns + columns; i++)
            {
                this->rectangleMatrix->Set(this->rectangleMatrix->Get(i)*scalar, i);
            }
        }
        else
        {
            throw "Row number is out of range";
        }
    }

    void ElementScalarCols (int col, T scalar)
    {
        if (col < this->columns)
        {
            for (int i = col; i <= (this->rows-1)*this->columns + col; i = i + columns)
            {
                this->rectangleMatrix->Set(this->rectangleMatrix->Get(i)*scalar, i);
            }
        }
        else
        {
            throw "Column number is out of range";
        }
    }
};
*/

int main(){

    ISorter<int> tmp;

    fstream file;

    high_resolution_clock::time_point t_start, t_end;
    duration<double> time_span1, time_span2, time_span3, time_span4, time_span5, time_span6, time_span7, time_span8, time_span9;

    int* items1 = new int[10000];
    for (int i = 0; i < 10000; i++)
        items1[i] = rand();

    int* items2 = new int[50000];
    for (int i = 0; i < 50000; i++)
        items2[i] = rand();

    int* items3 = new int[80000];
    for (int i = 0; i < 80000; i++)
        items3[i] = rand();

    ArraySequence<int> list_ex1(items1, 10000);
    Sequence<int>* sequence_ex1_bis = &list_ex1;
    Sequence<int>* sequence_ex1_qs = sequence_ex1_bis;
    Sequence<int>* sequence_ex1_ms = sequence_ex1_bis;

    ArraySequence<int> list_ex2(items2, 50000);
    Sequence<int>* sequence_ex2_bis = &list_ex2;
    Sequence<int>* sequence_ex2_qs = sequence_ex2_bis;
    Sequence<int>* sequence_ex2_ms = sequence_ex2_bis;

    ArraySequence<int> list_ex3(items3, 80000);
    Sequence<int>* sequence_ex3_bis = &list_ex3;
    Sequence<int>* sequence_ex3_qs = sequence_ex3_bis;
    Sequence<int>* sequence_ex3_ms = sequence_ex3_bis;

    /*tmp.Binary_Insertion_Sort(sequence_ex1_bis, comparator_ascending_order);
    tmp.Merge_Sort(sequence_ex1_ms, comparator_ascending_order);
    tmp.Quick_Sort(sequence_ex1_qs, comparator_ascending_order);

    tmp.Binary_Insertion_Sort(sequence_ex2_bis, comparator_ascending_order);
    tmp.Merge_Sort(sequence_ex2_ms, comparator_ascending_order);
    tmp.Quick_Sort(sequence_ex2_qs, comparator_ascending_order);

    tmp.Binary_Insertion_Sort(sequence_ex3_bis, comparator_ascending_order);
    tmp.Merge_Sort(sequence_ex3_ms, comparator_ascending_order);
    tmp.Quick_Sort(sequence_ex3_qs, comparator_ascending_order);*/


    t_start = high_resolution_clock::now();
    sequence_ex1_qs->Quick_Sort_(comparator_ascending_order);
    t_end = high_resolution_clock::now();
    time_span4 = duration_cast<duration<double>>(t_end - t_start);

    t_start = high_resolution_clock::now();
    sequence_ex2_qs->Quick_Sort_(comparator_ascending_order);
    t_end = high_resolution_clock::now();
    time_span5 = duration_cast<duration<double>>(t_end - t_start);

    t_start = high_resolution_clock::now();
    sequence_ex3_qs->Quick_Sort_(comparator_ascending_order);
    t_end = high_resolution_clock::now();
    time_span6 = duration_cast<duration<double>>(t_end - t_start);

    t_start = high_resolution_clock::now();
    sequence_ex1_ms->Merge_Sort_(comparator_ascending_order);
    t_end = high_resolution_clock::now();
    time_span7 = duration_cast<duration<double>>(t_end - t_start);

    t_start = high_resolution_clock::now();
    sequence_ex2_ms->Merge_Sort_(comparator_ascending_order);
    t_end = high_resolution_clock::now();
    time_span8 = duration_cast<duration<double>>(t_end - t_start);

    t_start = high_resolution_clock::now();
    sequence_ex3_ms->Merge_Sort_(comparator_ascending_order);
    t_end = high_resolution_clock::now();
    time_span9 = duration_cast<duration<double>>(t_end - t_start);

    t_start = high_resolution_clock::now();
    sequence_ex1_bis->Binary_Insertion_Sort_(comparator_ascending_order);
    t_end = high_resolution_clock::now();
    time_span1 = duration_cast<duration<double>>(t_end - t_start);

    t_start = high_resolution_clock::now();
    sequence_ex2_bis->Binary_Insertion_Sort_(comparator_ascending_order);
    t_end = high_resolution_clock::now();
    time_span2 = duration_cast<duration<double>>(t_end - t_start);

    t_start = high_resolution_clock::now();
    sequence_ex3_bis->Binary_Insertion_Sort_(comparator_ascending_order);
    t_end = high_resolution_clock::now();
    time_span3 = duration_cast<duration<double>>(t_end - t_start);


    file.open("comparison.csv", fstream::out | fstream::in | fstream::app);
    //Количество элементов;Время работы алгоритма сортировки двоичными вставками;Время работы алгоритма быстрой сортировки;Время работы алгоритма сортировки слиянием
    file << 10000 << ";" << time_span1.count() << ";" << time_span4.count() << ";" << time_span7.count() << ";" << "\n";
    file << 50000 << ";" << time_span2.count() << ";" << time_span5.count() << ";" << time_span8.count() << ";" << "\n";
    file << 80000 << ";" << time_span3.count() << ";" << time_span6.count() << ";" << time_span9.count() << ";" << "\n";
    file.close();
    cout << "Результаты сравнительного анализа можно увидеть в файле comparison.csv" << endl;
    cout << endl;
    
   
    return 0;
}
