#pragma once
#include<efi/efi.h>

void print_string(char* string, unsigned int length, EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* proto);