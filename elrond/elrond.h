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

#define ELROND_NO_ERROR 		      (0)
#define ELROND_UNKNOWN_MODE		      (1)
#define ELROND_LOADER_FNC_NOTPROV     (2)
#define ELROND_NO_DATA			      (3)
#define ELROND_MALOC_FAILURE	      (4)
#define ELROND_UNDEFINED_ELF_FORMAT   (65534)
#define ELROND_UNSUPPORTED_ELF_FORMAT (65535)

/** Called to inform kernel that loader needs those virtual addresses available (paged in)*/
typedef void (*address_allocator)(void* state, void* address, size_t n);
/** Called to inform kernel that loader wants data from file offset f into target address */
typedef void (*memcpy_fromfile)	 (void* state, void* target_address, size_t foffset, size_t n);
/** Called to inform kernel that loader wants data from source address to target_address */
typedef void (*memcpy_general)   (void* state, void* target_address, void* source_address, size_t n);
/** Returns size_t bytes into pointer buffer, returning 0 on success */
typedef int  (*get_elf_data)	 (void* state, char** buffer, size_t byterq, size_t offset);
/** Requesting kernel to allocate that many bytes */
typedef void*(*malloc_general)   (void* state, size_t n);
/** Requesting kernel to realoc that pointer */
typedef void*(*realloc_general)  (void* state, void* address, size_t newsize);
/** Requesting kernel to deallocate that many bytes */
typedef void*(*free_general)     (void* state, void* address);
/** Requesting to perform memset on this address */
typedef void*(*memset_general)   (void* address, uint8_t value, size_t n);

/**
 * elf_loader_t type
 *
 * Elf loader. libelrond uses this loader to load elf into memory. Kernel should supply these functions.
 * Kernel can use elf_loader->state pointer/data for any needed inner states.
 */
typedef struct elf_loader {
	address_allocator ea;
	memcpy_fromfile	  mc_ff;
	memcpy_general    mc_gen;
	get_elf_data	  get_elf;
	malloc_general	  malloc;
	realloc_general	  realloc;
	free_general	  free;
	memset_general	  memset;

	uint32_t		  error_code;
	void*			  state;
} elf_loader_t;

#ifdef __X86_64__
/**
 * Loads elf into memory based on settings in loader
 *
 * * loader - elf_loader_t instance
 * * returns 0 on success, non zero on failure
 *    error is then located in loader->error_code
 */
int load_elf_64(elf_loader_t* loader);
#endif
