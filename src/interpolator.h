//
// Created by siy on 4/8/18.
//

#ifndef VCNC_INTERPOLATOR_H
#define VCNC_INTERPOLATOR_H

#include "vcnc_types.h"

#include <iostream>

class StepMachine {
        StepVector const ZeroVector;

        VectorFilter filter;
        VelocityVectorQueue queue;

        StepVector counter;

        StepVector get() {
            return queue.empty() ? ZeroVector : queue.get();
        }

    public:
        StepMachine() = default;

        inline bool hasSpace() {
            return queue.empty();
        }

        bool put(RawVelocityVector&& move) {
            if (queue.full()) {
                return false;
            }

            StepVector vector(move, Parameters.scale());
            queue.put(vector);
            return true;
        }

        void generateNextMove(MainStepBufferIterator iterator) {
            StepVector current_speed = filter.prev();
            StepVector next_speed = filter.next(get());
            StepVector delta_speed(next_speed);
            delta_speed -= current_speed;

            while (iterator.hasNext()) {
                current_speed += current_speed;
                current_speed += delta_speed;
                delta_speed += delta_speed;

                std::cout << "Current speed: " << current_speed << std::endl;

                *iterator++ = 0;
                *iterator++ = 0;
            }
        }
};

#endif //VCNC_INTERPOLATOR_H
