//
// Created by siy on 4/8/18.
//

#ifndef VCNC_INTERPOLATOR_H
#define VCNC_INTERPOLATOR_H

#include "vcnc_types.h"

class StepMachine {
        FilterVector filters;
        VelocityVectorQueue queue;
    public:
        StepMachine() = default;

        inline bool hasSpace() {
            return queue.empty();
        }

        bool put(RawVelocityVector& move) {
            if (queue.full()) {
                return false;
            }

            StepVector vector(move, Parameters.scale());
            queue.put(vector);
            return true;
        }


};

#endif //VCNC_INTERPOLATOR_H
