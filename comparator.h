#pragma once
#include<iostream>

template<class T>
bool comparator_ascending_order(const T& first_element, const T& second_element) {
    return (first_element < second_element);
}
