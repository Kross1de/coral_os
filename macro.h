/*==============================================================================
Copyright (C) Kross1de. All rights reserved.
==============================================================================*/

#ifndef macro
        #define MACRO

        #define MACRO_DEBUF() { __asm__ volatile("xchg %bx, %bx"); }
#endif