#include "tekken.hpp"

void Tekken::b() {
    excuteCode[6] = 0x04;

    excuteMacro();
}

void Tekken::b_2() {
    excuteCode[6] = 0x04;
    excuteCode[7] = 0x80;

    excuteMacro();
}

void Tekken::bd() {
    excuteCode[6] = 0x06;

    excuteMacro();
}

void Tekken::f() {
    excuteCode[6] = 0x08;

    excuteMacro();
}

void Tekken::_1() {
    excuteCode[7] = 0x40;

    excuteMacro();
}

void Tekken::_134() {
    excuteCode[7] = 0x70;

    excuteMacro();
}

void Tekken::f_1() {
    excuteCode[6] = 0x08;
    excuteCode[7] = 0x40;

    excuteMacro();
}

void Tekken::f_2() {
    excuteCode[6] = 0x08;
    excuteCode[7] = 0x80;

    excuteMacro();
}

void Tekken::f_3() {
    excuteCode[6] = 0x08;
    excuteCode[7] = 0x10;

    excuteMacro();
}

void Tekken::fd() {
    excuteCode[6] = 0x0A;

    excuteMacro();
}

void Tekken::fd_1() {
    excuteCode[6] = 0x0A;
    excuteCode[7] = 0x40;

    excuteMacro();
}

void Tekken::fd_2() {
    excuteCode[6] = 0x0A;
    excuteCode[7] = 0x80;

    excuteMacro();
}

void Tekken::d() {
    excuteCode[6] = 0x02;

    excuteMacro();
}