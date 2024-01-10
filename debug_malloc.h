/*
 * Copyright (C) 2004-2022 Wu Yongwei <wuyongwei at gmail dot com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must
 *    not claim that you wrote the original software.  If you use this
 *    software in a product, an acknowledgement in the product
 *    documentation would be appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must
 *    not be misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 *
 * This file is part of Stones of Nvwa:
 *      https://github.com/adah1972/nvwa
 *
 */

/**
 * @file  debug_malloc.h
 *
 * Header file for checking leaks caused by unmatched malloc/realloc/free.
 */

#ifndef NVWA_DEBUG_NEW_H
#define NVWA_DEBUG_NEW_H

#include <stddef.h>             // size_t
#include <stdio.h>              // FILE

namespace nvwa {

/* Special allocation/deallocation functions */
void* debug_malloc(size_t size, const char* file, int line);
void* debug_realloc(void* ptr, size_t size, const char* file, int line);
void debug_free(void* ptr);

/* Use counter */

void debug_malloc_use();
void debug_malloc_unuse();

/**
 * Callback type for stack trace printing.
 *
 * @param fp          pointer to the output stream
 * @param stacktrace  pointer to the stack trace array (null-terminated)
 */
typedef void (*stacktrace_print_callback_t)(FILE* fp, void** stacktrace);

/**
 * Callback type for the leak whitelist function.  \a file, \a address,
 * and \a backtrace might be null depending on library configuration,
 * platform, and amount of runtime information available.  \a line can
 * be 0 when line number info is not available at runtime.
 *
 * @param file        null-terminated string of the file name
 * @param line        line number
 * @param addr        address of code where leakage happens
 * @param stacktrace  pointer to the stack trace array (null-terminated)
 * @return            \c true if the leak should be whitelisted;
 *                    \c false otherwise
 */
typedef bool (*leak_whitelist_callback_t)(char const* file, int line,
                                          void* addr, void** stacktrace);

/* Prototypes */
int check_leaks();
int check_mem_corruption();
size_t get_current_mem_alloc();
size_t get_total_mem_alloc_cnt();

/* Control variables */
extern bool new_autocheck_flag; // default to true: call check_leaks() on exit
extern bool new_verbose_flag;   // default to false: no verbose information
extern FILE* new_output_fp;     // default to stderr: output to console
extern const char* new_progname;// default to null; should be assigned argv[0]
extern stacktrace_print_callback_t stacktrace_print_callback;// default to null
extern leak_whitelist_callback_t leak_whitelist_callback;    // default to null

} // namespace nvwa

#endif // NVWA_DEBUG_NEW_H
