#include <iostream>
#include <vector>
#include <string>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myCube.h"
#include "myRoom.h"
#include <glm/gtc/type_ptr.hpp>
#include "myPyramid.h"
#include <algorithm>


using namespace rapidxml;

#include <map>
#include <random>

std::map<int, GLuint> allTextures;
std::map<std::string, GLuint> placeTextures;
std::map<std::string, GLuint> placeMarkings;
std::map<std::string, GLuint> transitionTextures;

glm::mat4 lightSpaceMatrix;
//glm::mat4 M = glm::mat4(1.0f);


GLuint tex0;

float speed_x = 0;
float speed_y = 0;
float aspectRatio = 1;

float camfr = 0;
float camlr = 0;
float camud = 0;
float s = 0;
int animate = 0;
float biggify = 1;
float biggify2 = 1;
float expand = 1;
int texmode = 0;

int file_num = 1;


int current_place_index = 0;

int switchplace = 0;

float begining_x = 0.0f;
float begining_y = 0.0f;
float changing_x = 0.0f;
float changing_y = 0.0f;


glm::vec4 lightDir1 = glm::vec4(-1.0f, 1.0f, 0.0f, 0.0f); 
glm::vec4 lightDir2 = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);  
glm::vec4 lightColor1 = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f); 
glm::vec4 lightColor2 = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);

struct Transition {
    float x, y;
    std::string type;
    std::string ID;
};


struct Edge {
    float startX, startY;
    float endX, endY;
    int source, target;
    std::string multiplicity;
};


struct Place {
    float x, y;
    std::string marking;
    std::string ID;

    std::string getMarking() const {
        return marking;
    }

    void setMarking(const std::string& newMarking) {
        marking = newMarking;
    }
};

std::vector<Place> places;
std::vector<Transition> transitions;
std::vector<Edge> edges;

float* cVertices = myCubeVertices;
float* cNormals = myCubeNormals;
float* cTexCoords = myCubeTexCoords;
float* cColors = myCubeColors;
int cVertexCount = myCubeVertexCount;


float* pVertices = myPyramidVertices;
float* pNormals = myPyramidNormals;
float* pTexCoords = myPyramidTexCoords;
float* pColors = myPyramidColors;
int pVertexCount = myPyramidVertexCount;


void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void drawCube(float x, float y) {
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(x, y, 0.0f)); 
    M = glm::scale(M, glm::vec3(0.6, 0.6, 0.6) * biggify);
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

    glEnableVertexAttribArray(spTextured->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
    glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, cVertices); //Wska¿ tablicê z danymi dla atrybutu vertex

    glUniform4f(spTextured->u("color"), 0, 1, 0, 1);

    glDrawArrays(GL_TRIANGLES, 0, cVertexCount); //Narysuj obiekt

}

struct AnimationState {
    float progress;
    glm::vec2 startPos;
    glm::vec2 endPos;
    size_t currentEdgeIndex;
    bool isAnimating;
    int typeofedge;

    AnimationState() : progress(0.0f), currentEdgeIndex(0), isAnimating(false), typeofedge(0) {}
};


AnimationState animationState;


void increaseMarking(const std::vector<Place>& places, int targetID,int markingcount) {
    for (auto it = places.begin(); it != places.end(); ++it) {
        if (std::stoi(it->ID) == targetID) {
            Place tempPlace = *it; 
            int newMarking = std::stoi(tempPlace.getMarking()) + markingcount;
            tempPlace.setMarking(std::to_string(newMarking));

            const_cast<Place&>(*it) = tempPlace;
            std::cout << "inc mark Wartoœæ targetID: " << targetID << std::endl;
           break;
        }
    }
}

void decreaseMarking(const std::vector<Place>& places, int sourceID) {
    for (auto it = places.begin(); it != places.end(); ++it) {
        if (std::stoi(it->ID) == sourceID) {
            Place tempPlace = *it; 
            int newMarking = std::max(0, std::stoi(tempPlace.getMarking()) - 1);
            tempPlace.setMarking(std::to_string(newMarking));
            const_cast<Place&>(*it) = tempPlace;
            std::cout << "dec mark Wartoœæ sourceID: " << sourceID << std::endl;
            break;
        }
    }
}

std::vector<int> validEdge(const std::vector<Edge>& edges, const std::vector<Place>& places) {
    std::vector<int> validEdgeIndices;

    for (size_t i = 0; i < edges.size(); ++i) {
        bool foundSourcePlace = false;
        for (const auto& place : places) {
            if (std::stoi(place.ID) == edges[i].source) {
                if (std::stoi(place.marking) > 0 && std::stoi(place.marking) >= std::stoi(edges[i].multiplicity)) {
                    foundSourcePlace = true;
                    break;
                }
            }
        }
        if (foundSourcePlace) {
            validEdgeIndices.push_back(i);
        }
    }

    std::cout << "validedge: ";
    for (const auto& index : validEdgeIndices) {
        std::cout << index << " ";
    }
    std::cout << std::endl;

    return validEdgeIndices;
}


