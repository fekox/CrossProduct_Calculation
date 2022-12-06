#include <iostream>
#include <cmath>
#include <ctime>
#include "Line.h"
#include "raylib.h"

using namespace std;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Algebra_TP2");

    srand(time(NULL));

    //Auxiliares para guardar el valor del tercer vector3.
    float i;
    float j;
    float k;

    //Auxiliares para guardar los resultdos del calculo de las areas.
    float area = 0;
    float areaLine1AndLine2 = 0;

    //Auxiliar para guardar el area total.
    float totalArea = 0;

    float base; // Base del vector3 (1) y vector3 (2) hasta el vector3 (3).
    float auxHeight = 0; // Auxiliar para calcular la altura.
    float height = 0; // Altura.


    float baseLine1AndLine2; // Base desde el vector3 (1) hasta el vector3 (2).
    float auxHeightLine1AndLine2 = 0; // Auxiliar para calcular la altura del vector3 (1) y del vector3 (2).
    float heightLine1AndLine2 = 0; // Altura del vector3 (1) y el vector3 (2).

    //Se crean las 3 lineas.
    Line line;
    Line line2;
    Line line3;

    //Se hace un ramdon para sacar los valores del vetor3 (1).
    line.x = (rand() % 100 + 1.1) / 10;
    line.y = (rand() % 100 + 1.1) / 10;
    line.z = (rand() % 100 + 1.1) / 10;

    //Se declaran los valores del vetor3 (2).
    line2.x = line.y;
    line2.y = line.x * -1; //Para que este a 90 grados del primer vector3.
    line2.z = line.z;

    //Se declaran los valores del vector3 (3).
    line3.x = 0;
    line3.y = 0;
    line3.z = 0;
    //----------------------------------------------------------------------------------

    while (!WindowShouldClose())
    {
        //----------------------------------------------------------------------------------
        
        //Calculo el largo de la linea desde el vector3{0,0,0} hasta el vector3 (1).
        //Teorema de Pitagoras. 
        line.length = sqrt(pow(0 - 0 - 0, 2) + pow(line.x - line.y - line.z, 2));


        //Calculo el largo de la linea desde el vector3{0,0,0} hasta el vector3 (2).
        //Teorema de Pitagoras. 
        line2.length = sqrt(pow(0 - 0 - 0, 2) + pow(line2.x - line2.y - line2.z, 2));
        //----------------------------------------------------------------------------------

        //Se crean los vectores para dibujar el grafico del producto cruz.
        Vector3 vector3LineStart;
        Vector3 vector3LineEnd;

        Vector3 vector3Line2Start;
        Vector3 vector3Line2End;

        Vector3 vector3Line3Start;
        Vector3 vectore3Line3End;

        //Punto de inicio de la primera linea.
        vector3LineStart.x = 300;
        vector3LineStart.y = 900;
        vector3LineStart.z = 0;

        //Punto final de la primera linea.
        vector3LineEnd.x = line.x *2 + 500;
        vector3LineEnd.y = line.y*2 + 900;
        vector3LineEnd.z = 0;
        //----------------------------------------------------------------------------------

        //Punto de inicio de la segunda linea.
        vector3Line2Start.x = 300;
        vector3Line2Start.y = 900;
        vector3Line2Start.z = 0;

        //Punto final de la segunda linea.
        vector3Line2End.x = line2.x*2 + 300;
        vector3Line2End.y = line2.y*2 + 700;
        vector3Line2End.z = 0;
        //----------------------------------------------------------------------------------

        //Punto de inicio de la tercera linea.
        vector3Line3Start.x = 300;
        vector3Line3Start.y = 900;
        vector3Line3Start.z = 0;

        //Punto final de la tercera linea.
        vectore3Line3End.x = line3.x*2 + 400;
        vectore3Line3End.y = line3.y*2 + 800;
        vectore3Line3End.z = 0;
        //----------------------------------------------------------------------------------

        // Update

        //Calculo para sacar el producto cruz
        i = line.y * line2.y - line.z * line2.y;
        j = line.z * line2.x - line.x * line2.z;
        k = line.x * line2.y - line.y * line2.x;

        //El resultado se iguala al nuevo vector3
        line3.x = i;
        line3.y = j;
        line3.z = k;
        //----------------------------------------------------------------------------------

        //Se obtiene la ditancia segun la linea mas corta.
        if (line.x < line2.x)
        {
            line3.distance = line.x;
        }

        if (line2.x < line.x)
        {
            line3.distance = line2.x;
        }
        
        //----------------------------------------------------------------------------------

        //Base
        
        //Para obtener la base de las caras de la piramide que son iguales.
        //Si la primera linea es la mas corta, se obtiene la base trasando el corte desde el vector3 (1) hasta el vector3 (3). 
        if (line.length < line2.length)
        {
            base = sqrt(pow(line.x - line.y - line.z, 2) + pow(line3.x - line.y - line3.z, 2));
        }

        //Si la segunda linea es la mas corta, se obtiene la base trasando el corte desde el vector3 (2) hasta el vector3 (3). 
        if (line2.length < line.length)
        {
            base = sqrt(pow(line2.x - line2.y - line2.z, 2) + pow(line3.x - line2.y - line3.z, 2));
        }

        //Si la primera linea y la segunda son igules, se obtiene la base trasando el corte desde el vector3 (1) hasta el vector3 (3).
        else
        {
            base = sqrt(pow(line.x - line.y - line.z, 2) + pow(line3.x - line.y - line3.z, 2));
        }


        //Para obtener la base de la cara restante.
        //Se calcula la dstanicia entre el vector3 (1) y el vector3 (2).
        baseLine1AndLine2 = sqrt(pow(line.x - line.y - line.z, 2) + pow(line2.x - line2.y - line.z, 2));

        //----------------------------------------------------------------------------------
        
        //Altura

        //Para calcular la altura de las dos caras que son iguales.
        //Se calcula el punto en el medio de la base dividiendola por dos.
        auxHeight = (auxHeight + base) / 2;

        //Luego se saca la distancia desde ese punto hasta el punto 0 para obtener la altura.
        //Como ambas caras miden lo mismo la altura es la misma.
        height = sqrt(pow(0, 2) + pow(auxHeight, 2));


        //Para calcular la altura de la cara restante.
        //Se calcula el punto en el medio de la base dividiendola por dos.
        auxHeightLine1AndLine2 = (auxHeightLine1AndLine2 + baseLine1AndLine2) / 2;

        //Luego se saca la distancia desde ese punto hasta el punto 0 para obtener la altura.S
        heightLine1AndLine2 = sqrt(pow(0, 2) + pow(auxHeightLine1AndLine2, 2));

        //----------------------------------------------------------------------------------
        
        //Area

        //Para calcular el area se utiliza la formula Base * Altura / 2.
        //Se calcula la base de las dos caras que son iguales.
        area = (base * height) / 2;

        //Se calcula la base de la cara restante.
        areaLine1AndLine2 = (baseLine1AndLine2 * heightLine1AndLine2) / 2;

        //Se suman todas las areas y se optiene el area total de la piramide.
        totalArea = area + area + areaLine1AndLine2;

        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Producto Cruz", GetScreenWidth() /2.4, GetScreenHeight() /8, 60, GREEN);

        //Dibuja los parametros del primer vector3.

        DrawText(TextFormat("X: %02f", line.x), GetScreenWidth() / 10, GetScreenHeight() / 4, 30, RED);
        DrawText(TextFormat("Y: %02f", line.y), GetScreenWidth() / 10, GetScreenHeight() / 3, 30, RED);
        DrawText(TextFormat("Z: %02f", line.z), GetScreenWidth() / 10, GetScreenHeight() / 2.4, 30, RED);

        //Dibuja los parametros del segundo vector3.

        DrawText(TextFormat("X: %02f", line2.x), GetScreenWidth() / 5, GetScreenHeight() / 4, 30, YELLOW);
        DrawText(TextFormat("Y: %02f", line2.y), GetScreenWidth() / 5, GetScreenHeight() / 3, 30, YELLOW);
        DrawText(TextFormat("Z: %02f", line2.z), GetScreenWidth() / 5, GetScreenHeight() / 2.4, 30, YELLOW);

        DrawText(" = ", GetScreenWidth() / 3.4, GetScreenHeight() / 3, 60, WHITE);

        //Dibuja los parametros del tercer vector3.

        DrawText(TextFormat("X: %02f", line3.x), GetScreenWidth() / 3, GetScreenHeight() / 4, 30, SKYBLUE);
        DrawText(TextFormat("Y: %02f", line3.y), GetScreenWidth() / 3, GetScreenHeight() / 3, 30, SKYBLUE);
        DrawText(TextFormat("Z: %02f", line3.z), GetScreenWidth() / 3, GetScreenHeight() / 2.4, 30, SKYBLUE);

        //Dibuja la distancia.

        DrawText(TextFormat("Distance: %01f", line3.distance), GetScreenWidth() / 5, GetScreenHeight() / 2, 30, WHITE);

        //Dibuja el area total.

        DrawText(TextFormat("Total Area: %02f", totalArea), GetScreenWidth() / 1.5, GetScreenHeight() / 3, 50, WHITE);

        //Dibuja las lineas del prducto cruz.

        DrawLine3D(vector3LineStart, vector3LineEnd, RED);
        DrawLine3D(vector3Line2Start, vector3Line2End, YELLOW);
        DrawLine3D(vector3Line3Start, vectore3Line3End, SKYBLUE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();      
    //--------------------------------------------------------------------------------------

    return 0;
}



