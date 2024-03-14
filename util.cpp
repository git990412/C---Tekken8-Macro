#include "util.hpp"

void s_sleep(double ms) {
    LARGE_INTEGER frequency;
    LARGE_INTEGER startCounter;
    LARGE_INTEGER endCounter;

    // 타이머의 주파수를 가져옵니다.
    QueryPerformanceFrequency(&frequency);

    // 현재 카운터 값을 가져옵니다.
    QueryPerformanceCounter(&startCounter);

    // 원하는 시간까지 루프를 돌면서 대기합니다.
    while (true) {
        QueryPerformanceCounter(&endCounter);
        long long elapsed = endCounter.QuadPart - startCounter.QuadPart;
        double usElapsed = (double)elapsed * 1000000.0 / frequency.QuadPart;
        if (usElapsed >= ms * 1000) break;
    }
}

void neutral() { s_sleep(16.8); }

int findValueByPointer(HANDLE hProcess, BYTE* baseAddress, int* offsets, int size) {
    int64_t result = (int64_t)baseAddress;

    for (int i = 0; i < size; i++) {
        ReadProcessMemory(hProcess, (LPVOID)(result + (int64_t)offsets[i]), &result, sizeof(result), NULL);
    }

    return (int)result;
}

bool is_key_down(int key) { return (GetAsyncKeyState(key) & 1) == 1; }