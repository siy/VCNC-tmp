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
        static_assert(Size < std::numeric_limits<size_t>::digits, "Vector size cannot exceed size of size_t in bits");
    public:
        ElementType data[Size];

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

        template <typename T>
        Vec& operator>>= (const T count) {
            for (int i = 0; i < Size; ++i) {
                data[i] >>= count;
            }
            return *this;
        }

        template <typename T>
        Vec& operator&= (const T mask) {
            for (int i = 0; i < Size; ++i) {
                data[i] &= mask;
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

        size_t step_and_reset(size_t mask) {
            size_t result = 0;

            for (int i = 0; i < Size; ++i) {
                if (data[i] & ~mask) {
                    result |= 1;
                    data[i] &= mask;
                }
                result <<= 1;
            }
            return result;
        }

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
