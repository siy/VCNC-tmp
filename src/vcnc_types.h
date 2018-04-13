//
// Created by siy on 4/8/18.
//

#include "vec.h"
#include "movingaverage.h"
#include "parameters.h"
#include "step_buffer.h"

#ifndef VCNC_VCNC_TYPES_H
#define VCNC_VCNC_TYPES_H

using substep = int32_t;
using bitvector = u_int8_t;

using StepVector = Vec<substep, NUM_AXES>;

using RawVelocityVector = Vec<float, NUM_AXES>;

using NormalisedVector = Vec<float, NUM_AXES>;

using VectorFilter = MovingAverage<Vec<substep, NUM_AXES>, FILTER_ORDER>;

using VelocityVectorQueue = RingBuffer<StepVector, VELOCITY_VECTOR_QUEUE_SIZE>;

using MainStepBuffer = StepBuffer<bitvector , STEP_BUFFER_SIZE>;

using MainStepBufferIterator = MainStepBuffer::Iterator<bitvector>;
using MainStepBufferIteratorFactory = MainStepBuffer::IteratorFactory<bitvector, STEP_BUFFER_SIZE>;

#endif //VCNC_VCNC_TYPES_H
