//
// Created by siy on 4/14/18.
//

#include "vcnc_types.h"
#include <iostream>

#ifndef VCNC_MAIN_STEP_MACHINE_H
#define VCNC_MAIN_STEP_MACHINE_H

class step_machine {
        step_vector const ZeroVector;

        step_vector_filter filter;
        step_vector_queue queue;

        step_vector current_speed;
        step_vector step_counter;

        step_vector get() {
            return queue.empty() ? ZeroVector : queue.get();
        }

    public:
        step_machine() = default;

        inline bool has_space() {
            return queue.empty();
        }

        bool put(velocity_vector&& move) {
            if (queue.full()) {
                return false;
            }

            step_vector vector(move, Parameters.scale());
            queue.put(vector);
            return true;
        }

        void generate_next_move(main_step_buffer_iterator iterator) {
            step_vector next_speed = filter.next(get());

            size_t signs = next_speed.abs();

            step_vector delta_speed = next_speed;
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

#endif //VCNC_MAIN_STEP_MACHINE_H
