#include<stdint.h>

#include<cpuid.h>

void cpuid_raw(uint32_t eax_in, uint32_t ecx_in, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx) {
  __asm__ __volatile__(
      "cpuid"
      : "=a" (*eax),
      "=b" (*ebx),
      "=c" (*ecx),
      "=d" (*edx)
      : "a" (eax_in), "c" (ecx_in)
      );
}

struct CPUID_BASIC get_cpuid_basic() {
  struct CPUID_BASIC basic;
  char* gen = basic.genuine;
  cpuid_raw(
      0,
      0, 
      (void*)&basic.max_cpuid_input_val, 
      (void*)basic.genuine, 
      (void*)basic.genuine+8, 
      (void*)basic.genuine+4
      );

  return basic;
}

uint32_t get_cpuid_max_extension() {
  uint32_t r; uint32_t rest;
  cpuid_raw(0x80000001, 0, &r, &rest, &rest, &rest);
  return r;
}