std::vector<Edge> findAllEdgesWithSameSource(const std::vector<Edge>& edges, const AnimationState& animationState) {
    // Pobierz source z aktualnej krawêdzi animacji
    int currentSource = edges[animationState.currentEdgeIndex].target;
    std::cout << "Wartoœæ current source: " << currentSource << std::endl;

    // ZnajdŸ wszystkie krawêdzie, których source jest taki sam jak target aktualnej krawêdzi
    std::vector<Edge> matchingEdges;
    for (const auto& edge : edges) {
        if (edge.source == currentSource) {
            matchingEdges.push_back(edge);
        }
    }

    // Jeœli nie znaleziono ¿adnych pasuj¹cych krawêdzi, zwróæ pusty wektor
    if (matchingEdges.empty()) {
        return {};
    }

    // Zwróæ wszystkie pasuj¹ce krawêdzie
    return matchingEdges;
}


void moveCubeAlongEdge(const std::vector<Edge>& edges, const std::vector<Place>& places) {
    if (!animationState.isAnimating) return;

    const float animationSpeed = 0.01f; 

    if (animationState.typeofedge == 0) {
        std::vector<int> validEdgeIndices = validEdge(edges, places);

        if (validEdgeIndices.empty()) {
            animationState.isAnimating = false;
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(0, validEdgeIndices.size() - 1);
        int randomIndex = distr(gen);
        int chosenEdgeIndex = validEdgeIndices[randomIndex];
        animationState.currentEdgeIndex = chosenEdgeIndex;

        const Edge& currentEdge = edges[animationState.currentEdgeIndex];

        if (animationState.progress == 0.0f) {
            animationState.startPos = glm::vec2(currentEdge.startX / 20.0f * expand, currentEdge.startY / 20.0f * expand);
            animationState.endPos = glm::vec2(currentEdge.endX / 20.0f * expand, currentEdge.endY / 20.0f * expand);
        }

        glm::vec2 interpolatedPosition = animationState.startPos + animationState.progress * (animationState.endPos - animationState.startPos);

        float cubeX = interpolatedPosition.x;
        float cubeY = interpolatedPosition.y;

        drawCube(cubeX, cubeY);

        animationState.progress += animationSpeed;
        if (animationState.progress >= 1.0f) {
            animationState.progress = 0.0f;

            int sourceID = edges[animationState.currentEdgeIndex].source;
            decreaseMarking(places, sourceID);

            animationState.typeofedge = 1;

            validEdgeIndices = validEdge(edges, places);
            if (validEdgeIndices.empty()) {
                animationState.isAnimating = false;
                return;
            }

            
        }

    }

    if (animationState.typeofedge == 1) {
        std::vector<Edge> edgeData = findAllEdgesWithSameSource(edges, animationState);

        for (const auto& edge : edgeData) {

            const Edge& currentEdge = edge;

            if (animationState.progress == 0.0f) {
                animationState.startPos = glm::vec2(currentEdge.startX / 20.0f * expand, currentEdge.startY / 20.0f * expand);
                animationState.endPos = glm::vec2(currentEdge.endX / 20.0f * expand, currentEdge.endY / 20.0f * expand);
            }

            glm::vec2 interpolatedPosition = animationState.startPos + animationState.progress * (animationState.endPos - animationState.startPos);

            float cubeX = interpolatedPosition.x;
            float cubeY = interpolatedPosition.y;

            drawCube(cubeX, cubeY);

            animationState.progress += animationSpeed;
            if (animationState.progress >= 1.0f) {
                animationState.progress = 0.0f;

                int sourceID = currentEdge.source;
                int targetID = currentEdge.target;        

                increaseMarking(places, targetID, std::stoi(currentEdge.multiplicity) );

                animationState.typeofedge = 0; 
            }
        }
    }
}




void moveCameraTo(float x, float y) {
    // Oblicz odleg³oœæ, na jak¹ nale¿y przesun¹æ kamerê, aby ustawiæ j¹ w punkcie (x, y)
    float deltaX = x - (begining_x + changing_x + camlr);
    float deltaY = y - (begining_y + changing_y + camfr);

    // Przesuñ kamerê o obliczon¹ odleg³oœæ
    changing_x += deltaX;
    changing_y += deltaY;

    // Ustaw nowe wspó³rzêdne pocz¹tkowe
    begining_x = x;
    begining_y = y;
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_LEFT) {
        }
        if (key == GLFW_KEY_RIGHT) {
            // Zwiêkszenie indeksu, aby wskazywa³ na nastêpne miejsce
            switchplace = 1;
            current_place_index = (current_place_index + 1) % places.size();

            // Pobranie wspó³rzêdnych nastêpnego miejsca
            const auto& next_place = places[current_place_index];
            float place_x = (next_place.x / 20.0f) * expand;
            float place_y = (next_place.y / 20.0f) * expand;
            std::cout << "Place ID: " << places[current_place_index].ID << std::endl;
            // Przesuniêcie kamery do wspó³rzêdnych nastêpnego miejsca
            moveCameraTo(place_x, place_y);
        }
        if (key == GLFW_KEY_UP) {
        }
        if (key == GLFW_KEY_DOWN) {
            switchplace = 0;
        }
    }


    if (action == GLFW_REPEAT || action == GLFW_PRESS) {
        if (key == GLFW_KEY_A) {
            camlr -= 0.5f; 
        }
        if (key == GLFW_KEY_D) {
            camlr += 0.5f; 
        }
        if (key == GLFW_KEY_W) {
            camfr -= 0.5f; 
        }
        if (key == GLFW_KEY_S) {
            camfr += 0.5f;
        }
        if (key == GLFW_KEY_SPACE) {
            camud -= 0.5f;
        }
        if (key == GLFW_KEY_Z) {
            camud += 0.5f;
        }
    }

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_0) animate = 0;
        if (key == GLFW_KEY_1) animate = 1;
    }

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_2) file_num = 1;
        if (key == GLFW_KEY_3) file_num = 2;
    }

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_I) texmode = 0;
        if (key == GLFW_KEY_M) texmode = 1;
    }

    if (action == GLFW_REPEAT || action == GLFW_PRESS) {
        if (key == GLFW_KEY_EQUAL) biggify += 0.1f;
        if (key == GLFW_KEY_MINUS) biggify -= 0.1f;
        if (key == GLFW_KEY_PERIOD) biggify2 += 0.2f;
        if (key == GLFW_KEY_COMMA) biggify2 -= 0.2f;
        if (key == GLFW_KEY_PERIOD) expand +=0.1f;
        if (key == GLFW_KEY_COMMA) expand -= 0.1f;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

    if (yoffset > 0) {
        s += 1.0;
    }
    if (yoffset < 0) {
        s -= 1.0;
    }

}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
    if (height == 0) return;
    aspectRatio = (float)width / (float)height;
    glViewport(0, 0, width, height);
}

