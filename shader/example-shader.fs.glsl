#version 330 core

/**
 * Definiere eine Ausgabevariable vom Typ
 * vec4, diese bestimmt die Farbe des
 * Fragments. Farben werden im RGBA Format
 * angegeben. Zudem haben die einzelnen
 * Kanäle einen Wertebereich von [0;1].
 */
layout(location = 0) out vec4 color;

/**
 * Ein Uniform Buffer mit dem Namen u_color
 * und vom Typ vec4.
 */
uniform vec4 u_color;

void main()
{
    color = vec4(u_color.x, u_color.y,
                 u_color.z, u_color.w);
}

/**
 * KOMMENTAR ZU main():
 * Dieser Kommentar wurde unter die
 * eingentliche Funktion geschrieben um Platz
 * im Bericht zu sparen.
 *
 * Die Farbe des Fragments ist die exakt die
 * Farbe, die durch u_color uebergeben wurde,
 * keine weitere berechnung ist noetig.
 */