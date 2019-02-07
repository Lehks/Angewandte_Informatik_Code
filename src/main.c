
#include <glad/glad.h>
// glfw must be included after glad
#include "util.h"

#include <GLFW/glfw3.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Die Vertex Daten, mit denen der Vertex
 * Buffer befuellt werden soll.
 */
float vertex_positions[4][2] = {{-0.75, -0.75},
                                {0.75, 0.75},
                                {-0.75, 0.75},
                                {0.75, -0.75}};

/**
 * Die Indices, mit denen der Index Buffer
 * befuellt werden soll.
 */
unsigned int index_buffer[6] = {0, 1, 2,
                                0, 3, 1};

/**
 * Der Farbwert, mit dem der Uniform Buffer
 * befuellt werden soll.
 */
float fragment_color[4] = {1.0f, 0.0f, 0.0f,
                           1.0f};

/**
 * Die Groesse einer einzigen Position in den
 * Vertex Daten (in diesem Fall 2, da 2
 * Koordinaten gespeichert werden).
 */
int SAI_VERTEX_BUFFER_ELEMENT_SIZE =
    sizeof(vertex_positions[0]) /
    sizeof(vertex_positions[0][0]);

/**
 * Die Groesse der gesamten Vertex Daten.
 */
int SAI_VERTEX_BUFFER_SIZE =
    sizeof(vertex_positions) / sizeof(float);

/**
 * Die Groesse der gesamten Index Daten.
 */
int SAI_INDEX_BUFFER_SIZE =
    sizeof(index_buffer) /
    sizeof(index_buffer[0]);

/**
 * Kreiert den Vertex Buffer und befuellt ihn
 * mit den Daten aus dem Array
 * vertex_positions.
 *
 * Zeilen ?-?: Generiere ein Vertex Array
 * Object und binde es. glGenVertexArrays()
 * generiert einen Buffer (die Anzahl wird
 * durch den ersten Parameter bestimmt) und
 * gibt die ID des Buffers durch vao_id
 * zurueck. glBindVertexArray() binded den
 * Buffer.
 *
 * Zeilen ?-?: Generiere einen Vertex Buffer
 * und binde ihn. glGenBuffers() generiert
 * einen Buffer (die Anzahl wird durch den
 * ersten Parameter bestimmt) und gibt die ID
 * des Buffers durch vbo_id zurueck.
 * glBindBuffer() binded den Buffer.
 * glGenBuffers() generiert einen generischen
 * Buffer und nicht zwingend einen Vertex
 * Buffer. Erst durch das binden des Buffers
 * als Vertex Buffer mit glBindBuffer() wird
 * bestimmt dass der Buffer als Vertex Buffer
 * verwendet werden soll (der erste Parameter
 * von glBindBuffer() bestimmt den
 * Verwendungszweck).
 *
 * Zeile ?-?: Setze die Daten des Vertex
 * Buffers.
 *  1. Parameter: Die Art des Buffers
 *  2. Parameter: Die Groesse der Daten (in
 *                Bytes)
 *  3. Parameter: Die Daten selbst als Array
 *  4. Parameter: Die Art der Daten.
 *                GL_STATIC_DRAW sagt aus, dass
 *                die Daten sich nicht oft
 *                veraendern, OpenGL kann
 *                dementsprechend optimieren.
 *
 * Zeilen ? bis ?: Setze das Layout der Daten.
 * Jede einzelne Art von Daten wird ein
 * Vertex-Attribut genannt. In diesem Fall gibt
 * es nur ein einziges Attribut, die
 * Positionsdaten. Gaebe es noch mehr
 * Attribute, muessten die Zeilen kopiert und
 * an die jeweiligen Attribute angepasst
 * werden. Attribute sind streng genommen nur
 * Arrays von Daten eines bestimmten Types. Die
 * moeglichen Typen werden von OpenGL bereit
 * gestellt.
 *
 * glEnableVertexAttribArray(0): Teilt OpenGL
 * mit, dass ein Attribut am Index 0 existiert.
 * glVertexAttribPointer(): Setzt das Layout
 * eines Attributes.
 *  1. Parameter: Der Index des Attributes.
 *  2. Parameter: Die Anzahl der Elemente im
 *                Attribut.
 *  3. Parameter: Der Typ der Elemente im
 *                Attribut. GL_FLOAT is das
 *                Gegenstueck zum C Datentyp
 *                float.
 *  4. Parameter: Nicht relevant.
 *  5. Parameter: Die Groesse, die die Daten
 *                des Attributes im Speicher
 *                einnehmen (in Bytes).
 *  6. Parameter: Nicht relevant.
 *
 * Zeilen ? und ?: Un-binde das Vertex Array
 * und den Vertex Buffer (0 ist ein invalider
 * Buffer).
 * Das un-binden waere in diesem Fall nicht
 * noetig, da die jeweiligen Buffer die
 * einzigen ihrer Art im Programm sind.
 * Muessten allerdings noch weitere Buffer
 * kreiert werden, ist es sauberer die Buffer
 * zu un-binden sodass auf keinen Fall die
 * falschen Buffer modifiziert werden.
 *
 * Diese Funktion gibt die ID des Vertex Arrays
 * zurueck, sodass es zu einer spaeteren zeit
 * wieder gebinded werden kann.
 */
