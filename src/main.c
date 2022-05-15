#include<stdbool.h> 
#include<stdint.h>

#include<efi/efi-macros.h>
#include<efi/libc/stdio.h>

#include<cpuid.h>
#include<print.h>

struct system_table_data system_table;

void reset_efi_console() {
  if(!system_table.in_boot_services){
    return;
  }

  call_efi_proto(system_table._->ConOut, Reset, true);
  call_efi_proto(system_table._->ConOut, SetAttribute, 0x50);
  call_efi_proto(system_table._->ConOut, ClearScreen);

}

efi_entry(efi_main)() {

  reset_efi_console();

  printf("Hello World!\r\n");

  cpuid_basic_info basic = get_cpuid_basic_info();
  //cpuid_feature_info features = get_cpuid_feature_info();

  printf("CPU name: %.12s\r\n", basic.genuine);

  while(1) {

  }

  return EFI_SUCCESS;
}
