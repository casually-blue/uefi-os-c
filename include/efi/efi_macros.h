#pragma once
#include"efi.h"

typedef EFI_STATUS EFIStatus;
typedef EFI_HANDLE* EFIHandle;
typedef EFI_SYSTEM_TABLE* EFISystemTable;
typedef EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* EFITextOutputProtocol;

#define call_efi_proto(proto, method, ...) proto -> method(proto, ##__VA_ARGS__)

// Make efi type check the entry point
#define efi_entry(methodname) \
EFIStatus efi_entry_main(EFIHandle handle, EFISystemTable st) {\
  EFIStatus (*efimain)(EFIHandle h, EFISystemTable st) = methodname; \
  return efimain(handle, st); \
}
