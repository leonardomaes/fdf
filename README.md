# 🗺️ FDF - 3D Wireframe Visualizer

A graphical application that transforms 2D maps into stunning 3D wireframe visualizations using isometric projection.

![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-Porto-black?style=flat)

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Controls](#controls)
- [Algorithm](#algorithm)
- [Performance](#performance)
- [What I Learned](#what-i-learned)

## 🎯 Overview

FDF (Fil de Fer / Wireframe) reads map files containing elevation data and renders them as interactive 3D wireframe models. The project focuses on graphics programming, mathematical transformations, and real-time rendering optimization.

**Development Period:** July 2024 - October 2024  
**Graphics Library:** MiniLibX (42's custom graphics library)

## ✨ Features

### Core Functionality
- 📊 Parse elevation maps from text files
- 🎨 Isometric 3D projection
- 🌈 Color gradients based on altitude
- ⚡ **40% faster rendering** through optimized algorithms
- 🖱️ Real-time user interactions

### Visual Features
- Zoom in/out
- Rotation (X, Y, Z axes)
- Translation (move map around)
- Color interpolation between vertices
- Multiple projection modes (isometric, parallel)

## 🚀 Installation
```bash
# Clone the repository
git clone https://github.com/yourusername/fdf.git
cd fdf

# Install MiniLibX (Linux)
sudo apt-get install libx11-dev libxext-dev libbsd-dev

# Compile
make

# Run with a map file
./fdf maps/42.fdf
```

### MacOS Installation
```bash
# MiniLibX comes bundled for macOS
make
./fdf maps/42.fdf
```

## 💻 Usage
```bash
./fdf <map_file>

# Examples
./fdf maps/42.fdf
./fdf maps/pyramide.fdf
./fdf maps/julia.fdf
```

### Map File Format
```
0  0  0  0  0
0 10 10 10  0
0 10 20 10  0
0 10 10 10  0
0  0  0  0  0
```
- Each number represents altitude (Z value)
- Optional hex colors: `10,0xFF0000` (red)

## 🎮 Controls

| Key | Action |
|-----|--------|
| `←` `→` `↑` `↓` | Move map |
| `+` `-` | Zoom in/out |
| `W` `S` | Rotate X axis |
| `A` `D` | Rotate Y axis |
| `z` `x` | Rotate Z axis |
| `1` `2` | Toggle isometric/parallel |
| `ESC` | Exit program |

## 🔍 Algorithm

### Bresenham's Line Algorithm

FDF uses Bresenham's algorithm for efficient line drawing without floating-point operations:
```c
void	draw_line(t_point p1, t_point p2)
{
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = p1.x < p2.x ? 1 : -1;
    int sy = p1.y < p2.y ? 1 : -1;
    int err = dx - dy;
    
    // ...
}
```

**Why Bresenham?**
- Integer-only operations (faster than floating-point)
- No multiplication or division
- Pixel-perfect line rendering

### Isometric Projection

Converts 3D coordinates to 2D screen space:
```c
void	isometric(int *x, int *y, int z)
{
    int prev_x = *x;
    int prev_y = *y;
    
    *x = (prev_x - prev_y) * cos(0.523599);
    *y = (prev_x + prev_y) * sin(0.523599) - z;
}
```

### Color Interpolation

Smooth color transitions between vertices:
```c
int	interpolate_color(int color1, int color2, float ratio)
{
    int r = (1 - ratio) * ((color1 >> 16) & 0xFF) + ratio * ((color2 >> 16) & 0xFF);
    int g = (1 - ratio) * ((color1 >> 8) & 0xFF) + ratio * ((color2 >> 8) & 0xFF);
    int b = (1 - ratio) * (color1 & 0xFF) + ratio * (color2 & 0xFF);
    
    return (r << 16) | (g << 8) | b;
}
```

## ⚡ Performance Optimization

### Before Optimization
- Recalculated all transformations every frame
- Direct pixel operations
- ~120ms per frame on complex maps

### After Optimization (40% improvement)
- ✅ Pre-calculate transformation matrices
- ✅ Use integer arithmetic where possible
- ✅ Image buffer instead of direct pixel writes
- ✅ ~70ms per frame on same maps

## 📚 What I Learned

### Technical Skills
- **Computer Graphics:** Rasterization, projections, transformations
- **Mathematics:** Linear algebra, trigonometry, matrix operations
- **Algorithms:** Bresenham, color interpolation
- **Optimization:** Profiling, bottleneck identification

### Concepts
- Coordinate system transformations (3D → 2D)
- Event-driven programming (keyboard/mouse hooks)
- Memory-efficient image rendering
- Balancing visual quality with performance

## 🎯 Challenges Solved

1. **Z-fighting:** Lines overlapping incorrectly
   - Solution: Proper depth sorting before rendering

2. **Performance bottleneck:** Slow on large maps
   - Solution: Pre-calculations + integer math

3. **Color bleeding:** Incorrect gradients
   - Solution: Per-pixel linear interpolation

## 🤝 Resources

- [Bresenham's Algorithm Explained](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- [Isometric Projection Mathematics](https://en.wikipedia.org/wiki/Isometric_projection)
- MiniLibX Documentation (42 Intra)

## 📝 License

This project is part of the 42 School curriculum and follows their academic policies.

---

**42 Porto** | [Leonardo Maes](https://linkedin.com/in/leonardo-maes)
