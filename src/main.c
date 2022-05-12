#include<efi.h>
#include<protocol/efi-gop.h>

void setup_idt(void);

EFI_GRAPHICS_OUTPUT_PROTOCOL* setup_graphics(EFI_SYSTEM_TABLE* system_table) {
  EFI_BOOT_SERVICES* boot_services = system_table->BootServices;

  EFI_GUID graphics_output_protocol_guid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

  EFI_GRAPHICS_OUTPUT_PROTOCOL* graphics_output_protocol;
  if(boot_services->LocateProtocol(&graphics_output_protocol_guid, 0, (void**) &graphics_output_protocol) != EFI_SUCCESS) {
    system_table->ConOut->OutputString(system_table->ConOut, L"Error, could not find graphics protocol");
  }

  if(graphics_output_protocol->SetMode(graphics_output_protocol, 0) != EFI_SUCCESS){
    system_table->ConOut->OutputString(system_table->ConOut, L"Could not set video mode");
  }

  return graphics_output_protocol;
}

EFI_STATUS efi_main(EFI_HANDLE* image_handle, EFI_SYSTEM_TABLE* system_table) {
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* console_output = system_table->ConOut;

  console_output->OutputString(console_output, L"Hello World\n");


  EFI_GRAPHICS_OUTPUT_PROTOCOL* graphics = setup_graphics(system_table);
  

  int* base = (int*)graphics->Mode->FrameBufferBase;
  unsigned long length = graphics->Mode->FrameBufferSize;

  system_table->BootServices->ExitBootServices(image_handle, 0);

  setup_idt();

  for(int i = 0; i < length; i++) {
    base[i] = 12321;
  }

  __asm__("int $13");

  while(1) {

  }

  return EFI_SUCCESS;
}
