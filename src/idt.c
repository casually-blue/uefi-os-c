#include<stdint.h>

struct InterruptDescriptor {
  uint16_t interrupt_function_pointer_0_15;

  uint16_t selector;
  uint8_t interrupt_stack_table_offset;
  uint8_t type_attributes;

  uint16_t interrupt_function_pointer_16_31;
  uint32_t interrupt_function_pointer_32_63;
  uint32_t reserved;
};

struct IDT {
  struct InterruptDescriptor entries[256];
} __attribute__((__packed__));

struct IDTR {
  uint16_t limit;
  struct IDT *base;
} __attribute__((__packed__));

struct IDT idt;

struct IDTR idtr = {
  .limit = 255,
  .base = &idt,
};

struct interrupt_frame {
  uint64_t ip;
  uint64_t cs;
  uint64_t flags;
  uint64_t sp;
  uint64_t ss;
} __attribute__((__packed__));

__attribute__ ((interrupt))
void interrupt_handler(struct interrupt_frame *frame) {

}

__attribute__ ((interrupt)) 
void interrupt_error_handler(struct interrupt_frame *frame, uint64_t error_code) {

}

void setup_idt(void) { 
  struct InterruptDescriptor interrupt_descriptor = {
    .interrupt_function_pointer_0_15 = ((uint32_t)(uint64_t)interrupt_handler) & 0x0000FFFF,
    .selector = 1,
    .reserved = 0,
    .type_attributes = 0xEE,
    .interrupt_function_pointer_16_31 = (((uint32_t)(uint64_t)interrupt_handler) & 0xFFFF0000) >> 16,
    .interrupt_function_pointer_32_63 = ((uint64_t)interrupt_handler) >> 32,
  };

  struct InterruptDescriptor interrupt_descriptor_e = {
    .interrupt_function_pointer_0_15 = ((uint32_t)(uint64_t)interrupt_error_handler) & 0x0000FFFF,
    .selector = 1,
    .reserved = 0,
    .type_attributes = 0xEE,
    .interrupt_function_pointer_16_31 = (((uint32_t)(uint64_t)interrupt_error_handler) & 0xFFFF0000) >> 16,
    .interrupt_function_pointer_32_63 = ((uint64_t)interrupt_error_handler) >> 32,
  };



  for(int i=0; i < 256; i++) {
    if((i <= 7 && i >= 0) || (i == 9) || (i == 15) || (i == 16) || (i <=29 && i >= 18) || (i == 31)) {
      idt.entries[i] = interrupt_descriptor;
    }

    if((i == 8) || (i >= 10 &&  i <= 14) || (i == 17) || (i == 30)) {
      idt.entries[i] = interrupt_descriptor_e;
    }
  }

  __asm__("lidt %0" :: "m"(idtr));
}
