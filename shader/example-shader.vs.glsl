#version 330 core

/**
 * Definiere ein Vertex-Attribut vom Typ vec4
 * (ein Vektor mit vier Elementen, je vom Typ
 * float) an dem Index 0.
 */
layout(location = 0) in vec4 vertex_position;

void main()
{
    gl_Position = vertex_position;
}

/**
 * KOMMENTAR ZU main():
 * Dieser Kommentar wurde unter die
 * eingentliche Funktion geschrieben um Platz
 * im Bericht zu sparen.
 *
 * gl_Position ist eine vorbestimmte Variable;
 * sie bestimmt die letztendliche Position des
 * Verticies.
 * Die Position des Vertex ist die exakt die
 * Position, die von der CPU uebergeben wurde,
 * keine weitere berechnung ist noetig.
 */