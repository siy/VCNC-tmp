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
class step_buffer {
        //Step buffer contains 2 halves, each of Size size and for each step there is accompanying step reset
        constexpr static const int SCALER = 4;
        constexpr static const int HALF_SCALER = 2;

        ElementType data[Size * SCALER] = {};
    public:

        constexpr size_t size() const {
            return Size * SCALER;
        }

        template <typename T>
        class iterator {
                T* data;
                size_t size;
            public:
                explicit iterator(T* ptr, size_t count):data(ptr),size(count) {}

                iterator(const iterator<T>& other) : data(other.data),size(other.size) {}

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

        inline iterator<ElementType> firstHalf() {
            return iterator<ElementType>(data, size()/2);
        }

        inline iterator<ElementType> secondHalf() {
            return iterator<ElementType>(data + size()/2 , size()/2);
        }

        template <typename T, size_t Sz>
        class iterator_factory {
                using IterableBuffer = step_buffer<T, Sz>;

                bool flipFlop = false;
                IterableBuffer& buffer;
            public:
                explicit iterator_factory(IterableBuffer& source):buffer(source) {}

                iterator<T> create() {
                    flipFlop = !flipFlop;
                    return flipFlop ? buffer.firstHalf() : buffer.secondHalf();
                }
        };

        iterator_factory<ElementType, Size> factory() {
            return iterator_factory<ElementType, Size>(*this);
        };

        template <typename T, size_t S>
        friend std::ostream& operator<< (std::ostream& os, const step_buffer<T, S>& buffer);
};

template <typename T, size_t Size>
std::ostream& operator<< (std::ostream& os, const step_buffer<T, Size>& buffer) {
    os << "<" << std::hex ;
    for(T value: buffer.data) {
        os  << "0x" << std::setfill('0') << std::setw(8) << value << ", ";
    }

    os << ">" << std::dec;
    return os;
};

#endif //VCNC_MAIN_STEP_BUFFER_H
