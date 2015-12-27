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
 * loader.c
 *  Created on: Dec 27, 2015
 *      Author: Peter Vanusanik
 *  Contents: 
 */

/* sourcedoc: http://www.x86-64.org/documentation/abi.pdf */

#include <elrond/elrond.h>

#include "elf_def.h"

#define ASSERT_NON_ZERO(test, error_action, error_ret_code) \
	do \
	if ((test) == 0){ \
		error_action; \
		return error_ret_code; \
	} while (0)

static int check_loader(elf_loader_t* loader){
	ASSERT_NON_ZERO(loader->ea, loader->error_code = ELROND_LOADER_FNC_NOTPROV, -1);
	ASSERT_NON_ZERO(loader->free, loader->error_code = ELROND_LOADER_FNC_NOTPROV, -1);
	ASSERT_NON_ZERO(loader->get_elf, loader->error_code = ELROND_LOADER_FNC_NOTPROV, -1);
	ASSERT_NON_ZERO(loader->malloc, loader->error_code = ELROND_LOADER_FNC_NOTPROV, -1);
	ASSERT_NON_ZERO(loader->realloc, loader->error_code = ELROND_LOADER_FNC_NOTPROV, -1);
	ASSERT_NON_ZERO(loader->mc_ff, loader->error_code = ELROND_LOADER_FNC_NOTPROV, -1);
	ASSERT_NON_ZERO(loader->mc_gen, loader->error_code = ELROND_LOADER_FNC_NOTPROV, -1);
	ASSERT_NON_ZERO(loader->memset, loader->error_code = ELROND_LOADER_FNC_NOTPROV, -1);

	return 0;
}

#ifdef __X86_64__

int load_elf_64(elf_loader_t* loader){
	if (check_loader(loader) != 0)
		return -1;
	loader->error_code = ELROND_NO_ERROR;

	Elf64_Ehdr* header;
	if (loader->get_elf(loader->state, (char**)&header, sizeof(Elf64_Ehdr), 0) != 0){
		loader->error_code = ELROND_NO_DATA;
		return -1;
	}

	if (header->e_ident[EI_CLASS] != ELFCLASS64){
		loader->error_code = ELROND_UNDEFINED_ELF_FORMAT;
		return 0;
	}

	if (header->e_ident[EI_DATA] != ELFDATA2LSB){
		loader->error_code = ELROND_UNDEFINED_ELF_FORMAT;
		return 0;
	}


	size_t prog_head_table_size = header->e_phnum * header->e_phentsize;
	if (header->e_phnum >= PN_XNUM){
		// TODO: add xnum support // page 62
	}



	return 0;
}

#endif
