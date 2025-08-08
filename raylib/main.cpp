#include <complex>
#include <numeric>

//For graphics
#include <raylib.h>

//Window width
#define WIDTH 800
//Window height
#define HEIGHT 600

//Window ratio
#define RATIO ((double)(HEIGHT) / (WIDTH))

//Maximum FPS
#define FPS 60

//Max iterations to check divergence
#define MAX_ITERS 1e3
//Divergence trigger
#define TRIGGER 1e6

//Used to scale the values of c
const double MIN = -2.5;
const double MAX = 2.5;

//This function map the value of x, in the interval [a1, b1], into the interval [a2, b2]
double map(double x, double a1, double b1, double a2, double b2) {    
    return a2 + (x - a1) * (b2 - a2) / (b1 - a1);
}

int diverges(const std::complex<double> c, unsigned max_iters, double trig) {
    //Mandelbrot set ==> z = z^2 + c
    //where z, c are two complex numbers

    std::complex<double> z(0.0, 0.0); //z always starts from zero

    //k is used to check if the function diverges
    for(unsigned k = 0; k < max_iters; k++) {
        //Complex function
        z = std::pow(z, 2) + c;

        //If the magnitude of z is greater than the trigger than the function diverges
        if(std::abs(z) > trig) {
            return k;
        }
    }

    return max_iters;
}

Image computeMandelbrotSet(void) {
    //Defining image, texture and sprite
    Image image = GenImageColor(WIDTH, HEIGHT, BLACK);
    Color color; //Single pixel color

    //Used tho check if the function diverges giving a certain value of c
    unsigned div = 0;

    //Calculating the Mandelbrot set - computing every pixel in the image
    for(int x = 0; x < WIDTH; x++) {
        for(int y = 0; y < HEIGHT; y++) {
            //Mapping the value of c between -scale-scale*i and scale+scale*i (zooming and centering)
            div = diverges(
                {
                    map(x, 0.f, WIDTH, MIN, MAX),
                    map(y, 0.f, HEIGHT, MIN * RATIO, MAX * RATIO)
                }, MAX_ITERS, TRIGGER
            );

            if(div == MAX_ITERS) {
                //The function does not diverge
                color = BLACK;
            } else {
                //The function diverges (set the color)
                color = (Color){
                    (unsigned char)(std::log2(div) * 5),
                    (unsigned char)(std::log2(div) * 9),
                    (unsigned char)(std::log2(div) * 20),
                    255
                };
            }

            ImageDrawPixel(&image, x, y, color);
        }
    }

    return image;
}

int main() {
    //Defining texture and image for drawing
    Texture texture;
    Image image;

    //Window initialization
    InitWindow(WIDTH, HEIGHT, "Mandelbrot set");

    //Setting framerate limit
    SetTargetFPS(FPS);

    //Computing the Mandelbrot set and preparing texture for printing the image
    image = computeMandelbrotSet();
    texture = LoadTextureFromImage(image);

    //Unloading the image
    UnloadImage(image);

    //Waiting window closing
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        //Drawing the Mandelbrot set
        DrawTexture(texture, 0, 0, WHITE);

        EndDrawing();
    }

    //Unloading resources
    UnloadTexture(texture);
    CloseWindow();

    return EXIT_SUCCESS;
}