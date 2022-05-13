#pragma once
#include<stdint.h>

#define CPUID_GENUINE_LEN 12

struct CPUID_BASIC {
  uint32_t max_cpuid_input_val;
  char genuine[CPUID_GENUINE_LEN];
};

struct CPUID_BASIC get_cpuid_basic();
uint32_t get_cpuid_max_extension();



