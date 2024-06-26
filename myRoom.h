#ifndef MYROOM_H_INCLUDED
#define MYROOM_H_INCLUDED


//myRoomVertices - homogeniczne współrzędne wierzchołków w przestrzeni modelu
//myRoomNormals - homogeniczne wektory normalne ścian (per wierzchołek) w przestrzeni modelu
//myRoomVertexNormals - homogeniczne wektory normalne wierzchołków w przestrzeni modelu
//myRoomTexCoords - współrzędne teksturowania
//myRoomColors - kolory wierzchołków
//myRoomC1 - kolumna macierzy TBN^-1
//myRoomC2 - kolumna macierzy TBN^-1
//myRoomC3 - kolumna macierzy TBN^-1

int myRoomVertexCount=36;


glm::vec4 myRoomWallPlanes[5] = {
	// Ściana 2
	glm::vec4(0.0f, 0.0f, -1.0f, 1.0f),

	// Ściana 3
	glm::vec4(0.0f, 1.0f, 0.0f, -1.0f),

	// Ściana 4
	glm::vec4(0.0f, -1.0f, 0.0f, -1.0f),

	// Ściana 5
	glm::vec4(1.0f, 0.0f, 0.0f, -1.0f),

	// Ściana 6
	glm::vec4(-1.0f, 0.0f, 0.0f, 1.0f)
};



float myRoomVertices[]={

                //Ściana 2
				-1.0f,-1.0f, 1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,
				1.0f,-1.0f, 1.0f,1.0f,

				-1.0f,-1.0f, 1.0f,1.0f,
				-1.0f, 1.0f, 1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,


				//Ściana 3
				-1.0f,-1.0f,-1.0f,1.0f,
				1.0f,-1.0f, 1.0f,1.0f,
				1.0f,-1.0f,-1.0f,1.0f,

				-1.0f,-1.0f,-1.0f,1.0f,
				-1.0f,-1.0f, 1.0f,1.0f,
				1.0f,-1.0f, 1.0f,1.0f,

				//Ściana 4
				-1.0f, 1.0f, 1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,

				-1.0f, 1.0f, 1.0f,1.0f,
				-1.0f, 1.0f,-1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,

				//Ściana 5
				-1.0f,-1.0f,-1.0f,1.0f,
				-1.0f, 1.0f, 1.0f,1.0f,
				-1.0f,-1.0f, 1.0f,1.0f,

				-1.0f,-1.0f,-1.0f,1.0f,
				-1.0f, 1.0f,-1.0f,1.0f,
				-1.0f, 1.0f, 1.0f,1.0f,

                //Ściana 6
				1.0f,-1.0f, 1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,
				1.0f,-1.0f,-1.0f,1.0f,

				1.0f,-1.0f, 1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,




			};


float myRoomColors[]={


				//Ściana 2
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,

				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,

				//Ściana 3
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,

				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,

				//Ściana 4
				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f,

				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f,

				//Ściana 5
				0.0f,1.0f,1.0f,1.0f,
				0.0f,1.0f,1.0f,1.0f,
				0.0f,1.0f,1.0f,1.0f,

				0.0f,1.0f,1.0f,1.0f,
				0.0f,1.0f,1.0f,1.0f,
				0.0f,1.0f,1.0f,1.0f,

				//Ściana 6
				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,

				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,
			};

float myRoomNormals[] = {
	// Ściana 2 (front)
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,

	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,
	0.0f, 0.0f, -1.0f, 0.0f,

	// Ściana 3 (bottom)
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,

	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,

	// Ściana 4 (top)
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,

	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,
	0.0f, -1.0f, 0.0f, 0.0f,

	// Ściana 5 (left)
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f, 0.0f,

	// Ściana 6 (right)
	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,

	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f, 0.0f,
};

