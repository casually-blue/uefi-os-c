#include<stdbool.h> 

#include<efi.h>
#include<efi_macros.h>

#include<os_main.h>


efi_entry(efi_main);

EFIStatus efi_main(EFIHandle image_handle, EFISystemTable system_table) {
  EFITextOutputProtocol console_output = system_table->ConOut;

  call_efi_proto(console_output, Reset, true);
  call_efi_proto(console_output, SetAttribute, 0x50);
  call_efi_proto(console_output, ClearScreen);

  while(1) {

  }

  return EFI_SUCCESS;
}
