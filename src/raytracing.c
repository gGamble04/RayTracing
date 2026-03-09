#include "raytracing.h"

void SetRenderDrawColor(SDL_Renderer *renderer, Uint32 color)
{
    // Color is 4 byte RGBA (0xRRGGBBAA)
    // Bit positions: 31-24 [RR], 23-16 [GG], 15-8 [BB], 7-0 [AA]
    // To get RR byte, shift RR to rightmost position
    // Bitwise AND with 0xFF (11111111) masks out everything but lowest 8 bits
    // Since the lowest 8 bits are now the RR byte , `& 0xFF` extracts the RR byte
    // Repeat for all other bytes
    Uint8 r = (color >> 24) & 0xFF;
    Uint8 g = (color >> 16) & 0xFF;
    Uint8 b = (color >> 8) & 0xFF;
    Uint8 a = color & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void DrawCircle(SDL_Renderer *renderer, Circle circle, Uint32 color)
{
    // Filled circle using midpoint algorithm with horizontal line fills
    // https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
    int x = 0;
    int y = circle.radius;
    int d = 1 - circle.radius;
    SetRenderDrawColor(renderer, color);
    while (x <= y)
    {
        // Draw horizontal lines for filled circle
        SDL_RenderDrawLine(renderer, circle.center.x - x, circle.center.y + y, circle.center.x + x, circle.center.y + y);
        SDL_RenderDrawLine(renderer, circle.center.x - x, circle.center.y - y, circle.center.x + x, circle.center.y - y);
        SDL_RenderDrawLine(renderer, circle.center.x - y, circle.center.y + x, circle.center.x + y, circle.center.y + x);
        SDL_RenderDrawLine(renderer, circle.center.x - y, circle.center.y - x, circle.center.x + y, circle.center.y - x);
        
        if (d < 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void GenerateRays(SDL_Renderer *renderer, Circle circle, int num_rays, Circle obstacle, Uint32 color)
{
    SetRenderDrawColor(renderer, color);
    for(int ray_num = 1; ray_num <= num_rays; ray_num++)
    {
        // Calculate ray end point
        float angle = (360.0 / num_rays) * ray_num * M_PI / 180.0; // convert to radians
        float end_x = circle.center.x + cos(angle) * RAY_SCALE;
        float end_y = circle.center.y + sin(angle) * RAY_SCALE;
        // Create ray
        Ray ray = {
            .origin = circle.center,
            .direction = {
                .x = (float)(cos(angle)),
                .y = (float)(sin(angle))
            }
        };
        // Check intersection with obstacle
        Vect2D intersection;
        if(Intersection(ray, obstacle, &intersection))
        {
            SDL_RenderDrawLine(renderer, circle.center.x, circle.center.y, intersection.x, intersection.y);
            continue;
        }

        SDL_RenderDrawLine(renderer, circle.center.x, circle.center.y, end_x, end_y);
    }
}

bool Intersection(Ray ray, Circle obstacle, Vect2D *intersection)
{
    // Ray-circle intersection using quadratic formula
    Vect2D F = vSubtract(ray.origin, obstacle.center); // Vector from circle center to ray origin
    float a = 1; // a = ray.direction ⋅ ray.direction, since ray.direction is normalized, a = 1
    float b = 2 * vDot(F, ray.direction); // b = 2 * (f ⋅ ray.direction)
    float c = vDot(F, F) - (obstacle.radius * obstacle.radius); // c = (f ⋅ f) - r^2
    float discriminant = (b * b) - 4 * a * c; // Discriminant of quadratic equation
    // If discriminant is >= 0, there is an intersection
    if(discriminant >= 0)
    {
        // Quadratic formula: (-b ± sqrt(discriminant)) / 2a
        // t must be >= 0
        float t1 = ((-b - sqrt(discriminant)) / (2 * a));
        float t2 = ((-b + sqrt(discriminant)) / (2 * a));

        if(t1 >= 0)
        {
            // P is a point along the array where P = 0 + tD, where O = ray.origin and D = ray.direction
            Vect2D tD = vScalarMult(t1, ray.direction);
            Vect2D P = vAdd(ray.origin, tD);
            intersection->x = P.x;
            intersection->y = P.y;
            return true;
        }
        else if(t2 >= 0)
        {
            // P is a point along the array where P = 0 + tD, where O = ray.origin and D = ray.direction
            Vect2D tD = vScalarMult(t2, ray.direction);
            Vect2D P = vAdd(ray.origin, tD);
            intersection->x = P.x;
            intersection->y = P.y;
            return true;
        }
        return false;
    }
    return false;
}