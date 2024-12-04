#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Image
{
    public:
        int width;
        int height;
        int*** image;

        void parsePNM (std::string filename)
        {
            std::ifstream inputFile;
            std::string line;
            std::string magicNumber;
            int pixelValue;
            int maxval;
            
            inputFile.open(filename);
            if (!inputFile)
            {
                std::cout << "Nie znaleziono pliku " << filename << std::endl;
            }

            std::getline(inputFile, magicNumber);
            while (std::getline(inputFile, line)) {
                if (line[0] == '#') continue;
                std::istringstream dimensions(line);
                dimensions >> width >> height;
                break;
            }

            if (magicNumber == "P2" || magicNumber == "P3")
            {
                while (std::getline(inputFile, line)) {
                    if (line[0] == '#') continue;
                    std::istringstream maxvalue(line);
                    maxvalue >> maxval;
                    break;
                }
            }

            image = new int**[height];
            for (int row = 0; row < height; row++)
            {
                image[row] = new int*[width];
                for (int col = 0; col < width; col++)
                {
                    image[row][col] = new int[3];
                    inputFile >> pixelValue;
                    if (magicNumber == "P1")
                    {
                        if (pixelValue == 1)
                        {
                            image[row][col][0] = 255;
                            image[row][col][1] = 255;
                            image[row][col][2] = 255;
                        }
                        else
                        {
                            image[row][col][0] = 0;
                            image[row][col][1] = 0;
                            image[row][col][2] = 0;
                        }
                    }
                    if (magicNumber == "P2")
                    {
                        image[row][col][0] = 255 * pixelValue / maxval;
                        image[row][col][1] = 255 * pixelValue / maxval;
                        image[row][col][2] = 255 * pixelValue / maxval;
                    }
                    if (magicNumber == "P3")
                    {
                        image[row][col][0] = 255 * pixelValue / maxval;
                        inputFile >> pixelValue;
                        image[row][col][1] = 255 * pixelValue / maxval;
                        inputFile >> pixelValue;
                        image[row][col][2] = 255 * pixelValue / maxval;
                    }
                }
            }

            inputFile.close();
        }

        void printImage()
        {
            for (int row = 0; row < height; row++)
            {
                for (int col = 0; col < width; col++)
                {
                    std::cout << image[row][col][0] << "," << image[row][col][1] << "," << image[row][col][2] << " ";
                }
                std::cout << std::endl;
            }
        }
};

int main()
{
    std::string filename = "plik.ppm";
    Image obraz;
    obraz.parsePNM(filename);
    obraz.printImage();
    return 0;
}