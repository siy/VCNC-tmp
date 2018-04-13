//
// Created by siy on 4/12/18.
//

#include <glob.h>
#include <utility>
#include <iostream>
#include <iomanip>

#ifndef VCNC_MAIN_STEP_BUFFER_H
#define VCNC_MAIN_STEP_BUFFER_H

template <typename ElementType, size_t Size>
class StepBuffer {
        //Step buffer contains 2 halves, each of Size size and for each step there is accompanying step reset
        constexpr static const int SCALER = 4;
        constexpr static const int HALF_SCALER = 2;

        ElementType data[Size * SCALER] = {};
    public:

        constexpr size_t size() const {
            return Size * SCALER;
        }

        template <typename T>
        class Iterator {
                T* data;
                size_t size;
            public:
                explicit Iterator(T* ptr, size_t count):data(ptr),size(count) {}

                Iterator(const Iterator<T>& other) : data(other.data),size(other.size) {}

                T* operator++(int) {
                    assert(size > 0);

                    size--;
                    T* result = data++;
                    return result;
                }

                size_t len() const {
                    return size;
                }

                bool hasNext() const {
                    return size > 0;
                }
        };

        inline Iterator<ElementType> firstHalf() {
            return Iterator<ElementType>(data, size()/2);
        }

        inline Iterator<ElementType> secondHalf() {
            return Iterator<ElementType>(data + size()/2 , size()/2);
        }

        template <typename T, size_t Sz>
        class IteratorFactory {
                using IterableBuffer = StepBuffer<T, Sz>;

                bool flipFlop = false;
                IterableBuffer& buffer;
            public:
                explicit IteratorFactory(IterableBuffer& source):buffer(source) {}

                Iterator<T> create() {
                    flipFlop = !flipFlop;
                    return flipFlop ? buffer.firstHalf() : buffer.secondHalf();
                }
        };

        IteratorFactory<ElementType, Size> factory() {
            return IteratorFactory<ElementType, Size>(*this);
        };

        template <typename T, size_t S>
        friend std::ostream& operator<< (std::ostream& os, const StepBuffer<T, S>& buffer);
};

template <typename T, size_t Size>
std::ostream& operator<< (std::ostream& os, const StepBuffer<T, Size>& buffer) {
    os << "<" << std::hex ;
    for(T value: buffer.data) {
        os  << "0x" << std::setfill('0') << std::setw(8) << value << ", ";
    }

    os << ">" << std::dec;
    return os;
};

#endif //VCNC_MAIN_STEP_BUFFER_H
