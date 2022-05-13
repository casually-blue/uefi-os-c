#include<efi_macros.h>

#include<print.h>
static unsigned short wchar_buffer[256] = {0};

void print_string(char* str, unsigned int length, EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* proto) {
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
