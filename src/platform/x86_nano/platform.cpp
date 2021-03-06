#include <os>
#include "../x86_pc/acpi.hpp"
#include "../x86_pc/idt.hpp"

void __arch_poweroff()
{
  x86::ACPI::shutdown();
  __builtin_unreachable();
}

void __platform_init()
{
  // setup CPU exception handlers
  x86::idt_initialize_for_cpu(0);
}

void __arch_reboot(){}
void __arch_enable_legacy_irq(unsigned char){}
void __arch_disable_legacy_irq(unsigned char){}


void SMP::global_lock() noexcept {}
void SMP::global_unlock() noexcept {}
int SMP::cpu_id() noexcept { return 0; }
int SMP::cpu_count() noexcept { return 1; }


// Support for the boot_logger plugin.
__attribute__((weak))
bool os_enable_boot_logging = false;
