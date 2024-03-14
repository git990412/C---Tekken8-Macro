#pragma once
#include <Windows.h>

#include <cstdint>
#include <iostream>
#include <vector>

void s_sleep(double ms);

void neutral();

int findValueByPointer(HANDLE hProcess, BYTE* baseAddress, int* offsets, int size);

bool is_key_down(int key);