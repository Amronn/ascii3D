#include <iostream>
#include <CImg.h>
#include <fstream>
#include <vector>


template<typename T>
class Matrix
{
    public:
        std::vector<T> matrix;

    Matrix(std::vector<std::vector<T>> matrix){
        this.matrix = matrix;
    }

};


struct size
{
    int width;
    int length;
};

int main() {

    const static size screen_size = {60,40};

    std::vector<std::vector<char>> matrix(screen_size.width, std::vector<char>(screen_size.length, '*'));

    for (auto& vec : matrix)
    {
        for(char el: vec)
        {
            std::cout<< el <<" ";
        }
        std::cout<<std::endl;
    }
    return 0;
}