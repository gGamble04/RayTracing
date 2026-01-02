#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<SDL2/SDL.h>

// Constants
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 900
#define HEIGHT 600
#define RAY_SCALE 1000

#define WHITE 0xFFFFFFFF
#define BLACK 0x00000000
#define GRAY 0x808080FF
#define RED 0xFF0000FF
#define ORANGE 0xFF8000FF
#define YELLOW 0xFFFF00FF
#define GREEN 0x00FF00FF
#define BLUE 0x0000FFFF
#define INDIGO 0x4B0082FF
#define VIOLET 0x8B00FFFF
#define LIGHT 0xF0DC50FF

/**
 * 2D Vector or Point
 */
typedef struct Vect2D {
    float x; // x coordinate
    float y; // y coordinate
} Vect2D;

/**
 * Circle defined by center point and radius
 */
typedef struct Circle {
    Vect2D center; // Center of circle {x, y} 
    int radius; // Radius of the circle
} Circle;

typedef struct Ray {
    Vect2D origin; // Origin point {x, y}
    Vect2D direction; // Normalized direction vector {x, y} 
} Ray;

/**
 * @brief Adds two Vect2D together
 * @param v First Vect2D
 * @param u Second Vect2D
 * @return Vect2D Resulting Vect2D
 */
static inline Vect2D vAdd(Vect2D v, Vect2D u)
{
    return (Vect2D){v.x + u.x, v.y + u.y};
}

/**
 * @brief Subtracts two Vect2D
 * @param v First Vect2D
 * @param u Second Vect2D
 * @return Vect2D Resulting Vect2D
 */
static inline Vect2D vSubtract(Vect2D v, Vect2D u)
{
    return (Vect2D){v.x - u.x, v.y - u.y};
}

/**
 * @brief Performs dot product between two Vect2D
 * @param v First Vect2D
 * @param u Second Vect2D
 * @return float Dot product result
 */
static inline float vDot(Vect2D v, Vect2D u)
{
    return v.x * u.x + v.y * u.y;
}

/**
 * @brief Multiplies a Vect2D by a scalar
 * @param scalar Scalar value
 * @param v Vect2D to multiply
 * @return Vect2D Resulting Vect2D
 */
static inline Vect2D vScalarMult(float scalar, Vect2D v)
{
    return (Vect2D){scalar * v.x, scalar * v.y};
}

/**
 * @brief Sets the SDL_Renderer draw color from a 4 byte RGBA color
 * @param renderer Pointer to SDL_Renderer
 * @param color 4 byte RGBA color (0xRRGGBBAA)
 * @return void
 */
void SetRenderDrawColor(SDL_Renderer *renderer, Uint32 color);

/**
 * @brief Draws a filled circle on the SDL_Renderer
 * @param renderer Pointer to SDL_Renderer
 * @param circle Circle to draw
 * @param color 4 byte RGBA color (0xRRGGBBAA)
 * @return void
 */
void DrawCircle(SDL_Renderer *renderer, Circle circle, Uint32 color);


/**
 * @brief Generates and draws rays from a circle on the SDL_Renderer
 * @param renderer Pointer to SDL_Renderer
 * @param circle Circle from which rays originate
 * @param num_rays Number of rays to generate
 * @param obstacle Circle obstacle to check for intersections
 * @param color 4 byte RGBA color (0xRRGGBBAA)
 * @return void
 */
void GenerateRays(SDL_Renderer *renderer, Circle circle, int num_rays, Circle obstacle, Uint32 color);

/**
 * @brief Checks for intersection between a ray and a circle obstacle
 * @param ray Ray to check
 * @param obstacle Circle obstacle
 * @param intersection Pointer to Vect2D to store intersection point if found
 * @return true if intersection occurs, false otherwise
 */
bool Intersection(Ray ray, Circle obstacle, Vect2D *intersection);