GLuint sai_create_vertex_buffer(void)
{
    GLuint vao_id;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);

    GLuint vbo_id;
    glGenBuffers(1, &vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(float) * SAI_VERTEX_BUFFER_SIZE,
        vertex_positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, SAI_VERTEX_BUFFER_ELEMENT_SIZE,
        GL_FLOAT, GL_FALSE,
        sizeof(float) *
            SAI_VERTEX_BUFFER_ELEMENT_SIZE,
        0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao_id;
}

/**
 * Kreiert den Index Buffer und befuellt ihn
 * mit den Daten aus dem Array index_buffer.

 * Zeilen ?-?: Generiere einen Index Buffer
 * und binde ihn. glGenBuffers() generiert
 einen
 * Buffer (die Anzahl wird durch den ersten
 * Parameter bestimmt) und gibt die ID des
 * Buffers durch buffer_id zurueck.
 * glBindBuffer() binded den Buffer.
 * glGenBuffers() generiert einen generischen
 * Buffer und nicht zwingend einen Index
 Buffer.
 * Erst durch das binden des Buffers als Index
 * Buffer mit glBindBuffer() wird bestimmt
 * dass der Index als Vertex Buffer verwendet
 * werden soll (der erste Parameter von
 * glBindBuffer() bestimmt den
 * Verwendungszweck).
 *
 * Zeile ?-?: Setze die Daten des Index
 * Buffers.
 *  1. Parameter: Die Art des Buffers
 *  2. Parameter: Die Groesse der Daten (in
 *                Bytes)
 *  3. Parameter: Die Daten selbst als Array
 *  4. Parameter: Die Art der Daten.
 *                GL_STATIC_DRAW sagt aus, dass
 *                die Daten sich nicht oft
 *                veraendern, OpenGL kann
 *                dementsprechend optimieren.
 *
 * Zeile ?: Un-binde den Index Buffer.
 *
 * Das un-binden waere in diesem Fall nicht
 * noetig, da der Buffer der einzige seiner Art
 * im Programm ist. Muessten allerdings noch
 * weitere Index Buffer kreiert werden, ist es
 * sauberer die Buffer zu un-binden sodass auf
 * keinen Fall die falschen Buffer modifiziert
 * werden.
 *
 * Diese Funktion gibt die ID des Index Buffers
 * zurueck, sodass es zu einer spaeteren zeit
 * wieder gebinded werden kann.
 */
GLuint sai_create_index_buffer(void)
{
    GLuint buffer_id;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
                 buffer_id);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 SAI_INDEX_BUFFER_SIZE *
                     sizeof(unsigned int),
                 index_buffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return buffer_id;
}