GLuint readTexture(const char* filename) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);
    std::vector<unsigned char> image; 
    unsigned width, height;
    //Wczytaj obrazek
    unsigned error = lodepng::decode(image, width, height, filename);
    //Import do pamiêci karty graficznej
    glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt

    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tex;
}

GLuint loadTextureForID(const std::string& ID) {
    std::string filename = "tex/" + ID + ".png"; 
    return readTexture(filename.c_str());
}

GLuint loadTextureForMarking(const std::string& marking) {
    std::string filename = "tex/" + marking + ".png";
    return readTexture(filename.c_str());
}


GLuint loadAllTextures(int i) {
    std::string filename = "tex/" + std::to_string(i) + ".png";
    return readTexture(filename.c_str());
}

GLuint shadowMapFBO;
GLuint shadowMapTexture;

void initShadowMap() {
    glGenFramebuffers(1, &shadowMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);

    glGenTextures(1, &shadowMapTexture);
    glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("Blad inicjalizacji shadow map: %d\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ShaderProgram* depthSP;



void drawShadowForPlace(glm::vec4 lightDir, const Place& element) {
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3((element.x / 20.0f) * expand, (element.y / 20.0f) * expand, 0.0f));
    M = glm::scale(M, glm::vec3(1, 1, 1) * -biggify);

    glm::vec3 lightPos = glm::vec3(lightDir);
    glm::mat4 lightView = glm::lookAt(glm::vec3((begining_x + camlr), begining_y + camfr, s + (-30.0f)),
        glm::vec3((begining_x + camlr), begining_y + camfr, s - 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));
    //glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f) * -0.5f;
    lightSpaceMatrix = lightProjection * lightView * M;

    glUniformMatrix4fv(depthSP->u("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
    //M = glm::scale(M, glm::vec3(0.0001f, 0.0001f, 0.0001f));
    glUniformMatrix4fv(depthSP->u("model"), 1, GL_FALSE, glm::value_ptr(M));

    glEnableVertexAttribArray(depthSP->a("vertex"));
    glVertexAttribPointer(depthSP->a("vertex"), 4, GL_FLOAT, false, 0, cVertices);

    glDrawArrays(GL_TRIANGLES, 0, cVertexCount);
}


void drawShadowForTransition(glm::vec4 lightDir, const Transition& element) {
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3((element.x / 20.0f) * expand, (element.y / 20.0f) * expand, 0.0f));
    M = glm::scale(M, glm::vec3(1, 1, 1) * -biggify);

    glm::vec3 lightPos = glm::vec3(lightDir);
    glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lightProjection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 1.0f, 7.5f) * 0.5f;

    lightSpaceMatrix = lightProjection * lightView * M;

    glUniformMatrix4fv(depthSP->u("lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
    glUniformMatrix4fv(depthSP->u("model"), 1, GL_FALSE, glm::value_ptr(M));

    glEnableVertexAttribArray(depthSP->a("vertex"));
    glVertexAttribPointer(depthSP->a("vertex"), 4, GL_FLOAT, false, 0, cVertices);

    glDrawArrays(GL_TRIANGLES, 0, cVertexCount);
}

void drawShadowMap(glm::vec4 lightDir, const std::vector<Place>& places, const std::vector<Transition>& transitions) {
    depthSP->use();
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    for (const auto& place : places) {
        drawShadowForPlace(lightDir, place);
    }

    for (const auto& transition : transitions) {
        drawShadowForTransition(lightDir, transition);
    }


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void initOpenGLProgram(GLFWwindow* window, const std::vector<Place>& places, const std::vector<Transition>& transitions) {
    initShaders();
    glClearColor(1, 1, 1, 1);
    glEnable(GL_DEPTH_TEST);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetScrollCallback(window, scroll_callback);

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    windowResizeCallback(window, width, height);
    initShadowMap();
    depthSP = new ShaderProgram("depth_vertex.glsl", NULL, "depth_fragment.glsl");

    for (int i = 0; i < 1000; i++) {
        allTextures[i] = loadAllTextures(i);
    }

    for (const auto& place : places) {
        placeTextures[place.ID] = allTextures[std::stoi(place.ID)];
        placeMarkings[place.ID] = allTextures[std::stoi(place.marking)];
    }

    for (const auto& transition : transitions) {
        transitionTextures[transition.ID] = allTextures[std::stoi(transition.ID)];
    }

    tex0 = readTexture("tex/blank.png");
}


void setCameraAtCenter(const std::vector<Place>& places, const std::vector<Transition>& transitions) {
    // ZnajdŸ najdalsze punkty na lewo, prawo, górê i dó³ wœród wszystkich obiektów
    float leftmost = std::numeric_limits<float>::max();
    float rightmost = std::numeric_limits<float>::min();
    float topmost = std::numeric_limits<float>::min();
    float bottommost = std::numeric_limits<float>::max();

    for (const auto& place : places) {
        leftmost = std::min(leftmost, place.x);
        rightmost = std::max(rightmost, place.x);
        topmost = std::max(topmost, place.y);
        bottommost = std::min(bottommost, place.y);
    }

    for (const auto& transition : transitions) {
        leftmost = std::min(leftmost, transition.x);
        rightmost = std::max(rightmost, transition.x);
        topmost = std::max(topmost, transition.y);
        bottommost = std::min(bottommost, transition.y);
    }

    // Oblicz œrodek zbioru obiektów
    float centerX = (leftmost / 20.0f + rightmost / 20.0f) / 2.0f;
    float centerY = (topmost / 20.0f + bottommost / 20.0f) / 2.0f;

    // Ustaw kamerê na œrodku zbioru obiektów
    begining_x = centerX;
    begining_y = centerY;
}

void drawRoom(glm::mat4 P, glm::mat4 V,float beg_x,float beg_y) {

    float maxDimension = std::max(std::max(std::abs(begining_x), std::abs(begining_y)), 1.0f);

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(begining_x*expand, begining_y*expand, 0.0f)); // Wylicz macierz modelu dla kostki

    // Dostosuj skalowanie kostki
    M = glm::scale(M, glm::vec3(1.0f * maxDimension, 1.0f * maxDimension, 1.0f * maxDimension)*(biggify*biggify2));


    glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P)); // Za³aduj do programu cieniuj¹cego macierz rzutowania
    glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V)); // Za³aduj do programu cieniuj¹cego macierz widoku
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M)); // Za³aduj do programu cieniuj¹cego macierz modelu
    glUniform4fv(spTextured->u("lightDir1"), 1, glm::value_ptr(lightDir1));
    glUniform4fv(spTextured->u("lightDir2"), 1, glm::value_ptr(lightDir2));
    glUniform4fv(spTextured->u("lightColor1"), 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)));
    glUniform4fv(spTextured->u("lightColor2"), 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)));
    glUniform1f(spTextured->u("lightIntensity"), 0.4f);
    glUniform1f(spTextured->u("kdFactor"), 0.4f);
    glUniform1f(spTextured->u("ksFactor"), 0.1f);


    glEnableVertexAttribArray(spTextured->a("vertex"));
    glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, myRoomVertices); // WspTexturedó³rzêdne wierzcho³ków bierz z tablicy myCubeVertices

    glEnableVertexAttribArray(spTextured->a("normal"));
    glVertexAttribPointer(spTextured->a("normal"), 4, GL_FLOAT, false, 0, myRoomNormals);

    glEnableVertexAttribArray(spTextured->a("texCoord"));
    glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, myRoomTexCoords); // WspTexturedó³rzêdne teksturowania bierz z tablicy myCubeTexCoords

    glUniform4f(spTextured->u("color"), 1, 1, 1, 1); 

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);
    glUniform1i(spTextured->u("tex"), 0);

    glDrawArrays(GL_TRIANGLES, 0, myRoomVertexCount);

    glDisableVertexAttribArray(spTextured->a("vertex"));
    glDisableVertexAttribArray(spTextured->a("normal"));
    glDisableVertexAttribArray(spTextured->a("color"));
}



