/*==============================================================================
Copyright (C) Kross1de. All rights reserved.
==============================================================================*/

	//----------------------------------------------------------------------
	// constants, structures, definitions
	// static --------------------------------------------------------------
	#include	"../library/color.h"
	#include	"../library/color.c"
	#include	"../library/font.h"
	#include	"../library/font.c"
	#include	"terminal.h"
	//----------------------------------------------------------------------

// limine definitions
#include	"../limine/limine.h"

// limine requests
static volatile struct limine_framebuffer_request limine_framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0
};

// our mighty init
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
	struct terminal term;
	terminal_init(&term, framebuffer, width, height, pitch);

	// show welcome message
	const char welcome[] = "CoralOS starting...again\n";
	terminal_print(&term, welcome, sizeof(welcome) - 1);

	// infinite loop
	for(;;);
}