/**
 * Die Funktion nimmt einen Shader Typ (z.B.
 * Vertex oder Fragment Shader) und Shader Code
 * entgegen. Daraus kompiliert sie ein OpenGL
 * Shader Objekt. Dieses Objekt wird dann
 * zurueck gegeben.
 *
 * Zeile ?: Kreiert einen Shader Objekt vom
 * jeweiligen Typen. Die Funktion gibt die ID
 * des kreierten Shaders zurueck.
 *
 * Zeile ? bis ?: Setzt den Quellcode des
 * Shaders.
 *  1. Parameter: Die ID des Shaders von dem
 *                der Quellcode gesetzt werden
 *                soll.
 *  2. Parameter: Nicht relevant.
 *  3. Parameter: Der Quellcode als
 *                Zeichenkette.
 *  4. Parameter: Nicht relevant.
 *
 * Zeile ?: Kompiliere den Shader.
 */
GLuint sai_compile_shader(
    GLenum shader_type,
    const char* shader_code)
{
    GLuint shader =
        glCreateShader(shader_type);

    glShaderSource(shader, 1, &shader_code,
                   NULL);

    glCompileShader(shader);

    return shader;
}

/**
 * Die Funktion laed die, fuer dieses Programm
 * notwendigen Shader, und bereitet sie vor, um
 * beim zeichen genutzt zu werden.
 *
 * OpenGL verwendet an dieser Stelle den
 * Begriff "program". Ein solches program
 * stellt die Pipeline auf CPU Seite dar.
 *
 * Der Grundlegende Ablauf ist der Folgende:
 * 1. program erstellen
 * 2. Die Vertex und Fragment Shader einzeln
 *    einlesen und kompilieren.
 * 3. Die kompilierten Shader in das program
 *    linken.
 *
 * Zeile ?: Das program erstellen.
 * Zeilen ? bis ?: Den Vertex Shader von der
 * Festplatte laden und kompilieren.
 * Zeilen ? bis ?: Den Fragment Shader von der
 * Festplatte laden und kompilieren.
 *
 * Zeilen ? und ?: Die Shader dem program
 * hinzufuegen.
 * Zeile ?: Das program linken.
 * Zeilen ? und ?: Die Shader vom program
 * entfernen (sie sind durch das linken jetzt
 * ein fester Bestandteil vom program, die
 * seperaten Objekte muessen nicht weiter
 * existieren).
 * Zeile ? und ?: Die Shader loeschen.
 *
 * Die Funktion gibt die program ID zurueck,
 * sodass dieses spaeter gebinded werden kann.
 */
