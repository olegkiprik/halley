
/*
 * Audio droupouts are likely to happen on a weak PC!
 *
 * Little endian
 *
 * there is no implicit SIMD type cast
 */

#include "basic_types.c"

static void failure_print_string(const char *s);
static void failure_print_dec_u64(U64 num);
static void sys_exit_group(S32 status);

#if !defined(NDEBUG)
#ifndef assert
#define assert(x)                                                  \
	do {                                                       \
		if (!(x)) {                                        \
			failure_print_string("assert failed at "); \
			failure_print_string(__FILE__);            \
			failure_print_string(" ");                 \
			failure_print_dec_u64(__LINE__);           \
			failure_print_string("\n");                \
			sys_exit_group(1);                         \
		}                                                  \
	} while (0 != 0)
#endif
#else
#ifndef assert
#define assert(x)
#endif
#endif

#include "basic_types_undef.c"

#ifndef SENTRY_EXTRA
#define SENTRY_EXTRA
#include "extra.c"
#endif

#ifndef SENTRY_UNDEF
#define SENTRY_UNDEF
#include "undef.c"
#endif

#if !defined(NDEBUG)
#define ALWAYS(x) assert(x)
#define NEVER(x) assert(x)
#endif

#ifndef SENTRY_COMMON_AUDIO
#define SENTRY_COMMON_AUDIO
#include "common_audio.c"
#endif

#ifndef SENTRY_ELF
#define SENTRY_ELF
#include "elf.c"
#endif

#ifndef SENTRY_NAIVE_MATH
#define SENTRY_NAIVE_MATH
#include "naive_math.c"
#endif

static BOOL_OUT init_all_pfn(void *c, void *p)
{
	void (*tmp)(void);
	int failed = 0;

	tmp = dlsym(p, "pthread_create");
	failed |= (int)(tmp == NULL);
	my_pthread_create = tmp;
	tmp = dlsym(p, "pthread_join");
	failed |= (int)(tmp == NULL);
	my_pthread_join = tmp;
	tmp = dlsym(p, "pthread_attr_init");
	failed |= (int)(tmp == NULL);
	my_pthread_attr_init = tmp;
	tmp = dlsym(p, "pthread_attr_destroy");
	failed |= (int)(tmp == NULL);
	my_pthread_attr_destroy = tmp;
	tmp = dlsym(p, "pthread_cond_init");
	failed |= (int)(tmp == NULL);
	my_pthread_cond_init = tmp;
	tmp = dlsym(p, "pthread_cond_signal");
	failed |= (int)(tmp == NULL);
	my_pthread_cond_signal = tmp;
	tmp = dlsym(p, "pthread_cond_wait");
	failed |= (int)(tmp == NULL);
	my_pthread_cond_wait = tmp;
	tmp = dlsym(p, "pthread_cond_destroy");
	failed |= (int)(tmp == NULL);
	my_pthread_cond_destroy = tmp;
	tmp = dlsym(p, "pthread_attr_setschedpolicy");
	failed |= (int)(tmp == NULL);
	my_pthread_attr_setschedpolicy = tmp;
	tmp = dlsym(p, "pthread_attr_setstacksize");
	failed |= (int)(tmp == NULL);
	my_pthread_attr_setstacksize = tmp;
	tmp = dlsym(p, "pthread_mutex_lock");
	failed |= (int)(tmp == NULL);
	my_pthread_mutex_lock = tmp;
	tmp = dlsym(p, "pthread_mutex_trylock");
	failed |= (int)(tmp == NULL);
	my_pthread_mutex_try_lock = tmp;
	tmp = dlsym(p, "pthread_mutex_unlock");
	failed |= (int)(tmp == NULL);
	my_pthread_mutex_unlock = tmp;
	tmp = dlsym(p, "pthread_mutex_init");
	failed |= (int)(tmp == NULL);
	my_pthread_mutex_init = tmp;
	tmp = dlsym(p, "pthread_mutex_destroy");
	failed |= (int)(tmp == NULL);
	my_pthread_mutex_destroy = tmp;
	tmp = dlsym(p, "pthread_attr_getschedparam");
	failed |= (int)(tmp == NULL);
	my_pthread_attr_getschedparam = (void *)tmp;
	tmp = dlsym(p, "pthread_attr_setschedparam");
	failed |= (int)(tmp == NULL);
	my_pthread_attr_setschedparam = (void *)tmp;
	tmp = dlsym(p, "pthread_attr_setinheritsched");
	failed |= (int)(tmp == NULL);
	my_pthread_attr_setinheritsched = (void *)tmp;

	tmp = dlsym(c, "close");
	failed |= (int)(tmp == NULL);
	my_close = (void *)tmp;
	tmp = dlsym(c, "eventfd");
	failed |= (int)(tmp == NULL);
	my_eventfd = (void *)tmp;
	tmp = dlsym(c, "poll");
	failed |= (int)(tmp == NULL);
	my_poll = (void *)tmp;
	tmp = dlsym(c, "read");
	failed |= (int)(tmp == NULL);
	my_read = (void *)tmp;
	tmp = dlsym(c, "write");
	failed |= (int)(tmp == NULL);
	my_write = (void *)tmp;
	tmp = dlsym(c, "sched_getscheduler");
	failed |= (int)(tmp == NULL);
	my_sched_getscheduler = (void *)tmp;
	tmp = dlsym(c, "sched_get_priority_min");
	failed |= (int)(tmp == NULL);
	my_sched_get_priority_min = (void *)tmp;
	tmp = dlsym(c, "sched_get_priority_max");
	failed |= (int)(tmp == NULL);
	my_sched_get_priority_max = (void *)tmp;
	tmp = dlsym(c, "clock_gettime");
	failed |= (int)(tmp == NULL);
	my_clock_gettime = (void *)tmp;
	tmp = dlsym(c, "fileno");
	failed |= (int)(tmp == NULL);
	my_fileno = (void *)tmp;
	tmp = dlsym(c, "vsnprintf");
	failed |= (int)(tmp == NULL);
	my_vsnprintf = (void *)tmp;
	tmp = dlsym(c, "pipe");
	failed |= (int)(tmp == NULL);
	my_pipe = (void *)tmp;
	tmp = dlsym(c, "fcntl");
	failed |= (int)(tmp == NULL);
	my_fcntl = (void *)tmp;
	tmp = dlsym(c, "strtol");
	failed |= (int)(tmp == NULL);
	my_strtol = (void *)tmp;
	tmp = dlsym(c, "atof");
	failed |= (int)(tmp == NULL);
	my_atof = (void *)tmp;
	tmp = dlsym(c, "snprintf");
	failed |= (int)(tmp == NULL);
	my_snprintf = (void *)tmp;
	tmp = dlsym(c, "strncmp");
	failed |= (int)(tmp == NULL);
	my_strncmp = (void *)tmp;
	tmp = dlsym(c, "memset");
	failed |= (int)(tmp == NULL);
	my_memset = (void *)tmp;
	tmp = dlsym(c, "__errno_location");
	failed |= (int)(tmp == NULL);
	my_errno_location = (void *)tmp;

	return failed;
}

