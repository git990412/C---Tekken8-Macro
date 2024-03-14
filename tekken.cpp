#include "tekken.hpp"

Tekken::Tekken() {
    isRunning = false;
    startRunningCheck();
    startWatchingGstate();
    startMacro();
}

Tekken::~Tekken() {
    for (auto &t : workers) {
        t.join();
    }
}

void Tekken::startRunningCheck() {
    std::thread t([this]() {
        while (true) {
            HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            PROCESSENTRY32W entry;
            entry.dwSize = sizeof(entry);

            bool foundTekkenProcess = false;

            if (Process32FirstW(snapshot, &entry) == 1) {
                while (true) {
                    if (wcscmp(entry.szExeFile, TEKKEN_PROCESS_NAME) == 0) {
                        foundTekkenProcess = true;

                        if (!isRunning) {
                            isRunning = true;
                            hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, entry.th32ProcessID);

                            // if success cout the process HANDLE
                            if (hProcess != NULL) {
                                std::cout << std::hex << hProcess << std::endl;

                                HANDLE module_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, entry.th32ProcessID);
                                MODULEENTRY32W module_entry;
                                module_entry.dwSize = sizeof(module_entry);

                                if (Module32FirstW(module_snapshot, &module_entry) == 1) {
                                    baseAddress = module_entry.modBaseAddr;

                                    std::cout << "base address : " << std::hex << (int64_t)baseAddress << std::endl;
                                }

                                int64_t jmp_addr = (int64_t)baseAddress + 0x5640F5E;

                                for (int i = 16; i < 22; i++) {
                                    shellCode[i] = ((BYTE *)&jmp_addr)[i - 16];
                                    excuteCode[i + 3] = ((BYTE *)&jmp_addr)[i - 16];
                                }

                                remoteAddress = VirtualAllocEx(hProcess, NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

                                for (int i = 3; i < 10; i++) {
                                    jmpCode[i] = ((BYTE *)&remoteAddress)[i - 3];
                                }

                                // write shell code
                                WriteProcessMemory(hProcess, remoteAddress, shellCode.data(), shellCode.size(), NULL);

                                // write jmp code
                                WriteProcessMemory(hProcess, (LPVOID)((int64_t)baseAddress + 0x5640F51), jmpCode.data(), jmpCode.size(),
                                                   NULL);

                                CloseHandle(module_snapshot);
                            }
                        }

                        break;
                    }

                    if (Process32NextW(snapshot, &entry) == 0) {
                        break;
                    }
                }
            }

            CloseHandle(snapshot);

            if (!foundTekkenProcess && isRunning) {
                CloseHandle(hProcess);

                isRunning = false;
                hProcess = NULL;
                baseAddress = NULL;
                remoteAddress = NULL;
                gstate = {0, 0, 0};
                isForeground = false;
            }

            if (isRunning) {
                isForeground = GetForegroundWindow() == FindWindowW(NULL, TEKKEN_WINDOW_NAME);
            }

            Sleep(1000);
        }
    });

    workers.push_back(std::move(t));
}

void Tekken::startWatchingGstate() {
    std::thread t([this]() {
        while (true) {
            if (isForeground) {
                std::array<int, 2> player_offsets = P1_OFFSETS;

                if (findValueByPointer(hProcess, baseAddress, (int *)REVERSE_OFFSETS.data(), REVERSE_OFFSETS.size()) == 0) {
                    player_offsets[1] = 0x38;
                }

                std::array<int, 3> facing_offsets;
                std::copy(player_offsets.begin(), player_offsets.end(), facing_offsets.begin());
                facing_offsets[2] = FACING_OFFSET;

                std::array<int, 3> charac_num_offsets;
                std::copy(player_offsets.begin(), player_offsets.end(), charac_num_offsets.begin());
                charac_num_offsets[2] = CHARAC_NUM_OFFSET;

                std::array<int, 3> frame_offsets;
                std::copy(player_offsets.begin(), player_offsets.end(), frame_offsets.begin());
                frame_offsets[2] = FRAME_OFFSET;

                gstate.facing = findValueByPointer(hProcess, baseAddress, facing_offsets.data(), facing_offsets.size());
                gstate.charac_num = findValueByPointer(hProcess, baseAddress, charac_num_offsets.data(), charac_num_offsets.size());
                gstate.frame = findValueByPointer(hProcess, baseAddress, frame_offsets.data(), frame_offsets.size());
            };

            s_sleep(1);
        }
    });

    workers.push_back(std::move(t));
}

void Tekken::startMacro() {
    std::thread t([this]() {
        while (true) {
            // Q 백대쉬
            if (is_key_down(0x51)) {
                b();
                neutral();
                bd();
                neutral();
                b();
            }

            if (gstate.charac_num == JIN || gstate.charac_num == DEVIL_JIN) {
                // E 초풍
                if (is_key_down(0x45)) {
                    f();
                    neutral();
                    d();
                    fd_2();
                }

                // Z 웨이브
                if (is_key_down(0x5A)) {
                    f();
                    neutral();
                    d();
                    fd();
                    f();
                }

                // F 대초
                if (is_key_down(0x46)) {
                    d();
                    fd_2();
                }
            }
            if (gstate.charac_num == JIN || gstate.charac_num == DEVIL_JIN) {
                // R 46_2
                if (is_key_down(0x52)) {
                    b();
                    neutral();
                    f_2();
                }
            }

            s_sleep(1);
        }
    });

    workers.push_back(std::move(t));
}

void Tekken::excuteMacro() {
    if (gstate.facing == 1) {
        int value = excuteCode[6] - 3;

        if (0 < value && value < 4) {
            excuteCode[6] += 4;
        } else if (value > 4) {
            excuteCode[6] -= 4;
        }
    }
    // write excute code
    WriteProcessMemory(hProcess, remoteAddress, excuteCode.data(), excuteCode.size(), NULL);

    s_sleep(16.8);

    // excute shell code
    WriteProcessMemory(hProcess, remoteAddress, shellCode.data(), shellCode.size(), NULL);

    excuteCode[6] = 0x00;
    excuteCode[7] = 0x00;
}