GLuint sai_load_shaders(void)
{
    GLuint program = glCreateProgram();

    const char* vertex_shader_code =
        sai_read_file(
            "shader/example-shader.vs.glsl");

    GLuint vs = sai_compile_shader(
        GL_VERTEX_SHADER, vertex_shader_code);

    free((void*)vertex_shader_code);

    if(vs == 0)
        return 0;

    const char* fragment_shader_code =
        sai_read_file(
            "shader/example-shader.fs.glsl");

    GLuint fs = sai_compile_shader(
        GL_FRAGMENT_SHADER,
        fragment_shader_code);

    free((void*)fragment_shader_code);

    if(fs == 0)
        return 0;

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDetachShader(program, vs);
    glDetachShader(program, fs);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

/**
 * Die Funktion setzt die Daten des Uniform
 * Buffers, dass die Farbe des Vierecks
 * bestimmt.
 *
 * Die Funktion nimmt die program ID entgegen,
 * da Uniform Buffer auf program Ebene gesetzt
 * werden (verschiedene programs koennen
 * verschiedene Uniform Buffer haben). Aus
 * diesem Grund muessen Uniforms auch nicht
 * gebinded werden, da sie im program selbst
 * gesetzt werden und nicht separat existieren.
 *
 * Zeilen ? bis ?: Erhalte eine Art Pointer zu
 * dem Uniform Buffer im program. Uniform
 * Buffer werden ueber ihren Namen
 * identifiziert. Zeile ? bis ?: Setze die
 * Daten des Uniform Buffers.
 *
 * Es gibt nur eine endliche, durch OpenGL
 * bestimmte Anzahl an Datentypen, die Uniform
 * Buffer speichern koennen. Fuer jeden dieser
 * Datentypen existiert eine Funktion
 * glUniform*(), wobei * ein Platzhalter fuer
 * das Kuerzel des Datentyps ist. Das Kuerzel
 * 4f steht fuer einen Vektor mit vier
 * Gleitkommazahl Elementen.
 */
void sai_set_color_uniform_data(GLuint program)
{
    GLint uniform_location =
        glGetUniformLocation(program,
                             "u_color");

    glUniform4f(
        uniform_location, fragment_color[0],
        fragment_color[1], fragment_color[2],
        fragment_color[3]);
}

/**
 * Initialisiert das Gesamte Programm.
 * Um das Geschehen zu verstehen sollten die
 * Kommentare zu den einzelnen Funktionen die
 * aufgerufen werden gelesen werden.
 *
 * Zeilen ? und ?: Das Fenster geoeffnet und
 * OpenGL initialisiert.
 *
 * Zeilen ? bis ?: Der Vertex Buffer wird
 * kreiert und das resultierende Vertex Array
 * gebinded.
 *
 * Zeilen ? bis ?: Der Index Buffer wird
 * kreiert und gebinded.
 *
 * Zeilen ? bis ?: Das program wird kreiert.
 *
 * Zeile ?: Die Daten des Unform Buffers, der
 * die Farbdaten speichert werden gesetzt.
 */
void initialize(void)
{
    sai_open_window();
    sai_load_opengl();

    sai_log("Creating vertex buffer...");
    GLuint vao_id = sai_create_vertex_buffer();

    glBindVertexArray(vao_id);
    sai_log("Vertex buffer has been created.");

    sai_log("Creating index buffer...");
    GLuint index_buffer =
        sai_create_index_buffer();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
                 index_buffer);
    sai_log("Index buffer has been created.");

    sai_log("Processing shaders...");
    GLuint program = sai_load_shaders();

    glUseProgram(program);
    sai_log("Shaders have been processed...");

    sai_log("Setting up uniform buffer...");
    sai_set_color_uniform_data(program);
    sai_log("Uniform buffer has been set up.");
}

/*
 * Zeichnet das Viereck.
 *
 * Zeilen ? bis ?: Zeichnet ein Bild anhand des
 * Index Buffers der derzeitig gebinded ist.
 *  1. Parameter: Die Art von Primitive die
 *                gezeichnet werden soll
 *                (Dreiecke in diesem Fall).
 *  2. Parameter: Die Anzahl der Indices, die
 *                gezeichnet werden sollen (in
 *                diesem Fall sollen alle
 *                Indizes im Buffer gezeichnet
 *                werden).
 *  3. Parameter: Nicht relevant.
 *  4. Parameter: Nicht relevant.
 *
 * Zeile ?: Update das Fenster (nicht
 * relevant); dieser Schritt hat nichts direkt
 * mit OpenGL oder dem Zeichnen zu tun.
 */
void draw(void)
{
    glDrawElements(GL_TRIANGLES,
                   SAI_INDEX_BUFFER_SIZE,
                   GL_UNSIGNED_INT, NULL);

    sai_update_window();
}

/*
 * Terminiert das Programm.
 *
 * Zeile ?: Schliesse das Fenster.
 */
void terminate(void)
{
    sai_close_window();
}

/**
 * Das Programm wird zuerst initialisiert, dann
 * wird gezeichnet bis das Fenster geschlossen
 * wird.
 *
 * Bei diesem Beispiel waere es nicht noetig
 * eine Schleife zu haben, da das gezeichnete
 * Bild zu jeder Zeit identisch ist. Wuerde
 * aber ein sich, ueber die Zeit, veraenderndes
 * Bild gezeichnet werden, dann waere eine
 * Schleife notwendig.
 */
int main(void)
{
    sai_log("Starting application...");
    initialize();

    sai_log("Now entering main loop...");

    while(sai_should_window_stay_open())
    {
        draw();
    }

    sai_log("Exited main loop.");

    terminate();

    sai_log("Program ran successfully.");
}
