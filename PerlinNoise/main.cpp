#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "SmoothingFunctions.h"

#include "Image.h"
#include "PGMWriter.h"
#include "PerlinNoiseGenerator.h"
#include "Util.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    // Default values
    size_t imageWidth = 1000;
    size_t imageHeight = 1000;
    double cellSize = 50;
    int seed = 0;
    fs::path outputFile;
    std::string smoothingFunctionName = "cubic";

    // Parse command-line arguments
    Util::parse_pargs(argc, argv, imageWidth, imageHeight, cellSize, seed, outputFile, smoothingFunctionName);

    const std::string fileName = std::string("perlinNoise_") + std::to_string(seed) + "_" + smoothingFunctionName + ".pgm";
    outputFile = fs::path(PROJECT_SOURCE_DIR) / "output" / fileName;

    std::cout << "image_width = " << imageWidth << std::endl;
    std::cout << "image_height = " << imageHeight << std::endl;
    std::cout << "cellSize = " << cellSize << std::endl;
    std::cout << "seed = " << seed << std::endl;
    std::cout << "smoothing_function = " << smoothingFunctionName << std::endl;
    std::cout << "outputFile = " << outputFile << std::endl;

    // Map function names to actual smoothing functions
    std::unordered_map<std::string, std::function<double(double)>> smoothingFunctions = {
        {"cubic", smoothCubic},
        {"constant", constantD},
        {"sin", smoothSin},
        {"smoother", smootherCubic}
    };

    // Select the smoothing function
    auto smoothFnIt = smoothingFunctions.find(smoothingFunctionName);
    if (smoothFnIt == smoothingFunctions.end()) {
        std::cerr << "Error: Unknown smoothing function '" << smoothingFunctionName << "'\n";
        std::cerr << "Available options: cubic, smoother, sin, constant\n";
        std::cerr << "Using cubic method as default.\n";
        return 1;
    }
    auto selectedSmoothFn = smoothFnIt->second;

    // Initialize PerlinNoiseGenerator with the selected smoothing function
    auto gridWidth = static_cast<size_t>(imageWidth / cellSize);
    auto gridHeight = static_cast<size_t>(imageHeight / cellSize);
    PerlinNoiseGenerator perlin(gridWidth, gridHeight, seed, selectedSmoothFn);

    // Generate the Perlin noise image
    Image image(imageWidth, imageHeight);
    for (int y = 0; y < imageHeight; ++y) {
        for (int x = 0; x < imageWidth; ++x) {
            double px = static_cast<double>(x) / cellSize;
            double py = static_cast<double>(y) / cellSize;
            double noise = perlin.eval(Vector2d(px, py));

            // Map noise from [-1, 1] to grayscale [0, 255]
            auto color = static_cast<uint8_t>((noise + 1.0) * 0.5 * 255);

            // Set the pixel color
            image.at(x, y) = color;
        }
    }

    // Save the image to a file
    PGMWriter::write(outputFile, image);

    return 0;
}