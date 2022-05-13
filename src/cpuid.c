#include<cpuid.h>

#include<stdint.h>


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
  cpuid_raw(
      0,
      0, 
      &basic.x1.cpuid[0],
      &basic.x1.cpuid[1],
      &basic.x1.cpuid[3],
      &basic.x1.cpuid[2]
      );
  cpuid_raw(
      1,
      0,
      &basic.x2.cpuid[0],
      &basic.x2.cpuid[1],
      &basic.x2.cpuid[2],
      &basic.x2.cpuid[3]
      );
  return basic;
}

uint32_t get_cpuid_max_extension() {
  uint32_t r; uint32_t rest;
  cpuid_raw(0x80000001, 0, &r, &rest, &rest, &rest);
  return r;
}
