//
// Created by siy on 4/14/18.
//

#include "bitnames.h"
#include <algorithm>

#ifndef VCNC_MAIN_BITMIXER_H
#define VCNC_MAIN_BITMIXER_H

namespace bitmixer {
    template <bit_name First, bit_name... Bits>
    struct bit_set {
        constexpr static auto mask = bit_set<First>::mask | bit_set<Bits...>::mask;
    };

    template <bit_name First>
    struct bit_set<First> {
        constexpr static auto mask = 1u << First;
    };

    template <bit_name... Bits>
    struct bit_reset {
        constexpr static auto mask = ~bit_set<Bits...>::mask;
    };

    template <typename T, bit_name... Bits>
    struct bit_set_t {
        constexpr static T mask = bit_set<Bits...>::mask;
    };

    template <typename T, bit_name... Bits>
    struct bit_reset_t {
        constexpr static T mask = ~bit_set_t<T, Bits...>::mask;
    };

    template <typename T, bit_name ... Bits>
    class bit_collector {
            T result;
            T const bits[sizeof...(Bits)] = {bit_set_t<T, Bits>::mask...};
            int index;
        public:
            bit_collector():result(0),index(0) {}

            ~bit_collector() = default;

            bit_collector& add(int bit) {
                assert(index < sizeof...(Bits));

                result |= bit ? bits[index] : 0;
                index++;
                return *this;
            }

//            template <typename T, size_t Len>
//            bit_collector& add(T value) {
//                using mask = bit_set_t<T, bit_name(Len)>;
//                auto bit_mask = mask::mask;
//                while (bit_mask) {
//                    add(value & bit_mask);
//                    bit_mask >>= 1;
//                }
//            }

            T value () const {
                return result;
            }

            T reset(const int start, const T mask) {
                result &= mask;
                index = start;
                return result;
            }
    };
}


#endif //VCNC_MAIN_BITMIXER_H
