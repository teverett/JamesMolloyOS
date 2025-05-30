// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

#include "monitor.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "paging.h"
#include "multiboot.h"
#include "fs.h"
#include "initrd.h"
#include "task.h"
#include "syscall.h"

struct multiboot;

extern u32int stack_bottom;
extern u32int stack_top;
extern u32int placement_address;
u32int initial_esp;

int main(struct multiboot *mboot_ptr, u32int initial_stack)
{
    // find the stack defined in the linker script
    u32int kernel_stack_bottom = (u32int) &stack_bottom;
    u32int kernel_stack_top = (u32int) &stack_top;
    
    // save the initial stack pointer (task.c::move_stack needs this)
    initial_esp = kernel_stack_bottom;

    // set the stack up
    asm volatile("mov %0, %%esp" : : "r" (kernel_stack_bottom));

    // Initialise all the ISRs and segmentation
    monitor_write("initialising descriptor tables\n");
    init_descriptor_tables();
    // Initialise the screen (by clearing it)
    monitor_clear();

    // Initialise the PIT to 100Hz
    monitor_write("initialising PIT\n");
    asm volatile("sti");
    init_timer(50);

    // Find the location of our initial ramdisk.
    ASSERT(mboot_ptr->mods_count > 0);
    u32int initrd_location = *((u32int*)mboot_ptr->mods_addr);
    u32int initrd_end = *(u32int*)(mboot_ptr->mods_addr+4);
    // Don't trample our module with placement accesses, please!
    placement_address = initrd_end;

    // Start paging.
    monitor_write("initialising paging\n");
    initialise_paging();

    // Start multitasking.
    monitor_write("initialising tasking\n");
    initialise_tasking();

    // Initialise the initial ramdisk, and set it as the filesystem root.
    monitor_write("initialising root filesystem\n");
    fs_root = initialise_initrd(initrd_location);

    monitor_write("initialising syscalls\n");
    initialise_syscalls();

    monitor_write("switching to usermode\n");
    switch_to_user_mode();

    syscall_monitor_write("Hello, user world!\n");
    return 0;
}
