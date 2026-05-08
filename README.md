*This project has been created as part of the 42 curriculum by thzeribi.*

# fract'ol

Real-time interactive fractal explorer with SIMD-accelerated multithreaded rendering.

[![build](https://img.shields.io/github/actions/workflow/status/TheoZerbibi/fract-ol/ci.yml?label=build)](https://github.com/TheoZerbibi/fract-ol/actions/workflows/ci.yml)
[![norminette](https://img.shields.io/github/actions/workflow/status/TheoZerbibi/fract-ol/ci.yml?label=norminette)](https://github.com/TheoZerbibi/fract-ol/actions/workflows/ci.yml)
![language](https://img.shields.io/badge/language-C-blue)
![license](https://img.shields.io/badge/license-42-lightgrey)

<p align="center">
  <img src="https://cdn.lacaleche.cc/public/fractol/preview.png" alt="fract'ol preview" width="720"/>
</p>

---

## Table of Contents

- [Description](#description)
  - [Mandatory Part](#mandatory-part)
  - [Bonus Part](#bonus-part)
- [Instructions](#instructions)
  - [Requirements](#requirements)
  - [Build](#build)
  - [Usage](#usage)
  - [Generating the Doxygen Documentation](#generating-the-doxygen-documentation)
- [Resources](#resources)
  - [Fractals and Mathematics](#fractals-and-mathematics)
  - [MiniLibX and X11](#minilibx-and-x11)
  - [Optimization](#optimization)
  - [Color Theory](#color-theory)
- [AI Usage](#ai-usage)

---

## Description

### Mandatory Part

A fractal is a geometric structure that exhibits self-similarity at every scale: zooming into any region reveals shapes that mirror the whole. fract'ol generates fractals in real time by applying the **escape-time algorithm** to the complex plane.

Each pixel on screen maps to a complex number `c = re + im*i`. The program iterates the recurrence relation `z_{n+1} = z_n^2 + c` starting from `z_0 = 0` (Mandelbrot) or `z_0 = c` with a fixed parameter (Julia), counting iterations until `|z|^2 > 4` (the escape condition, equivalent to `|z| > 2` but avoiding a `sqrt`). The iteration count is then mapped through a color palette to produce the final pixel color.

The CLI argument selects the fractal type. A window opens via MiniLibX, rendering the full image into an off-screen pixel buffer before flushing it to the window in a single call. The user can zoom with the mouse wheel, navigate with arrow keys, and exit cleanly via ESC or the window close button.

![Mandelbrot set](https://cdn.lacaleche.cc/public/fractol/mandelbrot.png)
![Julia set](https://cdn.lacaleche.cc/public/fractol/julia.png)

### Bonus Part

The bonus implementation extends the project with additional fractal sets, optimized rendering, and enhanced interactivity.

**Additional Fractal Sets**

- **Burning Ship**: Applies `z_{n+1} = (|Re(z_n)| + i|Im(z_n)|)^2 + c`, where absolute values are taken on the real and imaginary parts before squaring. This produces an asymmetric, flame-like structure.
- **Phoenix**: Uses a two-term recurrence `z_{n+1} = z_n^2 + Re(c) + Im(c) * z_{n-1}`, incorporating the previous iteration value. The result is a branching, organic fractal.
- **Buddhabrot**: A probability-density visualization of escaping Mandelbrot orbits. Random points are sampled from the complex plane; those that escape have their full orbit paths accumulated into a histogram, which is then tone-mapped to produce a nebula-like image.

**Mouse-Centered Zoom**

Zoom operations remap the complex plane boundaries such that the point under the cursor remains fixed. Given cursor position `(cx, cy)` mapping to complex coordinates `(cr, ci)`, the new boundaries are computed as:
```
new_min_r = cr - (cr - old_min_r) * zoom_factor
new_max_r = cr + (old_max_r - cr) * zoom_factor
```
This preserves the cursor's position in the fractal while scaling the viewport around it.

**Arrow Key Navigation**

Panning translates the viewport by a fraction (`MOVE_STEP = 0.1`) of the current viewport dimensions, applied uniformly to both `min` and `max` bounds on the corresponding axis.

**Color Shift**

Three distinct palettes cycle via the Shift key. Colors are computed by scaling `sqrt(iteration) * 2.5` into the palette size, with linear interpolation between adjacent palette entries for smooth gradients.

**Performance Optimizations**

- **Multithreaded rendering** via pthreads with CPU affinity (up to 128 threads)
- **AVX2 SIMD vectorization**: 4 pixels computed in parallel per iteration using `__m256d` intrinsics
- **Cardioid/bulb early-out** for Mandelbrot: skips iteration for points known to be inside the set
- **Period checking**: detects orbital cycles to skip remaining iterations
- **Dirty-flag rendering**: suppresses redundant redraws when the viewport is unchanged
- **Adaptive iteration count**: scales `max_iterations` logarithmically with zoom depth

![Bonus fractal](https://cdn.lacaleche.cc/public/fractol/burning_ship.png)
![Color shift](https://cdn.lacaleche.cc/public/fractol/palettes.png)

---

## Instructions

### Requirements

| Dependency | Purpose |
|---|---|
| `cc` (gcc/clang) | C compiler with C99 support |
| `make` | Build automation |
| `libX11-dev` | X11 windowing system |
| `libXext-dev` | X11 shared memory extension |
| `libm` | Math library (linked automatically) |
| MiniLibX | Graphics library (included as submodule) |

On Debian/Ubuntu:
```bash
sudo apt install gcc make libx11-dev libxext-dev
```

### Build

```bash
make          # builds the mandatory project
make bonus    # builds with bonus features (SIMD, threads, extra fractals)
make clean    # removes object files
make fclean   # full clean (objects + binary)
make re       # rebuild from scratch
```

### Usage

```bash
./fractol mandelbrot
./fractol julia <real> <imaginary>
./fractol burning_ship
./fractol phoenix
./fractol buddhabrot
./fractol <invalid>   # prints usage and exits
```

Short aliases are supported: `m`, `j`, `bs`, `p`, `bb`.

| Key / Action       | Effect                              |
|---------------------|-------------------------------------|
| Mouse wheel up      | Zoom in (centered on cursor)        |
| Mouse wheel down    | Zoom out (centered on cursor)       |
| Arrow keys / WASD   | Pan the viewport                    |
| Left Shift          | Cycle color palette                 |
| Space               | Lock/unlock Julia mouse tracking    |
| Left Ctrl           | Toggle usage overlay                |
| E                   | Toggle debug overlay (FPS, zoom)    |
| ESC                 | Exit                                |
| Window close button | Exit                                |

### Generating the Doxygen Documentation

A `Doxyfile` is provided at the project root. To generate the HTML documentation:

```bash
doxygen Doxyfile
```

Output is generated in `docs/` (not tracked by git). Open `docs/html/index.html` in a browser to browse the documentation.

---

## Resources

### Fractals and Mathematics

- [Mandelbrot set — Wikipedia](https://en.wikipedia.org/wiki/Mandelbrot_set) — Mathematical definition, properties, and history of the Mandelbrot set.
- [Julia set — Wikipedia](https://en.wikipedia.org/wiki/Julia_set) — Formal definition and relationship to the Mandelbrot set.
- [Burning Ship fractal — Wikipedia](https://en.wikipedia.org/wiki/Burning_Ship_fractal) — Description of the absolute-value variant and its visual characteristics.
- [Buddhabrot — Wikipedia](https://en.wikipedia.org/wiki/Buddhabrot) — Probability-density rendering technique for Mandelbrot orbit paths.
- [Escape time algorithm — Wikipedia](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set) — Core rendering algorithm used for escape-time fractals.
- [Cardioid and bulb checking](https://mathr.co.uk/blog/2022-11-19_cardioid_and_bulb_checking.html) - Fast optimization technique for Mandelbrot and Julia sets.
- [Complex number — Wikipedia](https://en.wikipedia.org/wiki/Complex_number) — Arithmetic operations on complex numbers and their geometric interpretation.

### MiniLibX and X11

- [42 MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — API reference and usage patterns for the 42 graphics library.
- [X11 event system — Xlib Programming Manual](https://tronche.com/gui/x/xlib/events/) — X11 event types, masks, and the event processing model.

### Optimization

- [Intel Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html) — Reference for AVX/AVX2 SIMD intrinsics (`__m256d`, `_mm256_mul_pd`, `_mm256_cmp_pd`).
- [GCC Auto-vectorization](https://gcc.gnu.gnu.org/onlinedocs/gcc/Optimize-Options.html) — Compiler flags for automatic vectorization (`-O3`, `-march=native`).
- [Mouse-centered zoom — fractal coordinate math](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#Zooming) — Coordinate remapping to keep the cursor position fixed during zoom.
- [Thread affinity](https://en.wikipedia.org/wiki/Processor_affinity) — CPU affinity, also known as processor affinity, is the property of a computer system that binds a computer process or thread of execution to a specific subset of the available physical processors.
- [List of x86 SIMD instructions ](https://en.wikipedia.org/wiki/List_of_x86_SIMD_instructions) — List of x86 SIMD instructions, which are used to perform parallel operations on data.

### Color Theory

- [HSL and HSV — Wikipedia](https://en.wikipedia.org/wiki/HSL_and_HSV) — Color space models used for psychedelic palette cycling.
- [Smooth coloring for fractals](https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#Continuous_(smooth)_coloring) — Fractional escape count using logarithms for band-free coloring.

---

## AI Usage

### Project Understanding

Claude Opus 4.6 and Gemini Pro 3.0 were used to build initial understanding of the project requirements and scope.

### Learning — Gemini Pro 3.0 Teaching Mode

Gemini's interactive Teaching mode was used to deeply understand:
- The mathematical concept of fractals and complex number iteration
- The escape-time algorithm and its visual interpretation
- Mandatory optimizations: image buffer rendering vs per-pixel MLX calls
- Bonus optimizations: SIMD vectorization, mouse-centered zoom math, smooth coloring algorithms

### Code Review — Claude Opus 4.6 (Thinking)

Claude Opus 4.6 with extended thinking was used to perform a two-part code review:
- **Part 1 — Norm & Compliance:** verification against 42 Norm v3 and subject requirements
- **Part 2 — Technical Review:** memory safety, logic correctness, MiniLibX usage optimization, and architecture quality

**No code was directly generated by AI in the project. I strongly advise against using AI directly for code generation in a school project / during your 42 curriculum!**

**More information on the effects of using AI in learning can be found here :**
- [*The Impact of Large Language Models on Programming Education and Student Learning Outcomes*](https://www.mdpi.com/2076-3417/14/10/4115).
- [*AI Meets the Classroom: When Do Large Language Models Harm Learning?*](https://arxiv.org/pdf/2409.09047)
- [*Ethical and Responsible Use of AI for Students*](https://genai.calstate.edu/communities/students/ethical-and-responsible-use-ai)
