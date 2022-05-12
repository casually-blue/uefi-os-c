#include<efi.h>
#include<protocol/efi-gop.h>

void setup_idt(void);

EFI_STATUS efi_main(EFI_HANDLE* image_handle, EFI_SYSTEM_TABLE* system_table) {
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* console_output = system_table->ConOut;

  console_output->Reset(console_output, 1);
  console_output->ClearScreen(console_output);
  console_output->OutputString(console_output, L"Hello World\n");



  EFI_BOOT_SERVICES* boot_services = system_table->BootServices;

  EFI_GUID gopGUID = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
  EFI_GRAPHICS_OUTPUT_PROTOCOL* graphics;
  if(boot_services->LocateProtocol(&gopGUID, 0, (void**) &graphics) != EFI_SUCCESS) {
    console_output->OutputString(console_output, L"Error, could not find graphics protocol");
  }

  if(graphics->SetMode(graphics, 0) != EFI_SUCCESS){
    console_output->OutputString(console_output, L"Could not set video mode");
  }

  int* base = (int*)graphics->Mode->FrameBufferBase;
  unsigned long length = graphics->Mode->FrameBufferSize;

  boot_services->ExitBootServices(image_handle, 0);

  setup_idt();

  for(int i = 0; i < length; i++) {
    base[i] = 12321;
  }

  while(1) {

  }

  return EFI_SUCCESS;
}
