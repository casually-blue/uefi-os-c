#include<efi.h>

EFI_STATUS efi_main(EFI_HANDLE* image_handle, EFI_SYSTEM_TABLE* system_table) {
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* console_output = system_table->ConOut;

  console_output->OutputString(console_output, L"Hello World\n");



  EFI_BOOT_SERVICES* boot_services = system_table->BootServices;
  boot_services->ExitBootServices(image_handle, 0);

  return EFI_SUCCESS;
}
