#include "image.h"
#include "DisjSets.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
using namespace ComputerVisionProjects;

// Sobel operator kernels for calculating horizontal (X) and vertical (Y) gradients
int GradientX[3][3] = {{-1, 0, 1}, 
                       {-2, 0, 2}, 
                       {-1, 0, 1}};

int GradientY[3][3] = {{-1, -2, -1}, 
                       { 0,  0,  0}, 
                       { 1,  2,  1}};

// Function to compute the gradient magnitude at a given pixel (x, y) in the image
int ComputeGradientMagnitude(const Image& img, int x, int y) {
    int gx_sum = 0, gy_sum = 0;  // Initialize gradient sums for x and y directions

    // Loop over the 3x3 neighborhood of the pixel
    for (int offset_x = -1; offset_x <= 1; ++offset_x) {
        for (int offset_y = -1; offset_y <= 1; ++offset_y) {
            // Get the pixel value from the image at position (x + offset_x, y + offset_y)
            int pixel_value = img.GetPixel(x + offset_x, y + offset_y);

            // Accumulate the weighted sum of pixels in the x and y directions
            gx_sum += GradientX[offset_x + 1][offset_y + 1] * pixel_value;
            gy_sum += GradientY[offset_x + 1][offset_y + 1] * pixel_value;
        }
    }
    // Calculate the gradient magnitude using Euclidean distance formula
    return static_cast<int>(sqrt(gx_sum * gx_sum + gy_sum * gy_sum));
}

int main(int argc, char* argv[]){
    // Check if the user provided correct command line arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input grayscale image> <output edge-detected image>" << endl;
        return 0;  
    }

    // Input and output file names
    const string source_file(argv[1]);
    const string dest_file(argv[2]);

    // Initialize the input image
    Image input_image;

    // Read the input image; if unable to read, output an error and exit
    if (!ReadImage(source_file, &input_image)) {
        cerr << "Error: Unable to open " << source_file << endl;
        return 0;
    }

    // Initialize the output image with the same dimensions as the input
    Image output_image;
    output_image.AllocateSpaceAndSetSize(input_image.num_rows(), input_image.num_columns());
    output_image.SetNumberGrayLevels(255);  // Set maximum gray level for the output

    // Loop over each pixel (excluding border pixels)
    for (size_t row = 1; row < input_image.num_rows() - 1; ++row) {
        for (size_t col = 1; col < input_image.num_columns() - 1; ++col) {
            // Compute the gradient magnitude for the current pixel
            int gradient_magnitude = ComputeGradientMagnitude(input_image, row, col);

            // Set the pixel value in the output image to the gradient magnitude, capped at 255
            output_image.SetPixel(row, col, min(gradient_magnitude, 255));
        }
    }

    // Write the output image; if unsuccessful, output an error and exit
    if (!WriteImage(dest_file, output_image)){
        cerr << "Error: Unable to write to " << dest_file << endl;
        return 0;
    }

    return 0;
}
