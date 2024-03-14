#pragma once
#include <array>

using namespace std;

extern const wchar_t *TEKKEN_PROCESS_NAME;
extern const wchar_t *TEKKEN_WINDOW_NAME;

extern array<unsigned char, 29> shellCode;
extern array<unsigned char, 14> jmpCode;
extern array<unsigned char, 29> excuteCode;

extern const array<int, 2> P1_OFFSETS;
extern const array<int, 2> P2_OFFSETS;
extern const array<int, 2> REVERSE_OFFSETS;

extern const int FACING_OFFSET;
extern const int CHARAC_NUM_OFFSET;
extern const int FRAME_OFFSET;

#define BACK 0x04
#define DOWN 0x02
#define FORWARD 0x08
#define UP 0x01
#define L_HAND 0x40
#define R_HAND 0x80
#define L_KICK 0x10
#define R_KICK 0x20

#define JMP_POINTER 0x5640F5E

#define JIN 6
#define KAZUYA 8
#define DEVIL_JIN 12
#define RAINA 28