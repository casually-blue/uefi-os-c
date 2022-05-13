#include<stdbool.h> 
#include<stdint.h>

#include<efi.h>
#include<efi_macros.h>

#include<os_main.h> 
#include<cpuid.h>
#include<print.h>

efi_entry(efi_main);

void reset_efi_console(EFISystemTable st) {
  call_efi_proto(st->ConOut, Reset, true);
  call_efi_proto(st->ConOut, SetAttribute, 0x50);
  call_efi_proto(st->ConOut, ClearScreen);

}

EFIStatus efi_main(EFIHandle image_handle, EFISystemTable system_table) {
  reset_efi_console(system_table);

  call_efi_proto(system_table->ConOut, OutputString, L"CPUID:\r\n\t");

  struct CPUID_BASIC basic = get_cpuid_basic();

  print_string(basic.x1.genuine, CPUID_GENUINE_LEN, system_table->ConOut);

  print_string("\r\n\tmodel: ", 10, system_table->ConOut);
  print_uint(basic.x2.model, 16, system_table->ConOut);
  print_string("\r\n\tfamily: ", 14, system_table->ConOut);
  print_uint(basic.x2.family_id, 16, system_table->ConOut);
  print_string("\r\n\tfamily_ext: ", 18, system_table->ConOut);
  print_uint(basic.x2.ext_family_id, 16, system_table->ConOut);

  while(1) {

  }

  return EFI_SUCCESS;
}
