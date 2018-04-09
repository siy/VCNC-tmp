//
// Created by siy on 4/2/18.
//

#include <cstddef>
#include <utility>
#include <cassert>
#include <algorithm>
#include <iostream>

#ifndef VCNC_VEC_H
#define VCNC_VEC_H

template <typename ElementType, size_t Size>
class Vec {
        ElementType data[Size];
    public:

        using SelfType = Vec<ElementType, Size>;

        Vec():data{} {
        }

        explicit Vec(ElementType initialValue) {
            std::fill_n(std::begin(data), Size, initialValue);
        }

        template <typename ... Args>
        explicit Vec(Args ... args): data{ElementType(args) ...} {
        }

        Vec(const SelfType& other) {
            std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
        }

        Vec(const SelfType&& other) noexcept {
            std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
        }

        Vec& operator= (const SelfType& other) {
            std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
            return *this;
        }

        template <typename OtherElementType>
        Vec(Vec<OtherElementType, Size>& other, ElementType scaleFactor) {
            std::transform(std::begin(other.data),
                           std::end(other.data),
                           std::begin(data),
                           [=] (OtherElementType value) { return ElementType(value * scaleFactor);});
        }

        template <typename ScalerType>
        Vec& operator*= (ScalerType scaleFactor) {
            std::transform(std::begin(data),
                           std::end(data),
                           std::begin(data),
                           [=] (ElementType value) { return ElementType(value * scaleFactor);});
        }

        template <typename ScalerType>
        Vec& operator/= (const ScalerType scaleFactor) {
            std::transform(std::begin(data),
                           std::end(data),
                           std::begin(data),
                           [=] (ElementType value) { return ElementType(value / scaleFactor);});
        }

        Vec& operator+= (const SelfType other) {
            for (int i = 0; i < Size; ++i) {
                data[i] += other.data[i];
            }
            return *this;
        }

        Vec& operator-= (const SelfType other) {
            for (int i = 0; i < Size; ++i) {
                data[i] -= other.data[i];
            }
            return *this;
        }

        SelfType operator/ (const SelfType other) {
            SelfType result(*this);
            for (int i = 0; i < Size; ++i) {
                result.data[i] /= other.data[i];
            }
            return result;
        }

        template <typename ScalerType>
        SelfType operator/ (const ScalerType other) {
            SelfType result(*this);
            for (int i = 0; i < Size; ++i) {
                result.data[i] /= other;
            }
            return result;
        }

        SelfType operator* (const SelfType other) {
            SelfType result(*this);
            for (int i = 0; i < Size; ++i) {
                result.data[i] *= other.data[i];
            }
            return result;
        }

        template <typename ScalerType>
        SelfType operator* (const ScalerType other) {
            SelfType result(*this);
            for (int i = 0; i < Size; ++i) {
                result.data[i] *= other;
            }
            return result;
        }

        const ElementType& operator[](int idx) {
            assert(idx < Size);
            return data[idx];
        }

        template <typename T>
        class Iterator {
                T* data;
            public:
                explicit Iterator(T* ptr):data(ptr) {}

                Iterator(const Iterator<T>& other) : data(other.data) {}

                T* operator++() {
                    return ++data;
                }
        };

        inline Iterator<ElementType> begin() {
            return Iterator<ElementType>(data);
        }

        inline Iterator<ElementType> end() {
            return Iterator<ElementType>(data + Size);
        }

        inline Iterator<ElementType> mid() {
            return Iterator<ElementType>(data + Size/2);
        }

        template <typename T>
        class FlipFlopIteratorFactory {
                bool flipFlop = false;
                Iterator<T> begin;
                Iterator<T> mid;
                Iterator<T> end;

            public:
                explicit FlipFlopIteratorFactory(Vec<T, Size> vector):begin(vector.begin()), mid(vector.mid()), end(vector.end()) {}

                using iterator_pair = std::pair<Iterator<T>, Iterator<T>>;

                iterator_pair iterators() {
                    flipFlop ^= true;

                    return flipFlop ? iterator_pair(begin, mid) : iterator_pair(mid, end);
                }
        };

        template <typename T, size_t S>
        friend std::ostream& operator<< (std::ostream& os, const Vec<T, S>& vec);
};

template <typename T, size_t Size>
std::ostream& operator<< (std::ostream& os, const Vec<T, Size>& vec) {
    os << "<";
    for(T value: vec.data) {
        os << value << ", ";
    }
    os << ">";
    return os;
};

#endif //VCNC_VEC_H
