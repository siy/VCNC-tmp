//
// Created by siy on 4/2/18.
//

#include <cstddef>

#ifndef VCNC_RINGBUFFER_H
#define VCNC_RINGBUFFER_H

//TODOL rework it to use different algorithm
template<typename ElementType, size_t Size>
class RingBuffer {
    public:
        RingBuffer():head_(0), tail_(0) {
        }

        RingBuffer& reset(ElementType value = 0, size_t num_prefill = Size) {
            head_ = tail_;

            for(size_t idx = 0; idx < num_prefill; idx++) {
                put(value);
            }

            return *this;
        }

        RingBuffer& put(ElementType element) {
            data[head_] = element;
            head_ = next(head_);

            if (head_ == tail_) {
                tail_ = next(tail_);
            }
            return *this;
        }

        ElementType get() {
            if(empty()) {
                return ElementType();
            }

            auto element = data[tail_];
            tail_ = next(tail_);

            return element;
        }

        constexpr size_t size() {
            return Size;
        }

        inline bool empty() {
            return head_ == tail_;
        }

        inline bool full() {
            return next(head_) == tail_;
        }

    private:
        inline size_t next(size_t index) {
            return (index + 1) % (Size + 1);
        }

        ElementType data[Size + 1];
        size_t head_;
        size_t tail_;
};

#endif //VCNC_RINGBUFFER_H
