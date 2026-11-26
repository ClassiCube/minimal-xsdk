/* <dirent.h> includes <sys/dirent.h>, which is this file.  On a
   system which supports <dirent.h>, this file is overridden by
   dirent.h in the libc/sys/.../sys directory.  On a system which does
   not support <dirent.h>, we will get this file which uses #error to force
   an error.  */

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __XSDK__
/* The Xbox 360 SDK lists directories through the retail kernel. */
#include <sys/types.h>

#define DT_UNKNOWN	0
#define DT_FIFO		1
#define DT_CHR		2
#define DT_DIR		4
#define DT_BLK		6
#define DT_REG		8
#define DT_LNK		10
#define DT_SOCK		12

struct dirent {
	ino_t d_ino;
	unsigned char d_type;
	char d_name[256];
};

typedef struct __xsdk_dir DIR;

DIR *opendir(const char *);
struct dirent *readdir(DIR *);
void rewinddir(DIR *);
int closedir(DIR *);
#else
#error "<dirent.h> not supported"
#endif
#ifdef __cplusplus
}
#endif
