#ifndef SAI_UTIL_H
#define SAI_UTIL_H

void sai_open_window(void);

void sai_close_window(void);

void sai_load_opengl(void);

int sai_should_window_stay_open(void);

void sai_update_window(void);

void sai_log(const char* str);

void sai_fatal(const char* str);

const char* sai_read_file(const char* path);

#endif