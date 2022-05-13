#include<stdbool.h> 
#include<stdint.h>

#include<efi.h>
#include<efi_macros.h>

#include<os_main.h>

struct CPUID_BASIC {
  uint32_t max_cpuid_input_val;
  char genuine[13];
};

unsigned short wchar_buffer[256] = {0};

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

void get_cpuid_basic(struct CPUID_BASIC* basic) {
  char* gen = basic->genuine;
  cpuid_raw(
      0,
      0, 
      (void*)&basic->max_cpuid_input_val, 
      (void*)gen, 
      (void*)gen+8, 
      (void*)gen+4
      );
}

void print_string(char* str, int length, EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* proto) {
  if(length > 255) {
    call_efi_proto(proto, OutputString, L"Error string to long");
    return;
  }
  wchar_buffer[length] = 0;
  for(int i=0; i < length; i++) {
    wchar_buffer[i] = str[i];
  }

  call_efi_proto(proto, OutputString, wchar_buffer);
}

uint32_t get_cpuid_max_extension() {
  uint32_t r; uint32_t rest;
  cpuid_raw(0x80000001, 0, &r, &rest, &rest, &rest);
  return r;
}


efi_entry(efi_main);

EFIStatus efi_main(EFIHandle image_handle, EFISystemTable system_table) {
  EFITextOutputProtocol console_output = system_table->ConOut;

  call_efi_proto(console_output, Reset, true);
  call_efi_proto(console_output, SetAttribute, 0x50);
  call_efi_proto(console_output, ClearScreen);

  call_efi_proto(console_output, OutputString, L"CPUID:\r\n\t");

  struct CPUID_BASIC info;
  get_cpuid_basic(&info);

  print_string(info.genuine, 12, console_output);

  while(1) {

  }

  return EFI_SUCCESS;
}
