#include "syscall_x86_64.c"

static ALWAYS_INLINE void sys_exit(S32 status)
{
	union_syscall_result rax;
	assert(status == (S32)status);
	priv_syscall1((S64)status, SYS_EXIT, &rax);
	(void)rax;
}

static ALWAYS_INLINE void sys_exit_group(S32 status)
{
	union_syscall_result rax;
	assert(status == (S32)status);
	priv_syscall1((S64)status, SYS_EXIT_GROUP, &rax);
	(void)rax;
}

static ALWAYS_INLINE S64 sys_write(S64 fd, const void *restrict data, U64 nbytes, S64 *restrict result)
{
	union_syscall_result rax;

	ALWAYS(data != NULL);
	ALWAYS(fd >= 0);
	ALWAYS(fd <= S32_MAX);

#if defined(STDIO_DESCRIPTOR_NO_HACKING)
	ALWAYS(fd != STDIN_FILENO);
#endif

	priv_syscall3((U64)(S64)fd, (U64)data, nbytes, SYS_WRITE, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax < 0 || (U64)rax > nbytes)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l >= 0);
	ALWAYS((U64)rax.l <= nbytes);

	if (MORE_LIKELY(result != NULL)) {
		*result = rax.l;
	}
	return rax.l;
}

static ALWAYS_INLINE S64 write_no_eintr(S64 fd, const void *restrict data, U64 nbytes, S64 *restrict result)
{
	S64 res;
	S64 nbytes_succeeded;
	S64 err;
	char *curr_data;

	ALWAYS(nbytes != 0);
	ALWAYS(data != NULL);
	ALWAYS(fd >= 0);
	ALWAYS(fd <= S32_MAX);

	nbytes_succeeded = 0;
	curr_data = (char *)data;

	while (1 == 1) {
		err = sys_write(fd, curr_data, nbytes, &res);

		if (RARELY(err < 0)) {
			if (MORE_LIKELY(-err == EINTR)) {
				continue;
			} else {
				break;
			}
		} else {
			if (OFTEN((U64)res == nbytes)) {
				break;
			}
			curr_data += res;
			nbytes_succeeded += res;
			nbytes -= res;
		}
	}

	if (LESS_LIKELY(result != NULL)) {
		*result = nbytes_succeeded;
	}
	return err;
}

static ALWAYS_INLINE S64 sys_read(S64 fd, void *restrict buf, U64 nbytes, S64 *restrict result)
{
	union_syscall_result rax;

	ALWAYS(buf != NULL);
	ALWAYS(fd >= 0);
	ALWAYS(fd <= S32_MAX);

#if defined(STDIO_DESCRIPTOR_NO_HACKING)
	ALWAYS(fd != STDOUT_FILENO);
	ALWAYS(fd != STDERR_FILENO);
#endif

	priv_syscall3((U64)(S64)fd, (U64)buf, nbytes, SYS_READ, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax < 0 || (U64)rax > nbytes)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l >= 0);
	ALWAYS((U64)rax.l <= nbytes);

	if (OFTEN(result != NULL)) {
		*result = rax.l;
	}
	return rax.l;
}

static ALWAYS_INLINE S64 read_no_eintr(S64 fd, void *restrict buf, U64 nbytes, S64 *restrict result)
{
	S64 res;
	S64 nbytes_succeeded;
	S64 err;
	char *curr_buf;

	ALWAYS(nbytes != 0);
	ALWAYS(buf != NULL);
	ALWAYS(fd >= 0);
	ALWAYS(fd <= S32_MAX);

	nbytes_succeeded = 0;
	curr_buf = (char *)buf;

	while (1 == 1) {
		err = sys_read(fd, curr_buf, nbytes, &res);
		if (RARELY(err < 0)) {
			if (MORE_LIKELY(-err == EINTR)) {
				continue;
			} else {
				break;
			}
		} else {
			if (OFTEN((U64)res == nbytes)) {
				break;
			}
			curr_buf += res;
			nbytes_succeeded += res;
			nbytes -= res;
		}
	}

	if (MORE_LIKELY(result != NULL)) {
		*result = nbytes_succeeded;
	}
	return err;
}

static ALWAYS_INLINE void sys_sync(void)
{
	union_syscall_result rax;
	(void)priv_syscall0(SYS_SYNC, &rax);
	(void)rax;
}