void freeOpenGLProgram(GLFWwindow* window) {
    // Usuwanie tekstur z pamiêci karty graficznej
    glDeleteTextures(1, &tex0);
    for (auto& entry : allTextures) {
        glDeleteTextures(1, &entry.second);
    }
    for (auto& entry : placeTextures) {
        glDeleteTextures(1, &entry.second);
    }
    for (auto& entry : placeMarkings) {
        glDeleteTextures(1, &entry.second);
    }
    for (auto& entry : transitionTextures) {
        glDeleteTextures(1, &entry.second);
    }

    // Usuwanie Framebuffer Object
    glDeleteFramebuffers(1, &shadowMapFBO);

    // Usuwanie dynamicznie alokowanych obiektów
    delete spTextured;
    delete depthSP;

    // Opró¿nianie map
    allTextures.clear();
    placeTextures.clear();
    placeMarkings.clear();
    transitionTextures.clear();

    // Jeœli masz inne dynamicznie alokowane zasoby, usuñ je tutaj

    // Wywo³anie funkcji glfwTerminate do zakoñczenia dzia³ania GLFW
    glfwTerminate();
}



void drawPyramid() {
    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(0.0f, 0.0f, 0.0f)); // Wylicz macierz modelu dla piramidy

    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

    glEnableVertexAttribArray(spTextured->a("vertex"));
    glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, myCubeVertices); // WspTexturedó³rzêdne wierzcho³ków bierz z tablicy myCubeVertices

    glEnableVertexAttribArray(spTextured->a("texCoord"));
    glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, myCubeTexCoords); // WspTexturedó³rzêdne teksturowania bierz z tablicy myCubeTexCoords

    glUniform4f(spTextured->u("color"), 0, 0, 0, 1); // Ustaw kolor na zielony

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);
    glUniform1i(spTextured->u("tex"), 0);

    glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);

    glDisableVertexAttribArray(spTextured->a("vertex"));
    glDisableVertexAttribArray(spTextured->a("color"));
}

