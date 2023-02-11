#pragma once
#include <iostream>
#include <cstdlib> 
#include <chrono>
#include <string>
#include <fstream>
#include "sequence_virtual.h"

using namespace std;
using namespace std::chrono;

template <class T>
class ISorter {
public:
    void Quick_Sort(Sequence<T>* seq, bool(*comparator_ascending_order)(const T&, const T&)){
        high_resolution_clock::time_point t_start, t_end;
        duration<double> time_span;
        message_before(seq);
        t_start = high_resolution_clock::now();
        seq->Quick_Sort_(comparator_ascending_order);
        t_end = high_resolution_clock::now();
        time_span = duration_cast<duration<double>>(t_end - t_start);
        message_after(seq);
        cout << "Время, которое было затрачено на работу алгоритма, составило " << time_span.count() << " секунд" << endl;
        cout << endl;
    }

    void Merge_Sort(Sequence<T>* seq, bool(*comparator_ascending_order)(const T&, const T&)) {
        high_resolution_clock::time_point t_start, t_end;
        duration<double> time_span;
        message_before(seq);
        t_start = high_resolution_clock::now();
        seq->Merge_Sort_(comparator_ascending_order);
        t_end = high_resolution_clock::now();
        time_span = duration_cast<duration<double>>(t_end - t_start);
        message_after(seq);
        cout << "Время, которое было затрачено на работу алгоритма, составило " << time_span.count() << " секунд" << endl;
        cout << endl;
    }

    void Binary_Insertion_Sort(Sequence<T>* seq, bool(*comparator_ascending_order)(const T&, const T&)) {
        high_resolution_clock::time_point t_start, t_end;
        duration<double> time_span;
        message_before(seq);
        t_start = high_resolution_clock::now();
        seq->Binary_Insertion_Sort_(comparator_ascending_order);
        t_end = high_resolution_clock::now();
        time_span = duration_cast<duration<double>>(t_end - t_start);
        message_after(seq);
        cout << "Время, которое было затрачено на работу алгоритма, составило " << time_span.count() << " секунд" << endl;
        cout << endl;
    }

    void message_before(Sequence<T>* seq) {
        cout << "Последовательность до сортировки: " << endl;
        for (int i = 0; i < seq->GetLength(); i++) {
            cout << seq->Get(i) << ' ';
        }
        cout << endl;
    }

    void message_after(Sequence<T>* seq) {
    cout << "Последовательность после сортировки: " << endl;
    for (int i = 0; i < seq->GetLength(); i++) {
        cout << seq->Get(i) << ' ';
    }
    cout << endl;
    }
};