float myRoomVertexNormals[] = {
	// Ściana 2 (front)
	-1.0f, -1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, -1.0f, 0.0f,

	-1.0f, -1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, -1.0f, 0.0f,

	// Ściana 3 (bottom)
	-1.0f, 1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, -1.0f, 0.0f,

	-1.0f, 1.0f, -1.0f, 0.0f,
	-1.0f, 1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 0.0f,

	// Ściana 4 (top)
	-1.0f, -1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 0.0f,

	-1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, -1.0f, 0.0f,

	// Ściana 5 (left)
	1.0f, -1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 0.0f,
	1.0f, -1.0f, 1.0f, 0.0f,

	1.0f, -1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, -1.0f, 0.0f,
	1.0f, 1.0f, 1.0f, 0.0f,

	// Ściana 6 (right)
	-1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, -1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f, 0.0f,

	-1.0f, -1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, -1.0f, 0.0f,
};

			float myRoomTexCoords[]={

				//Ściana 2
				1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
				1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

				//Ściana 3
				1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
				1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

				//Ściana 4
				1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
				1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

				//Ściana 5
				1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
				1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,

				//Ściana 6
				1.0f,1.0f, 0.0f,0.0f, 0.0f,1.0f,
				1.0f,1.0f, 1.0f,0.0f, 0.0f,0.0f,
			};

			float myRoomC1[] = {

				//Ściana 2
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,

				//Ściana 3
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				//Ściana 4
				-1.000000f,0.000000f,-0.000000f,0.000000f,
				-1.000000f,0.000000f,-0.000000f,0.000000f,
				-1.000000f,0.000000f,-0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,

				//Ściana 5
				0.000000f,-0.000000f,-1.000000f,0.000000f,
				0.000000f,-0.000000f,-1.000000f,0.000000f,
				0.000000f,-0.000000f,-1.000000f,0.000000f,
				0.000000f,-0.000000f,-1.000000f,0.000000f,
				0.000000f,-0.000000f,-1.000000f,0.000000f,
				0.000000f,-0.000000f,-1.000000f,0.000000f,

				//Ściana 6
				0.000000f,0.000000f,1.000000f,0.000000f,
				0.000000f,0.000000f,1.000000f,0.000000f,
				0.000000f,0.000000f,1.000000f,0.000000f,
				0.000000f,-0.000000f,1.000000f,0.000000f,
				0.000000f,-0.000000f,1.000000f,0.000000f,
				0.000000f,-0.000000f,1.000000f,0.000000f,

			};
			float myRoomC2[] = {

				//Ściana 2
				-0.000000f,-1.000000f,-0.000000f,0.000000f,
				-0.000000f,-1.000000f,-0.000000f,0.000000f,
				-0.000000f,-1.000000f,-0.000000f,0.000000f,
				-0.000000f,-1.000000f,-0.000000f,0.000000f,
				-0.000000f,-1.000000f,-0.000000f,0.000000f,
				-0.000000f,-1.000000f,-0.000000f,0.000000f,

				//Ściana 3
				-0.000000f,0.000000f,-1.000000f,0.000000f,
				-0.000000f,0.000000f,-1.000000f,0.000000f,
				-0.000000f,0.000000f,-1.000000f,0.000000f,
				-0.000000f,0.000000f,-1.000000f,0.000000f,
				-0.000000f,0.000000f,-1.000000f,0.000000f,
				-0.000000f,0.000000f,-1.000000f,0.000000f,
				//Ściana 4
				-0.000000f,0.000000f,1.000000f,0.000000f,
				-0.000000f,0.000000f,1.000000f,0.000000f,
				-0.000000f,0.000000f,1.000000f,0.000000f,
				0.000000f,0.000000f,1.000000f,0.000000f,
				0.000000f,0.000000f,1.000000f,0.000000f,
				0.000000f,0.000000f,1.000000f,0.000000f,

				//Ściana 5
				-0.000000f,-1.000000f,0.000000f,0.000000f,
				-0.000000f,-1.000000f,0.000000f,0.000000f,
				-0.000000f,-1.000000f,0.000000f,0.000000f,
				0.000000f,-1.000000f,-0.000000f,0.000000f,
				0.000000f,-1.000000f,-0.000000f,0.000000f,
				0.000000f,-1.000000f,-0.000000f,0.000000f,
				//Ściana 6
				-0.000000f,-1.000000f,-0.000000f,0.000000f,
				-0.000000f,-1.000000f,-0.000000f,0.000000f,
				-0.000000f,-1.000000f,-0.000000f,0.000000f,
				-0.000000f,-1.000000f,-0.000000f,0.000000f,
				-0.000000f,-1.000000f,-0.000000f,0.000000f,
				-0.000000f,-1.000000f,-0.000000f,0.000000f,

			};
			float myRoomC3[] = {

				//Ściana 2
				0.000000f,-0.000000f,1.000000f,0.000000f,
				0.000000f,-0.000000f,1.000000f,0.000000f,
				0.000000f,-0.000000f,1.000000f,0.000000f,
				0.000000f,-0.000000f,1.000000f,0.000000f,
				0.000000f,-0.000000f,1.000000f,0.000000f,
				0.000000f,-0.000000f,1.000000f,0.000000f,

				//Ściana 3
				0.000000f,-1.000000f,0.000000f,0.000000f,
				0.000000f,-1.000000f,0.000000f,0.000000f,
				0.000000f,-1.000000f,0.000000f,0.000000f,
				0.000000f,-1.000000f,0.000000f,0.000000f,
				0.000000f,-1.000000f,0.000000f,0.000000f,
				0.000000f,-1.000000f,0.000000f,0.000000f,
				//Ściana 4
				0.000000f,1.000000f,0.000000f,0.000000f,
				0.000000f,1.000000f,0.000000f,0.000000f,
				0.000000f,1.000000f,0.000000f,0.000000f,
				0.000000f,1.000000f,0.000000f,0.000000f,
				0.000000f,1.000000f,0.000000f,0.000000f,
				0.000000f,1.000000f,0.000000f,0.000000f,


				//Ściana 5
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,
				-1.000000f,-0.000000f,0.000000f,0.000000f,

				//Ściana 6
				1.000000f,-0.000000f,0.000000f,0.000000f,
				1.000000f,-0.000000f,0.000000f,0.000000f,
				1.000000f,-0.000000f,0.000000f,0.000000f,
				1.000000f,-0.000000f,0.000000f,0.000000f,
				1.000000f,-0.000000f,0.000000f,0.000000f,
				1.000000f,-0.000000f,0.000000f,0.000000f,


			};



#endif // MYROOM_H_INCLUDED
