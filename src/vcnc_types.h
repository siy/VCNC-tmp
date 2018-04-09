//
// Created by siy on 4/8/18.
//

#include "vec.h"
#include "movingaverage.h"
#include "parameters.h"

#ifndef VCNC_VCNC_TYPES_H
#define VCNC_VCNC_TYPES_H

using substep = int;
using bitvector = u_int16_t;

using StepVector = Vec<substep, NUM_AXES>;

using RawVelocityVector = Vec<float, NUM_AXES>;

using NormalisedVector = Vec<float, NUM_AXES>;

using FilterVector = Vec<MovingAverage<substep, FILTER_ORDER>, NUM_AXES>;

using VelocityVectorQueue = RingBuffer<StepVector, VELOCITY_VECTOR_QUEUE_SIZE>;

using StepBuffer = Vec<bitvector , STEP_BUFFER_SIZE>;

#endif //VCNC_VCNC_TYPES_H
