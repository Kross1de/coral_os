/*==============================================================================
Copyright (C) Kross1de. All rights reserved.
==============================================================================*/

#ifndef MACRO
        #define MACRO

        #define MACRO_DEBUF() { __asm__ volatile("xchg %bx, %bx"); }
        #define MACRO_PAGE_ALIGN_UP(address) (((address) + (STD_PAGE_BYTE - 1)) & ~(STD_PAGE_BYTE - 1))
        #define MACRO_PAGE_ALIGN_DOWN(address) ((address) & ~(STD_PAGE_byte - 1))
#endif