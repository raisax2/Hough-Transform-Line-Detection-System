#include "image.h"
#include <vector>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;
using namespace ComputerVisionProjects;

/*
Performs the Hough Transform.
Input: binary image, hough image, accumulator array, rho bins, theta bins.
*/
void HoughTransform(const Image &binary_image, Image &hough_image, vector<vector<int>> &accumulator, 
                    double delta_rho, double delta_theta){

    int img_height = binary_image.num_rows();
    int img_width = binary_image.num_columns();
    double max_distance = sqrt(img_height * img_height + img_width * img_width); // Max rho length.

    int rho_bins = static_cast<int>(2 * max_distance / delta_rho) + 1; // Rho sampling
    int theta_bins = static_cast<int>(M_PI / delta_theta); // Theta sampling

    // Initialize accumulator array with zeros
    accumulator.assign(theta_bins, vector<int>(rho_bins, 0)); 

    for(int row = 0; row < img_height; ++row){
        for(int col = 0; col < img_width; ++col){
            if(binary_image.GetPixel(row, col) != 0){ // Check if pixel is part of the edge
                // Loop over theta bins
                for(int theta_index = 0; theta_index < theta_bins; ++theta_index){
                    double theta = theta_index * delta_theta; // Current theta value

                    // Calculate rho
                    double rho = row * cos(theta) + col * sin(theta);
                    
                    // Map rho to the nearest bin index
                    int rho_index = static_cast<int>((rho + max_distance) / delta_rho);

                    if(rho_index >= 0 && rho_index < rho_bins){
                        accumulator[theta_index][rho_index]++; // Increment the accumulator
                    }
                }  
            }
        }
    }

    int max_votes = 0;
    // Locate maximum vote count
    for(int theta_index = 0; theta_index < theta_bins; ++theta_index){
        for(int rho_index = 0; rho_index < rho_bins; ++rho_index){
            if(accumulator[theta_index][rho_index] > max_votes){
                max_votes = accumulator[theta_index][rho_index];
            }
        }
    }

    // Create the Hough image based on votes
    for(int theta_index = 0; theta_index < theta_bins; ++theta_index){
        for(int rho_index = 0; rho_index < rho_bins; ++rho_index){
            // Scale votes to fit gray level
            int gray_level = (max_votes > 0) ? static_cast<int>(255.0 * accumulator[theta_index][rho_index] / max_votes) : 0;
            hough_image.SetPixel(theta_index, rho_index, gray_level);
        }
    }
}

int main(int argc, char* argv[]){
    if (argc != 4) {
        printf("Usage: %s {input binary edge image} {output gray-level Hough image} {output Hough-voting array}\n", argv[0]);
        return 0;  
    }

    const string binary_file(argv[1]); // Input binary image
    const string hough_out_file(argv[2]); // Output Hough image
    const string accumulator_file(argv[3]); // Output accumulator array

    // Load input image
    Image binary_image;
    if (!ReadImage(binary_file, &binary_image)) {
        cout << "Unable to open file " << binary_file << endl;
        return 0;
    }

    // Hough Transform parameters
    double delta_rho = 1.0;
    double delta_theta = M_PI / 180;

    int img_height = binary_image.num_rows();
    int img_width = binary_image.num_columns();
    double max_distance = sqrt(img_height * img_height + img_width * img_width);

    int rho_bins = static_cast<int>(2 * max_distance / delta_rho) + 1;
    int theta_bins = static_cast<int>(M_PI / delta_theta);

    // Set up Hough image
    Image hough_image;
    hough_image.AllocateSpaceAndSetSize(theta_bins, rho_bins);
    hough_image.SetNumberGrayLevels(255);

    vector<vector<int>> accumulator;
    accumulator.assign(theta_bins, vector<int>(rho_bins, 0));

    HoughTransform(binary_image, hough_image, accumulator, delta_rho, delta_theta);

    // Save Hough image
    if(!WriteImage(hough_out_file, hough_image)){
        cout << "Unable to save to file " << hough_out_file << endl;
        return 0;
    }

    // Save accumulator array
    ofstream accumulator_output(accumulator_file);
    if (!accumulator_output) {
        cout << "Unable to open file " << accumulator_file << endl;
        return 0;
    }

    for(int theta_index = 0; theta_index < accumulator.size(); ++theta_index){
        for(int rho_index = 0; rho_index < accumulator[theta_index].size(); ++rho_index){
            accumulator_output << accumulator[theta_index][rho_index] << " ";
        }
        accumulator_output << endl; 
    }

    accumulator_output.close();

    return 0;
}