void drawPyramidOnEdge(const Edge& edge, const glm::vec2& startPos, const glm::vec2& endPos) {
    glm::vec2 middlePoint = ((startPos + endPos) / 2.0f);
    glm::vec2 direction = glm::normalize(endPos - startPos);
    float angle = atan2(direction.y, direction.x);

    glm::mat4 M = glm::mat4(1.0f);
    M = glm::translate(M, glm::vec3(middlePoint, 0.0f)); // Przenieœ do œrodkowego punktu krawêdzi
    M = glm::rotate(M, angle - PI / 2, glm::vec3(0, 0, 1)); // Obrót tak, aby czubek piramidy wskazywa³ cel
    M = glm::scale(M, glm::vec3(0.5, 0.5, 1)*biggify);
    glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

    glEnableVertexAttribArray(spTextured->a("vertex"));  // W³¹cz przesy³anie danych do atrybutu vertex
    glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, pVertices); // Wska¿ tablicê z danymi dla atrybutu vertex

    // Ustaw kolor na niebieski
    glUniform4f(spTextured->u("color"), 0, 0, 1, 1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex0);
    glUniform1i(spTextured->u("tex"), 0);

    glDrawArrays(GL_TRIANGLES, 0, pVertexCount); // Narysuj piramidê

    glDisableVertexAttribArray(spTextured->a("vertex"));  // Wy³¹cz przesy³anie danych do atrybutu vertex
}


