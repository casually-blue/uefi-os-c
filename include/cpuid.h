#pragma once
#include<stdint.h>
typedef unsigned int uint;
#define bit(name) uint name: 1

#define CPUID_GENUINE_LEN 12

struct __attribute__((__packed__)) CPUID_BASIC {
  union {
    struct __attribute__((__packed__)) {
      uint32_t max_cpuid_input_val;
      char genuine[CPUID_GENUINE_LEN];
    };
    uint32_t cpuid[4];
  } x1;

  union {
    struct __attribute__((__packed__)) {
      unsigned int stepping_id: 4;
      unsigned int model: 4;
      unsigned int family_id: 4;
      unsigned int proc_type: 2;
      unsigned int : 2;
      unsigned int ext_model_id: 4;
      unsigned int : 4;
      unsigned int ext_family_id: 8;

      uint brand_index: 8;
      uint cflush_line_size: 8;
      uint max_addressable_logical_processor_ids: 8;
      uint initial_apic_id: 8;

      struct __attribute__((__packed__)) {
        bit(supports_streaming_simd3);
        bit(supports_pclmulqdq);
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
        bit();

        bit(supports_process_context_identifiers);
        bit(supports_prefetch_memory_mapped_data);
        bit(supports_sse4_1);
        bit(supports_sse4_2);
        bit(supports_x2APIC);
        bit(supports_movbe);
        bit(supports_popcnt);
        bit(supporgs_apic_oneshot_tsc_deadline);
        bit(supports_aesni);
        bit(supports_osxsave);
        bit(supports_avx_extensions);
        bit(supports_16bit_floating_converison_instructions);
        bit(supports_rdrand);
        bit();

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
        bit();
        bit(supports_sysenter_sysexit);
        bit(has_memory_type_range_registers);
        bit(supports_page_global_bit);
        bit(supports_machine_check_architecture);
        bit(supports_cmov);
        bit(supports_page_attribute_table);
        bit(supports_page_size_extension_36bit);
        bit(supports_processor_serial_number);
        bit(supports_cflush);
        bit();
        bit(supports_debug_store);
        bit(supports_acpi);
        bit(supports_intel_mmx);
        bit(supports_fxsave_fxstor);
        bit(supports_sse);
        bit(supports_sse2);
        bit(supports_self_snoop);
        bit(max_apic_ids_field_valid);
        bit(supports_thermal_monitor);
        bit();
        bit(supports_pending_break_enable);
      } feature_information;
    };
    uint32_t cpuid[4];
  } x2;
};

struct CPUID_BASIC get_cpuid_basic();
uint32_t get_cpuid_max_extension();



