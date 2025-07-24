/*==============================================================================
Copyright (C) Kross1de. All rights reserved.
==============================================================================*/

#include "../std.h"

void kernel_page_clean(uintptr_t address, uint64_t n) {
        uint64_t *page = (uint64_t *)address;
        for (uint64_t i = 0; i < n << STD_SHIFT_512; i++) page[i] = EMPTY;
}