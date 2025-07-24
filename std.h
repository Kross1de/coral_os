/*==============================================================================
Copyright (C) Kross1de. All rights reserved.
==============================================================================*/

#ifndef STD
	#define STD

	// definitions, that are always nice to have
	#include "stdint.h"
	#include "stddef.h"
	#include "stdarg.h"
	#include "macro.h"

	#define EMPTY       0

	#define TRUE        1
	#define FALSE       0

	#define LOCK        TRUE
	#define UNLOCK      FALSE

	#define STD_VIDEO_DEPTH_shift   2
	#define STD_VIDEO_DEPTH_byte    4
	#define STD_VIDEO_DEPTH_bit     32
	#define STD_COLOR_WHITE         0xFFFFFFFF

	#define STD_SHIFT_PAGE          12
	#define STD_SHIFT_512           9
	#define STD_PAGE_BYTE           (1 << STD_SHIFT_PAGE)
	#define KERNEL_PAGE_MIRROR      0xFFFF800000000000

	struct _kernel {
		uint64_t *memory_base_address;
	};

	// page.c
	void kernel_page_clean(uintptr_t address, uint64_t n);
	// mem.c
	void init_memory(void);

	// externs
	extern struct _kernel *kernel;
	extern volatile struct limine_framebuffer_request limine_framebuffer_request;
	extern volatile struct limine_memmap_request limine_memmap_request;
	extern volatile struct limine_rsdp_request limine_rsdp_request;
	extern struct terminal term;
#endif