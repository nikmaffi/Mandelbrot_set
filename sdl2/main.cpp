#include <complex>
#include <numeric>

//For graphics
#include <SDL2/SDL.h>

//Window width
#define WIDTH 800.0
//Window height
#define HEIGHT 600.0

//Window ratio
#define RATIO ((HEIGHT) / (WIDTH))

//Max iterations to check divergence
#define MAX_ITERS 1e3
//Divergence trigger
#define TRIGGER 1e6

//Used to scale the values of c
const long double MIN = -2.5;
const long double MAX = 2.5;

//This function map the value of x, in the interval [a1, b1], into the interval [a2, b2]
long double map(long double x, long double a1, long double b1, long double a2, long double b2) {    
    return a2 + x * (b2 - a2) / (b1 - a1);
}

int diverges(const std::complex<long double> c, unsigned max_iters, long double trig) {
    //Mandelbrot set ==> z = z^2 + c
    //where z, c are two complex numbers

    std::complex<long double> z(0.0, 0.0); //z always starts from zero

    //k is used to check if the function diverges
    for(unsigned k = 0; k < max_iters; k++) {
        //Complex function
        z = std::pow(z, 2) + c;

        //If the magnitude of z is greather than the trigger than the function diverges
        if(std::abs(z) > trig) {
            return k;
        }
    }

    return max_iters;
}

int main() {
    //Defining SDL window, renderer, event
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_Event event;

    //Used for exit the "game loop"
    bool done = false;

    //Used tho check if the function diverges giving a certain value of c
    unsigned div = 0;

    //SDL env initialization
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);

    //Waiting ESC pressed or window closing
    while(!done) {
        //Events checker
        while(SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                done = true;
            }
        }

        //Computing every pixel in the window
        for(int x = 0; x < WIDTH; x++) {
            for(int y = 0; y < HEIGHT; y++) {                
                //Mapping the value of c between -scale-scale*i and scale+scale*i (zooming and centering)
                div = diverges(
                    {
                        map(x, 0.0, WIDTH, MIN, MAX),
                        map(y, 0.0, HEIGHT, MIN * RATIO, MAX * RATIO)
                    }, MAX_ITERS, TRIGGER
                );

                if(div == MAX_ITERS) {
                    //The function does not diverge
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                } else {
                    //The function diverges (set the color based on x + 1.8*x + 3*x)
                    //SDL_SetRenderDrawColor(renderer, (Uint8)div, (Uint8)(div * 1.8), (Uint8)(div * 3), 255);
                    SDL_SetRenderDrawColor(renderer, (Uint8)(std::log2(div)), (Uint8)(std::log2(div) * 9), (Uint8)(std::log2(div) * 20), 255);
                }

                //Put the pixel
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }

        //Rendering
        SDL_RenderPresent(renderer);
    }

    //Program end
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return EXIT_SUCCESS;
}