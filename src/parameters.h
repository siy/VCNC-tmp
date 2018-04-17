//
// Created by siy on 4/2/18.
//

#include <cstddef>
#include <cstdint>

#ifndef VCNC_PARAMETERS_H
#define VCNC_PARAMETERS_H

constexpr float const INTERPOLATION_INTERVAL = 1e-3; //1ms

constexpr size_t const NUM_AXES = 3;
constexpr size_t const FILTER_ORDER = 4;
constexpr size_t const VELOCITY_VECTOR_QUEUE_SIZE = 16;

constexpr size_t const STEP_BUFFER_SIZE_POWER = 4;
constexpr size_t const STEP_BUFFER_SIZE = 1u << STEP_BUFFER_SIZE_POWER;

constexpr size_t const SUBSTEPS_POWER = 10;
constexpr size_t const SUBSTEPS = 1u << SUBSTEPS_POWER;
constexpr size_t const SUBSTEPS_MASK = SUBSTEPS - 1;

class machine_parameters {
        float leadscrew_pitch = 10.0;
        u_int16_t steps_per_pitch = 200;
        u_int16_t microsteps = 32;

        float _max_feed = 100.0; //mm/s
        float _max_free_feed = 200.0; //mm/s
        float _max_accel = 500.0; //mm/s^2

        int32_t scale_factor = 0;

        machine_parameters& recalculate_scale_factor() {
            double tmp = 1.0f * steps_per_pitch * microsteps;

            scale_factor = int32_t(tmp/leadscrew_pitch);
            return *this;
        }

    public:

        machine_parameters() noexcept {
            recalculate_scale_factor();
        }

        machine_parameters& set_pitch(float _pitch) {
            leadscrew_pitch = _pitch;
            return recalculate_scale_factor();
        }

        int32_t scale() const {
            return scale_factor;
        }

        float max_feed() const {
            return _max_feed;
        }

        float max_free_feed() const {
            return _max_free_feed;
        }

        float max_acceleration() const {
            return _max_accel;
        }

        float mm_per_step() {
            double tmp = leadscrew_pitch / (steps_per_pitch * microsteps);

            return float(tmp);
        }

};

extern machine_parameters Parameters;

#endif //VCNC_PARAMETERS_H
