/*-
 * Copyright 1996, 1997, 1998, 2000 John D. Polstra.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */

typedef void (*fptr)(void);

fptr ctor_list[1] __attribute__((section(".ctors"))) __attribute__((visibility("hidden")));
fptr dtor_list[1] __attribute__((section(".dtors"))) __attribute__((visibility("hidden")));

__attribute__((visibility("hidden"))) void *__dso_handle = &__dso_handle;

static void
do_ctors(void) __attribute__((used));

static void
do_ctors(void)
{
    fptr *fpp;

    for(fpp = ctor_list + 1;  *fpp != 0;  ++fpp)
	;
    while(--fpp > ctor_list)
	(**fpp)();
}

static void
do_dtors(void) __attribute__((used));

static void
do_dtors(void)
{
    fptr *fpp;

    for(fpp = dtor_list + 1;  *fpp != 0;  ++fpp)
	(**fpp)();
}

#if defined(__i386) || defined(__amd64)
__asm__(".section .init,\"ax\",@progbits; call do_ctors; .previous");
__asm__(".section .fini,\"ax\",@progbits; call do_dtors; .previous");
#elif defined(__ppc64__) || defined(__aarch64__)
__asm__(".section .init,\"ax\",@progbits; bl do_ctors; .previous");
__asm__(".section .fini,\"ax\",@progbits; bl do_dtors; .previous");
#else
#error "Define initialization code for platform"
#endif