void drawPlaces(const std::vector<Place>& places) {
    for (const auto& place : places) {
        glm::mat4 M = glm::mat4(1.0f);
        M = glm::translate(M, glm::vec3((place.x / 20.0f) * expand, (place.y / 20.0f) * expand, 0.0f));
        M = glm::scale(M, glm::vec3(1, 1, 1) * biggify);
        glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

        float maxDimension = std::max(std::max(std::abs(begining_x), std::abs(begining_y)), 1.0f);

        float room_x = (begining_x * expand) + (0.5 * maxDimension * biggify * biggify2);

        float room_y = (begining_y * expand) + (0.5 * maxDimension * biggify * biggify2);

        if (((place.x / 20.0f) * expand >= room_x) && ((place.y / 20.0f) * expand >= room_y)) {
            expand = 1;
            biggify = 1;
            biggify2 = 1;
        }

        glEnableVertexAttribArray(spTextured->a("vertex"));
        glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, cVertices);

        if (switchplace && place.ID==places[current_place_index].ID) {

            glUniform1f(spTextured->u("lightIntensity"), 1.2f);
        }
        else {
            glUniform1f(spTextured->u("lightIntensity"), 0.6f);
        }

        if (texmode == 0) {
            if (placeTextures.find(place.ID) != placeTextures.end()) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, placeTextures[place.ID]);
                glUniform1i(spTextured->u("tex"), 0);
            }
            else {

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, tex0);
                glUniform1i(spTextured->u("tex"), 0);
            }
        }
        else if (texmode == 1){
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, allTextures[std::stoi(place.marking)]);
                glUniform1i(spTextured->u("tex"), 0);
        }

        glUniform4f(spTextured->u("color"), 1, 1, 0, 1);

        glDrawArrays(GL_TRIANGLES, 0, cVertexCount);

        glUniform1f(spTextured->u("lightIntensity"), 0.6f);
        glDisableVertexAttribArray(spTextured->a("vertex"));
    }
}

void drawTransitions(const std::vector<Transition>& transitions) {
    for (const auto& transition : transitions) {
        glm::mat4 M = glm::mat4(1.0f);
        M = glm::translate(M, glm::vec3((transition.x / 20.0f) * expand, (transition.y / 20.0f) * expand, 0.0f));
        M = glm::scale(M, glm::vec3(1, 1, 1) * biggify);
        glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

        float maxDimension = std::max(std::max(std::abs(begining_x), std::abs(begining_y)), 1.0f);

        float room_x = (begining_x * expand) + (0.5 * maxDimension * biggify * biggify2);

        float room_y = (begining_y * expand) + (0.5 * maxDimension * biggify * biggify2);

        if (((transition.x / 20.0f) * expand >= room_x) && ((transition.y / 20.0f) * expand >= room_y)) {
            expand = 1;
            biggify = 1;
            biggify2 = 1;
        }

        glEnableVertexAttribArray(spTextured->a("vertex"));
        glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, cVertices);

        if (texmode == 0) {
            if (transitionTextures.find(transition.ID) != transitionTextures.end()) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, transitionTextures[transition.ID]);
                glUniform1i(spTextured->u("tex"), 0);
            }
            else {

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, tex0);
                glUniform1i(spTextured->u("tex"), 0);
            }
        }
        else if (texmode == 1) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, tex0);
            glUniform1i(spTextured->u("tex"), 0);
        }

        glUniform4f(spTextured->u("color"), 1, 0, 0, 1);

        glDrawArrays(GL_TRIANGLES, 0, cVertexCount);

        glDisableVertexAttribArray(spTextured->a("vertex"));
    }
}

void drawEdges(const std::vector<Edge>& edges, const std::vector<Place>& places, const std::vector<Transition>& transitions) {
    for (const auto& edge : edges) {
        float startX, startY, endX, endY;


        for (const auto& place : places) {
            if (place.ID == std::to_string(edge.source)) {
                startX = (place.x / 20.0f)*expand;
                startY = (place.y / 20.0f)*expand;
                break;
            }
        }

        for (const auto& transition : transitions) {
            if (transition.ID == std::to_string(edge.source)) {
                startX = (transition.x / 20.0f)*expand;
                startY = (transition.y / 20.0f)*expand;
                break;
            }
        }

        for (const auto& place : places) {
            if (place.ID == std::to_string(edge.target)) {
                endX = (place.x / 20.0f) * expand;
                endY = (place.y / 20.0f) * expand;
                break;
            }
        }

        for (const auto& transition : transitions) {
            if (transition.ID == std::to_string(edge.target)) {
                endX = (transition.x / 20.0f) * expand;
                endY = (transition.y / 20.0f) * expand;
                break;
            }
        }

        glm::vec2 startPos = glm::vec2(startX, startY);
        glm::vec2 endPos = glm::vec2(endX, endY);

        drawPyramidOnEdge(edge, startPos, endPos);

        // Obliczanie d³ugoœci i kierunku prostopad³oœcianu
        float length = glm::distance(glm::vec2(startX, startY) / 2.0f, glm::vec2(endX, endY) / 2.0f);
        glm::vec2 direction = glm::normalize(glm::vec2(endX - startX, endY - startY));

        // Ustawienie skali prostopad³oœcianu (d³ugoœæ, szerokoœæ, wysokoœæ)
        glm::vec3 scale = glm::vec3(length, 0.1f, 0.1f);

        // Obliczanie œrodka prostopad³oœcianu
        glm::vec3 center = glm::vec3((startX + endX) / 2.0f, (startY + endY) / 2.0f, 0.0f);

        // Obliczanie k¹ta obrotu prostopad³oœcianu (na p³aszczyŸnie XY)
        float angle = atan2(direction.y, direction.x);

        // Rysowanie prostopad³oœcianu
        glm::mat4 M = glm::mat4(1.0f);
        M = glm::translate(M, center); // Wylicz macierz translacji
        M = glm::rotate(M, angle, glm::vec3(0, 0, 1)); // Wylicz macierz rotacji
        M = glm::scale(M, scale * biggify) ; // Wylicz macierz skalowania

        glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

        glEnableVertexAttribArray(spTextured->a("vertex"));  // W³¹cz przesy³anie danych do atrybutu vertex
        glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, cVertices); // Wska¿ tablicê z danymi dla atrybutu vertex

        glUniform4f(spTextured->u("color"), 0, 0, 1, 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex0);
        glUniform1i(spTextured->u("tex"), 0);

        glDrawArrays(GL_TRIANGLES, 0, cVertexCount); // Narysuj obiekt

        glDisableVertexAttribArray(spTextured->a("vertex"));  // Wy³¹cz przesy³anie danych do atrybutu vertex
    }
}


