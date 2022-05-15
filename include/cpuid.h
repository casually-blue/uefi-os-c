#pragma once
#include<stdint.h>
typedef unsigned int uint;
#define bit(name) uint name: 1
#define reserved(n) uint : n
#define bits(n, name) uint name: n

#define CPUID_GENUINE_LEN 12

typedef struct __attribute__((__packed__)){
  uint32_t eax;
  uint32_t ebx;
  uint32_t ecx;
  uint32_t edx;
} cpuid_regs;

#define cpuid_union(name, data) \
  typedef union __attribute__((__packed__)) {\
    struct __attribute__((__packed__)) data; \
    cpuid_regs regs;\
  } name; \
  _Static_assert(sizeof(name) == 16, "CPUID struct must be 128 bits wide")

cpuid_union(cpuid_basic_info, {
    uint32_t max_cpuid_input_val;
    char genuine[CPUID_GENUINE_LEN];
    });


cpuid_union(cpuid_feature_info, {
    bits(4, stepping_id);
    bits(4, model);
    bits(4, family_id);
    bits(2, proc_type);
    reserved(2);
    bits(4, ext_model_id);
    reserved(4);
    bits(8, ext_family_id);

    bits(8, brand_index);
    bits(8, cflush_line_size);
    bits(8, max_addressable_logical_processor_ids);
    bits(8, initial_apic_id);

    union __attribute__((__packed__)) {
    struct __attribute__((__packed__)) {
    reserved(1);
    bit(supports_pclmulqdq);
    } instruction_support;
    struct __attribute__((__packed__)) {
    bit(supports_streaming_simd3);
    reserved(1);
    bit(supports_ds64);
    bit(supports_monitor);
    bit(supports_ds_cpl);
    bit(supports_vmx);
    bit(supports_smx);
    bit(supports_enhanced_speed_step);
    bit(supports_thermal_monitor2);
    bit(supports_supplemental_streaming_simd3);
    bit(supports_l1_context_id);
    bit(supports_ia32_debug_interface);
    bit(supports_fma_extensions);
    bit(supports_cmpxchg16b);
    bit(supports_xTPR_update_control);
    bit(supports_perfmon_debug_capability);
    reserved(1);

    bit(supports_process_context_identifiers);
    bit(supports_prefetch_memory_mapped_data);
    bit(supports_sse4_1);
    bit(supports_sse4_2);
    bit(supports_x2APIC);
    bit(supports_movbe);
    bit(supports_popcnt);
    bit(supporgs_apic_oneshot_tsc_deadline);
    bit(supports_aesni);
    bit(supports_xsave);
    bit(supports_osxsave);
    bit(supports_avx_extensions);
    bit(supports_16bit_floating_converison_instructions);
    bit(supports_rdrand);

    reserved(1);

    bit(has_x87_fpu);
    bit(has_virtual_8086_enhancements);
    bit(supports_debugging_extensions);
    bit(supports_4mb_pages);
    bit(has_time_stamp_counter);
    bit(rw_msrs);
    bit(supports_physical_address_extension);
    bit(supports_machine_check_exception);
    bit(supports_cmpxchg8b);
    bit(has_on_chip_apic);
    reserved(1);
    bit(supports_sysenter_sysexit);
    bit(has_memory_type_range_registers);
    bit(supports_page_global_bit);
    bit(supports_machine_check_architecture);
    bit(supports_cmov);
    bit(supports_page_attribute_table);
    bit(supports_page_size_extension_36bit);
    bit(supports_processor_serial_number);
    bit(supports_cflush);
    reserved(1);
    bit(supports_debug_store);
    bit(supports_acpi);
    bit(supports_intel_mmx);
    bit(supports_fxsave_fxstor);
    bit(supports_sse);
    bit(supports_sse2);
    bit(supports_self_snoop);
    bit(max_apic_ids_field_valid);
    bit(supports_thermal_monitor);
    reserved(1);
    bit(supports_pending_break_enable);
    } feature_information;
    };
}) ;

cpuid_basic_info get_cpuid_basic_info();
cpuid_feature_info get_cpuid_feature_info();

uint32_t get_cpuid_max_extension();



