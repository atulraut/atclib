# steps for linux porting .

# Introduction to Linux Porting #

Basic info about Linux Porting & Core BSP.

# Details #

## Building tool chain ##
  * Decide the TARGET
  * Decide on the Kernel/GCC/Glibc/Binutils version combo.
  * Procure patches for all the above, if any available.
  * Decide PREFIX variable, where to put the image.
  * Compile binutils.
  * Obtain suitable KERNEL HEADERS for your platform.
  * Compile minimal GCC.
  * Build Glibc.
  * Recompile full-featured GCC.


## Board Support Package BSP ##

# BSP has two components : The BSP hides the board & CPU-specific
details form the rest of the OS, so portability of drivers across multiple boards & CPUs becomes extremely easy.

### **1] The microprocessor support_###_

and**

### **2] The board specific routine_###_

A typical HAL for the board hardware will include :
  * Bootlaoder Support
  * Memory Map Support
  * System timers
  * Interrupt controller Support
  * Real-Time Clock (RTC)
  * Serial Support (debug & console)
  * Bus Support (PCI/ISA)
  * DMA Support
  * Power Management**

## Inserting BSP in Kernel Build Procedure ##

# The Linux HAL source code resides under arch/ and include/

&lt;asm-xxx&gt;

 (xxx = processor name) directories.
Under each processor directory, all boards bases on that CPU are categorized again into sub-directories.

  * **Kernel** : This directory contains the CPU-specific routines for initializing, IRQ set-up, interrupts, and traps routines.
  * **mm** : Contains the hardware-specific TLAB set-up and excepting-handling code.