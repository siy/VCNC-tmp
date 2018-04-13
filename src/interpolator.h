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

        StepVector current_speed;
        StepVector step_counter;

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

            RawVelocityVector tmp = move;

            StepVector vector(tmp, Parameters.scale());
            queue.put(vector);
            return true;
        }

        void generateNextMove(MainStepBufferIterator iterator) {
            StepVector next_speed = filter.next(get());
            StepVector delta_speed = next_speed;
            delta_speed -= current_speed;
            delta_speed >>= STEP_BUFFER_SIZE_POWER;

            std::cout << "Next speed " << next_speed << std::endl;
            std::cout << "Current speed " << current_speed << std::endl;
            std::cout << "Speed delta " << delta_speed << std::endl;

            int step_cnt = 0;
            while (iterator.hasNext()) {
                current_speed += delta_speed;
                step_counter += current_speed;
                size_t full_steps = step_counter.step_and_reset(SUBSTEPS_MASK);

                if(full_steps) {
                    step_cnt++;
                }

                *iterator++ = 0;
                *iterator++ = 0;
            }

            std::cout << "total steps by X: " << step_cnt << std::endl;
            std::cout << "Current speed " << current_speed << std::endl;
        }
};

#endif //VCNC_INTERPOLATOR_H
