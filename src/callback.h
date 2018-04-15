//
// Created by siy on 4/15/18.
//

#ifndef VCNC_MAIN_CALLBACK_H
#define VCNC_MAIN_CALLBACK_H

template <typename PayloadType>
class callaback {
        using callaback_function_ptr = void (*)(PayloadType);
        PayloadType payload;
        callaback_function_ptr fn_ptr;
    public:
        callaback():payload(0), fn_ptr(0) {}
        callaback(PayloadType payload_, callaback_function_ptr ptr):payload(payload_), fn_ptr(ptr) {}

        void invoke() {
            if (fn_ptr) {
                fn_ptr(payload);
            }
        }
};

#endif //VCNC_MAIN_CALLBACK_H
