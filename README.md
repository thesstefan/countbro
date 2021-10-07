<p align="center">
  <img src="https://github.com/thesstefan/countbro/blob/master/extra/countbro.png" alt="Count Bro Logo"/>
</p>

# Count Bro

Program written in C using no additional libraries, providing a toolset used to count objects where no overlapping occurs (e.g. cells, coins) and specific constraints are set. (mainly based on colour)

The program implements several image-processing tools which can be used independently. The intended workflow for counting objects is:

1. Threshold the input image, using a well-chosen thresholding interval
2. Apply the necessary morphological operations (dilation, closing, opening, erosion) 
3. Use the labelling algorithm and count the objects

The project is made with no additional libraries, being created with a learning purpose in mind. 

# Features:

1. BMP file interface, able of I/O and general access
2. Implementations of data structures such as `vector`, `set`
3. Interfaces for various image types such as `binary` or `grayscale`
4. Implementation of morphological operators, used for detail enhancing or impurity removal
5. Basic image processing specific kernel functionality
6. Colour based two-pass labelling algorithm

# Installation
Simply clone the project through your preferred IDE or by using the bash command
```bash
git clone git@github.com:thesstefan/countbro.git
```

# Usage
After closing the repository, write your customized `main.cpp` (see some examples in `extra/`) and
modify the `Makefile` to suit your needs (specify input/output image file paths). Next,
compile the project and count the objects in the image by executing (assuming a shell environment)
```bash
make -jX && make run
```
where `X` is the desired number of jobs to be ran in parallel.

# Examples:

1. Counting (1033) and detection of stars using [`extra/main_sky.c`](https://github.com/thesstefan/countbro/master/extra/main_sky.c) as source
and [`data/sky_input.bmp`](https://github.com/thesstefan/countbro/blob/master/data/sky_input.bmp) as input.

<p align="center">
  <img src="https://github.com/thesstefan/Cell-Counter/blob/master/extra/sky_process.gif" alt="Sky GIF"/>
</p>

2. Counting (10) and detection of some coins using [`extra/main_coins.c`](https://github.com/thesstefan/countbro/master/extra/main_coins.c) as source
and [`data/coins_input.bmp`](https://github.com/thesstefan/countbro/blob/master/data/coins_input.bmp) as input.

<p align="center">
  <img src="https://github.com/thesstefan/Cell-Counter/blob/master/extra/coins_process.gif" alt="Coins GIF"/>
</p>

3. Counting and detection (~184 with overlapping cells errors) of blood cells in a scan (the original purpose of the project), using 
[`extra/main_cells.c`](https://github.com/thesstefan/countbro/blob/master/extra/main_cells.c) as source and 
[`extra/data_input.bmp`](https://github.com/thesstefan/countbro/blob/master/data/cells_input.bmp) as input.
<p align="center">
  <img src="https://github.com/thesstefan/Cell-Counter/blob/master/extra/cells_process.gif" alt="Cells GIF"/>
</p>

# Future Plans:

1. [ ] Implement colour-range thresholding for finer detection control 
2. [ ] Transition everything to shader & GPU implementations for performance improvements 

<div>Icons made by <a href="https://www.flaticon.com/authors/freepik" title="Freepik">Freepik</a> from <a href="https://www.flaticon.com/" title="Flaticon">www.flaticon.com</a></div>

