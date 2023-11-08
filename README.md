# Mandelbrot_set
Mandelbrot Set simulation written in C++ and SDL 2

The Mandelbrot set is defined in the complex plane as the complex numbers $` c `$ for which the function $` f_c(z) = z^2 + c `$ does not diverge to infinity when iterated starting at $` z = 0 `$.

More informations at [Mandelbrot set - Wikipedia](https://en.wikipedia.org/wiki/Mandelbrot_set)

---

Here some images computed with different functions:

- $` f_c(z) = z^2 + c `$
<img alt="z^2 + c" src="./img/z^2+c.bmp">

- $` f_c(z) = z^2 + \sqrt{c} `$
<img alt="z^2 + sqrt(c)" src="./img/z^2+sqrt(c).bmp">

- $` f_c(z) = z + c^3 + c^2 + c `$
<img alt="z + c^3 + c^2 + c" src="./img/z+c^3+c^2+c.bmp">

- $` f_c(z) = c - \sin{z} `$
<img alt="c - sin(z)" src="./img/c-sin(z).bmp">

- $` f_c(z) = c - \cos{z} `$
<img alt="c - cos(z)" src="./img/c-cos(z).bmp">

- $` f_c(z) = c - \sin{z} -\cos{z} `$
<img alt="c - sin(z) - cos(z)" src="./img/c-sin(z)-cos(z).bmp">
