//
// Created by siy on 4/14/18.
//

#include "bitnames.h"

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

    template <typename T, bit_name ... Bits>
    class bit_collector {
            T result;
            u_int16_t const bits[sizeof...(Bits)];
            int index;
        public:
            bit_collector():result(0),index(0),bits{bit_set_t<u_int16_t, Bits>::mask...} {}
            ~bit_collector() = default;

            bit_collector& add(int bit) {
                assert(index < sizeof...(Bits));

                result |= bit ? bits[index] : 0;
                index++;
                return *this;
            }

            T value () const {
                return result;
            }
    };
}


#endif //VCNC_MAIN_BITMIXER_H
