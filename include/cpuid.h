#pragma once
#include<stdint.h>

struct CPUID_BASIC {
  uint32_t max_cpuid_input_val;
  char genuine[13];
};

struct CPUID_BASIC get_cpuid_basic();
uint32_t get_cpuid_max_extension();



