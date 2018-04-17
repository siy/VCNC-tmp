#include <iostream>
#include <bitset>

#include "src/vcnc_types.h"
#include "src/move_block.h"
#include "src/step_machine.h"
#include "src/bitmixer.h"
//---------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------

machine_parameters Parameters;


void testMovingAverage1();

void testVectorScaling();

void testMovingAverage2();

void testStepBuffer();

void testRingBuffer();

void testStepMachine();

void testBitMixer();

int main() {
    //testMovingAverage1();

    //testVectorScaling();

    //testMovingAverage2();

    //testStepBuffer();

    //testRingBuffer();

    testStepMachine();

    //testBitMixer();

    return 0;
}

void testStepMachine() {
    step_machine stepper([] (physical_location& loc) {
        std::cout << "Machine position: " << loc << std::endl;
    });

    stepper.put(velocity_vector(1000.0f, 2000.0f, 3072.0f));
//    stepper.put(velocity_vector(100.0f, 200.0f, 300.0f));
//    stepper.put(velocity_vector(2.0f, 4.0f, 6.0f));
//    stepper.put(velocity_vector(1.0f, 2.0f, 3.0f));
//    stepper.put(velocity_vector(300.0f, 200.0f, 100.0f));
//    stepper.put(velocity_vector(-1.0f, 2.0f, -3.0f));
//    stepper.put(velocity_vector(-2.0f, 4.0f, -6.0f));
//    stepper.put(velocity_vector(-300.0f, -200.0f, -100.0f));
    stepper.put(velocity_vector(-1000.0f, -2000.0f, -3072.0f));
    stepper.put(velocity_vector(0.0f, 0.0f, 0.0f));

    stepper.generate_next_move();
    stepper.generate_next_move();
    stepper.generate_next_move();
    stepper.generate_next_move();
    stepper.generate_next_move();
    stepper.generate_next_move();

    std::cout << "(F100.0 * Ti * scale) = " << (1000.0f * INTERPOLATION_INTERVAL * Parameters.scale()/2) << std::endl;
    std::cout << "(F200.0 * Ti * scale) = " << (2000.0f * INTERPOLATION_INTERVAL * Parameters.scale()/2) << std::endl;
    std::cout << "(F300.0 * Ti * scale) = " << (3072.0f * INTERPOLATION_INTERVAL * Parameters.scale()/2) << std::endl;
}

void testBitMixer() {
    std::cout << "Extract mask: 0x" << std::setfill('0') << std::setw(4) << std::hex << bitmixer::bit_set<Bit0>::mask << std::endl;
    std::cout << "Reset mask: 0x" << std::setfill('0') << std::setw(4) << std::hex << bitmixer::bit_reset<Bit0>::mask << std::endl;
    std::cout << "Extract mask: 0x" << std::setfill('0') << std::setw(4) << std::hex << bitmixer::bit_set<Bit2>::mask << std::endl;
    std::cout << "Reset mask: 0x" << std::setfill('0') << std::setw(4) << std::hex << bitmixer::bit_reset<Bit2>::mask << std::endl;
    std::cout << "Extract mask: 0x" << std::setfill('0') << std::setw(4) << std::hex << bitmixer::bit_set<Bit3, Bit0>::mask << std::endl;
    std::cout << "Reset mask: 0x" << std::setfill('0') << std::setw(4) << std::hex << bitmixer::bit_reset<Bit3, Bit0>::mask << std::endl;
    std::cout << "Extract mask: 0x" << std::setfill('0') << std::setw(4) << std::hex << bitmixer::bit_set<Bit15, Bit7, Bit0, Bit6>::mask << std::endl;
    std::cout << "Reset mask: 0x" << std::setfill('0') << std::setw(4) << std::hex << bitmixer::bit_reset<Bit15, Bit7, Bit0, Bit6>::mask << std::endl;

    bitmixer::bit_collector<u_int16_t, Bit15, Bit7, Bit0, Bit6> collector;

    std::cout << "Value: 0x" << std::setfill('0') << std::setw(4) << std::hex << collector.value() << std::endl;
    collector.add(1);
    std::cout << "Value: 0x" << std::setfill('0') << std::setw(4) << std::hex << collector.value() << std::endl;
    collector.add(1);
    std::cout << "Value: 0x" << std::setfill('0') << std::setw(4) << std::hex << collector.value() << std::endl;
    collector.add(1);
    std::cout << "Value: 0x" << std::setfill('0') << std::setw(4) << std::hex << collector.value() << std::endl;
    collector.add(1);
    std::cout << "Value: 0x" << std::setfill('0') << std::setw(4) << std::hex << collector.value() << std::endl;
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
