//
// Created by siy on 4/14/18.
//

#include "vcnc_types.h"

#ifndef VCNC_MAIN_STEP_MACHINE_H
#define VCNC_MAIN_STEP_MACHINE_H

class step_machine {
        step_vector const ZeroVector;

        step_vector_queue queue;

        step_vector next_speed;
        step_vector step_counter;
        step_vector next_position_change;

        step_bit_collector step_bits;

        physical_location machine_location;
        physical_location scaled_position;
        position_callback callback = nullptr;

        main_step_buffer main_buffer;
        main_step_buffer_iterator_factory factory;

        step_vector get() {
            return queue.empty() ? ZeroVector : queue.get();
        }

    public:
        step_machine():factory(main_buffer) {}
        explicit step_machine(position_callback entry_point):callback(entry_point), factory(main_buffer) {}

        bool put(velocity_vector&& move) {
            if (queue.full()) {
                return false;
            }

            velocity_vector scaled_move(move, INTERPOLATION_INTERVAL);
            step_vector vector(scaled_move, Parameters.scale());

            queue.put(vector);
            return true;
        }

        physical_location& position() {
            scaled_position = machine_location;
            scaled_position /= STEP_BUFFER_SIZE;
            return scaled_position;
        }

        void set_callback(position_callback entry_point) {
            callback = entry_point;
        }

        main_step_buffer buffer() {
            return main_buffer;
        }

        void generate_next_move() {
            machine_location += next_position_change;

            if (callback) {
                callback(position());
            }

            step_vector current_speed = next_speed;
            next_speed = get();

            next_position_change = next_speed;
            next_position_change += current_speed;
            next_position_change *= (STEP_BUFFER_SIZE/2);

            step_vector speed_delta = next_speed;
            speed_delta -= current_speed;

            current_speed *= STEP_BUFFER_SIZE;

            step_bits.clear();
            next_speed.sign(step_bits);

            main_step_buffer_iterator iterator = factory.create();

            while (iterator.hasNext()) {
                current_speed += speed_delta;
                step_counter.add_abs(current_speed);

                *iterator++ = step_counter.step_and_reset<step_bit_collector, SUBSTEPS_DELTA_MASK>(step_bits).value();
                *iterator++ = step_bits.reset();
            }
        }
};

#endif //VCNC_MAIN_STEP_MACHINE_H
