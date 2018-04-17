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

    template <typename T, size_t Preserve, bit_name ... Bits>
    class bit_collector {
            T result;
            T const bits[sizeof...(Bits)] = {bit_set_t<T, Bits>::mask...};
            int index;
            T preserve_mask;
        public:
            bit_collector():result(0),index(0) {
                for(int i = 0; i < Preserve; i++) {
                    preserve_mask |= bits[i];
                }
            }

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

            T reset() {
                result &= preserve_mask;
                index = Preserve;
            }

            T clear() {
                result = 0;
                index = 0;
            }

            template <typename Tp, size_t P, bit_name ... Bitsp>
            friend std::ostream& operator<< (std::ostream& os, const bit_collector<Tp, P, Bitsp...>& vec);
    };
}
template <typename T, size_t P, bit_name ... Bits>
std::ostream& operator<< (std::ostream& os, const bitmixer::bit_collector<T, P, Bits...>& vec) {
    std::bitset<std::numeric_limits<T>::digits> val(vec.value());
    os << "<" << val << ">";
    return os;
};


#endif //VCNC_MAIN_BITMIXER_H