static ALWAYS_INLINE S64 sys_lseek(S64 fd, S64 offset, S64 whence, S64 *result)
{
	union_syscall_result rax;

	ALWAYS(fd >= 0);
	ALWAYS(whence >= 0);
	ALWAYS(fd <= S32_MAX);
	ALWAYS(whence <= S32_MAX);

	priv_syscall3((U64)fd, (U64)offset, (U64)whence, SYS_LSEEK, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax <= -0x1000)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l >= 0);
	if (OFTEN(result != NULL)) {
		*result = rax.l;
	}
	return rax.l;
}

static ALWAYS_INLINE S64 sys_openat_uint(S64 dirfd, const void *restrict pathname, S64 flags, U64 mode, S32 *restrict result)
{
	union_syscall_result rax;
	U64 dirfd_ul;

	ALWAYS(result != NULL);
	ALWAYS(flags >= 0);
	ALWAYS(dirfd == AT_FDCWD || dirfd >= 0);
	ALWAYS(AT_FDCWD >= -S64_MAX);
	ALWAYS(AT_FDCWD < 0);
	ALWAYS(mode <= U32_MAX);
	ALWAYS(flags <= S32_MAX);
	ALWAYS(dirfd <= S32_MAX);

	if (dirfd == AT_FDCWD) {
		dirfd_ul = U64_MAX - (-AT_FDCWD) + 1;
	} else {
		dirfd_ul = (U64)dirfd;
	}

	priv_syscall4(dirfd_ul, (U64)pathname, (U64)(S64)flags, (U64)mode, SYS_OPENAT, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax > S32_MAX || rax <= -0x1000)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#if defined(STDIO_DESCRIPTOR_NO_HACKING)
	if (LESS_LIKELY(rax == STDOUT_FILENO || rax == STDERR_FILENO || rax == STDIN_FILENO)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif
#endif /* KERNEL_MITIGATION_ERRNO */

	ALWAYS(rax.l <= S32_MAX);
	ALWAYS(rax.l > -0x1000);
#if defined(STDIO_DESCRIPTOR_NO_HACKING)
	ALWAYS(rax.l != STDOUT_FILENO);
	ALWAYS(rax.l != STDERR_FILENO);
	ALWAYS(rax.l != STDIN_FILENO);
#endif

	if (OFTEN(result != NULL)) {
		*result = (S32)rax.l;
	}
	return rax.l;
}

static ALWAYS_INLINE S64 sys_openat(S64 dirfd, const void *restrict pathname, S64 flags, S32 *restrict result)
{
	union_syscall_result rax;
	U64 dirfd_ul;

	ALWAYS(result != NULL);
	ALWAYS(flags >= 0);
	ALWAYS(dirfd == AT_FDCWD || dirfd >= 0);
	ALWAYS(AT_FDCWD >= -S64_MAX);
	ALWAYS(AT_FDCWD < 0);
	ALWAYS(dirfd <= S32_MAX);
	ALWAYS(flags <= S32_MAX);

	if (dirfd == AT_FDCWD) {
		dirfd_ul = U64_MAX - (-AT_FDCWD) + 1;
	} else {
		dirfd_ul = (U64)dirfd;
	}

	priv_syscall3(dirfd_ul, (U64)pathname, (U64)(S64)flags, SYS_OPENAT, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax > S32_MAX || rax <= -0x1000)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#if defined(STDIO_DESCRIPTOR_NO_HACKING)
	if (LESS_LIKELY(rax == STDOUT_FILENO || rax == STDERR_FILENO || rax == STDIN_FILENO)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif
#endif /* KERNEL_MITIGATION_ERRNO */

	ALWAYS(rax.l <= S32_MAX);
	ALWAYS(rax.l > -0x1000);
#if defined(STDIO_DESCRIPTOR_NO_HACKING)
	ALWAYS(rax.l != STDOUT_FILENO);
	ALWAYS(rax.l != STDERR_FILENO);
	ALWAYS(rax.l != STDIN_FILENO);
#endif

	if (OFTEN(result != NULL)) {
		*result = (S32)rax.l;
	}
	return rax.l;
}

static ALWAYS_INLINE S64 sys_close(S64 fd)
{
	union_syscall_result rax;

	ALWAYS(fd >= 0);
	ALWAYS(fd <= S32_MAX);
#if defined(STDIO_DESCRIPTOR_NO_HACKING)
	ALWAYS(fd != STDIN_FILENO);
	ALWAYS(fd != STDOUT_FILENO);
	ALWAYS(fd != STDERR_FILENO);
#endif

	priv_syscall1((U64)(S64)fd, SYS_CLOSE, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax.l != 0)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l == 0);
	return rax.l;
}

static ALWAYS_INLINE S64 sys_fsync(S64 fd)
{
	union_syscall_result rax;

	ALWAYS(fd >= 0);
	ALWAYS(fd <= S32_MAX);

	priv_syscall1((U64)(S64)fd, SYS_FSYNC, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax.l != 0)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l == 0);
	return rax.l;
}

