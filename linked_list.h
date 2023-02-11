#include<iostream>

#pragma once

using namespace std;


template <class T>
class Node {
public:
    T data;
    Node<T>* next;
    Node() : data(0), next(nullptr) {}
	Node(const T& item, Node<T>* ptr = nullptr) : data(item), next(ptr) {}
};

template <class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
public:
    LinkedList(T* items, int amount); //copy elements from given array

    LinkedList();

    LinkedList(const LinkedList<T>& old_version); //copy constructor

    ~LinkedList();

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

    ///////////iterator//////////////
    class Iterator {
		friend class LinkedList;
	private:
		Node<T>* some_node;
		Iterator(Node<T>* new_node);
		Iterator();
	public:
		Iterator& operator++();
		Iterator operator++(int);

		Iterator& operator--();
		Iterator operator--(int);

		bool operator!=(Iterator it);
		bool operator==(Iterator it);

		const T& operator*();
	};

    Iterator begin();
	Iterator end();
	Iterator advance_forward(int amount);
	Iterator advance_back(int amount);

    ///////////////sorting algorithms///////////////

    //////////////quick sort///////////////////////
    Iterator partition(Iterator head, Iterator tail, bool(*comparator_ascending_order)(const T&, const T&));
	void Quick_Sort(Iterator head, Iterator tail, bool(*comparator_ascending_order)(const T&, const T&));
	void Quick_Sort_(bool(*comparator_ascending_order)(const T&, const T&));

    //////////////merge sort///////////////////////
    void Split(Iterator head, Iterator& f, Iterator& s);
	void Merge_Sort(Iterator& head, bool(*comparator_ascending_order)(const T&, const T&));
	void Merge_Sort_(bool(*comparator_ascending_order)(const T&, const T&));
	Iterator merge(Iterator f, Iterator s, bool(*comparator_ascending_order)(const T&, const T&));

    //////////////binary search sort///////////////
    Iterator find_middle(Iterator head, Iterator tail);
	Iterator binary_search(Iterator head, Iterator tail, const T& key, bool(*comparator_ascending_order)(const T&, const T&));
	Iterator previous(Iterator some_node);
	void Binary_Insertion_Sort_(bool(*comparator_ascending_order)(const T&, const T&));


};

template <class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template<class T>
LinkedList<T>::LinkedList(T* items, int amount) {
	if (amount == 0) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		Node<T>* current = new Node<T>;
		head = current;
		for (int i = 0; i < amount; i++) {
			current->data = items[i];
			tail = current;
			if (i != amount - 1) {
				Node<T>* new_node = new Node<T>;
				current->next = new_node;
				current = current->next;
			}
		}
	}
}

/*template <class T>
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
}*/

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
    else {
        head = nullptr;
        tail = nullptr;
    }
}
template<class T>
LinkedList<T>::~LinkedList() {
	Node<T>* current = head;
	while (current) {
		Node<T>* for_deleting = current;
		current = current->next;
		delete for_deleting;
	}
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

template<class T>
LinkedList<T>::Iterator::Iterator(Node<T>* new_node) : some_node(new_node) {};
template<class T>
LinkedList<T>::Iterator::Iterator() : some_node(nullptr) {};

template<class T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++() {
	some_node = some_node->next;
	return (*this);
}
template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int) {
	Iterator result = *this;
	++(*this);
	return result;
}

template<class T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator--() {
	some_node = (this->previous)(some_node);
	return (*this);
}
template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator--(int) {
	Iterator result = *this;
	--(*this);
	return result;
}

template<class T>
bool LinkedList<T>::Iterator::operator!=(Iterator it) {
	return (some_node != it.some_node);
}
template<class T>
bool LinkedList<T>::Iterator::operator==(Iterator it) {
	return (some_node == it.some_node);
}

template<class T>
const T& LinkedList<T>::Iterator::operator*() {
	return this->some_node->data;
}

template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
	return Iterator(head);
}
template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
	return nullptr;
}
template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::advance_forward(int amount) {
	Iterator result = *this;
	for (int i = 0; i < amount; i++)
		++(*this);
	return result;
}
template<class T>
typename LinkedList<T>::Iterator LinkedList<T>::advance_back(int amount) {
	Iterator result = *this;
	for (int i = 0; i < amount; i++)
		--(*this);
	return result;
}

