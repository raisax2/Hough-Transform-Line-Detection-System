# **Hough Transform Line Detection System**

## **Description**
This project implements a line detection system using the Hough Transform technique. The system processes grayscale images to detect and highlight straight lines, which can be applied to tasks such as interpreting engineering drawings.

The system consists of three implemented programs:
1. **Edge Detection**: Identifies edge points in grayscale images.
2. **Edge Thresholding**: Filters edges to retain only strong ones.
3. **Hough Transform**: Generates the Hough Transform space for line detection.

---

## **Files**
- **Source Code**:
  - `h1.cc`: Edge detection.
  - `h2.cc`: Edge thresholding.
  - `h3.cc`: Hough Transform space generation.
  - `image.h`, `image.cc`: Image processing utilities.
  - `DisjSets.h`, `DisjSets.cc`: Disjoint sets data structure (if used).

- **Supporting Files**:
  - `Makefile`: Builds all executables (`h1`, `h2`, `h3`).
  - `README.md`: This file.
  - `thresholds.txt`: Contains threshold values used in the programs.

---

## **Compilation and Execution**

### **Compilation**
Run the following command to compile all programs:
```bash
make all
```

### **Execution**
#### **Program 1: Edge Detection**
```bash
./h1 {input_gray_level_image} {output_edge_image}
```
- **Input**: Grayscale image.
- **Output**: Edge image with intensity proportional to edge magnitude.

#### **Program 2: Edge Thresholding**
```bash
./h2 {input_edge_image} {threshold_value} {output_binary_edge_image}
```
- **Input**: Edge image and threshold value.
- **Output**: Binary edge image.

#### **Program 3: Hough Transform Space Generation**
```bash
./h3 {input_binary_edge_image} {output_hough_image} {output_hough_voting_array}
```
- **Input**: Binary edge image.
- **Output**: Hough Transform image and voting array file.

---

## **Assumptions and Details**
1. Edge detection uses the squared gradient operator with Sobel masks.
2. Thresholding retains only strong edges for efficient processing.
3. The Hough Transform uses the polar representation of a line: \(x \cos \theta + y \sin \theta = \rho\).
4. Voting arrays are constrained to reasonable resolutions for computational efficiency.

