/* Definitions for the Xbox 360 SDK's target, powerpc-xsdk-elf: titles for
   the Xbox 360's retail kernel.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

/* Call as the console's own compiler does (-mcall-xsdk, rs6000.h).  */
#undef RS6000_ABI_NAME
#define RS6000_ABI_NAME "xsdk"

/* Pad a struct in registers as the argument itself is padded: 1, 2 and 4
   bytes at the low end, other sizes from the high byte, and the last part of
   a longer one from its register's high byte, as the console's own compiler
   passes them.  Without this, any block smaller than a register goes at its
   low end.  */
#define BLOCK_REG_PADDING(MODE, TYPE, FIRST) \
  (!(FIRST) ? PAD_UPWARD : targetm.calls.function_arg_padding (MODE, TYPE))

/* int32_t and uint32_t are int and unsigned int, as the console's own
   compiler and desktop compilers have them, rather than long, which
   newlib-stdint.h picks whenever long is 32 bits.  Code written for those
   compilers assumes int.  */
#undef STDINT_LONG32
#define STDINT_LONG32 0

/* Under the console's calling convention, have the assembler flag each
   object (-mxsdk, EF_PPC_XSDK), so that the linker refuses to link it with
   one built for another convention.  sysv4.h's spec, with -mxsdk added.  */
/* The console's processor raises an alignment exception for a
   floating-point register load or store at an address not aligned to its
   size, where integer loads and stores take any address, so a float register
   meets only memory GCC knows is aligned.  */
#undef RS6000_ALIGNED_FPR_MEMORY
#define RS6000_ALIGNED_FPR_MEMORY 1

#undef ASM_SPEC
#define ASM_SPEC "%(asm_cpu) \
%{,assembler|,assembler-with-cpp: %{mregnames} %{mno-regnames}} \
%{mrelocatable} %{mrelocatable-lib} %{" FPIE_OR_FPIC_SPEC ":-K PIC} \
%{memb|msdata=eabi: -memb} %{!mcall-*: -mxsdk} %{mcall-xsdk: -mxsdk}" \
ENDIAN_SELECT(" -mbig", " -mlittle", DEFAULT_ASM_ENDIAN)
