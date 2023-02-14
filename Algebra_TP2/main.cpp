#include <iostream>
#include <cmath>
#include "raylib.h"

using namespace std;

struct Vector
{
	Vector3 start;
	Vector3 end;
};

const int windowWidth = 800;
const int windowHeight = 450;

Vector x; //Dibuja un vector default en la punta de la piramide.

Vector vA;
Vector vB;
Vector vC;

Vector3 p1;
Vector3 p2;
Vector3 p3;

Camera3D camera;

void Init();
void Loop();
void Update();
void Draw();

void InitVectors();

void CreateFirstVector();
void CreateSecondVector();
void CreateThirdVector();

float CalculateTriangleArea(float a, float b, float c);
float GetDistance(Vector3 point1, Vector3 point2);

void CalculateArea();
void SliceVectors();


int main() 
{
	InitWindow(windowWidth, windowHeight, "Algebra EJ2");
	Init();
	
	while (!WindowShouldClose()) 
	{
		Loop();
	}
	
	CloseWindow();

	return 0;
}

void Init() 
{
	//Init camara.
	SetTargetFPS(30);

	camera.position = Vector3{ 0.0f, 0.0f, 20.0f };
	camera.target = Vector3{ 0.0f, 5.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	SetCameraMode(camera, CAMERA_ORBITAL);

	InitVectors();
}

void Loop() 
{
	Update();
	Draw();
}

void Update() 
{
	UpdateCamera(&camera);
}

void Draw() 
{
	BeginDrawing();
	ClearBackground(BLACK);

	BeginMode3D(camera); // 3D

	//Dibuja el vector default en la punta de la piramide.
	DrawLine3D(x.start, x.end, RED);

	//Los tres vectores generados random.
	DrawLine3D(vA.start, vA.end, BEIGE);
	DrawLine3D(vB.start, vB.end, PURPLE);
	DrawLine3D(vC.start, vC.end, GREEN);

	DrawSphere(p1, 0.2, BLUE);
	DrawSphere(p2, 0.2, BLUE);
	DrawSphere(p3, 0.2, BLUE);

	EndMode3D();
	EndDrawing();
}

void InitVectors() //Se ocupa de inicializar los vectores.
{
	x.start.x = -10;
	x.start.y = 0;
	x.start.z = 0;

	x.end.x = 10;
	x.end.y = 0;
	x.end.z = 0;

	cout << "\n";

	CreateFirstVector();
	cout << "Vector A: (X: " << vA.end.x << ", Y: " << vA.end.y << ", Z: " << vA.end.z << ")\n";

	CreateSecondVector();
	cout << "Vector B: (X: " << vB.end.x << ", Y: " << vB.end.y << ", Z: " << vB.end.z << ")\n";

	CreateThirdVector();
	cout << "Vector C: (X: " << vC.end.x << ", Y: " << vC.end.y << ", Z: " << vC.end.z << ")\n";
	cout << "\n";

	SliceVectors();

	cout << "Punto 1: (X: " << p1.x << ", Y: " << p1.y << ", Z: " << p1.z << ")\n";
	cout << "Punto 2: (X: " << p2.x << ", Y: " << p2.y << ", Z: " << p2.z << ")\n";
	cout << "Punto 3: (X: " << p3.x << ", Y: " << p3.y << ", Z: " << p3.z << ")\n";

	cout << "\n";

	CalculateArea();
}

void CreateFirstVector() //Crea el primer vector de manera aleatoria.
{
	vA.start.x = 0;
	vA.start.y = 0;
	vA.start.z = 0;

	vA.end.x = GetRandomValue(1, 5);
	vA.end.y = GetRandomValue(1, 5);
	vA.end.z = GetRandomValue(-5, -1);
}

void CreateSecondVector() //Crea el segundo vector a 90 grados del primero.
{
	vB.start.x = 0;
	vB.start.y = 0;
	vB.start.z = 0;

	vB.end.x = -vA.end.y;
	vB.end.y = vA.end.x;
	vB.end.z = vA.end.z;
}

void CreateThirdVector() //Crea el tercer vector haciendo producto cruz de los anteriores dos vectores.
{
	//Se usa el producto cruz para crear el tercer vector. 
	vC.end.x = ((vA.end.y * vB.end.z) - (vA.end.z * vB.end.y));
	vC.end.y = ((vA.end.z * vB.end.x) - (vA.end.x * vB.end.z));  
	vC.end.z = ((vA.end.x * vB.end.y) - (vA.end.y * vB.end.x));  
}

float CalculateTriangleArea(float a, float b, float c) //Calcula el area de un triangulo pasandole la distancia de cada lado.
{
	//Resuelto usando la formula de Heron.

	float s = ((a + b + c) / 2);
	
	return sqrt(s * ((s - a) * (s - b) * (s - c)));
}

float GetDistance(Vector3 point1, Vector3 point2) //Devuelve la distancia entre 2 puntos en 3D.
{
	//Teorema de Pitagoras. 
	
	return pow((pow((point2.x - point1.x), 2) + pow((point2.y - point1.y), 2) + pow((point2.z - point1.z), 2)), 0.5);
}

void CalculateArea() //Se ocupa de calcular el perimetro y area de las caras.
{
	Vector3 p0 = { 0, 0, 0 };

	//Cara del primer triangulo.

	float d1 = GetDistance(p1, p3);
	float d2 = GetDistance(p3, p0);
	float d3 = GetDistance(p0, p1);

	cout << "Lados del triangulo A: (" << d1 << ", " << d2 << ", " << d3 << ")\n";

	float area1 = CalculateTriangleArea(d1, d2, d3);

	cout << "El area es: " << area1 << "\n";
	cout << "\n";

	//Cara del segundo triangulo.

	d1 = GetDistance(p1, p2);
	d2 = GetDistance(p2, p0);
	d3 = GetDistance(p0, p1);

	cout << "Lados del triangulo B: (" << d1 << ", " << d2 << ", " << d3 << ")\n";

	float area2 = CalculateTriangleArea(d1, d2, d3);

	cout << "El area es: " << area2 << "\n";
	cout << "\n";

	//Cara de el tercer triangulo.

	d1 = GetDistance(p2, p3);
	d2 = GetDistance(p3, p0);
	d3 = GetDistance(p0, p2);

	cout << "Lados del triangulo C: (" << d1 << ", " << d2 << ", " << d3 << ")\n";

	float area3 = CalculateTriangleArea(d1, d2, d3);

	cout << "El area es: " << area3 << "\n";
	cout << "\n";

	cout << "El area total es: " << (area1 + area2 + area3) << "!\n";
}

void SliceVectors() //Agarra al vector mas bajo y corta a los demas a esa altura.
{

	if (vA.end.y < vB.end.y) 
	{
		p1 = vA.end;

		p2.y = p1.y;
		p2.x = (vB.end.x / vB.end.y) * p2.y;
		p2.z = (vB.end.z / vB.end.y) * p2.y;

		p3.y = p1.y;
		p3.x = (vC.end.x / vC.end.y) * p2.y;
		p3.z = (vC.end.z / vC.end.y) * p2.y;
	}
	
	else
	{
		p1 = vB.end;

		p2.y = p1.y;
		p2.x = (vA.end.x / vA.end.y) * p2.y;
		p2.z = (vA.end.z / vA.end.y) * p2.y;

		p3.y = p1.y;
		p3.x = (vC.end.x / vC.end.y) * p2.y;
		p3.z = (vC.end.z / vC.end.y) * p2.y;
	}
}