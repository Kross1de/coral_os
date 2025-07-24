/*==============================================================================
Copyright (C) Kross1de. All rights reserved.
==============================================================================*/

	//----------------------------------------------------------------------
	// includes
	#include	"../library/color.h"
	#include	"../library/color.c"
	#include	"../library/font.h"
	#include	"../library/font.c"
	#include	"config.h"
	#include	"terminal.h"
	//----------------------------------------------------------------------

// limine definitions
#include	"../limine/limine.h"

struct terminal term;

// entry point
void _entry( void ) {
	// linear framebuffer is available (with 32 bits per pixel)?
	if( limine_framebuffer_request.response == NULL || limine_framebuffer_request.response -> framebuffer_count != 1 || limine_framebuffer_request.response -> framebuffers[ 0 ] -> bpp != 32 )
		// no, infinite loop (screen will be black)
		for(;;);

	// set pointer to first pixel of video memory area
	uint32_t *framebuffer = (uint32_t *) limine_framebuffer_request.response -> framebuffers[ 0 ] -> address;
	uint32_t width = limine_framebuffer_request.response -> framebuffers[ 0 ] -> width;
	uint32_t height = limine_framebuffer_request.response -> framebuffers[ 0 ] -> height;
	uint32_t pitch = limine_framebuffer_request.response -> framebuffers[ 0 ] -> pitch;

	// initialize terminal
	terminal_init(&term, framebuffer, width, height, pitch);

	// show welcome message
	const char welcome[] = "Hello, World\n";
	terminal_print(&term, welcome, sizeof(welcome) - 1);

	// create binary memory map
	init_memory();

	// infinite loop
	for(;;);
}