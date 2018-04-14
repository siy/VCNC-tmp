//
// Created by siy on 4/14/18.
//

#include "vcnc_types.h"
#include <iostream>
#include <bitset>

#ifndef VCNC_MAIN_STEP_MACHINE_H
#define VCNC_MAIN_STEP_MACHINE_H

class step_machine {
        step_vector const ZeroVector;

        step_vector_filter filter;
        step_vector_queue queue;

        step_vector current_speed;
        step_vector step_counter;

        step_bit_collector step_bits;

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
            step_bits.reset(0, 0);
            next_speed.abs(step_bits);

            step_vector delta_speed = next_speed;
            delta_speed -= current_speed;
            delta_speed >>= STEP_BUFFER_SIZE_POWER;

            std::cout << "Next speed " << next_speed << std::endl;
            std::cout << "Current speed " << current_speed << std::endl;
            std::cout << "Speed delta " << delta_speed << std::endl;

            int step_cnt = 0;

            std::cout << std::setfill('0') << std::setw(4) << std::hex;

            while (iterator.hasNext()) {
                current_speed += delta_speed;
                step_counter += current_speed;

                *iterator++ = step_counter.step_and_reset(SUBSTEPS_MASK, step_bits).value();
                std::bitset<8> tmp1 = step_bits.value();
                std::cout << "step : " << tmp1 << std::endl;

                if (step_bits.value() & step_bit_mask) {
                    step_cnt++;
                }

                *iterator++ = step_bits.reset(NUM_AXES, ~step_bit_mask);
                std::bitset<8> tmp2 = step_bits.value();
                std::cout << "reset: " << tmp2 << std::endl;
            }

            std::cout << std::dec;
            std::cout << "total steps by X: " << step_cnt << std::endl;
            std::cout << "Current speed " << current_speed << std::endl;
        }
};

#endif //VCNC_MAIN_STEP_MACHINE_H
