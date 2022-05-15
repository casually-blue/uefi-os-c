#include<stdarg.h>

#include<efi/efi.h>
#include<efi/efi-macros.h>
#include<efi/libc/stdlib.h>
#include<efi/libc/string.h> 

#include<print.h>


int print_char(char c) {
  uint16_t ca[2] = {c, 0};
  return call_efi_proto(system_table._->ConOut, OutputString, ca);
}

int print_string(char* string, int specific_len) {
  uint16_t* buffer;
  int length = specific_len == -1 ? strlen(string): specific_len;

  buffer = malloc(sizeof(int16_t) * length + 1);

  for(int index = 0; index < length; index++) {
    buffer[index] = string[index];
  }
  buffer[length] = 0;

  call_efi_proto(system_table._->ConOut, OutputString, buffer);

  free(buffer);
  return 0;
}

int parse_format_specifier(const char* fmt, int index, int* specified_len) {
  int start_index = index;
  if(fmt[index] == '.') {
    index++;
    *specified_len = 0;
    while(fmt[index] >= '0' && fmt[index] <='9') {
      *specified_len *= 10;
      *specified_len += fmt[index] - '0';
      index++;
    }
  }

  return index - start_index;
}

int printf(const char* fmt, ...) {
  if(!system_table.in_boot_services)
    return 1;

  va_list ap;
  va_start(ap, fmt);


  int specified_len = -1;
  for(int index = 0; fmt[index] != 0; index++){
    switch(fmt[index]) {
      case '%':
        index++;
        index += parse_format_specifier(fmt, index, &specified_len);
        switch(fmt[index]) {
          case 's':
            {
              if(print_string(va_arg(ap, char*), specified_len))
                return 1;
            }
            break;
        }
        break;
      default:
        if(print_char(fmt[index])) {
          return 1;
        }
        break;
    }
  }

  return 0;
}