void drawScene(GLFWwindow* window, const std::vector<Place>& places, const std::vector<Transition>& transitions, const std::vector<Edge>& edges) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setCameraAtCenter(places, transitions);

    glm::mat4 V = glm::lookAt(glm::vec3((begining_x + camlr + changing_x), begining_y + camfr + changing_y, s + (-30.0f)),
        glm::vec3((begining_x + camlr + changing_x), begining_y + camfr + changing_y, s - 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 P = glm::perspective(-50.0f * PI / 180.0f, aspectRatio, 0.01f, 1000.0f);

    //glm::vec4 lightDir1 = glm::vec4(-1.0f, 1.0f, 0.0f, 0.0f);
    //glm::vec4 lightDir2 = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);

    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    spTextured->use(); // Aktywacja programu cieniuj¹cego

    glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V));
    glUniformMatrix4fv(spTextured->u("lightSpaceMatrix"), 1, false, glm::value_ptr(lightSpaceMatrix));
    glUniformMatrix4fv(spTextured->u("lightSpaceMatrix"), 1, false, glm::value_ptr(lightSpaceMatrix));
    glUniform4fv(spTextured->u("lightDir1"), 1, glm::value_ptr(lightDir1));
    glUniform4fv(spTextured->u("lightDir2"), 1, glm::value_ptr(lightDir2));
    glUniform4fv(spTextured->u("lightColor1"), 1, glm::value_ptr(lightColor1));
    glUniform4fv(spTextured->u("lightColor2"), 1, glm::value_ptr(lightColor2));
    glUniform1f(spTextured->u("lightIntensity"), 0.4f);
    glUniform1f(spTextured->u("kdFactor"), 1.0f);
    glUniform1f(spTextured->u("ksFactor"), 0.6f);

    GLint timeLocation = spTextured->u("u_time");
    glUniform1f(timeLocation, static_cast<float>(glfwGetTime()));

    drawPlaces(places);
    drawTransitions(transitions);
    drawEdges(edges, places, transitions);


    if (animate) {
        animationState.isAnimating = true;
        moveCubeAlongEdge(edges, places);
    }
    else {
        animationState.isAnimating = false;
    }

    drawRoom(P, V, begining_x, begining_y);

    drawShadowMap(lightDir2, places, transitions);

    glfwSwapBuffers(window);

}


