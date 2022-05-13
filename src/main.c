#include<stdbool.h> 
#include<stdint.h>

#include<efi.h>
#include<efi_macros.h>

#include<os_main.h> 
#include<cpuid.h>
#include<print.h>

efi_entry(efi_main);

EFIStatus efi_main(EFIHandle image_handle, EFISystemTable system_table) {
  EFITextOutputProtocol console_output = system_table->ConOut;

  call_efi_proto(console_output, Reset, true);
  call_efi_proto(console_output, SetAttribute, 0x50);
  call_efi_proto(console_output, ClearScreen);

  call_efi_proto(console_output, OutputString, L"CPUID:\r\n\t");

  struct CPUID_BASIC info = get_cpuid_basic();

  print_string(info.genuine, 12, console_output);

  while(1) {

  }

  return EFI_SUCCESS;
}
