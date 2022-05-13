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


void print_uint(int num, int base, EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* proto) {
  int i = 0;

  if(base == 16) {
    wchar_buffer[i++] = '0';
    wchar_buffer[i++] = 'x';
  }

  if(num == 0) {
    wchar_buffer[i] = '0';
    i++;
  }

  while (num != 0)
  {
    unsigned short rem = num % base;
    wchar_buffer[i] = rem > 10 ? (rem - 10) + 'A' : (rem + '0');
    num = num/base;
    i++;
  }

  wchar_buffer[i--] = 0;

  for(int j = (base == 16 ? 2 : 0); j < i; j++, i--) {
    unsigned short temp = wchar_buffer[i];
    wchar_buffer[i] = wchar_buffer[j];
    wchar_buffer[j] = temp;
  }

  call_efi_proto(proto, OutputString, wchar_buffer);
}
