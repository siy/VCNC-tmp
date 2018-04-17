//
// Created by siy on 4/8/18.
//

#include "short_vector.h"
#include "movingaverage.h"
#include "parameters.h"
#include "step_buffer.h"
#include "bitmixer.h"

#ifndef VCNC_VCNC_TYPES_H
#define VCNC_VCNC_TYPES_H


using substep = int32_t;
using bitvector = u_int8_t;

using location = short_vector<float, NUM_AXES>;
using physical_location = short_vector<substep, NUM_AXES>;
using position_callback = void (*)(physical_location&);

using velocity_vector = short_vector<float, NUM_AXES>;
using normalised_velocity_vector = velocity_vector;

using step_vector = short_vector<substep, NUM_AXES>;
using step_vector_filter = moving_average<step_vector, FILTER_SIZE>;
using step_vector_queue = ring_buffer<step_vector, VELOCITY_VECTOR_QUEUE_SIZE>;

using main_step_buffer = step_buffer<bitvector, STEP_BUFFER_SIZE>;
using main_step_buffer_iterator = main_step_buffer::iterator<bitvector>;
using main_step_buffer_iterator_factory = main_step_buffer::iterator_factory<bitvector, STEP_BUFFER_SIZE>;

//Mapping of logical step/dir/pwm bits into physical bit positions.
// Bits are added in following order:
// Dir X, Dir Y, Dir Z
// Step X, Step Y, Step Z
// Pwm 1, Pwm 2
// Listed bits specify actual physical positions of corresponding logical signals
//using step_bit_collector = bitmixer::bit_collector<bitvector, NUM_AXES, Bit1, Bit3, Bit5, Bit0, Bit2, Bit4, Bit6, Bit7>;
using step_bit_collector = bitmixer::bit_collector<bitvector, NUM_AXES, Bit0, Bit1, Bit2, Bit3, Bit4, Bit5, Bit6, Bit7>;

#endif //VCNC_VCNC_TYPES_H
