#include <iostream>

#include "src/vcnc_types.h"
#include "src/interpolator.h"
//---------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------

MachineParameters Parameters;


void testMovingAverage1();

void testVectorScaling();

void testMovingAverage2();

int main() {
    //testMovingAverage1();

    //testVectorScaling();

    //testMovingAverage2();

    StepBuffer<u_int16_t, 8> buffer;
    auto factory = buffer.factory();

    auto iter1 = factory.create();

    while (iter1.len() > 0) {
        *iter1++ = u_int16_t(0x5555);
    }

    auto iter2 = factory.create();

    while (iter2.len() > 0) {
        *iter2++ = u_int16_t(0xAAAA);
    }

    std::cout << buffer << std::endl;

    return 0;
}

void testMovingAverage2() {
    MovingAverage<Vec<double , 2>, 4> vecMa;

    std::cout << vecMa.next(Vec<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(Vec<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(Vec<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(Vec<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(Vec<double, 2>(1.0, 1.0)) << std::endl;
}

void testVectorScaling() {
    std::cout << "Scale factor " << Parameters.scale() << std::endl;

    Vec<double, NUM_AXES> vector(1.0, 2.0, 4.0);

    std::cout << "Original vector:" << vector << std::endl;

    vector *= 3.0;

    std::cout << "Scaled vector:" << vector << std::endl;
}

void testMovingAverage1() {
    MovingAverage<double, 64> ma;

    for(int i = 0; i < 64; i++) {
        std::cout << i << "," << ma.next(i * 0.1) << std::endl;
    }
}