static ALWAYS_INLINE S64 sys_fdatasync(S64 fd)
{
	union_syscall_result rax;

	ALWAYS(fd >= 0);
	ALWAYS(fd <= S32_MAX);

	priv_syscall1((U64)(S64)fd, SYS_FDATASYNC, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax.l != 0)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l == 0);
	return rax.l;
}

static ALWAYS_INLINE S64 sys_mmap(void *restrict addr, U64 length, S64 prot, S64 flags, S64 fd, S64 offset,
				  void **restrict result)
{
	union_syscall_result rax;
	U64 offset_ul;
	U64 fd_ul;

	ALWAYS(prot >= 0);
	ALWAYS(flags >= 0);
	ALWAYS(fd >= 0 || fd == -1);
	ALWAYS(prot <= S32_MAX);
	ALWAYS(flags <= S32_MAX);
	ALWAYS(fd <= S32_MAX);

	if (offset < 0) {
		offset -= -S64_MAX - 1;
		offset_ul = (U64)offset;
		offset_ul -= -S64_MAX - 1;
	} else {
		offset_ul = (U64)offset;
	}

	if (fd == -1) {
		fd_ul = U64_MAX;
	} else {
		fd_ul = (U64)fd;
	}

	/* 'offset' is changed */

	priv_syscall6((U64)addr, length, (U64)(S64)prot, (U64)(S64)flags, fd_ul, offset_ul, SYS_MMAP, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax.l < 0)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l >= 0);

	if (OFTEN(result != NULL)) {
		*result = rax.p;
	}

	return rax.l;
}

static ALWAYS_INLINE S64 sys_munmap(void *addr, U64 length)
{
	union_syscall_result rax;

	priv_syscall2((U64)addr, length, SYS_MUNMAP, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax != 0)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l == 0);
	return rax.l;
}

static ALWAYS_INLINE S64 sys_madvise(void *addr, U64 length, S64 advice)
{
	union_syscall_result rax;

	ALWAYS(addr != NULL);
	ALWAYS(length != 0);
	ALWAYS(advice >= 0);
	ALWAYS(advice <= S32_MAX);

	priv_syscall3((U64)addr, length, (U64)(S64)advice, SYS_MADVISE, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax != 0)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l == 0);
	return rax.l;
}

static ALWAYS_INLINE S64 sys_msync(void *addr, U64 length, S64 flags)
{
	union_syscall_result rax;

	ALWAYS(flags >= 0);
	ALWAYS(flags <= S32_MAX);

	priv_syscall3((U64)addr, length, (U64)(S64)flags, SYS_MSYNC, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax != 0)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l == 0);
	return rax.l;
}

static ALWAYS_INLINE S64 sys_mlock2(const void *start, UPTR len, S32 flags)
{
	union_syscall_result rax;

	ALWAYS(flags >= 0);

	priv_syscall3((UPTR)start, len, (U64)(S64)flags, SYS_MLOCK2, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax != 0)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l == 0);
	return rax.l;
}

static ALWAYS_INLINE S64 sys_munlock(const void *start, UPTR len)
{
	union_syscall_result rax;

	priv_syscall2((UPTR)start, len, SYS_MUNLOCK, &rax);
	if (RARELY(rax.l < 0 && rax.l > -0x1000)) {
		return rax.l;
	}

#if defined(KERNEL_MITIGATION_ERRNO)
	if (RARELY(rax.l != 0)) {
		return -KERNEL_MITIGATION_ERRNO;
	}
#endif

	ALWAYS(rax.l == 0);
	return rax.l;
}
