#include <iostream>

#include "src/vcnc_types.h"
#include "src/step_machine.h"
//---------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------

machine_parameters Parameters;


void testMovingAverage1();

void testVectorScaling();

void testMovingAverage2();

void testStepBuffer();

void testRingBuffer();

int main() {
    //testMovingAverage1();

    //testVectorScaling();

    //testMovingAverage2();

    //testStepBuffer();

    //testRingBuffer();

    step_machine stepMachine;

    main_step_buffer buffer;
    main_step_buffer_iterator_factory factory(buffer);

    stepMachine.put(velocity_vector(1.0, 2.0, 3.0));
    stepMachine.put(velocity_vector(2.0, 3.0, 4.0));
    stepMachine.put(velocity_vector(3.0, 4.0, 5.0));
    stepMachine.put(velocity_vector(4.0, 5.0, 6.0));
    stepMachine.put(velocity_vector(4.0, 5.0, 6.0));
    stepMachine.put(velocity_vector(4.0, 5.0, 6.0));
    stepMachine.put(velocity_vector(4.0, 5.0, 6.0));
    stepMachine.put(velocity_vector(4.0, 5.0, 6.0));
    stepMachine.put(velocity_vector(3.0, 4.0, 5.0));
    stepMachine.put(velocity_vector(2.0, 3.0, 4.0));
    stepMachine.put(velocity_vector(1.0, 2.0, 3.0));
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());
    stepMachine.generate_next_move(factory.create());

    return 0;
}

void testRingBuffer() {
    ring_buffer<int, 4> buffer;

    std::cout << "Is full: " << buffer.full() << ", is empty: " << buffer.empty() << ", count: " << buffer.count() << std::endl;

    buffer.put(1);

    std::cout << "Is full: " << buffer.full() << ", is empty: " << buffer.empty() << ", count: " << buffer.count() << std::endl;

    buffer.put(2);

    std::cout << "Is full: " << buffer.full() << ", is empty: " << buffer.empty() << ", count: " << buffer.count() << std::endl;

    buffer.put(3);

    std::cout << "Is full: " << buffer.full() << ", is empty: " << buffer.empty() << ", count: " << buffer.count() << std::endl;

    buffer.put(4);

    std::cout << "Is full: " << buffer.full() << ", is empty: " << buffer.empty() << ", count: " << buffer.count() << std::endl;

    auto val = buffer.get();

    std::cout << "Is full: " << buffer.full() << ", is empty: " << buffer.empty() << ", count: " << buffer.count() << ", value:" << val << std::endl;

    val = buffer.get();

    std::cout << "Is full: " << buffer.full() << ", is empty: " << buffer.empty() << ", count: " << buffer.count() << ", value:" << val << std::endl;

    val = buffer.get();

    std::cout << "Is full: " << buffer.full() << ", is empty: " << buffer.empty() << ", count: " << buffer.count() << ", value:" << val << std::endl;

    val = buffer.get();

    std::cout << "Is full: " << buffer.full() << ", is empty: " << buffer.empty() << ", count: " << buffer.count() << ", value:" << val << std::endl;
}

void testStepBuffer() {
    step_buffer<u_int16_t, 8> buffer;
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
}

void testMovingAverage2() {
    moving_average<short_vector<double , 2>, 4> vecMa;

    std::cout << vecMa.next(short_vector<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(short_vector<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(short_vector<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(short_vector<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(short_vector<double, 2>(1.0, 1.0)) << std::endl;
}

void testVectorScaling() {
    std::cout << "Scale factor " << Parameters.scale() << std::endl;

    short_vector<double, NUM_AXES> vector(1.0, 2.0, 4.0);

    std::cout << "Original vector:" << vector << std::endl;

    vector *= 3.0;

    std::cout << "Scaled vector:" << vector << std::endl;
}

void testMovingAverage1() {
    moving_average<double, 64> ma;

    for(int i = 0; i < 64; i++) {
        std::cout << i << "," << ma.next(i * 0.1) << std::endl;
    }
}
