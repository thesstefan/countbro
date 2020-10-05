<p align="center">
  <img src="https://github.com/thesstefan/count_bro/blob/master/extra/count_bro.png" alt="Count Bro Logo"/>
</p>

# Count Bro

Program written in C using no additional libraries, used to count things where no overlapping
occurs (ex: cells, coins) and specific constraints are set. (mainly based on colour)



The program implements several image-processing tools which can be used in any way. The intended way is to:

1. Threshold the input image, using a well-chosen thresholding interval
2. Apply the necessary morphological operations (dilation, closing, opening, erosion) 
3. Use the labelling algorithm and count the objects

The project is made with no additional libraries, being created with a learning purpose in mind. 

# Installation:
```bash
git clone https://github.com/thesstefan/count_bro.git
```

# Features:

1. BMP file interface, able of I/O and general access
2. Implementations of data structures such as `vector`, `set`
3. Interfaces for various image types such as `binary` or `grayscale`
4. Implementation of morphological operators, used for detail enhancing or impurity removal
5. Basic image processing specific kernel functionality
6. Colour based two-pass labelling algorithm

# TODO:

1. [ ] Implement colour-range thresholding for finer detection control 
2. [ ] Transition everything to shader & GPU implementations for performance improvements 

# Examples:

1. Counting (1033) and detection of stars using [main_sky.c](https://github.com/thesstefan/count_bro/master/extra/main_sky.c) as source
and [sky_input.bmp](https://github.com/thesstefan/count_bro/blob/master/data/sky_input.bmp) as input.

<p align="center">
  <img src="https://github.com/thesstefan/Cell-Counter/blob/master/extra/sky_process.gif" alt="Sky GIF"/>
</p>

2. Counting (10) and detection of some coins using [main_coins.c](https://github.com/thesstefan/count_bro/master/extra/main_coins.c) as source
and [coins_input.bmp](https://github.com/thesstefan/count_bro/blob/master/data/coins_input.bmp) as input.

<p align="center">
  <img src="https://github.com/thesstefan/Cell-Counter/blob/master/extra/coins_process.gif" alt="Coins GIF"/>
</p>

3. Counting and detection (~184 with overlapping cells errors) of blood cells in a scan (the original purpose of the project), using 
[main_cells.c](https://github.com/thesstefan/count_bro/blob/master/extra/main_cells.c) as source and 
[cells_input.bmp](https://github.com/thesstefan/count_bro/blob/master/data/cells_input.bmp) as input.

<p align="center">
  <img src="https://github.com/thesstefan/Cell-Counter/blob/master/extra/cells_process.gif" alt="Cells GIF"/>
</p>
