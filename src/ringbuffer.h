//
// Created by siy on 4/2/18.
//

#include <cstddef>

#ifndef VCNC_RINGBUFFER_H
#define VCNC_RINGBUFFER_H

template<typename ElementType, size_t Size>
class ring_buffer {
        static_assert((Size & (Size -1)) == 0, "Size must be power of 2");

        constexpr static size_t MASK = Size - 1;

        volatile size_t read_index;
        volatile size_t write_index;

        ElementType data[Size];
    public:
        ring_buffer():read_index(0), write_index(0) {
        }

        ring_buffer& reset(ElementType value = 0, size_t num_prefill = Size) {
            read_index = write_index = 0;

            for(size_t idx = 0; idx < num_prefill; idx++) {
                put(value);
            }

            return *this;
        }

        ring_buffer& put(ElementType element) {
            assert(!full());

            data[write_index++ & MASK] = element;
            return *this;
        }

        ElementType get() {
            assert(!empty());

            return data[read_index++ & MASK];
        }

        constexpr size_t size() const {
            return Size;
        }

        inline bool empty() const {
            return read_index == write_index;
        }

        inline bool full() const {
            return ((write_index - read_index) & ~MASK) != 0;
        }

        inline size_t count() const {
            return full() ? size() : (write_index - read_index) & MASK;
        }
};

#endif //VCNC_RINGBUFFER_H
