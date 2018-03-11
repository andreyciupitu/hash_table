#ifndef UTIL_H
#define UTILS_H 1

#include <stdio.h>
#include <errno.h>

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
				__FILE__, __LINE__);			\
			perror(call_description);			\
			exit(errno);					\
		}							\
	} while (0)

#define CUSTOM_DIE(assertion, errmsg, err)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): %s\n",		\
				__FILE__, __LINE__, errmsg);		\
			exit(err);					\
		}							\
	} while (0)

typedef enum {
	INVALID_PARAMETERS = -1,
	INVALID_COMMAND = -2,
	INVALID_ARGUMENT = -3
} hash_err;

#endif
