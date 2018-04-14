//
// Created by siy on 4/8/18.
//

#include "short_vector.h"
#include "movingaverage.h"
#include "parameters.h"
#include "step_buffer.h"

#ifndef VCNC_VCNC_TYPES_H
#define VCNC_VCNC_TYPES_H

using substep = int32_t;
using bitvector = u_int8_t;

using velocity_vector = short_vector<float, NUM_AXES>;
using normalised_velocity_vector = velocity_vector;

using step_vector = short_vector<substep, NUM_AXES>;
using step_vector_filter = moving_average<step_vector, FILTER_ORDER>;
using step_vector_queue = ring_buffer<step_vector, VELOCITY_VECTOR_QUEUE_SIZE>;

using main_step_buffer = step_buffer<bitvector , STEP_BUFFER_SIZE>;
using main_step_buffer_iterator = main_step_buffer::iterator<bitvector>;
using main_step_buffer_iterator_factory = main_step_buffer::iterator_factory<bitvector, STEP_BUFFER_SIZE>;

#endif //VCNC_VCNC_TYPES_H
