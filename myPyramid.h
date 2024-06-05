#ifndef MYPYRAMID_H_INCLUDED
#define MYPYRAMID_H_INCLUDED

// myPyramidVertices - homogeniczne wsp�rz�dne wierzcho�k�w w przestrzeni modelu
// myPyramidNormals - homogeniczne wektory normalne �cian (per wierzcho�ek) w przestrzeni modelu
// myPyramidVertexNormals - homogeniczne wektory normalne wierzcho�k�w w przestrzeni modelu
// myPyramidTexCoords - wsp�rz�dne teksturowania
// myPyramidColors - kolory wierzcho�k�w
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

    // �ciana 1 (bok, zwi�kszona wysoko��)
    -0.5f, 0.0f, -0.5f, 1.0f,
     0.5f, 0.0f, -0.5f, 1.0f,
     0.0f, 2.0f,  0.0f, 1.0f,

     // �ciana 2 (bok, zwi�kszona wysoko��)
      0.5f, 0.0f, -0.5f, 1.0f,
      0.5f, 0.0f,  0.5f, 1.0f,
      0.0f, 2.0f,  0.0f, 1.0f,

      // �ciana 3 (bok, zwi�kszona wysoko��)
       0.5f, 0.0f,  0.5f, 1.0f,
      -0.5f, 0.0f,  0.5f, 1.0f,
       0.0f, 2.0f,  0.0f, 1.0f,

       // �ciana 4 (bok, zwi�kszona wysoko��)
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

    // �ciany boczne (kolor zielony)
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
    // Podstawa (normale do do�u)
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,
    0.0f, -1.0f, 0.0f, 0.0f,

    // �ciany boczne
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

    // �ciany boczne
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

    // �ciany boczne
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

    // �ciany boczne
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

    // �ciany boczne
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

    // �ciany boczne
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
