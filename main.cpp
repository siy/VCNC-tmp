#include <iostream>

#include "src/vcnc_types.h"

//---------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------

MachineParameters Parameters;



int main() {
    MovingAverage<double, 64> ma;

    for(int i = 0; i < 64; i++) {
        std::cout << i << "," << ma.next(i * 0.1) << std::endl;
    }

    std::cout << "Scale factor " << Parameters.scale() << std::endl;

    Vec<double, NUM_AXES> vector(1.0, 2.0, 4.0);

    std::cout << "Original vector:" << vector << std::endl;

    vector *= 3.0;

    std::cout << "Scaled vector:" << vector << std::endl;



    MovingAverage<Vec<double , 2>, 4> vecMa;

    std::cout << vecMa.next(Vec<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(Vec<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(Vec<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(Vec<double, 2>(1.0, 1.0)) << std::endl;
    std::cout << vecMa.next(Vec<double, 2>(1.0, 1.0)) << std::endl;

    return 0;
}
