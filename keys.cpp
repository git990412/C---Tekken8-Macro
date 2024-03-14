#include "tekken.hpp"

void Tekken::b() {
    excuteCode[6] = BACK;

    excuteMacro();
}

void Tekken::b_2() {
    excuteCode[6] = BACK;
    excuteCode[7] = R_HAND;

    excuteMacro();
}

void Tekken::bd() {
    excuteCode[6] = BACK + DOWN;

    excuteMacro();
}

void Tekken::f() {
    excuteCode[6] = FORWARD;

    excuteMacro();
}

void Tekken::_1() {
    excuteCode[7] = L_HAND;

    excuteMacro();
}

void Tekken::_134() {
    excuteCode[7] = L_HAND + R_KICK + L_KICK;

    excuteMacro();
}

void Tekken::f_1() {
    excuteCode[6] = FORWARD;
    excuteCode[7] = L_HAND;

    excuteMacro();
}

void Tekken::f_2() {
    excuteCode[6] = FORWARD;
    excuteCode[7] = R_HAND;

    excuteMacro();
}

void Tekken::f_3() {
    excuteCode[6] = FORWARD;
    excuteCode[7] = L_KICK;

    excuteMacro();
}

void Tekken::fd() {
    excuteCode[6] = FORWARD + DOWN;

    excuteMacro();
}

void Tekken::fd_1() {
    excuteCode[6] = FORWARD + DOWN;
    excuteCode[7] = L_HAND;

    excuteMacro();
}

void Tekken::fd_2() {
    excuteCode[6] = FORWARD + DOWN;
    excuteCode[7] = R_HAND;

    excuteMacro();
}

void Tekken::fd_4() {
    excuteCode[6] = FORWARD + DOWN;
    excuteCode[7] = R_KICK;

    excuteMacro();
}

void Tekken::d() {
    excuteCode[6] = DOWN;

    excuteMacro();
}