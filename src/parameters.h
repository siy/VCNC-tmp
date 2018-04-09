//
// Created by siy on 4/2/18.
//

#include <cstddef>
#include <cstdint>

#ifndef VCNC_PARAMETERS_H
#define VCNC_PARAMETERS_H

constexpr size_t NUM_AXES = 3;
constexpr size_t FILTER_ORDER = 64;
constexpr size_t VELOCITY_VECTOR_QUEUE_SIZE = 1024; //1s of movements
constexpr size_t STEP_BUFFER_SIZE = 1024;

constexpr size_t SUBSTEPS = 1024;
constexpr size_t SUBSTEPS_MASK = SUBSTEPS - 1;

class MachineParameters {
        float leadscrewPitch = 10.0;
        u_int16_t stepsPerPitch = 200;
        u_int16_t microsteps = 32;
        u_int16_t substeps = 1024;

        float max_feed = 100.0; //mm/s
        float max_free_feed = 200.0; //mm/s
        float max_accel = 500.0; //mm/s^2

        int32_t scaleFactor = 0;

        MachineParameters& recalculate_scale_factor() {
            double tmp = stepsPerPitch;
            tmp *= microsteps;
            tmp *= substeps;

            scaleFactor = int32_t(tmp/leadscrewPitch);
            return *this;
        }

    public:

        MachineParameters() noexcept {
            recalculate_scale_factor();
        }

        MachineParameters& setPitch(float newPitch) {
            leadscrewPitch = newPitch;
            return recalculate_scale_factor();
        }

        int32_t scale() const {
            return scaleFactor;
        }

        float maxFeed() const {
            return max_feed;
        }

        float maxFreeFeed() const {
            return max_free_feed;
        }

        float maxAcceleration() const {
            return max_accel;
        }
};

extern MachineParameters Parameters;

#endif //VCNC_PARAMETERS_H
