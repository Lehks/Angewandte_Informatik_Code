#ifndef SAI_UTIL_H
#define SAI_UTIL_H

/**
 * Oeffnet ein Fenster mit GLFW und bereitet es vor von OpenGL genutzt zu werden.
 * 
 * Zum oeffnen von Fenstern wird GLFW (https://www.glfw.org) verwendet.
 */
void sai_open_window(void);

/**
 * Oeffnet ein Fenster mit GLFW und bereitet es vor von OpenGL genutzt zu werden.
 */
void sai_close_window(void);

/**
 * Lade die OpenGL Funktionen.
 * 
 * Um die Funktionen zu laden wird GLAD (https://github.com/Dav1dde/glad) verwendet. 
 * 
 * Warum das Laden von Funktionen ist notwending ist, ist auf dieser Seite erklärt:
 * https://www.khronos.org/opengl/wiki/OpenGL_Loading_Library
 */
void sai_load_opengl(void);

/**
 * Gibt solange true zurück bis der Nutzer das Fenster schließt.
 */
int sai_should_window_stay_open(void);

/**
 * Updated das Fenster indem Buffer ausgetauscht und Events eingelesen werden.
 * 
 * https://www.glfw.org/docs/latest/window_guide.html#buffer_swap
 * https://www.glfw.org/docs/latest/input_guide.html#events
 */
void sai_update_window(void);

/**
 * Schreibt einen string auf stdout.
 */
void sai_log(const char* str);

/**
 * Schreibt einen string auf stderr.
 */
void sai_fatal(const char* str);

/**
 * List eine Datei mit dem spezifizierten Pfad in einen string. Dieser string wird zurueck gegeben.
 * 
 * Der zurueckgegebene String muss mit der Funktion free() wieder freigegeben werden.
 */
const char* sai_read_file(const char* path);

#endif