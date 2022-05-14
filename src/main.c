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

  cpuid_basic_info basic = get_cpuid_basic_info();
  cpuid_feature_info features = get_cpuid_feature_info();

  while(1) {

  }

  return EFI_SUCCESS;
}
