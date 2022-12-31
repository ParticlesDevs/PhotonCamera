//
// Created by troop on 03.03.2018.
//

#ifndef FREEDCAM_CUSTOMMATRIX_H
#define FREEDCAM_CUSTOMMATRIX_H

class CustomMatrix
{
public:
    float *colorMatrix1;
    float *colorMatrix2;
    float *neutralColorMatrix;
    float *fowardMatrix1;
    float *fowardMatrix2;
    float *reductionMatrix1;
    float *reductionMatrix2;
    double *noiseMatrix;

    CustomMatrix()
    {
        colorMatrix1 = nullptr;
        colorMatrix2 = nullptr;
        neutralColorMatrix = nullptr;
        fowardMatrix1 = nullptr;
        fowardMatrix2 = nullptr;
        reductionMatrix1 = nullptr;
        reductionMatrix2 = nullptr;
        noiseMatrix = nullptr;
    }

    void clear()
    {
        if(colorMatrix1 != nullptr)
        {
            delete[] colorMatrix1;
            colorMatrix1 = nullptr;
        }
        if(colorMatrix2 != nullptr)
        {
            delete[] colorMatrix2;
            colorMatrix2 = nullptr;
        }
        if(neutralColorMatrix != nullptr)
        {
            delete[] neutralColorMatrix;
            neutralColorMatrix = nullptr;
        }
        if(fowardMatrix1 != nullptr)
        {
            delete[] fowardMatrix1;
            fowardMatrix1 = nullptr;
        }
        if(fowardMatrix2 != nullptr)
        {
            delete[] fowardMatrix2;
            fowardMatrix2 = nullptr;
        }
        if(reductionMatrix1 != nullptr)
        {
            delete[] reductionMatrix1;
            reductionMatrix1 = nullptr;
        }
        if(reductionMatrix2 != nullptr)
        {
            delete[] reductionMatrix2;
            reductionMatrix2 = nullptr;
        }
        if(reductionMatrix2 != nullptr)
        {
            delete[] reductionMatrix2;
            reductionMatrix2 = nullptr;
        }
        if(noiseMatrix != nullptr)
        {
            delete[] noiseMatrix;
            noiseMatrix = nullptr;
        }
    }
};

#endif //FREEDCAM_CUSTOMMATRIX_H
