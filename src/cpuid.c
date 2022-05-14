#pragma clang diagnostic ignored "-Waddress-of-packed-member"

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

cpuid_basic_info get_cpuid_basic_info() {
  cpuid_basic_info basic;
  cpuid_raw(
      0,
      0, 
      &basic.regs.eax,
      &basic.regs.ebx,
      &basic.regs.edx,
      &basic.regs.ecx
      );
  return basic;
}

cpuid_feature_info get_cpuid_feature_info() {
  cpuid_feature_info features;
  cpuid_raw(
      1,
      0,
      &features.regs.eax,
      &features.regs.ebx,
      &features.regs.ecx,
      &features.regs.edx
      );
  return features;
}

uint32_t get_cpuid_max_extension() {
  uint32_t r; uint32_t rest;
  cpuid_raw(0x80000001, 0, &r, &rest, &rest, &rest);
  return r;
}

#pragma clang diagnostic warning "-Waddress-of-packed-member"
