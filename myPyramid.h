#ifndef MYPYRAMID_H_INCLUDED
#define MYPYRAMID_H_INCLUDED

// myPyramidVertices - homogeniczne wspó³rzêdne wierzcho³ków w przestrzeni modelu
// myPyramidNormals - homogeniczne wektory normalne œcian (per wierzcho³ek) w przestrzeni modelu
// myPyramidVertexNormals - homogeniczne wektory normalne wierzcho³ków w przestrzeni modelu
// myPyramidTexCoords - wspó³rzêdne teksturowania
// myPyramidColors - kolory wierzcho³ków
// myPyramidC1 - kolumna macierzy TBN^-1
// myPyramidC2 - kolumna macierzy TBN^-1
// myPyramidC3 - kolumna macierzy TBN^-1

int myPyramidVertexCount = 18;

float myPyramidVertices[] = {
    // Podstawa (zmniejszona)
    -0.5f, 0.0f, -0.5f, 1.0f,
     0.5f, 0.0f, -0.5f, 1.0f,
     0.5f, 0.0f,  0.5f, 1.0f,
    -0.5f, 0.0f, -0.5f, 1.0f,
     0.5f, 0.0f,  0.5f, 1.0f,
    -0.5f, 0.0f,  0.5f, 1.0f,

    // Œciana 1 (bok, zwiêkszona wysokoœæ)
    -0.5f, 0.0f, -0.5f, 1.0f,
     0.5f, 0.0f, -0.5f, 1.0f,
     0.0f, 2.0f,  0.0f, 1.0f,

     // Œciana 2 (bok, zwiêkszona wysokoœæ)
      0.5f, 0.0f, -0.5f, 1.0f,
      0.5f, 0.0f,  0.5f, 1.0f,
      0.0f, 2.0f,  0.0f, 1.0f,

      // Œciana 3 (bok, zwiêkszona wysokoœæ)
       0.5f, 0.0f,  0.5f, 1.0f,
      -0.5f, 0.0f,  0.5f, 1.0f,
       0.0f, 2.0f,  0.0f, 1.0f,

       // Œciana 4 (bok, zwiêkszona wysokoœæ)
       -0.5f, 0.0f,  0.5f, 1.0f,
       -0.5f, 0.0f, -0.5f, 1.0f,
        0.0f, 2.0f,  0.0f, 1.0f
};

float myPyramidColors[] = {
    // Podstawa (kolor czerwony)
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    // Œciany boczne (kolor zielony)
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f
};

float myPyramidNormals[] = {
    // Podstawa (normale do do³u)
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,

    // Œciany boczne
    -0.577f, 0.577f, -0.577f, 0.0f,
    -0.577f, 0.577f, -0.577f, 0.0f,
    -0.577f, 0.577f, -0.577f, 0.0f,

    0.577f, 0.577f, -0.577f, 0.0f,
    0.577f, 0.577f, -0.577f, 0.0f,
    0.577f, 0.577f, -0.577f, 0.0f,

    0.577f, 0.577f, 0.577f, 0.0f,
    0.577f, 0.577f, 0.577f, 0.0f,
    0.577f, 0.577f, 0.577f, 0.0f,

    -0.577f, 0.577f, 0.577f, 0.0f,
    -0.577f, 0.577f, 0.577f, 0.0f,
    -0.577f, 0.577f, 0.577f, 0.0f
};

float myPyramidVertexNormals[] = {
    // Podstawa
    -0.5f, 0.0f, -0.5f, 0.0f,
     0.5f, 0.0f, -0.5f, 0.0f,
     0.5f, 0.0f,  0.5f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0.0f,
     0.5f, 0.0f,  0.5f, 0.0f,
    -0.5f, 0.0f,  0.5f, 0.0f,

    // Œciany boczne
    -0.5f, 0.0f, -0.5f, 0.0f,
     0.5f, 0.0f, -0.5f, 0.0f,
     0.0f, 2.0f,  0.0f, 0.0f,

     0.5f, 0.0f, -0.5f, 0.0f,
     0.5f, 0.0f,  0.5f, 0.0f,
     0.0f, 2.0f,  0.0f, 0.0f,

     0.5f, 0.0f,  0.5f, 0.0f,
    -0.5f, 0.0f,  0.5f, 0.0f,
     0.0f, 2.0f,  0.0f, 0.0f,

    -0.5f, 0.0f,  0.5f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0.0f,
     0.0f, 2.0f,  0.0f, 0.0f
};

float myPyramidTexCoords[] = {
    // Podstawa
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    // Œciany boczne
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f
};

float myPyramidC1[] = {
    // Podstawa
    1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f, 0.0f,

    // Œciany boczne
    -0.707f, 0.0f, 0.707f, 0.0f,
    -0.707f, 0.0f, 0.707f, 0.0f,
    -0.707f, 0.0f, 0.707f, 0.0f,

    0.707f, 0.0f, 0.707f, 0.0f,
    0.707f, 0.0f, 0.707f, 0.0f,
    0.707f, 0.0f, 0.707f, 0.0f,

    0.707f, 0.0f, -0.707f, 0.0f,
    0.707f, 0.0f, -0.707f, 0.0f,
    0.707f, 0.0f, -0.707f, 0.0f,

    -0.707f, 0.0f, -0.707f, 0.0f,
    -0.707f, 0.0f, -0.707f, 0.0f,
    -0.707f, 0.0f, -0.707f, 0.0f
};

float myPyramidC2[] = {
    // Podstawa
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,

    // Œciany boczne
    0.0f, 0.707f, 0.707f, 0.0f,
    0.0f, 0.707f, 0.707f, 0.0f,
    0.0f, 0.707f, 0.707f, 0.0f,

    0.0f, 0.707f, 0.707f, 0.0f,
    0.0f, 0.707f, 0.707f, 0.0f,
    0.0f, 0.707f, 0.707f, 0.0f,

    0.0f, 0.707f, 0.707f, 0.0f,
    0.0f, 0.707f, 0.707f, 0.0f,
    0.0f, 0.707f, 0.707f, 0.0f,

    0.0f, 0.707f, 0.707f, 0.0f,
    0.0f, 0.707f, 0.707f, 0.0f,
    0.0f, 0.707f, 0.707f, 0.0f
};

float myPyramidC3[] = {
    // Podstawa
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,

    // Œciany boczne
    -0.707f, -0.707f, 0.0f, 0.0f,
    -0.707f, -0.707f, 0.0f, 0.0f,
    -0.707f, -0.707f, 0.0f, 0.0f,

    0.707f, -0.707f, 0.0f, 0.0f,
    0.707f, -0.707f, 0.0f, 0.0f,
    0.707f, -0.707f, 0.0f, 0.0f,

    0.707f, -0.707f, 0.0f, 0.0f,
    0.707f, -0.707f, 0.0f, 0.0f,
    0.707f, -0.707f, 0.0f, 0.0f,

    -0.707f, -0.707f, 0.0f, 0.0f,
    -0.707f, -0.707f, 0.0f, 0.0f,
    -0.707f, -0.707f, 0.0f, 0.0f
};

#endif // MYPYRAMID_H_INCLUDED
