//
// Created by siy on 4/15/18.
//

#include "vcnc_types.h"

#ifndef VCNC_MAIN_MOVE_BLOCK_H
#define VCNC_MAIN_MOVE_BLOCK_H

class move_block {
    public:
        location start;
        location end;
        float entry_velocity;
        float exit_velocity;
        float cruise_velocity;
};

#endif //VCNC_MAIN_MOVE_BLOCK_H
