//
// Created by siy on 4/14/18.
//

#include "vcnc_types.h"

#ifndef VCNC_MAIN_STEP_MACHINE_H
#define VCNC_MAIN_STEP_MACHINE_H

class step_machine {
        step_vector const ZeroVector;

        step_vector_queue queue;

        step_vector current_speed;
        step_vector step_counter;
        step_vector next_delta;

        step_bit_collector step_bits;

        physical_location machine_location;
        position_callback callback = nullptr;

        step_vector get() {
            return queue.empty() ? ZeroVector : queue.get();
        }

    public:
        step_machine() = default;
        explicit step_machine(position_callback entry_point):callback(entry_point) {}

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

        physical_location& position() {
            return machine_location;
        }

        void set_callback(position_callback entry_point) {
            callback = entry_point;
        }

        void generate_next_move(main_step_buffer_iterator iterator) {
            machine_location += next_delta;

            if (callback) {
                callback(machine_location);
            }

            step_vector next_speed = get();
            next_delta = next_speed;
            next_delta >>= SUBSTEPS_POWER;

            step_bits.reset(0, 0);
            next_speed.abs(step_bits);

            step_vector delta_speed = next_speed;
            delta_speed -= current_speed;

            delta_speed >>= STEP_BUFFER_SIZE_POWER;

            while (iterator.hasNext()) {
                current_speed += delta_speed;
                step_counter += current_speed;

                *iterator++ = step_counter.step_and_reset(SUBSTEPS_MASK, step_bits).value();
                *iterator++ = step_bits.reset(NUM_AXES, step_bit_mask);
            }
        }
};

#endif //VCNC_MAIN_STEP_MACHINE_H
