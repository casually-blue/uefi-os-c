#pragma once
#include<efi/efi.h>

typedef EFI_STATUS EFIStatus;
typedef EFI_HANDLE* EFIHandle;
typedef EFI_SYSTEM_TABLE* EFISystemTable;
typedef EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* EFITextOutputProtocol;

#define call_efi_proto(proto, method, ...) proto -> method(proto, ##__VA_ARGS__)

// Make efi type check the entry point
#define efi_entry(methodname) \
EFIStatus efi_entry_main(EFIHandle handle, EFISystemTable st) {\
  /* Setup system table pointer and indicate we are in boot services mdoe */\
  system_table._ = st; \
  system_table.image_handle = handle; \
  system_table.in_boot_services = true; \
  /* Call the actuall main method */\
  EFIStatus (*efimain)(EFIHandle h, EFISystemTable st) = methodname; \
  return efimain(handle, st); \
} \
 \
inline EFIStatus methodname

struct system_table_data {
EFISystemTable _;
EFIHandle image_handle;
unsigned int in_boot_services: 1;
};

extern struct system_table_data system_table;

EFIStatus efi_main(EFIHandle image_handle, EFISystemTable system_table);
