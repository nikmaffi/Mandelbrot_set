#include <complex>
#include <numeric>

//For graphics
#include <SFML/Graphics.hpp>

//Window width
#define WIDTH 800.0
//Window height
#define HEIGHT 600.0

//Window ratio
#define RATIO ((HEIGHT) / (WIDTH))

//Maximum FPS
#define FPS 60

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

sf::Image computeMandelbrotSet(void) {
    //Defining image, texture and sprite
    sf::Image image;

    //Used tho check if the function diverges giving a certain value of c
    unsigned div = 0;

    //Calculating the Mandelbrot set
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    //Computing every pixel in the image
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
                image.setPixel(x, y, sf::Color::Black);
            } else {
                //The function diverges (set the color based on x + 1.8*x + 3*x)
                //SDL_SetRenderDrawColor(renderer, (Uint8)div, (Uint8)(div * 1.8), (Uint8)(div * 3), 255);
                image.setPixel(x, y, sf::Color(std::log2(div), std::log2(div) * 9, std::log2(div) * 20));
            }
        }
    }

    return image;
}

int main() {
    //Defining SFML window, event, texture and sprite for drawing
    //Windown initialization
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot set", sf::Style::Close);
    sf::Event event;
    sf::Texture texture;
    sf::Sprite sprite;

    //Setting framerate limit
    window.setFramerateLimit(FPS);

    //Computing the Mandelbrot set and preparing texture and sprite for printing the image
    texture.loadFromImage(computeMandelbrotSet());
    sprite.setTexture(texture);

    //Waiting window closing
    while(window.isOpen()) {
        //Events checker
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();

        //Drawing the Mandelbrot set
        window.draw(sprite);

        window.display();
    }

    return EXIT_SUCCESS;
}