static void (*glShaderSourceSRC)(GLuint shader, GLsizei count, const GLchar *const *string, const GLint *length);
static GLuint (*glCreateShaderSRC)(GLenum type);
static void (*glCompileShaderSRC)(GLuint shader);
static GLuint (*glCreateProgramSRC)(void);
static void (*glAttachShaderSRC)(GLuint program, GLuint shader);
static void (*glBindAttribLocationSRC)(GLuint program, GLuint index, const GLchar *name);
static void (*glLinkProgramSRC)(GLuint program);
static void (*glBindBufferSRC)(GLenum target, GLuint buffer);
static void (*glBufferDataSRC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
static void (*glEnableVertexAttribArraySRC)(GLuint index);
static void (*glVertexAttribPointerSRC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
static void (*glDisableVertexAttribArraySRC)(GLuint index);
static void (*glDeleteBuffersSRC)(GLsizei n, const GLuint *buffers);
static void (*glDeleteVertexArraysSRC)(GLsizei n, const GLuint *arrays);
static void (*glUseProgramSRC)(GLuint program);
static void (*glDetachShaderSRC)(GLuint program, GLuint shader);
static void (*glDeleteShaderSRC)(GLuint shader);
static void (*glDeleteProgramSRC)(GLuint program);
static void (*glBufferSubDataSRC)(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);
static void (*glGetShaderivSRC)(GLuint shader, GLenum pname, GLint *params);
static void (*glGetShaderInfoLogSRC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
static void (*glGetProgramivSRC)(GLuint program, GLenum pname, GLint *params);
static void (*glGetProgramInfoLogSRC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
static void (*glGenVertexArraysSRC)(GLsizei n, GLuint *arrays);
static void (*glGenBuffersSRC)(GLsizei n, GLuint *buffers);
static void (*glBindVertexArraySRC)(GLuint array);
static GLint (*glGetUniformLocationSRC)(GLuint program, const GLchar *name);
static void (*glUniformMatrix4fvSRC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
static void (*glActiveTextureSRC)(GLenum texture);
static void (*glDebugMessageCallbackSRC)(void *callback, const void *);
static void (*glDrawElementsSRC)(GLenum mode, GLsizei count, GLenum type, const void *indices);
static void (*glDrawArraysSRC)(GLenum mode, GLint, GLsizei);
static void (*glClearColorSRC)(GLfloat, GLfloat, GLfloat, GLfloat);
static void (*glClearSRC)(GLbitfield mask);
static void (*glViewportSRC)(GLint, GLint, GLsizei, GLsizei);
static void (*glUniform3fSRC)(GLint, GLfloat, GLfloat, GLfloat);

#define glActiveTexture (*glActiveTextureSRC)
#define glShaderSource (*glShaderSourceSRC)
#define glCreateShader (*glCreateShaderSRC)
#define glCompileShader (*glCompileShaderSRC)
#define glCreateProgram (*glCreateProgramSRC)
#define glAttachShader (*glAttachShaderSRC)
#define glBindAttribLocation (*glBindAttribLocationSRC)
#define glLinkProgram (*glLinkProgramSRC)
#define glBindBuffer (*glBindBufferSRC)
#define glBufferData (*glBufferDataSRC)
#define glEnableVertexAttribArray (*glEnableVertexAttribArraySRC)
#define glVertexAttribPointer (*glVertexAttribPointerSRC)
#define glDisableVertexAttribArray (*glDisableVertexAttribArraySRC)
#define glDeleteBuffers (*glDeleteBuffersSRC)
#define glDeleteVertexArrays (*glDeleteVertexArraysSRC)
#define glUseProgram (*glUseProgramSRC)
#define glDetachShader (*glDetachShaderSRC)
#define glDeleteShader (*glDeleteShaderSRC)
#define glDeleteProgram (*glDeleteProgramSRC)
#define glBufferSubData (*glBufferSubDataSRC)
#define glGetShaderiv (*glGetShaderivSRC)
#define glGetShaderInfoLog (*glGetShaderInfoLogSRC)
#define glGetProgramiv (*glGetProgramivSRC)
#define glGetProgramInfoLog (*glGetProgramInfoLogSRC)
#define glGenVertexArrays (*glGenVertexArraysSRC)
#define glGenBuffers (*glGenBuffersSRC)
#define glBindVertexArray (*glBindVertexArraySRC)
#define glGetUniformLocation (*glGetUniformLocationSRC)
#define glUniformMatrix4fv (*glUniformMatrix4fvSRC)
#define glDebugMessageCallback (*glDebugMessageCallbackSRC)
#define glDrawElements (*glDrawElementsSRC)
#define glDrawArrays (*glDrawArraysSRC)
#define glClear (*glClearSRC)
#define glClearColor (*glClearColorSRC)
#define glViewport (*glViewportSRC)
#define glUniform3f (*glUniform3fSRC)

/* clang-format off */
static const char *const vertexShaderSource =
"#version 330 core\n"
""
"layout (location = 0) in vec2 aPos;"
"void main()"
"{"
"    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);"
"}"
;

static const char *const fragmentShaderSource =
"#version 330 core\n"
""
"precision mediump float;"
"out vec4 FragColor;"
"uniform vec3 color;"
"void main()"
"{"
"    FragColor = vec4(color, 1.0f);"
"}"
;
/* clang-format on */

static const float main_color_r = 0.682352941f;
static const float main_color_g = 0.643137255f;
static const float main_color_b = 0.945098039f;

static void failure_print_dec_u64(U64 num)
{
	if (num == 0) {
		char c = '0';
		sys_write(STDERR_FILENO, &c, 1, NULL);
		return;
	}

	char c;
	int print_zero = 0;
	U64 divisor = 10000000000000000000uLL;

	while (divisor != 0) {
		c = '0' + num / divisor;
		if (c != '0') {
			print_zero = 1;
		}
		if (print_zero) {
			sys_write(STDERR_FILENO, &c, 1, NULL);
		}
		num %= divisor;
		divisor /= 10;
	}
}

static void failure_print_string(const char *s)
{
	sys_write(STDERR_FILENO, s, naive_strlen(s), NULL);
}

#define RGL_PROC_DEF(proc, name) name##SRC = (void *)(*(proc))(#name)

static BOOL_OUT RGL_loadGL3(void (*(*proc)(const char *name))(void))
{
	RGL_PROC_DEF(proc, glShaderSource);
	RGL_PROC_DEF(proc, glCreateShader);
	RGL_PROC_DEF(proc, glCompileShader);
	RGL_PROC_DEF(proc, glCreateProgram);
	RGL_PROC_DEF(proc, glAttachShader);
	RGL_PROC_DEF(proc, glBindAttribLocation);
	RGL_PROC_DEF(proc, glLinkProgram);
	RGL_PROC_DEF(proc, glBindBuffer);
	RGL_PROC_DEF(proc, glBufferData);
	RGL_PROC_DEF(proc, glEnableVertexAttribArray);
	RGL_PROC_DEF(proc, glVertexAttribPointer);
	RGL_PROC_DEF(proc, glDisableVertexAttribArray);
	RGL_PROC_DEF(proc, glDeleteBuffers);
	RGL_PROC_DEF(proc, glDeleteVertexArrays);
	RGL_PROC_DEF(proc, glUseProgram);
	RGL_PROC_DEF(proc, glDetachShader);
	RGL_PROC_DEF(proc, glDeleteShader);
	RGL_PROC_DEF(proc, glDeleteProgram);
	RGL_PROC_DEF(proc, glBufferSubData);
	RGL_PROC_DEF(proc, glGetShaderiv);
	RGL_PROC_DEF(proc, glGetShaderInfoLog);
	RGL_PROC_DEF(proc, glGetProgramiv);
	RGL_PROC_DEF(proc, glGetProgramInfoLog);
	RGL_PROC_DEF(proc, glGenVertexArrays);
	RGL_PROC_DEF(proc, glGenBuffers);
	RGL_PROC_DEF(proc, glBindVertexArray);
	RGL_PROC_DEF(proc, glGetUniformLocation);
	RGL_PROC_DEF(proc, glUniformMatrix4fv);
	RGL_PROC_DEF(proc, glActiveTexture);
	RGL_PROC_DEF(proc, glDebugMessageCallback);
	RGL_PROC_DEF(proc, glDrawElements);
	RGL_PROC_DEF(proc, glDrawArrays);
	RGL_PROC_DEF(proc, glClear);
	RGL_PROC_DEF(proc, glClearColor);
	RGL_PROC_DEF(proc, glViewport);
	RGL_PROC_DEF(proc, glUniform3f);

	if ((int)(glShaderSourceSRC == NULL) |
	    (int)(glCreateShaderSRC == NULL) |
	    (int)(glCompileShaderSRC == NULL) |
	    (int)(glCreateProgramSRC == NULL) |
	    (int)(glAttachShaderSRC == NULL) |
	    (int)(glBindAttribLocationSRC == NULL) |
	    (int)(glLinkProgramSRC == NULL) |
	    (int)(glBindBufferSRC == NULL) |
	    (int)(glBufferDataSRC == NULL) |
	    (int)(glEnableVertexAttribArraySRC == NULL) |
	    (int)(glVertexAttribPointerSRC == NULL) |
	    (int)(glDisableVertexAttribArraySRC == NULL) |
	    (int)(glDeleteBuffersSRC == NULL) |
	    (int)(glDeleteVertexArraysSRC == NULL) |
	    (int)(glUseProgramSRC == NULL) |
	    (int)(glDetachShaderSRC == NULL) |
	    (int)(glDeleteShaderSRC == NULL) |
	    (int)(glDeleteProgramSRC == NULL) |
	    (int)(glBufferSubDataSRC == NULL) |
	    (int)(glGetShaderivSRC == NULL) |
	    (int)(glGetShaderInfoLogSRC == NULL) |
	    (int)(glGetProgramivSRC == NULL) |
	    (int)(glGetProgramInfoLogSRC == NULL) |
	    (int)(glGenVertexArraysSRC == NULL) |
	    (int)(glGenBuffersSRC == NULL) |
	    (int)(glBindVertexArraySRC == NULL) |
	    (int)(glGetUniformLocationSRC == NULL) |
	    (int)(glUniformMatrix4fvSRC == NULL) |
	    (int)(glClearSRC == NULL) |
	    (int)(glClearColorSRC == NULL) |
	    (int)(glDrawElementsSRC == NULL) |
	    (int)(glDrawArraysSRC == NULL) |
	    (int)(glViewportSRC == NULL) |
	    (int)(glUniform3fSRC == NULL)) {
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		return 1;
	}

	GLuint vao;
	(*glGenVertexArraysSRC)(1, &vao);

	if (vao == 0) {
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		return 1;
	}

	(*glDeleteVertexArraysSRC)(1, &vao);
	return 0;
}

#undef RGL_PROC_DEF

struct isolated_audio_thread_data_ audio_thread_data;
struct isolated_audio_vertices_ audio_vert;
U32 fft_phase_frames[2];
pthread_mutex_t vert_mutex = PTHREAD_MUTEX_INITIALIZER;
int tmpphase = 0;

OPTIONAL_ALIGNAS(SIMD_NBYTES)
F32 fft_buffer_original[(1uLL << MAX_K) * 2];

OPTIONAL_ALIGNAS(SIMD_NBYTES)
F32 fft_buffer_processed[(1uLL << MAX_K) * 2];

OPTIONAL_ALIGNAS(SIMD_NBYTES)
F32 buffer_for_visualization[1uLL << MAX_K];

#define REQUESTED_NR_PERIODS 2

#define GENERATE_DECLARE_rt_audio_callback(in, out, fft_k, i_sizeofbits, o_sizeofbits, nr_active_channels, nr_all_channels)    \
	void rt_audio_callback_##in##_##out##_##fft_k##_##nr_active_channels##_##nr_all_channels(ma_device *restrict p_device, \
												 void *restrict p_output,      \
												 const void *restrict p_input, \
												 ma_uint32 frame_count_ma_param)

GENERATE_DECLARE_rt_audio_callback(s16, s16, 10, 16, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 10, 24, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 10, 32, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 10, 32, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 10, 16, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 10, 24, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 10, 32, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 10, 32, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 10, 16, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 10, 24, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 10, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 10, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 10, 16, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 10, 24, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 10, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 10, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 11, 16, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 11, 24, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 11, 32, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 11, 32, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 11, 16, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 11, 24, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 11, 32, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 11, 32, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 11, 16, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 11, 24, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 11, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 11, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 11, 16, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 11, 24, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 11, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 11, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 12, 16, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 12, 24, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 12, 32, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 12, 32, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 12, 16, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 12, 24, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 12, 32, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 12, 32, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 12, 16, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 12, 24, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 12, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 12, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 12, 16, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 12, 24, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 12, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 12, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 13, 16, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 13, 24, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 13, 32, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 13, 32, 16, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 13, 16, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 13, 24, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 13, 32, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 13, 32, 24, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 13, 16, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 13, 24, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 13, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 13, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 13, 16, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 13, 24, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 13, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 13, 32, 32, 1, 1);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 10, 16, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 10, 24, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 10, 32, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 10, 32, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 10, 16, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 10, 24, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 10, 32, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 10, 32, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 10, 16, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 10, 24, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 10, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 10, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 10, 16, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 10, 24, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 10, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 10, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 11, 16, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 11, 24, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 11, 32, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 11, 32, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 11, 16, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 11, 24, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 11, 32, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 11, 32, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 11, 16, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 11, 24, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 11, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 11, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 11, 16, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 11, 24, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 11, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 11, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 12, 16, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 12, 24, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 12, 32, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 12, 32, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 12, 16, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 12, 24, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 12, 32, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 12, 32, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 12, 16, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 12, 24, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 12, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 12, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 12, 16, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 12, 24, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 12, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 12, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 13, 16, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 13, 24, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 13, 32, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 13, 32, 16, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 13, 16, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 13, 24, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 13, 32, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 13, 32, 24, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 13, 16, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 13, 24, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 13, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 13, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 13, 16, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 13, 24, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 13, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 13, 32, 32, 1, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 10, 16, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 10, 24, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 10, 32, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 10, 32, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 10, 16, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 10, 24, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 10, 32, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 10, 32, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 10, 16, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 10, 24, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 10, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 10, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 10, 16, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 10, 24, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 10, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 10, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 11, 16, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 11, 24, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 11, 32, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 11, 32, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 11, 16, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 11, 24, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 11, 32, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 11, 32, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 11, 16, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 11, 24, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 11, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 11, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 11, 16, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 11, 24, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 11, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 11, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 12, 16, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 12, 24, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 12, 32, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 12, 32, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 12, 16, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 12, 24, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 12, 32, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 12, 32, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 12, 16, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 12, 24, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 12, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 12, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 12, 16, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 12, 24, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 12, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 12, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s16, 13, 16, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s16, 13, 24, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s16, 13, 32, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s16, 13, 32, 16, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s24, 13, 16, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s24, 13, 24, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s24, 13, 32, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s24, 13, 32, 24, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, s32, 13, 16, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, s32, 13, 24, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, s32, 13, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, s32, 13, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s16, f32, 13, 16, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s24, f32, 13, 24, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(s32, f32, 13, 32, 32, 2, 2);
GENERATE_DECLARE_rt_audio_callback(f32, f32, 13, 32, 32, 2, 2);

#define ARENA_FOR_DEPENDENCIES_MAX_NBYTES_TOTAL (1024uLL * 1024)
#define ARENA_FOR_DEPENDENCIES_MAX_NBYTES_SINGLE (1024uLL * 128)
#define ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES 128

static void *arena_for_dependencies = NULL;

static void rt_audio_callback_dummy(ma_device *restrict p_device,
				    void *restrict p_output,
				    const void *restrict p_input,
				    ma_uint32 frame_count_ma_param)
{
	(void)p_device;
	(void)p_output;
	(void)p_input;
	(void)frame_count_ma_param;
}

int gl_argc;
char **gl_argv;

static THREAD_LOCAL char tls_failure_report[4096];

static NOINLINE void tls_fail(void *user_report, void *dev_report)
{
#if !defined(DEV_REPORT)
	(void)dev_report;
#endif

	U64 i;
	U64 n;
	S32 newline_done;

	newline_done = 0;
	i = naive_strlen(tls_failure_report);

	if (i == sizeof tls_failure_report - 1) {
		return;
	}

	if (user_report != NULL) {
		tls_failure_report[i] = newline_done ? ' ' : '\n';
		newline_done = 1;
		++i;

		if (i == sizeof tls_failure_report - 1) {
			return;
		}

		n = naive_strlen(user_report);
		n = MIN(n, sizeof tls_failure_report - 1 - i);
		naive_memcpy(tls_failure_report + i, user_report, n);
		i += n;

		if (i == sizeof tls_failure_report - 1) {
			return;
		}
	}

#if defined(DEV_REPORT)

	if (dev_report != NULL) {
		tls_failure_report[i] = newline_done ? ' ' : '\n';
		newline_done = 1;
		++i;

		if (i == sizeof tls_failure_report - 1) {
			return;
		}

		n = naive_strlen(dev_report);
		n = MIN(n, sizeof tls_failure_report - 1 - i);
		naive_memcpy(tls_failure_report + i, dev_report, n);
		i += n;

		if (i == sizeof tls_failure_report - 1) {
			return;
		}
	}

#endif
}

static ALWAYS_INLINE int submain(void)
{
	S32 argc = gl_argc;
	char **argv = gl_argv;

	U32 nr_active_channels = 1;

	if (argc >= 3) {
		if (argv[2][0] == '1') {
			nr_active_channels = 1;
		} else if (argv[2][0] == '2') {
			nr_active_channels = 2;
		}
	}

	/* */

	void *c = NULL;
	void *p = NULL;

	int device_init;
	int mem_lock;

	disable_denormals();

	device_init = 0;
	mem_lock = 0;
	(void)mem_lock;

	/* arena for dependencies */

	if (RARELY(0 > sys_mmap(NULL, ARENA_FOR_DEPENDENCIES_MAX_NBYTES_TOTAL, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0, &arena_for_dependencies))) {
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		goto l_exit_failure;
	}

	for (UPTR i = 0; i < ARENA_FOR_DEPENDENCIES_MAX_NBYTES_TOTAL / sizeof(UPTR); ++i) {
		ATOMIC_STORE(sizeof(ATOMIC UPTR) * CHAR_BIT, (ATOMIC UPTR *)arena_for_dependencies + i, 0, ATOMIC_RELEASE);
	}

	/* dlopen */

	c = dlopen(NULL, RTLD_NOW);
	if (RARELY(c == NULL)) {
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		goto l_exit_failure;
	}

	p = dlopen("libpthread.so.0", RTLD_NOW);
	if (RARELY(p == NULL)) {
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		goto l_exit_failure;
	}

	if (RARELY(0 != init_all_pfn(c, p))) {
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		goto l_exit_failure;
	}

	/* audio */

	ma_device_config deviceConfig;
	ma_device dummy_device;
	ma_device device;

	ma_device_config_init(&deviceConfig, ma_device_type_playback | ma_device_type_capture);

	deviceConfig.playback.channels = REQUESTED_PLAYBACK_NR_CHANNELS;
	deviceConfig.dataCallback = rt_audio_callback_dummy;
	deviceConfig.pUserData = NULL;
	deviceConfig.noFixedSizedCallback = MA_TRUE;
	deviceConfig.periods = REQUESTED_NR_PERIODS;
	deviceConfig.noClip = MA_TRUE;
	deviceConfig.performanceProfile = ma_performance_profile_low_latency;
	deviceConfig.noPreSilencedOutputBuffer = MA_TRUE;

	deviceConfig.alsa.noAutoResample = MA_TRUE;
	deviceConfig.alsa.noAutoChannels = MA_TRUE;
	deviceConfig.alsa.noAutoFormat = MA_TRUE;

	if (RARELY(MA_SUCCESS != ma_device_init(NULL, &deviceConfig, &dummy_device))) {
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		goto l_exit_failure;
	}
	device_init = 1;

	if (RARELY((int)(dummy_device.playback.internalSampleRate != dummy_device.capture.internalSampleRate) |
		   (int)(dummy_device.capture.internalSampleRate != 48000) &
		       (int)(dummy_device.capture.internalSampleRate != 96000) &
		       (int)(dummy_device.capture.internalSampleRate != 192000) &
		       (int)(dummy_device.capture.internalSampleRate != 384000) |
		   (int)(dummy_device.playback.internalChannels != REQUESTED_PLAYBACK_NR_CHANNELS) |
		   (int)(dummy_device.capture.internalChannels != 1) & (int)(dummy_device.capture.internalChannels != 2) |
		   (int)(dummy_device.playback.internalFormat != ma_format_s16) &
		       (int)(dummy_device.playback.internalFormat != ma_format_s24) &
		       (int)(dummy_device.playback.internalFormat != ma_format_f32) &
		       (int)(dummy_device.playback.internalFormat != ma_format_s32) |
		   (int)(dummy_device.capture.internalFormat != ma_format_s16) &
		       (int)(dummy_device.capture.internalFormat != ma_format_s24) &
		       (int)(dummy_device.capture.internalFormat != ma_format_s32) &
		       (int)(dummy_device.capture.internalFormat != ma_format_f32) |
		   (int)(dummy_device.playback.internalPeriods != REQUESTED_NR_PERIODS) |
		   (int)(dummy_device.capture.internalPeriods != REQUESTED_NR_PERIODS))) {
		failure_print_string("line ");
		failure_print_dec_u64(__LINE__);
		failure_print_string("\nactual data:\ndevice.playback.internalSampleRate = ");
		failure_print_dec_u64(dummy_device.playback.internalSampleRate);
		failure_print_string("\ndevice.capture.internalSampleRate = ");
		failure_print_dec_u64(dummy_device.capture.internalSampleRate);
		failure_print_string("\ndevice.playback.internalChannels = ");
		failure_print_dec_u64(dummy_device.playback.internalChannels);
		failure_print_string(", requested " STRINGIZE_VALUE(REQUESTED_PLAYBACK_NR_CHANNELS) "\ndevice.capture.internalChannels = ");
		failure_print_dec_u64(dummy_device.capture.internalChannels);
		failure_print_string("\ndevice.playback.internalFormat = ");
		failure_print_dec_u64(dummy_device.playback.internalFormat);
		failure_print_string(", requested ");
		failure_print_dec_u64(ma_format_f32);
		failure_print_string("\ndevice.capture.internalFormat = ");
		failure_print_dec_u64(dummy_device.capture.internalFormat);
		failure_print_string(", requested ");
		failure_print_dec_u64(ma_format_f32);
		failure_print_string("\ndevice.playback.internalPeriods = ");
		failure_print_dec_u64(dummy_device.playback.internalPeriods);
		failure_print_string(", requested " STRINGIZE_VALUE(REQUESTED_NR_PERIODS) "\ndevice.capture.internalPeriods = ");
		failure_print_dec_u64(dummy_device.capture.internalPeriods);
		failure_print_string(", requested " STRINGIZE_VALUE(REQUESTED_NR_PERIODS) "\ndevice.playback.internalPeriodSizeInFrames = ");
		failure_print_dec_u64(dummy_device.playback.internalPeriodSizeInFrames);
		failure_print_string("\ndevice.capture.internalPeriodSizeInFrames = ");
		failure_print_dec_u64(dummy_device.capture.internalPeriodSizeInFrames);
		failure_print_string("\n");
		goto l_exit_failure;
	}

	U32 dummy_device_playback_internalSampleRate = dummy_device.playback.internalSampleRate;
	ma_format dummy_device_capture_internalFormat = dummy_device.capture.internalFormat;
	ma_format dummy_device_playback_internalFormat = dummy_device.playback.internalFormat;
	U32 dummy_device_capture_internalChannels = dummy_device.capture.internalChannels;
	U32 dummy_device_playback_internalChannels = dummy_device.playback.internalChannels;
	U32 dummy_device_capture_internalSampleRate = dummy_device.capture.internalSampleRate;

	ma_device_uninit(&dummy_device);
	device_init = 0;

	{
		U32 sample_rate_idx;
		U32 in_idx;
		U32 out_idx;
		U32 channelconf_idx;

		switch (dummy_device_playback_internalSampleRate) {
		case 48000:
			sample_rate_idx = 0;
			break;
		case 96000:
			sample_rate_idx = 1;
			break;
		case 192000:
			sample_rate_idx = 2;
			break;
		case 384000:
			sample_rate_idx = 3;
			break;
		default:
			NEVER(0);
			sample_rate_idx = 0;
			break;
		}

		switch (dummy_device_capture_internalFormat) {
		case ma_format_s16:
			in_idx = 0;
			break;
		case ma_format_s24:
			in_idx = 1;
			break;
		case ma_format_s32:
			in_idx = 2;
			break;
		case ma_format_f32:
			in_idx = 3;
			break;
		default:
			NEVER(0);
			in_idx = 0;
			break;
		}

		switch (dummy_device_playback_internalFormat) {
		case ma_format_s16:
			out_idx = 0;
			break;
		case ma_format_s24:
			out_idx = 1;
			break;
		case ma_format_s32:
			out_idx = 2;
			break;
		case ma_format_f32:
			out_idx = 3;
			break;
		default:
			NEVER(0);
			out_idx = 0;
			break;
		}

		nr_active_channels = MIN(nr_active_channels, dummy_device_capture_internalChannels);
		nr_active_channels = MIN(nr_active_channels, dummy_device_playback_internalChannels);

		assert(dummy_device_playback_internalChannels == REQUESTED_PLAYBACK_NR_CHANNELS);

		if (nr_active_channels == 1 && dummy_device_capture_internalChannels == 1) {
			channelconf_idx = 0;
		} else if (nr_active_channels == 1 && dummy_device_capture_internalChannels == 2) {
			channelconf_idx = 1;
		} else if (nr_active_channels == 2 && dummy_device_capture_internalChannels == 2 && dummy_device_playback_internalChannels == 2) {
			channelconf_idx = 2;
		} else {
			NEVER(0);
			channelconf_idx = 0;
		}

		out_idx <<= 2;
		in_idx <<= 4;
		channelconf_idx <<= 6;

		/* clang-format off */
		switch (channelconf_idx | in_idx | out_idx | sample_rate_idx) {
		case 0  : deviceConfig.dataCallback = rt_audio_callback_s16_s16_10_1_1; break;
		case 1  : deviceConfig.dataCallback = rt_audio_callback_s16_s16_11_1_1; break;
		case 2  : deviceConfig.dataCallback = rt_audio_callback_s16_s16_12_1_1; break;
		case 3  : deviceConfig.dataCallback = rt_audio_callback_s16_s16_13_1_1; break;
		case 4  : deviceConfig.dataCallback = rt_audio_callback_s16_s24_10_1_1; break;
		case 5  : deviceConfig.dataCallback = rt_audio_callback_s16_s24_11_1_1; break;
		case 6  : deviceConfig.dataCallback = rt_audio_callback_s16_s24_12_1_1; break;
		case 7  : deviceConfig.dataCallback = rt_audio_callback_s16_s24_13_1_1; break;
		case 8  : deviceConfig.dataCallback = rt_audio_callback_s16_s32_10_1_1; break;
		case 9  : deviceConfig.dataCallback = rt_audio_callback_s16_s32_11_1_1; break;
		case 10 : deviceConfig.dataCallback = rt_audio_callback_s16_s32_12_1_1; break;
		case 11 : deviceConfig.dataCallback = rt_audio_callback_s16_s32_13_1_1; break;
		case 12 : deviceConfig.dataCallback = rt_audio_callback_s16_f32_10_1_1; break;
		case 13 : deviceConfig.dataCallback = rt_audio_callback_s16_f32_11_1_1; break;
		case 14 : deviceConfig.dataCallback = rt_audio_callback_s16_f32_12_1_1; break;
		case 15 : deviceConfig.dataCallback = rt_audio_callback_s16_f32_13_1_1; break;
		case 16 : deviceConfig.dataCallback = rt_audio_callback_s24_s16_10_1_1; break;
		case 17 : deviceConfig.dataCallback = rt_audio_callback_s24_s16_11_1_1; break;
		case 18 : deviceConfig.dataCallback = rt_audio_callback_s24_s16_12_1_1; break;
		case 19 : deviceConfig.dataCallback = rt_audio_callback_s24_s16_13_1_1; break;
		case 20 : deviceConfig.dataCallback = rt_audio_callback_s24_s24_10_1_1; break;
		case 21 : deviceConfig.dataCallback = rt_audio_callback_s24_s24_11_1_1; break;
		case 22 : deviceConfig.dataCallback = rt_audio_callback_s24_s24_12_1_1; break;
		case 23 : deviceConfig.dataCallback = rt_audio_callback_s24_s24_13_1_1; break;
		case 24 : deviceConfig.dataCallback = rt_audio_callback_s24_s32_10_1_1; break;
		case 25 : deviceConfig.dataCallback = rt_audio_callback_s24_s32_11_1_1; break;
		case 26 : deviceConfig.dataCallback = rt_audio_callback_s24_s32_12_1_1; break;
		case 27 : deviceConfig.dataCallback = rt_audio_callback_s24_s32_13_1_1; break;
		case 28 : deviceConfig.dataCallback = rt_audio_callback_s24_f32_10_1_1; break;
		case 29 : deviceConfig.dataCallback = rt_audio_callback_s24_f32_11_1_1; break;
		case 30 : deviceConfig.dataCallback = rt_audio_callback_s24_f32_12_1_1; break;
		case 31 : deviceConfig.dataCallback = rt_audio_callback_s24_f32_13_1_1; break;
		case 32 : deviceConfig.dataCallback = rt_audio_callback_s32_s16_10_1_1; break;
		case 33 : deviceConfig.dataCallback = rt_audio_callback_s32_s16_11_1_1; break;
		case 34 : deviceConfig.dataCallback = rt_audio_callback_s32_s16_12_1_1; break;
		case 35 : deviceConfig.dataCallback = rt_audio_callback_s32_s16_13_1_1; break;
		case 36 : deviceConfig.dataCallback = rt_audio_callback_s32_s24_10_1_1; break;
		case 37 : deviceConfig.dataCallback = rt_audio_callback_s32_s24_11_1_1; break;
		case 38 : deviceConfig.dataCallback = rt_audio_callback_s32_s24_12_1_1; break;
		case 39 : deviceConfig.dataCallback = rt_audio_callback_s32_s24_13_1_1; break;
		case 40 : deviceConfig.dataCallback = rt_audio_callback_s32_s32_10_1_1; break;
		case 41 : deviceConfig.dataCallback = rt_audio_callback_s32_s32_11_1_1; break;
		case 42 : deviceConfig.dataCallback = rt_audio_callback_s32_s32_12_1_1; break;
		case 43 : deviceConfig.dataCallback = rt_audio_callback_s32_s32_13_1_1; break;
		case 44 : deviceConfig.dataCallback = rt_audio_callback_s32_f32_10_1_1; break;
		case 45 : deviceConfig.dataCallback = rt_audio_callback_s32_f32_11_1_1; break;
		case 46 : deviceConfig.dataCallback = rt_audio_callback_s32_f32_12_1_1; break;
		case 47 : deviceConfig.dataCallback = rt_audio_callback_s32_f32_13_1_1; break;
		case 48 : deviceConfig.dataCallback = rt_audio_callback_f32_s16_10_1_1; break;
		case 49 : deviceConfig.dataCallback = rt_audio_callback_f32_s16_11_1_1; break;
		case 50 : deviceConfig.dataCallback = rt_audio_callback_f32_s16_12_1_1; break;
		case 51 : deviceConfig.dataCallback = rt_audio_callback_f32_s16_13_1_1; break;
		case 52 : deviceConfig.dataCallback = rt_audio_callback_f32_s24_10_1_1; break;
		case 53 : deviceConfig.dataCallback = rt_audio_callback_f32_s24_11_1_1; break;
		case 54 : deviceConfig.dataCallback = rt_audio_callback_f32_s24_12_1_1; break;
		case 55 : deviceConfig.dataCallback = rt_audio_callback_f32_s24_13_1_1; break;
		case 56 : deviceConfig.dataCallback = rt_audio_callback_f32_s32_10_1_1; break;
		case 57 : deviceConfig.dataCallback = rt_audio_callback_f32_s32_11_1_1; break;
		case 58 : deviceConfig.dataCallback = rt_audio_callback_f32_s32_12_1_1; break;
		case 59 : deviceConfig.dataCallback = rt_audio_callback_f32_s32_13_1_1; break;
		case 60 : deviceConfig.dataCallback = rt_audio_callback_f32_f32_10_1_1; break;
		case 61 : deviceConfig.dataCallback = rt_audio_callback_f32_f32_11_1_1; break;
		case 62 : deviceConfig.dataCallback = rt_audio_callback_f32_f32_12_1_1; break;
		case 63 : deviceConfig.dataCallback = rt_audio_callback_f32_f32_13_1_1; break;
		case 64 : deviceConfig.dataCallback = rt_audio_callback_s16_s16_10_1_2; break;
		case 65 : deviceConfig.dataCallback = rt_audio_callback_s16_s16_11_1_2; break;
		case 66 : deviceConfig.dataCallback = rt_audio_callback_s16_s16_12_1_2; break;
		case 67 : deviceConfig.dataCallback = rt_audio_callback_s16_s16_13_1_2; break;
		case 68 : deviceConfig.dataCallback = rt_audio_callback_s16_s24_10_1_2; break;
		case 69 : deviceConfig.dataCallback = rt_audio_callback_s16_s24_11_1_2; break;
		case 70 : deviceConfig.dataCallback = rt_audio_callback_s16_s24_12_1_2; break;
		case 71 : deviceConfig.dataCallback = rt_audio_callback_s16_s24_13_1_2; break;
		case 72 : deviceConfig.dataCallback = rt_audio_callback_s16_s32_10_1_2; break;
		case 73 : deviceConfig.dataCallback = rt_audio_callback_s16_s32_11_1_2; break;
		case 74 : deviceConfig.dataCallback = rt_audio_callback_s16_s32_12_1_2; break;
		case 75 : deviceConfig.dataCallback = rt_audio_callback_s16_s32_13_1_2; break;
		case 76 : deviceConfig.dataCallback = rt_audio_callback_s16_f32_10_1_2; break;
		case 77 : deviceConfig.dataCallback = rt_audio_callback_s16_f32_11_1_2; break;
		case 78 : deviceConfig.dataCallback = rt_audio_callback_s16_f32_12_1_2; break;
		case 79 : deviceConfig.dataCallback = rt_audio_callback_s16_f32_13_1_2; break;
		case 80 : deviceConfig.dataCallback = rt_audio_callback_s24_s16_10_1_2; break;
		case 81 : deviceConfig.dataCallback = rt_audio_callback_s24_s16_11_1_2; break;
		case 82 : deviceConfig.dataCallback = rt_audio_callback_s24_s16_12_1_2; break;
		case 83 : deviceConfig.dataCallback = rt_audio_callback_s24_s16_13_1_2; break;
		case 84 : deviceConfig.dataCallback = rt_audio_callback_s24_s24_10_1_2; break;
		case 85 : deviceConfig.dataCallback = rt_audio_callback_s24_s24_11_1_2; break;
		case 86 : deviceConfig.dataCallback = rt_audio_callback_s24_s24_12_1_2; break;
		case 87 : deviceConfig.dataCallback = rt_audio_callback_s24_s24_13_1_2; break;
		case 88 : deviceConfig.dataCallback = rt_audio_callback_s24_s32_10_1_2; break;
		case 89 : deviceConfig.dataCallback = rt_audio_callback_s24_s32_11_1_2; break;
		case 90 : deviceConfig.dataCallback = rt_audio_callback_s24_s32_12_1_2; break;
		case 91 : deviceConfig.dataCallback = rt_audio_callback_s24_s32_13_1_2; break;
		case 92 : deviceConfig.dataCallback = rt_audio_callback_s24_f32_10_1_2; break;
		case 93 : deviceConfig.dataCallback = rt_audio_callback_s24_f32_11_1_2; break;
		case 94 : deviceConfig.dataCallback = rt_audio_callback_s24_f32_12_1_2; break;
		case 95 : deviceConfig.dataCallback = rt_audio_callback_s24_f32_13_1_2; break;
		case 96 : deviceConfig.dataCallback = rt_audio_callback_s32_s16_10_1_2; break;
		case 97 : deviceConfig.dataCallback = rt_audio_callback_s32_s16_11_1_2; break;
		case 98 : deviceConfig.dataCallback = rt_audio_callback_s32_s16_12_1_2; break;
		case 99 : deviceConfig.dataCallback = rt_audio_callback_s32_s16_13_1_2; break;
		case 100: deviceConfig.dataCallback = rt_audio_callback_s32_s24_10_1_2; break;
		case 101: deviceConfig.dataCallback = rt_audio_callback_s32_s24_11_1_2; break;
		case 102: deviceConfig.dataCallback = rt_audio_callback_s32_s24_12_1_2; break;
		case 103: deviceConfig.dataCallback = rt_audio_callback_s32_s24_13_1_2; break;
		case 104: deviceConfig.dataCallback = rt_audio_callback_s32_s32_10_1_2; break;
		case 105: deviceConfig.dataCallback = rt_audio_callback_s32_s32_11_1_2; break;
		case 106: deviceConfig.dataCallback = rt_audio_callback_s32_s32_12_1_2; break;
		case 107: deviceConfig.dataCallback = rt_audio_callback_s32_s32_13_1_2; break;
		case 108: deviceConfig.dataCallback = rt_audio_callback_s32_f32_10_1_2; break;
		case 109: deviceConfig.dataCallback = rt_audio_callback_s32_f32_11_1_2; break;
		case 110: deviceConfig.dataCallback = rt_audio_callback_s32_f32_12_1_2; break;
		case 111: deviceConfig.dataCallback = rt_audio_callback_s32_f32_13_1_2; break;
		case 112: deviceConfig.dataCallback = rt_audio_callback_f32_s16_10_1_2; break;
		case 113: deviceConfig.dataCallback = rt_audio_callback_f32_s16_11_1_2; break;
		case 114: deviceConfig.dataCallback = rt_audio_callback_f32_s16_12_1_2; break;
		case 115: deviceConfig.dataCallback = rt_audio_callback_f32_s16_13_1_2; break;
		case 116: deviceConfig.dataCallback = rt_audio_callback_f32_s24_10_1_2; break;
		case 117: deviceConfig.dataCallback = rt_audio_callback_f32_s24_11_1_2; break;
		case 118: deviceConfig.dataCallback = rt_audio_callback_f32_s24_12_1_2; break;
		case 119: deviceConfig.dataCallback = rt_audio_callback_f32_s24_13_1_2; break;
		case 120: deviceConfig.dataCallback = rt_audio_callback_f32_s32_10_1_2; break;
		case 121: deviceConfig.dataCallback = rt_audio_callback_f32_s32_11_1_2; break;
		case 122: deviceConfig.dataCallback = rt_audio_callback_f32_s32_12_1_2; break;
		case 123: deviceConfig.dataCallback = rt_audio_callback_f32_s32_13_1_2; break;
		case 124: deviceConfig.dataCallback = rt_audio_callback_f32_f32_10_1_2; break;
		case 125: deviceConfig.dataCallback = rt_audio_callback_f32_f32_11_1_2; break;
		case 126: deviceConfig.dataCallback = rt_audio_callback_f32_f32_12_1_2; break;
		case 127: deviceConfig.dataCallback = rt_audio_callback_f32_f32_13_1_2; break;
		case 128: deviceConfig.dataCallback = rt_audio_callback_s16_s16_10_2_2; break;
		case 129: deviceConfig.dataCallback = rt_audio_callback_s16_s16_11_2_2; break;
		case 130: deviceConfig.dataCallback = rt_audio_callback_s16_s16_12_2_2; break;
		case 131: deviceConfig.dataCallback = rt_audio_callback_s16_s16_13_2_2; break;
		case 132: deviceConfig.dataCallback = rt_audio_callback_s16_s24_10_2_2; break;
		case 133: deviceConfig.dataCallback = rt_audio_callback_s16_s24_11_2_2; break;
		case 134: deviceConfig.dataCallback = rt_audio_callback_s16_s24_12_2_2; break;
		case 135: deviceConfig.dataCallback = rt_audio_callback_s16_s24_13_2_2; break;
		case 136: deviceConfig.dataCallback = rt_audio_callback_s16_s32_10_2_2; break;
		case 137: deviceConfig.dataCallback = rt_audio_callback_s16_s32_11_2_2; break;
		case 138: deviceConfig.dataCallback = rt_audio_callback_s16_s32_12_2_2; break;
		case 139: deviceConfig.dataCallback = rt_audio_callback_s16_s32_13_2_2; break;
		case 140: deviceConfig.dataCallback = rt_audio_callback_s16_f32_10_2_2; break;
		case 141: deviceConfig.dataCallback = rt_audio_callback_s16_f32_11_2_2; break;
		case 142: deviceConfig.dataCallback = rt_audio_callback_s16_f32_12_2_2; break;
		case 143: deviceConfig.dataCallback = rt_audio_callback_s16_f32_13_2_2; break;
		case 144: deviceConfig.dataCallback = rt_audio_callback_s24_s16_10_2_2; break;
		case 145: deviceConfig.dataCallback = rt_audio_callback_s24_s16_11_2_2; break;
		case 146: deviceConfig.dataCallback = rt_audio_callback_s24_s16_12_2_2; break;
		case 147: deviceConfig.dataCallback = rt_audio_callback_s24_s16_13_2_2; break;
		case 148: deviceConfig.dataCallback = rt_audio_callback_s24_s24_10_2_2; break;
		case 149: deviceConfig.dataCallback = rt_audio_callback_s24_s24_11_2_2; break;
		case 150: deviceConfig.dataCallback = rt_audio_callback_s24_s24_12_2_2; break;
		case 151: deviceConfig.dataCallback = rt_audio_callback_s24_s24_13_2_2; break;
		case 152: deviceConfig.dataCallback = rt_audio_callback_s24_s32_10_2_2; break;
		case 153: deviceConfig.dataCallback = rt_audio_callback_s24_s32_11_2_2; break;
		case 154: deviceConfig.dataCallback = rt_audio_callback_s24_s32_12_2_2; break;
		case 155: deviceConfig.dataCallback = rt_audio_callback_s24_s32_13_2_2; break;
		case 156: deviceConfig.dataCallback = rt_audio_callback_s24_f32_10_2_2; break;
		case 157: deviceConfig.dataCallback = rt_audio_callback_s24_f32_11_2_2; break;
		case 158: deviceConfig.dataCallback = rt_audio_callback_s24_f32_12_2_2; break;
		case 159: deviceConfig.dataCallback = rt_audio_callback_s24_f32_13_2_2; break;
		case 160: deviceConfig.dataCallback = rt_audio_callback_s32_s16_10_2_2; break;
		case 161: deviceConfig.dataCallback = rt_audio_callback_s32_s16_11_2_2; break;
		case 162: deviceConfig.dataCallback = rt_audio_callback_s32_s16_12_2_2; break;
		case 163: deviceConfig.dataCallback = rt_audio_callback_s32_s16_13_2_2; break;
		case 164: deviceConfig.dataCallback = rt_audio_callback_s32_s24_10_2_2; break;
		case 165: deviceConfig.dataCallback = rt_audio_callback_s32_s24_11_2_2; break;
		case 166: deviceConfig.dataCallback = rt_audio_callback_s32_s24_12_2_2; break;
		case 167: deviceConfig.dataCallback = rt_audio_callback_s32_s24_13_2_2; break;
		case 168: deviceConfig.dataCallback = rt_audio_callback_s32_s32_10_2_2; break;
		case 169: deviceConfig.dataCallback = rt_audio_callback_s32_s32_11_2_2; break;
		case 170: deviceConfig.dataCallback = rt_audio_callback_s32_s32_12_2_2; break;
		case 171: deviceConfig.dataCallback = rt_audio_callback_s32_s32_13_2_2; break;
		case 172: deviceConfig.dataCallback = rt_audio_callback_s32_f32_10_2_2; break;
		case 173: deviceConfig.dataCallback = rt_audio_callback_s32_f32_11_2_2; break;
		case 174: deviceConfig.dataCallback = rt_audio_callback_s32_f32_12_2_2; break;
		case 175: deviceConfig.dataCallback = rt_audio_callback_s32_f32_13_2_2; break;
		case 176: deviceConfig.dataCallback = rt_audio_callback_f32_s16_10_2_2; break;
		case 177: deviceConfig.dataCallback = rt_audio_callback_f32_s16_11_2_2; break;
		case 178: deviceConfig.dataCallback = rt_audio_callback_f32_s16_12_2_2; break;
		case 179: deviceConfig.dataCallback = rt_audio_callback_f32_s16_13_2_2; break;
		case 180: deviceConfig.dataCallback = rt_audio_callback_f32_s24_10_2_2; break;
		case 181: deviceConfig.dataCallback = rt_audio_callback_f32_s24_11_2_2; break;
		case 182: deviceConfig.dataCallback = rt_audio_callback_f32_s24_12_2_2; break;
		case 183: deviceConfig.dataCallback = rt_audio_callback_f32_s24_13_2_2; break;
		case 184: deviceConfig.dataCallback = rt_audio_callback_f32_s32_10_2_2; break;
		case 185: deviceConfig.dataCallback = rt_audio_callback_f32_s32_11_2_2; break;
		case 186: deviceConfig.dataCallback = rt_audio_callback_f32_s32_12_2_2; break;
		case 187: deviceConfig.dataCallback = rt_audio_callback_f32_s32_13_2_2; break;
		case 188: deviceConfig.dataCallback = rt_audio_callback_f32_f32_10_2_2; break;
		case 189: deviceConfig.dataCallback = rt_audio_callback_f32_f32_11_2_2; break;
		case 190: deviceConfig.dataCallback = rt_audio_callback_f32_f32_12_2_2; break;
		case 191: deviceConfig.dataCallback = rt_audio_callback_f32_f32_13_2_2; break;
		default:
			NEVER(0);
			break;
		}
		/* clang-format on */

		deviceConfig.periodSizeInFrames = (1 << 10) * (1 << sample_rate_idx);
		deviceConfig.sampleRate = dummy_device_playback_internalSampleRate;
		deviceConfig.playback.channels = REQUESTED_PLAYBACK_NR_CHANNELS;
		deviceConfig.capture.channels = dummy_device_capture_internalChannels;
		deviceConfig.playback.format = dummy_device_playback_internalFormat;
		deviceConfig.capture.format = dummy_device_capture_internalFormat;
	}

	if (RARELY(MA_SUCCESS != ma_device_init(NULL, &deviceConfig, &device))) {
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		goto l_exit_failure;
	}
	device_init = 1;

	if (RARELY((int)(device.playback.internalSampleRate != device.capture.internalSampleRate) |
		   (int)(device.capture.internalSampleRate != dummy_device_capture_internalSampleRate) |
		   (int)(device.playback.internalChannels != REQUESTED_PLAYBACK_NR_CHANNELS) |
		   (int)(device.capture.internalChannels != dummy_device_capture_internalChannels) |
		   (int)(device.playback.internalFormat != dummy_device_playback_internalFormat) |
		   (int)(device.capture.internalFormat != dummy_device_capture_internalFormat) |
		   (int)(device.playback.internalPeriods != REQUESTED_NR_PERIODS) |
		   (int)(device.capture.internalPeriods != REQUESTED_NR_PERIODS))) {
		failure_print_string("line ");
		failure_print_dec_u64(__LINE__);
		failure_print_string("\nactual data:\ndevice.playback.internalSampleRate = ");
		failure_print_dec_u64(device.playback.internalSampleRate);
		failure_print_string("\ndevice.capture.internalSampleRate = ");
		failure_print_dec_u64(device.capture.internalSampleRate);
		failure_print_string(", requested ");
		failure_print_dec_u64(dummy_device_capture_internalSampleRate);
		failure_print_string("\ndevice.playback.internalChannels = ");
		failure_print_dec_u64(device.playback.internalChannels);
		failure_print_string(", requested " STRINGIZE_VALUE(REQUESTED_PLAYBACK_NR_CHANNELS) "\ndevice.capture.internalChannels = ");
		failure_print_dec_u64(device.capture.internalChannels);
		failure_print_string("\ndevice.playback.internalFormat = ");
		failure_print_dec_u64(device.playback.internalFormat);
		failure_print_string("\ndevice.capture.internalFormat = ");
		failure_print_dec_u64(device.capture.internalFormat);
		failure_print_string("\ndevice.playback.internalPeriods = ");
		failure_print_dec_u64(device.playback.internalPeriods);
		failure_print_string(", requested " STRINGIZE_VALUE(REQUESTED_NR_PERIODS) "\ndevice.capture.internalPeriods = ");
		failure_print_dec_u64(device.capture.internalPeriods);
		failure_print_string(", requested " STRINGIZE_VALUE(REQUESTED_NR_PERIODS) "\ndevice.playback.internalPeriodSizeInFrames = ");
		failure_print_dec_u64(device.playback.internalPeriodSizeInFrames);
		failure_print_string("\ndevice.capture.internalPeriodSizeInFrames = ");
		failure_print_dec_u64(device.capture.internalPeriodSizeInFrames);
		failure_print_string("\n");
		goto l_exit_failure;
	}

	/* graphics */

	for (U32 i = 0; i < (1uLL << MAX_K); i += 1) {
		audio_vert.time[i * 2 + 0] = ((F32)i / (1uLL << MAX_K)) * 2 - 1;
#if 0
		audio_vert.freq[i * 2 + 0] = ((F32)i / VISUALIZATION_K) * 4 - 1;
		audio_vert.phase[i * 2 + 0] = ((F32)i / VISUALIZATION_K) * 4 - 1;
#else
		F32 tmp = 1 / M_Ef / M_Ef / M_Ef / M_Ef;
		audio_vert.freq[i * 2 + 0] = ((F32)naive_log_natural_iter_f32((F32)i / (1uLL << MAX_K) * (1 - tmp) + tmp, 50) / 4 + 1) * 2.375f - 1;
		audio_vert.phase[i * 2 + 0] = audio_vert.freq[i * 2 + 0];
#endif
	}

	RGFW_init("halley", RGFW_initOpenGL);

	RGFW_glHints *hints = RGFW_getGlobalHints_OpenGL();
	hints->major = 3;
	hints->minor = 3;
	RGFW_setGlobalHints_OpenGL(hints);

	RGFW_window *window = RGFW_createWindow("Halley", 800, 600, 800, 600, RGFW_windowAllowDND | RGFW_windowCenter | RGFW_windowScaleToMonitor | RGFW_windowOpenGL);
	if (RARELY(window == NULL)) {
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		goto l_exit_failure;
	}

	RGFW_window_makeCurrentContext_OpenGL(window);

	if (RARELY(0 != RGL_loadGL3((void (*(*)(const char *name))(void))RGFW_getProcAddress_OpenGL))) {
		RGFW_window_close(window);
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		goto l_exit_failure;
	}

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (RARELY(!success)) {
		glGetShaderInfoLog(vertexShader, ARRAY_LENGTH(infoLog), NULL, infoLog);
		failure_print_string("vertex shader:\n");
		failure_print_string(infoLog);
		failure_print_string("\nLine ");
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		return 1;
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (RARELY(!success)) {
		glGetShaderInfoLog(fragmentShader, ARRAY_LENGTH(infoLog), NULL, infoLog);
		failure_print_string("fragment shader:\n");
		failure_print_string(infoLog);
		failure_print_string("\nLine ");
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		return 1;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (RARELY(!success)) {
		glGetProgramInfoLog(shaderProgram, ARRAY_LENGTH(infoLog), NULL, infoLog);
		failure_print_string("shader program:\n");
		failure_print_string(infoLog);
		failure_print_string("\nLine ");
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		return 1;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint vao2;
	GLuint vbo2;
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo2);

	glBindVertexArray(vao2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof audio_vert.time + sizeof audio_vert.freq + sizeof audio_vert.phase, NULL, GL_STREAM_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(F32), (void *)0);
	glEnableVertexAttribArray(0);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof audio_vert.time, audio_vert.time);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof audio_vert.time, sizeof audio_vert.freq, audio_vert.freq);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof audio_vert.time + sizeof audio_vert.freq, sizeof audio_vert.phase, audio_vert.phase);

	ATOMIC_STORE(8, &audio_thread_data.data, 14, ATOMIC_RELEASE);

	full_memory_fence();
	if (RARELY(MA_SUCCESS != ma_device_start(&device))) {
		failure_print_dec_u64(__LINE__);
		failure_print_string("\n");
		goto l_exit_failure;
	}

	glClearColor(0.f, 0.f, 0.f, 1.0f);

#if 0
	glBindVertexArray(vao2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
#endif
	glUseProgram(shaderProgram);

	// mlock

	U8 audio_thread_data_send = 14;
	(void)audio_thread_data_send;

	GLint color_location = glGetUniformLocation(shaderProgram, "color");

	while (OFTEN(RGFW_FALSE == RGFW_window_shouldClose(window))) {
		RGFW_event event;

		while (RGFW_window_checkEvent(window, &event)) {
			int window_close = 0;
			i32 mouseX, mouseY;

			U32 event_merged_data;
			event_merged_data = event.type;
			event_merged_data <<= 16;

			if ((int)(event.type == RGFW_mouseButtonPressed) | (int)(event.type == RGFW_mouseButtonReleased)) {
				event_merged_data |= event.button.value;
			} else if (event.type == RGFW_keyPressed) {
				event_merged_data |= (U32)event.key.mod << 8;
				event_merged_data |= event.key.value;
			}

			switch (event_merged_data & ~(U32)(RGFW_modCapsLock << 8) & ~(U32)(RGFW_modNumLock << 8) & ~(U32)(RGFW_modScrollLock << 8) & ~(U32)(RGFW_modSuper << 8)) {
			case (U32)RGFW_windowClose << 16: {
				window_close = 1;
				break;
			}
			case (U32)RGFW_mouseButtonPressed << 16 | RGFW_mouseLeft: {
				RGFW_window_getMouse(window, &mouseX, &mouseY);
				(void)mouseX;
				(void)mouseY;
				break;
			}
			case (U32)RGFW_keyPressed << 16 | (U32)RGFW_modShift << 8 | RGFW_keyQ: {
				RGFW_window_setShouldClose(event.common.win, 1);
				break;
			}

			case (U32)RGFW_keyPressed << 16 | RGFW_key1: {
				U8 tmpxor = audio_thread_data_send;
				audio_thread_data_send &= ~(7 << 1);
				audio_thread_data_send |= 2;
				tmpxor ^= audio_thread_data_send;
				ATOMIC_FETCH_XOR(8, &audio_thread_data.data, tmpxor, ATOMIC_ACQ_REL);
				break;
			}
			case (U32)RGFW_keyPressed << 16 | RGFW_key2: {
				U8 tmpxor = audio_thread_data_send;
				audio_thread_data_send &= ~(7 << 1);
				audio_thread_data_send |= 4;
				tmpxor ^= audio_thread_data_send;
				ATOMIC_FETCH_XOR(8, &audio_thread_data.data, tmpxor, ATOMIC_ACQ_REL);
				break;
			}
			case (U32)RGFW_keyPressed << 16 | RGFW_key3: {
				U8 tmpxor = audio_thread_data_send;
				audio_thread_data_send &= ~(7 << 1);
				audio_thread_data_send |= 6;
				tmpxor ^= audio_thread_data_send;
				ATOMIC_FETCH_XOR(8, &audio_thread_data.data, tmpxor, ATOMIC_ACQ_REL);
				break;
			}
			case (U32)RGFW_keyPressed << 16 | RGFW_key4: {
				U8 tmpxor = audio_thread_data_send;
				audio_thread_data_send &= ~(7 << 1);
				audio_thread_data_send |= 8;
				tmpxor ^= audio_thread_data_send;
				ATOMIC_FETCH_XOR(8, &audio_thread_data.data, tmpxor, ATOMIC_ACQ_REL);
				break;
			}
			case (U32)RGFW_keyPressed << 16 | RGFW_key5: {
				U8 tmpxor = audio_thread_data_send;
				audio_thread_data_send &= ~(7 << 1);
				audio_thread_data_send |= 10;
				tmpxor ^= audio_thread_data_send;
				ATOMIC_FETCH_XOR(8, &audio_thread_data.data, tmpxor, ATOMIC_ACQ_REL);
				break;
			}
			case (U32)RGFW_keyPressed << 16 | RGFW_key6: {
				U8 tmpxor = audio_thread_data_send;
				audio_thread_data_send &= ~(7 << 1);
				audio_thread_data_send |= 12;
				tmpxor ^= audio_thread_data_send;
				ATOMIC_FETCH_XOR(8, &audio_thread_data.data, tmpxor, ATOMIC_ACQ_REL);
				break;
			}
			case (U32)RGFW_keyPressed << 16 | RGFW_key7: {
				U8 tmpxor = audio_thread_data_send;
				audio_thread_data_send &= ~(7 << 1);
				audio_thread_data_send |= 14;
				tmpxor ^= audio_thread_data_send;
				ATOMIC_FETCH_XOR(8, &audio_thread_data.data, tmpxor, ATOMIC_ACQ_REL);
				break;
			}
			case (U32)RGFW_keyPressed << 16 | RGFW_key0: {
				U8 tmpxor = audio_thread_data_send;
				audio_thread_data_send &= ~(7 << 1);
				audio_thread_data_send |= 0;
				tmpxor ^= audio_thread_data_send;
				ATOMIC_FETCH_XOR(8, &audio_thread_data.data, tmpxor, ATOMIC_ACQ_REL);
				break;
			}

			case (U32)RGFW_keyPressed << 16 | RGFW_keyW: {
				audio_thread_data_send ^= 1;
				ATOMIC_FETCH_XOR(8, &audio_thread_data.data, 1, ATOMIC_ACQ_REL);
				break;
			}
			case (U32)RGFW_windowResized << 16: {
				S32 w;
				S32 h;
				w = event.update.w;
				h = event.update.h;
				glViewport(0, 0, w, h);
				break;
			}
			case (U32)RGFW_mouseScroll << 16: {
				break;
			}
			default:
				break;
			}

			if (window_close) {
				break;
			}
		}

#if 0
		(*my_printf)("%d", (1u << 7) &ATOMIC_LOAD(8, &audio_thread_data.data, ATOMIC_ACQUIRE) ? 1 : 0);
#endif

		int upd_graphics = 1;
		if (0 != (*(int (*)(pthread_mutex_t *))my_pthread_mutex_try_lock)(&vert_mutex)) {
			upd_graphics = 0;
		}

		if (upd_graphics) {
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof audio_vert.time, audio_vert.time);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof audio_vert.time, sizeof audio_vert.freq, audio_vert.freq);
			glBufferSubData(GL_ARRAY_BUFFER, sizeof audio_vert.time + sizeof audio_vert.freq, sizeof audio_vert.phase, audio_vert.phase);
			(*(void (*)(pthread_mutex_t *))my_pthread_mutex_unlock)(&vert_mutex);
			upd_graphics = 0;
		}

		glClear(GL_COLOR_BUFFER_BIT);
		glUniform3f(color_location, main_color_r, main_color_g, main_color_b);
		glDrawArrays(GL_LINE_STRIP, 0, (1uLL << MAX_K));
		glUniform3f(color_location, main_color_b, main_color_r, main_color_g);
		glDrawArrays(GL_LINE_STRIP, (1uLL << MAX_K), (1uLL << MAX_K) / 2 + 1);
		RGFW_window_swapBuffers_OpenGL(window);
	}

	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo2);
	glDeleteVertexArrays(1, &vao2);

	RGFW_window_close(window);
	full_memory_fence();
	ma_device_uninit(&device);

	(void)dlclose(p);
	(void)dlclose(c);
	return 0;

l_exit_failure:
	if (device_init) {
		ma_device_uninit(&device);
	}

	if (p != NULL) {
		(void)dlclose(p);
	}
	if (c != NULL) {
		(void)dlclose(c);
	}
	return 1;
}

static void *priv_wrapped_malloc(size_t nbytes)
{
	nbytes += ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES - 1;
	nbytes /= ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES;
	nbytes *= ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES;

	if (RARELY(nbytes == 0) || RARELY(nbytes > ARENA_FOR_DEPENDENCIES_MAX_NBYTES_SINGLE)) {
		return NULL;
	}

	void *ptr = arena_for_dependencies;
	UPTR total = 0;
	UPTR len;

	while (1 == 1) {
		while (1 == 1) {
			len = ATOMIC_LOAD(sizeof(UPTR ATOMIC) * CHAR_BIT, (UPTR ATOMIC *)ptr, ATOMIC_ACQUIRE);
			if (LESS_LIKELY(len == 0)) {
				break;
			}
			total += len + ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES;
			ptr = (char *)ptr + len + ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES;
		}

		if (RARELY(total + nbytes + ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES * 2 > ARENA_FOR_DEPENDENCIES_MAX_NBYTES_TOTAL)) {
			return NULL;
		}

		if (RARELY(0 != ATOMIC_COMPARE_EXCHANGE_WEAK(sizeof(ATOMIC UPTR) * CHAR_BIT, (ATOMIC UPTR *)ptr, &len, nbytes, ATOMIC_ACQ_REL, ATOMIC_ACQUIRE))) {
			total += len + ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES;
			ptr = (char *)ptr + len + ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES;
			ATOMIC_CAS_LOOP_PAUSE();
		} else {
			break;
		}
	}

	return (char *)ptr + ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES;
}

static void *priv_wrapped_realloc(void *oldptr, size_t nbytes)
{
	if (oldptr == NULL) {
		return priv_wrapped_malloc(nbytes);
	}

	if (RARELY(nbytes == 0)) {
		return NULL;
	}

	void *prev_len_ptr = (char *)get_raw_data_pointer((UPTR)oldptr) - ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES;
	UPTR prev_len = ATOMIC_LOAD(sizeof(ATOMIC UPTR) * CHAR_BIT, (ATOMIC UPTR *)prev_len_ptr, ATOMIC_RELAXED);
	if (nbytes <= prev_len) {
		return oldptr;
	}

	void *res = priv_wrapped_malloc(nbytes);
	if (RARELY(res == NULL)) {
		return res;
	}

	ASSUME_ALIGNED(&res, ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES);
	ASSUME_ALIGNED(&oldptr, ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES);
	ALWAYS(prev_len % ARENA_FOR_DEPENDENCIES_GRANULARITY_NBYTES == 0);
	naive_memcpy(res, oldptr, prev_len);
	return res;
}

static void priv_wrapped_free(void *ptr)
{
	/* no op */
	(void)ptr;
}

#ifndef PRIV_ATOMIC_REQUIRED_SIZE_PREVENT_ERROR
#define PRIV_ATOMIC_REQUIRED_SIZE_PREVENT_ERROR 8
#endif
STATIC_ASSERT(ATOMIC_ALWAYS_LOCK_FREE(PRIV_ATOMIC_REQUIRED_SIZE_PREVENT_ERROR));

#include "fft.c"

#if defined(DO_NOT_BLACKLIST)
#if 1
#endif "DO_NOT_BLACKLIST is defined"
#endif

/*
 * Copyright 2026 Oleh Kiprik
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
