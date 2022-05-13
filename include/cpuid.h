#pragma once
#include<stdint.h>

#define CPUID_GENUINE_LEN 12

struct CPUID_BASIC {
  union {
    struct {
      uint32_t max_cpuid_input_val;
      char genuine[CPUID_GENUINE_LEN];
    };
    uint32_t cpuid[4];
  } x1;

  union {
    struct {
      unsigned int stepping_id: 4;
      unsigned int model: 4;
      unsigned int family_id: 4;
      unsigned int proc_type: 2;
      unsigned int reserved2: 2;
      unsigned int ext_model_id: 4;
      unsigned int reserved1: 4;
      unsigned int ext_family_id: 8;
      uint32_t reserved[3];
    } __attribute__((__packed__));
    uint32_t cpuid[4];
  } __attribute__((__packed__)) x2;
} __attribute__((__packed__));

struct CPUID_BASIC get_cpuid_basic();
uint32_t get_cpuid_max_extension();



