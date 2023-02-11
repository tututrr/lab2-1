
#pragma once
#include<iostream>
using namespace std;

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

    ///////////////sorting functions///////////////

    virtual void Quick_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) = 0;
    virtual void Merge_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) = 0;
    virtual void Binary_Insertion_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) = 0;

};

template <class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* Array;
    int size; 
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

    void Quick_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) override {
        this->Array->Quick_Sort_(comparator_ascending_order);
    }
    
    void Merge_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) override {
        this->Array->Merge_Sort_(comparator_ascending_order);
    }

    void Binary_Insertion_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) override {
        this->Array->Binary_Insertion_Sort_(comparator_ascending_order);
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

    void Quick_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) override {
        this->List->Quick_Sort_(comparator_ascending_order);
    }

    void Merge_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) override  {
        this->List->Merge_Sort_(comparator_ascending_order);
    }
    void Binary_Insertion_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) override {
        this->List->Binary_Insertion_Sort_(comparator_ascending_order);
    }
};
