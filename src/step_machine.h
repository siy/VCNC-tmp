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
            scaled_position /= SUBSTEPS;
            return scaled_position;
        }

        void set_callback(position_callback entry_point) {
            callback = entry_point;
        }

        step_buffer& buffer() {
            return main_buffer;
        }

        //TODO: update implementation to support smooth speed transition, current implementation uses avarage speed
        void generate_next_move() {
            machine_location += next_delta;

            if (callback) {
                callback(position());
            }

            step_vector next_speed = get();
            step_vector delta_speed = next_speed;

            delta_speed += current_speed;
            delta_speed /= 2;

            step_bits.clear();
            //next_speed.sign(step_bits);

            next_delta = ZeroVector;

            main_step_buffer_iterator iterator = factory.create();
            int cnt_1 = 0;
            int cnt_2 = 0;
            int cnt_3 = 0;

            std::cout << "Delta speed: " << delta_speed << std::endl;
            std::cout << "Step counter: " << step_counter << std::endl;

            while (iterator.hasNext()) {
                //current_speed += delta_speed;
                //step_counter.add_abs(current_speed);

                //next_delta += current_speed;

                step_counter.add_abs(delta_speed);
                next_delta += delta_speed;

                //*iterator++ = step_counter.step_and_reset(SUBSTEPS_MASK, step_bits).value();
                auto val = step_counter.step_and_reset(SUBSTEPS_MASK, step_bits).value();

                if (val & 0x08) {
                    cnt_1++;
                }
                if (val & 0x10) {
                    cnt_2++;
                }
                if (val & 0x20) {
                    cnt_3++;
                }

                *iterator++ = val;
                *iterator++ = step_bits.reset();
            }

            current_speed = next_speed;

            std::cout << "Next delta: " << next_delta << std::endl;
            std::cout << "Cnt: " << cnt_1 << ", " << cnt_2 << ", " << cnt_3 << std::endl;
        }
};

#endif //VCNC_MAIN_STEP_MACHINE_H
