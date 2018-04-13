//
// Created by siy on 4/2/18.
//

#include <cstddef>
#include "ringbuffer.h"

#ifndef VCNC_MOVINGAVERAGE_H
#define VCNC_MOVINGAVERAGE_H

template <typename ElementType, size_t Size>
class MovingAverage {
        RingBuffer<ElementType,Size> buffer;
        ElementType accumulator;
        ElementType last_value;
    public:

        MovingAverage():accumulator(ElementType(0)),last_value(ElementType(0)) {
            buffer.reset(ElementType(0), Size);
        }

        ~MovingAverage() = default;

        ElementType next(ElementType const element) {
            auto old = buffer.get();
            buffer.put(element);
            accumulator -= old;
            accumulator += element;

            return last_value = (accumulator / Size);
        }

        inline ElementType prev() const {
            return last_value;
        }
};

#endif //VCNC_MOVINGAVERAGE_H
