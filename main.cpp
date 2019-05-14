#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "library.h"
#include "List.h"

SCENARIO("testing list") {
  void *DS = Init(2, 3);
  AddLecture(DS, 0, 0, 23);
  Quit(&DS);
}