//////////////quick sort///////////////////////

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::partition(Iterator head, Iterator tail, bool(*comparator_ascending_order)(const T&, const T&)) {
	Iterator pivot = head, current = head;
	while ((current != nullptr) && (current != tail)) {
		if (comparator_ascending_order(current.operator*(), tail.operator*())) {
			pivot = head;
			T tmp = head.operator*();
			head.some_node->data = current.operator*();
			current.some_node->data = tmp;
			++head;
		}
		++current;
	}
	T tmp = head.operator*();
	head.some_node->data = tail.operator*();
	tail.some_node->data = tmp;
	return pivot;
}
template <class T>
void LinkedList<T>::Quick_Sort(Iterator head, Iterator tail, bool(*comparator_ascending_order)(const T&, const T&)) {
	if (head == tail)
		return;
	Iterator pivot = partition(head, tail, comparator_ascending_order);
	Iterator pivot_next = pivot;
	++pivot_next;
	if ((pivot != nullptr) && (pivot_next != nullptr))
		Quick_Sort(pivot_next, tail, comparator_ascending_order);
	if ((pivot != nullptr) && (head != pivot))
		Quick_Sort(head, pivot, comparator_ascending_order);
}
template <class T>
void LinkedList<T>::Quick_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) {
	Quick_Sort(head, tail, comparator_ascending_order);
}

//////////////merge sort///////////////////////

template <class T>
void LinkedList<T>::Split(Iterator head, Iterator& f, Iterator& s) {
	Iterator slow = head, fast = head;
	++fast;
	while (fast != nullptr) {
		++fast;
		if (fast != nullptr) {
			++slow;
			++fast;
		}
	}
	Iterator tmp = slow;
	++tmp;
	f = head;
	s = tmp;
	slow.some_node->next = nullptr;
}
template <class T>
void LinkedList<T>::Merge_Sort(Iterator& head, bool(*comparator_ascending_order)(const T&, const T&)) {
	Iterator head_ = head, f, s;
	Iterator tmp = head;
	++tmp;
	if ((head_ == nullptr) || (tmp == nullptr))
		return;
	Split(head_, f, s);
	Merge_Sort(f, comparator_ascending_order);
	Merge_Sort(s, comparator_ascending_order);
	head = merge(f, s, comparator_ascending_order);
}
template <class T>
void LinkedList<T>::Merge_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) {
	Iterator head_ = begin();
	Merge_Sort(head_, comparator_ascending_order);
	head = head_.some_node;
}
template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::merge(Iterator f, Iterator s, bool(*comparator_ascending_order)(const T&, const T&)) {
	Iterator result = nullptr;
	if (f == nullptr)
		return s;
	if (s == nullptr)
		return f;
	if (comparator_ascending_order(s.operator*(), f.operator*())) {
		result = s;
		++s;
	}
	else {
		result = f;
		++f;
	}
	Iterator tmp = result;
	while (f != nullptr && s != nullptr) {
		if (comparator_ascending_order(s.operator*(), f.operator*())) {
			tmp.some_node->next = s.some_node;
			++s;
		}
		else {
			tmp.some_node->next = f.some_node;
			++f;
		}
		++tmp;
	}
	if (f != nullptr) {
		tmp.some_node->next = f.some_node;
	}
	if (s != nullptr) {
		tmp.some_node->next = s.some_node;
	}
	return result;
}

//////////////binary search sort///////////////

template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::find_middle(Iterator head, Iterator tail) {
	if (head == nullptr)
		return nullptr;
	Iterator slow = head, fast = head;
	++fast;
	while (fast != tail) {
		++fast;
		if (fast != tail) {
			++slow;
			++fast;
		}
	}
	return slow;
}
template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::binary_search(Iterator head, Iterator tail, const T& key, bool(*comparator_ascending_order)(const T&, const T&)) {
	Iterator head_ = head;
	Iterator tail_ = tail;
	++tail_;//=nullptr
	do {
		Iterator middle = find_middle(head_, tail_);
		if (middle == nullptr)
			return nullptr;
		if (middle.operator*() == key)
			return middle;
		if (comparator_ascending_order(middle.operator*(), key)) {
			Iterator middle_next = middle;
			++middle_next;
			head_ = middle_next;
		}
		else tail_ = middle;
	} while (tail_ != head_);
	return head_;
}
template <class T>
typename LinkedList<T>::Iterator LinkedList<T>::previous(Iterator some_node) {
	Iterator current = head, tmp = head;
	++tmp;
	while (tmp != nullptr) {
		if (tmp == some_node)
			return current;
		++current;
		++tmp;
	}
	return nullptr;
}
template <class T>
void LinkedList<T>::Binary_Insertion_Sort_(bool(*comparator_ascending_order)(const T&, const T&)) {
	Iterator must_be_replaced = nullptr, prev_mbr = nullptr, j = head, i = nullptr, i_ = nullptr, tmp = nullptr;
	if (head == nullptr)
		i = nullptr;
	else {
		tmp = head;
		++tmp;
		i = tmp;
	}
	while (i != nullptr) {
		tmp = i;
		++tmp;
		i_ = tmp;
		T key = i.operator*();
		must_be_replaced = binary_search(head, j, key, comparator_ascending_order);
		if (i != must_be_replaced) {
			if (must_be_replaced != head) {
				prev_mbr = previous(must_be_replaced);
				prev_mbr.some_node->next = i.some_node;
			}
			else head = i.some_node;
			j.some_node->next = i.some_node->next;
			i.some_node->next = must_be_replaced.some_node;
		}
		i = i_;
		j = previous(i);
	}
}