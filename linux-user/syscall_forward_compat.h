
#if defined(CONFIG_SYSCALL_FORWARD_COMPAT)
/*
 * We enable forward compatibility of host syscalls there.
 * It means for instance that if QEMU is built on a host
 * with a old kernel and with SYSCALL_FORWARD_COMPAT
 * it will execute syscalls when running on a more
 * recent host.
 * If the syscall is actually not supported on the actual
 * host running QEMU, the behavior is undefined, generally
 * the syscall will fail.
 * The standard behavior without SYSCALL_FORWARD_COMPAT
 * is that QEMU skips the syscall ("unsupported syscall").
 *
 * A typical example case is the support for *at syscalls
 * introduced in kernel 2.6.16. For instance if QEMU is
 * compiled on a CentOS4 (kernel 2.6.9), the same binary
 * will be also usable on a CentOS5 (kernel 2.6.18) running
 * a guest system with a 2.6.16+ kernel.
 * Actually when executing an openat syscall on the 2.6.16+
 * guest, QEMU will forward it to the openat syscall on the
 * CenOS5 kernel.
 * Note that it is different from syscall emulation, for
 * instance running the same 2.6.16+ guest system on the
 * initial CentOS4 2.6.0 kernel will fail as the openat 
 * syscall is actually not supported.
 *
 * In order to activate forward compatibility, we just have
 * to define when it is not the case the recent syscall
 * numbers as extracted from the target syscall number files.
 *
 * Currently forward compatibility is supported only for
 * i386 and x86_64 hosts, but the principle would be the
 * same for the other hosts.
 * In order to generate the syscall_nr_compat.h files
 * from the syscall_nr.h file, execyte the following
 * sed commands:
 * sed 's!^#define[\t ]*TARGET_\([^\t ]*\)[\t ]*\([0-9]*\).*!#ifndef __\1\n#define __\1 \2\n#endif!' <x86_64/syscall_nr.h >x86_64/syscall_nr_compat.h
 * sed 's!^#define[\t ]*TARGET_\([^\t ]*\)[\t ]*\([0-9]*\).*!#ifndef __\1\n#define __\1 \2\n#endif!' <i386/syscall_nr.h >i386/syscall_nr_compat.h
 */
#if defined(__x86_64__)
#include "x86_64/syscall_nr_compat.h"
#elif defined(__i386__)
#include "i386/syscall_nr_compat.h"
#else
#error "syscall forward compatibility mode not supported for this host"
#endif

#endif /* CONFIG_SYSCALL_FORWARD_COMPAT */