void loadXMLFile(const std::string& filename) {
    // Implementacja wczytywania pliku XML i przetwarzania jego zawartoœci
    std::cout << "Wczytano plik XML: " << filename << std::endl;
    xml_document<> doc;
    std::vector<char> buffer;
    buffer.reserve(filename.size() + 1);
    std::copy(filename.begin(), filename.end(), std::back_inserter(buffer));
    buffer.push_back('\0'); // Dodaj terminator koñca ci¹gu znaków

    file<> xmlFile(buffer.data()); // Przekazanie char* do konstruktora
    doc.parse<0>(xmlFile.data());

    xml_node<>* root = doc.first_node();

    // place
    xml_node<>* placeClassNode = root->first_node("nodeclasses")->first_node("nodeclass");
    for (xml_node<>* placeNode = placeClassNode->first_node("node");
        placeNode;
        placeNode = placeNode->next_sibling("node")) {

        float x = std::stof(placeNode->first_node("graphics")->first_node("graphic")->first_attribute("x")->value());
        float y = std::stof(placeNode->first_node("graphics")->first_node("graphic")->first_attribute("y")->value());
        std::string ID = placeNode->first_attribute("id")->value();
        //places.push_back({ x, y, "Place", ID });

        xml_node<>* markingNode = nullptr;
        for (xml_node<>* attributeNode = placeNode->first_node("attribute"); attributeNode; attributeNode = attributeNode->next_sibling("attribute")) {
            if (std::string(attributeNode->first_attribute("name")->value()) == "Marking") {
                markingNode = attributeNode;
                break;
            }
        }


        if (markingNode) {

            std::string marking = markingNode->first_node()->value();
            places.push_back({ x, y, marking, ID });
        }
    }

    // transition
    xml_node<>* transitionClassNode = placeClassNode->next_sibling("nodeclass");
    for (xml_node<>* transitionNode = transitionClassNode->first_node("node");
        transitionNode;
        transitionNode = transitionNode->next_sibling("node")) {
        float x = std::stof(transitionNode->first_node("graphics")->first_node("graphic")->first_attribute("x")->value());
        float y = std::stof(transitionNode->first_node("graphics")->first_node("graphic")->first_attribute("y")->value());
        std::string ID = transitionNode->first_attribute("id")->value();
        transitions.push_back({ x, y, "Transition", ID });
    }

    // krawêdŸ
    xml_node<>* edgeClassNode = root->first_node("edgeclasses")->first_node("edgeclass");
    for (xml_node<>* edgeNode = edgeClassNode->first_node("edge");
        edgeNode;
        edgeNode = edgeNode->next_sibling("edge")) {
        float startX = std::stof(edgeNode->first_node("graphics")->first_node("graphic")->first_node("points")->first_node("point")->first_attribute("x")->value());
        float startY = std::stof(edgeNode->first_node("graphics")->first_node("graphic")->first_node("points")->first_node("point")->first_attribute("y")->value());
        float endX = std::stof(edgeNode->first_node("graphics")->first_node("graphic")->first_node("points")->last_node("point")->first_attribute("x")->value());
        float endY = std::stof(edgeNode->first_node("graphics")->first_node("graphic")->first_node("points")->last_node("point")->first_attribute("y")->value());
        int source = std::stof(edgeNode->first_attribute("source")->value());
        int target = std::stof(edgeNode->first_attribute("target")->value());


        xml_node<>* multiplicityNode = nullptr;
        for (xml_node<>* attributeNode = edgeNode->first_node("attribute"); attributeNode; attributeNode = attributeNode->next_sibling("attribute")) {
            if (std::string(attributeNode->first_attribute("name")->value()) == "Multiplicity") {
                multiplicityNode = attributeNode;
                break;
            }
        }


        if (multiplicityNode) {

            std::string multiplicity = multiplicityNode->first_node()->value();

            edges.push_back({ startX, startY, endX, endY, source, target, multiplicity });
        }



    }
}

void clearObjects() {
    places.clear();
    transitions.clear();
    edges.clear();
}

int main(void) {


    GLFWwindow* window; //WskaŸnik na obiekt reprezentuj¹cy okno

    if (file_num == 1) {
        loadXMLFile("test.pn");
    }

    glfwSetErrorCallback(error_callback); //Zarejestruj procedurê obs³ugi b³êdów

    if (!glfwInit()) { //Zainicjuj bibliotekê GLFW
        fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(1920, 1080, "OpenGL", NULL, NULL);  


    if (!window) //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
    {
        fprintf(stderr, "Nie mo¿na utworzyæ okna.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siê aktywny i polecenia OpenGL bêd¹ dotyczyæ w³aœnie jego.
    glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

    if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekê GLEW
        fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW.\n");
        exit(EXIT_FAILURE);
    }

    initOpenGLProgram(window, places, transitions); //Operacje inicjuj¹ce

    //G³ówna pêtla
    glfwSetTime(0); 

    int previous_file_num = -1;

    while (!glfwWindowShouldClose(window)) //Tak d³ugo jak okno nie powinno zostaæ zamkniête
    {

        if (file_num != previous_file_num) {
            clearObjects();
            if (file_num == 1) {
                loadXMLFile("test.pn");
            }
            else if (file_num == 2) {
                loadXMLFile("test1.pn"); 
            }
            previous_file_num = file_num; // Zaktualizuj poprzedni¹ wartoœæ file_num
        }

        glfwSetTime(0); 
        drawScene(window,places, transitions, edges); //Wykonaj procedurê rysuj¹c¹

        glfwPollEvents(); 
    }

    freeOpenGLProgram(window);

    glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
    glfwTerminate(); //Zwolnij zasoby zajête przez GLFW
    exit(EXIT_SUCCESS);
}