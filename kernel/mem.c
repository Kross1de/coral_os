/*==============================================================================
Copyright (C) Kross1de. All rights reserved.
==============================================================================*/

#include "config.h"
#include "terminal.h"
#include "../std.h"

void init_memory(void) {
        if (limine_memmap_request.response == NULL || !limine_memmap_request.response->entry_count) {
                terminal_print(&term, "Problems appeared!\n", 21);
                while (TRUE);
        }

        uint64_t largest_byte = EMPTY;
        uint64_t overall_page = EMPTY;

        for (uint64_t i = 0; i < limine_memmap_request.response->entry_count; i++) {
                if (limine_memmap_request.response->entries[i]->type == LIMINE_MEMMAP_USABLE) {
                        overall_page += limine_memmap_request.response->entries[i]->length >> STD_SHIFT_PAGE;
                        kernel_page_clean(limine_memmap_request.response->entries[i]->base, 
                                        limine_memmap_request.response->entries[i]->length >> STD_SHIFT_PAGE);

                        if (largest_byte < limine_memmap_request.response->entries[i]->length) {
                                kernel = (struct _kernel *) (limine_memmap_request.response->entries[i]->base | KERNEL_PAGE_MIRROR);
                                largest_byte = limine_memmap_request.response->entries[i]->length;
                        }
                }
        }

        kernel->memory_base_address = (uint64_t *) (MACRO_PAGE_ALIGN_UP((uintptr_t) kernel + sizeof(struct _kernel)));
}