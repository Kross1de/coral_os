/*==============================================================================
Copyright (C) Kross1de. All rights reserved.
==============================================================================*/

#include "config.h"

struct _kernel *kernel = EMPTY;

// limine requests
volatile struct limine_framebuffer_request limine_framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0
};

volatile struct limine_memmap_request limine_memmap_request = {
	.id = LIMINE_MEMMAP_REQUEST,
	.revision = 0
};

volatile struct limine_rsdp_request limine_rsdp_request = {
	.id = LIMINE_RSDP_REQUEST,
	.revision = 0
};