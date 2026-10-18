
#ifndef SENTRY_NAIVE
#define SENTRY_NAIVE
#include "naive.c"
#endif

typedef union union_syscall_result_ {
	S64 l;
	U64 ul;
	void *p;
	void (*fp)(void);
} union_syscall_result;

/* io */
#define SYS_WRITE 0x01
#define SYS_READ 0x00
#define SYS_OPENAT 0x101
#define SYS_CLOSE 0x03
#define SYS_LSEEK 0x08
#define SYS_SYNC 0xa2
#define SYS_MSYNC 0x1a
#define SYS_FSYNC 0x4a
#define SYS_FDATASYNC 0x4b

/* mem */
#define SYS_MMAP 0x09
#define SYS_MUNMAP 0x0b
#define SYS_MADVISE 0x1c
#define SYS_MLOCK2 0x145
#define SYS_MUNLOCK 0x96
#define SYS_MLOCKALL 0x97
#define SYS_MUNLOCKALL 0x98

/* time */
#define SYS_NANOSLEEP 0x23
#define SYS_CLOCK_GETTIME 0xe4 /* not on 32 bit */

/* process */
#define SYS_EXIT 0x3c
#define SYS_EXIT_GROUP 0xe7
#define SYS_GETPID 0x27
#define SYS_CLONE3 0x1b3
#define SYS_WAIT4 0x3d

/* signal */
#define SYS_KILL 0x3e
#define SYS_RT_SIGACTION 0x0d

/* NOT implemented yet: */

/* network */
#define SYS_SOCKET 0x29
#define SYS_BIND 0x31
#define SYS_LISTEN 0x32
#define SYS_CONNECT 0x2a
#define SYS_ACCEPT 0x2b
#define SYS_SHUTDOWN 0x30
#define SYS_SETSOCKOPT 0x36
#define SYS_GETSOCKOPT 0x37
#define SYS_EPOLL_CREATE1 0x123
#define SYS_EPOLL_CTL 0xe9
#define SYS_EPOLL_PWAIT 0x119
#define SYS_RECVFROM 0x2d
#define SYS_SENDTO 0x2c

/* more io */
#define SYS_DUP3 0x124
#define SYS_FLOCK 0x49
#define SYS_FCNTL 0x48
#define SYS_WRITEV 0x14
#define SYS_READV 0x13
#define SYS_UNLINKAT 0x107
#define SYS_TRUNCATE 0x4c
#define SYS_FTRUNCATE 0x4d

/* more mem */
#define SYS_MLOCK 0x95
#define SYS_MUNLOCK 0x96

/* more time */
#define SYS_CLOCK_GETRES 0xe5
#define SYS_GETTIMEOFDAY 0x60

/* more process */
#define SYS_GETPRIORITY 0x8c
#define SYS_SETPRIORITY 0x8d
#define SYS_SETRLIMIT 0xa0
#define SYS_GETRLIMIT 0x61

/* more signal */
#define SYS_RT_SIGSUSPEND 0x82

/* misc */
#define SYS_GETPPID 0x6e
#define SYS_GETUID 0x66
#define SYS_GETEUID 0x6b
#define SYS_GETGROUPS 0x73
#define SYS_GETGID 0x68
#define SYS_GETEGID 0x6c
#define SYS_SETUID 0x69
#define SYS_SETGID 0x6a
#define SYS_SETGROUPS 0x74
#define SYS_PTRACE 0x65
#define SYS_GETSID 0x7c
#define SYS_GETPGID 0x79
#define SYS_SETSID 0x70
#define SYS_SETPGID 0x6d
#define SYS_SYSLOG 0x67
#define SYS_SOCKETPAIR 0x35
#define SYS_PSELECT6 0x10e
#define SYS_LINKAT 0x109
#define SYS_SYMLINKAT 0x10a
#define SYS_FCHMOD 0x5b
#define SYS_MKDIRAT 0x102
#define SYS_IOCTL 0x10
#define SYS_RENAMEAT 0x108
#define SYS_EXECVE 0x3b
#define SYS_MQ_OPEN 0xf0
#define SYS_MQ_UNLINK 0xf1
#define SYS_MQ_GETSETATTR 0xf5
#define SYS_MQ_NOTIFY 0xf4
#define SYS_MKNODAT 0x103
#define SYS_FSTAT 0x05
#define SYS_GETCWD 0x4f
#define SYS_CHROOT 0xa1
#define SYS_CHDIR 0x50
#define SYS_UMASK 0x5f
#define SYS_FUTEX 0xca

#define EOF (-1)

#define AT_FDCWD (-100)

