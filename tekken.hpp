#pragma once

// clang-format off
#include <Windows.h>
#include <TlHelp32.h>

#include <iostream>
#include <thread>
#include <vector>
#include <array>

#include "global.hpp"
#include "util.hpp"

struct Gstate {
  int facing;
  int charac_num;
  int frame;
};

class Tekken {
 public:
  Tekken();
  ~Tekken();

  std::vector<std::thread> workers;
  HANDLE hProcess;
  BYTE *baseAddress;
  LPVOID remoteAddress;

  Gstate gstate;
  bool isRunning;
  bool isForeground;

  void startRunningCheck();
  void startWatchingGstate();
  void startMacro();

  void excuteMacro();

  void b();
  void b_2();
  void _1();
  void _134();
  void f();
  void f_1();
  void f_2();
  void f_3();
  void fd();
  void fd_1();
  void fd_2();
  void d();
  void bd();
};