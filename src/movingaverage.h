//
// Created by siy on 4/2/18.
//

#include <cstddef>
#include "ringbuffer.h"

#ifndef VCNC_MOVINGAVERAGE_H
#define VCNC_MOVINGAVERAGE_H

template <typename ElementType, size_t Size>
class moving_average {
        ring_buffer<ElementType,Size> buffer;
        ElementType accumulator;
        ElementType last_value;
    public:

        moving_average():accumulator(ElementType(0)),last_value(ElementType(0)) {
            buffer.reset(ElementType(0), Size);
        }

        ~moving_average() = default;

        ElementType next(ElementType const element) {
            auto old = buffer.get();
            buffer.put(element);
            accumulator -= old;
            accumulator += element;

            last_value = accumulator;

            return last_value /= Size;
        }

        inline ElementType prev() const {
            return last_value;
        }
};

#endif //VCNC_MOVINGAVERAGE_H