#define O_APPEND 0x400
#define O_CLOEXEC 0x80000
#define O_CREAT 0x40
#define O_DIRECTORY 0x10000
#define O_DSYNC 0x1000
#define O_EXCL 0x80
#define O_NOCTTY 0x100
#define O_NOFOLLOW 0x20000
#define O_NONBLOCK 0x800
#define O_NDELAY O_NONBLOCK
#define O_SYNC 0x101000
#define O_TRUNC 0x200

#define O_RDONLY 0x0
#define O_WRONLY 0x1
#define O_RDWR 0x2

#define S_IRWXU 0x1c0
#define S_IRUSR 0x100
#define S_IWUSR 0x080
#define S_IXUSR 0x040
#define S_IRWXG 0x038
#define S_IRGRP 0x020
#define S_IWGRP 0x010
#define S_IXGRP 0x008
#define S_IRWXO 0x007
#define S_IROTH 0x004
#define S_IWOTH 0x002
#define S_IXOTH 0x001

#define PROT_NONE 0x0
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define PROT_EXEC 0x4

#define MAP_PRIVATE 0x2
#define MAP_ANONYMOUS 0x20
#define MAP_LOCKED 0x2000

#define MADV_NORMAL 0x0
#define MADV_RANDOM 0x1
#define MADV_SEQUENTIAL 0x2
#define MADV_WILLNEED 0x3
#define MADV_DONTNEED 0x4

#define MCL_CURRENT 0x1
#define MCL_FUTURE 0x2

#define MS_SYNC 0x4
#define MS_INVALIDATE 0x2

#define SIGHUP 0x1
#define SIGINT 0x2
#define SIGQUIT 0x3
#define SIGKILL 0x9
#define SIGSEGV 0xb
#define SIGTERM 0xf
#define SIGSTOP 0x13

#define SIG_DFL ((void (*)(U32))0x0)
#define SIG_IGN ((void (*)(U32))0x1)

#define SA_RESETHAND (0x7fffFFFFl + 1)
#define SA_SIGINFO 0x4

#define WNOHANG 0x1
#define WCONTINUED 0x8
#define WUNTRACED 0x2

#define SEEK_CUR 0x1
#define SEEK_END 0x2
#define SEEK_SET 0x0

#define STDOUT_FILENO 0x1
#define STDERR_FILENO 0x2
#define STDIN_FILENO 0x0

#define EINTR 0x4
#define EINVAL 0x16

/*
 * borrowed from musl.
 * https://github.com/kraj/musl/blob/kraj/master/arch/
 */

static ALWAYS_INLINE void priv_syscall0(U64 n, union_syscall_result *res)
{
	asm volatile("syscall" : "=a"(*res) : "a"(n) : "rcx", "r11", "memory");
}

static ALWAYS_INLINE void priv_syscall1(U64 a1, U64 n, union_syscall_result *res)
{
	asm volatile("syscall" : "=a"(*res) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
}

static ALWAYS_INLINE void priv_syscall2(U64 a1, U64 a2, U64 n, union_syscall_result *res)
{
	asm volatile("syscall" : "=a"(*res) : "a"(n), "D"(a1), "S"(a2) : "rcx", "r11", "memory");
}

static ALWAYS_INLINE void priv_syscall3(U64 a1, U64 a2, U64 a3, U64 n, union_syscall_result *res)
{
	asm volatile("syscall" : "=a"(*res) : "a"(n), "D"(a1), "S"(a2), "d"(a3) : "rcx", "r11", "memory");
}

static ALWAYS_INLINE void priv_syscall4(U64 a1, U64 a2, U64 a3, U64 a4, U64 n, union_syscall_result *res)
{
	register U64 r10 asm("r10") = a4;
	asm volatile("syscall"
		     : "=a"(*res)
		     : "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10)
		     : "rcx", "r11", "memory");
}

static ALWAYS_INLINE void priv_syscall5(U64 a1, U64 a2, U64 a3, U64 a4, U64 a5, U64 n,
					union_syscall_result *res)
{
	register U64 r10 asm("r10") = a4;
	register U64 r8 asm("r8") = a5;
	asm volatile("syscall"
		     : "=a"(*res)
		     : "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8)
		     : "rcx", "r11", "memory");
}

static ALWAYS_INLINE void priv_syscall6(U64 a1, U64 a2, U64 a3, U64 a4, U64 a5, U64 a6, U64 n,
					union_syscall_result *res)
{
	register U64 r10 asm("r10") = a4;
	register U64 r8 asm("r8") = a5;
	register U64 r9 asm("r9") = a6;
	asm volatile("syscall"
		     : "=a"(*res)
		     : "a"(n), "D"(a1), "S"(a2), "d"(a3), "r"(r10), "r"(r8), "r"(r9)
		     : "rcx", "r11", "memory");
}
