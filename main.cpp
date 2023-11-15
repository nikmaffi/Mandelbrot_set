#include <complex>
#include <numeric>
#include <iostream>
#include <fstream>

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
        z = std::pow(z, 2) + c; //Complex function

        //If the magnitude of z is greather than the trigger than the function diverges
        if(std::abs(z) > trig) {
            return k;
        }
    }

    return max_iters;
}

//This function produce a character in [min, max] based on the value of div
char draw(char min, char max, unsigned div) {
    return div % (max - min) + min;
}

int main(int argc, const char *argv[]) {
    //File for mandelbrot set drawing
    std::fstream stream("mandelbrot.draw", std::ios::out | std::ios::binary);

    unsigned WIDTH = 80; //Terminal max characters (columns)
    unsigned HEIGHT = 24; //Terminal max characters (rows)
    long double RATIO = HEIGHT / (long double)WIDTH; //Terminal ratio

    unsigned MAX_ITERS = 1e3; //Max iterations to check divergence
    unsigned TRIGGER = 1e6; //Divergence trigger

    //Used tho check if the function diverges giving a certain value of c
    unsigned div = 0;

    //Character to print
    char c = '\0';

    //Used to scale the values of c
    long double min = -3;
    long double max = 3;

    if(argc == 7) {
        //Getting values for drawing the set
        WIDTH = strtoul(argv[1], nullptr, 10);
        HEIGHT = strtoul(argv[2], nullptr, 10);

        RATIO = HEIGHT / (long double) WIDTH;

        min = strtold(argv[3], nullptr);
        max = strtold(argv[4], nullptr);

        MAX_ITERS = strtoul(argv[5], nullptr, 10);
        TRIGGER = strtoul(argv[6], nullptr, 10);
    } else if(argc != 1) {
        std::cout << "\nSYNOPSIS:\n"
            << "\t" << argv[0] << " width height min max iters trig\n\n"
            << "OPTIONS:\n"
            << "\t" << " <width>:  Maximun characters columns.\n\t\t   Default is " << WIDTH << ".\n\n"
            << "\t" << "<height>:  Maximum characters rows.\n\t\t   Default is " << HEIGHT << ".\n\n"
            << "\t" << "   <min>:  Minimum real number considered.\n\t\t   Default is " << min << ".\n\n"
            << "\t" << "   <max>:  Maximum real number considered.\n\t\t   Default is " << max << ".\n\n"
            << "\t" << " <iters>:  Numbers of iterations to check divergence.\n\t\t   Default is " << MAX_ITERS << ".\n\n"
            << "\t" << "  <trig>:  Trigger value corresponding to infinity.\n\t\t   Default is " << TRIGGER << ".\n\n";

        return EXIT_FAILURE;
    }

    //Computing every pixel in the window
    for(unsigned y = 0; y < HEIGHT; y++) {
        for(unsigned x = 0; x < WIDTH; x++) {                
            //Mapping the value of c between -scale-scale*i and scale+scale*i (zooming and centering)
            div = diverges(
                {
                    map(x, 0.0, WIDTH, min, max),
                    map(y, 0.0, HEIGHT, min * RATIO, max * RATIO)
                }, MAX_ITERS, TRIGGER
            );

            if(div == MAX_ITERS) {
                //The function does not diverge
                c = ' ';
            } else {
                //The function diverges (set a char between 'a' and 'z' based on div)
                c = draw('a', 'z', div);
            }

            //Writing the caracter into the file
            stream.write(&c, sizeof(char));
        }

        //New row
        stream.write("\n", sizeof(char));
    }

    stream.close();

    return EXIT_SUCCESS;
}