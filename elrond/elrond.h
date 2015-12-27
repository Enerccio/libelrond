/*
 * The MIT License (MIT)
 * Copyright (c) 2015 Peter Vanusanik <admin@en-circle.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal in 
 * the Software without restriction, including without limitation the rights to use, copy, 
 * modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
 * and to permit persons to whom the Software is furnished to do so, subject to the 
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies 
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS 
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * elrond.h
 *  Created on: Dec 27, 2015
 *      Author: Peter Vanusanik
 *  Contents: 
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#define ELROND_MODE_COPYBYTES   (1)
#define ELROND_MODE_INFORM      (2)

#define ELROND_NO_ERROR 		  (0)
#define ELROND_UNKNOWN_MODE		  (1)
#define ELROND_LOADER_FNC_NOTPROV (2)
#define ELROND_NO_DATA			  (3)

typedef void (*address_allocator)(void* state, void* address, size_t n);
typedef void (*memcpy_fromfile)	 (void* state, void* target_address, size_t foffset, size_t n);
typedef void (*memcpy_general)   (void* state, void* target_address, void* source_address, size_t n);
typedef int  (*get_elf_data)	 (void* state, char** buffer, size_t byterq);
typedef void (*free_elf_data)    (void* state, char* buffer);
typedef void*(*malloc_general)   (void* state, size_t n);
typedef void*(*realloc_general)  (void* state, void* address, size_t newsize);
typedef void*(*free_general)     (void* state, void* address);
typedef void*(*memset_general)   (void* address, uint8_t value, size_t n);

typedef struct elf_loader {
	uint32_t		  loader_mode;

	address_allocator ea;
	memcpy_fromfile	  mc_ff;
	memcpy_general    mc_gen;
	get_elf_data	  get_elf;
	free_elf_data	  free_elf;
	malloc_general	  malloc;
	realloc_general	  realloc;
	free_general	  free;
	memset_general	  memset;
	uint32_t		  error_code;
	void*			  state;
} elf_loader_t;

#ifdef __X86_64__
int load_elf_64(elf_loader_t* loader);
#endif
