#include "types.h"

typedef struct __PSFTAG
{
 char *key;
 char *value;
 struct __PSFTAG *next;
} PSFTAG;

typedef struct {
        u32 length;
        u32 stop;
        u32 fade;
        char *title,*artist,*game,*year,*genre,*psfby,*comment,*copyright;
        PSFTAG *tags;
} PSFINFO;

// These functions are actually defined in misc.c
int sexy_seek(u32 t);
void sexy_stop(void);
void sexy_execute(void);
void sexy_jumpout(void);

PSFINFO *sexy_load(char *path);
PSFINFO *sexy_getpsfinfo(char *path);
void sexy_freepsfinfo(PSFINFO *info);

void sexyd_update(unsigned char*,long);
