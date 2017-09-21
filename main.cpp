//Nicolas Stoian
//This program needs 2 command line arguments
//argv[1] "input" for text file representing the input graph
//argv[2] "output" to write the outputs

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int loadMatrix(int** adjacentMatrix, int arraySize, ifstream& inFile);
void printGraph(int** adjacentMatrix, int arraySize, int indexStart, ofstream& outFile);
void printAdjacentMatrix(int** adjacentMatrix, int arraySize, int indexStart, ofstream& outFile);
void colorGraph(int** adjacentMatrix, int arraySize, int indexStart, ofstream& outFile, int* nodeColor);
bool isAdjacentSameColor(int** adjacentMatrix, int arraySize, int newNode, int newColor, int* nodeColor);

int main(int argc, char* argv[]){
    ifstream inFile;
    inFile.open(argv[1]);
    int numNodes;
    inFile >> numNodes;
    int** adjacentMatrix;
    adjacentMatrix = new int* [numNodes];
    for(int i = 0; i < numNodes; i++){
        adjacentMatrix[i] = new int [numNodes];
    }
    for(int row = 0; row < numNodes; row++){
        for(int col = 0; col < numNodes; col++){
            adjacentMatrix[row][col] = 0;
        }
    }
    int indexStart = loadMatrix(adjacentMatrix, numNodes, inFile);
    inFile.close();
    ofstream outFile;
    outFile.open(argv[2]);
    printGraph(adjacentMatrix, numNodes, indexStart, outFile);
    outFile << endl << endl;
    printAdjacentMatrix(adjacentMatrix, numNodes, indexStart, outFile);
    int* nodeColor = new int [numNodes];
    for(int i = 0; i < numNodes; i++){
        nodeColor[i] = 0;
    }
    outFile << endl << endl;
    colorGraph(adjacentMatrix, numNodes, indexStart, outFile, nodeColor);
    outFile << endl << endl;
    printAdjacentMatrix(adjacentMatrix, numNodes, indexStart, outFile);
    outFile.close();
    for(int i = 0; i < numNodes; i++) {
        delete[] adjacentMatrix[i];
    }
    delete [] adjacentMatrix;
}


int loadMatrix(int** adjacentMatrix, int arraySize, ifstream& inFile){
    int n1;
    int n2;
    int indexStart = 0;
    while(inFile >> n1){
        inFile >> n2;
        if(n1 == arraySize && n2 == arraySize){
            adjacentMatrix[0][0] = 1;
            indexStart = 1;
        }
        else if(n1 == arraySize){
            adjacentMatrix[0][n2] = 1;
            indexStart = 1;
        }
        else if(n2 == arraySize){
            adjacentMatrix[n1][0] = 1;
            indexStart = 1;
        }
        else{
            adjacentMatrix[n1][n2] = 1;
        }
    }
    return indexStart;
}

void printGraph(int** adjacentMatrix, int arraySize, int indexStart, ofstream& outFile){
    if(indexStart == 0){
        for(int row = 0; row < arraySize; row++){
            for(int col = 0; col < arraySize; col++){
                if (adjacentMatrix[row][col] != 0){
                    outFile << row << " " << col << endl;
                }
            }
        }
    }
    else{
        for(int row = 1; row <= arraySize; row++){
            for(int col = 1; col <= arraySize; col++){
                if(row == arraySize && col == arraySize){
                    if(adjacentMatrix[0][0] != 0){
                        outFile << row << " " << col << endl;
                    }
                }
                else if(row == arraySize){
                    if(adjacentMatrix[0][col] != 0){
                        outFile << row << " " << col << endl;
                    }
                }
                else if(col == arraySize){
                    if(adjacentMatrix[row][0] != 0){
                        outFile << row << " " << col << endl;
                    }
                }
                else{
                    if (adjacentMatrix[row][col] != 0){
                        outFile << row << " " << col << endl;
                    }
                }
            }
        }
    }
}

void printAdjacentMatrix(int** adjacentMatrix, int arraySize, int indexStart, ofstream& outFile){
    outFile << right << setw(5) << "index";
    if(indexStart == 0){
        for(int col = 0; col < arraySize; col++){
            outFile  << setw(3) << col;
        }
        outFile << endl;
        for(int row = 0; row < arraySize; row++){
            outFile << setw(5) << row;
            for(int col = 0; col < arraySize; col++){
                outFile  << setw(3) << adjacentMatrix[row][col];
            }
            outFile << endl;
        }
    }
    else{
        for(int col = 1; col <= arraySize; col++){
            outFile  << setw(3) << col;
        }
        outFile << endl;
        for(int row = 1; row <= arraySize; row++){
            outFile << setw(5) << row;
            for(int col = 1; col <= arraySize; col++){
                if(row == arraySize && col == arraySize){
                    outFile << setw(3) << adjacentMatrix[0][0];
                }
                else if(row == arraySize){
                    outFile << setw(3) << adjacentMatrix[0][col];
                }
                else if(col == arraySize){
                    outFile << setw(3) << adjacentMatrix[row][0];
                }
                else{
                    outFile << setw(3) << adjacentMatrix[row][col];
                }
            }
            outFile << endl;
        }
    }
}

void colorGraph(int** adjacentMatrix, int arraySize, int indexStart, ofstream& outFile, int* nodeColor){
    if(indexStart == 0){
        int numColored = 0;
        int newColor = 0;
        while(numColored < arraySize){
            newColor++;
            for(int newNode = 0; newNode < arraySize; newNode++){
                if(nodeColor[newNode] == 0 && !(isAdjacentSameColor(adjacentMatrix, arraySize, newNode, newColor, nodeColor))){
                    nodeColor[newNode] = newColor;
                    numColored++;
                }
            }
            outFile << "newColor = " << newColor << endl;
            outFile << setw(11) << left << "index";
            for(int i = 0; i < arraySize; i++){
                outFile << setw(3) << i;
            }
            outFile << endl << setw(11) << left << "nodeColor";
            for(int i = 0; i < arraySize; i++){
                outFile << setw(3) << nodeColor[i];
            }
            outFile << endl << endl;
        }
        for(int i = 0; i < arraySize; i++){
            adjacentMatrix[i][i] = nodeColor[i];
        }
        outFile << "The number of colors used to color the graph = " << newColor << endl;
    }
    else{
        int numColored = 0;
        int newColor = 0;
        while(numColored < arraySize){
            newColor++;
            for(int newNode = 1; newNode <= arraySize; newNode++){
                if(newNode == arraySize){
                    newNode = 0;
                }
                if(nodeColor[newNode] == 0 && !(isAdjacentSameColor(adjacentMatrix, arraySize, newNode, newColor, nodeColor))){
                    nodeColor[newNode] = newColor;
                    numColored++;
                }
                if(newNode == 0){
                    newNode = arraySize;
                }
            }
            outFile << "newColor = " << newColor << endl;
            outFile << setw(11) << left << "index";
            for(int i = 1; i <= arraySize; i++){
                if(i == arraySize){
                    outFile << setw(3) << arraySize;
                }
                else{
                    outFile << setw(3) << i;
                }
            }
            outFile << endl << setw(11) << left << "nodeColor";
            for(int i = 1; i <= arraySize; i++){
                if(i == arraySize){
                    outFile << setw(3) << nodeColor[0];
                }
                else{
                    outFile << setw(3) << nodeColor[i];
                }
            }
            outFile << endl << endl;
        }
        for(int i = 0; i < arraySize; i++){
            adjacentMatrix[i][i] = nodeColor[i];
        }
        outFile << "The number of colors used to color the graph = " << newColor << endl;
    }
}

bool isAdjacentSameColor(int** adjacentMatrix, int arraySize, int newNode, int newColor, int* nodeColor){
    bool isColored = false;
    for(int i = 0; i < arraySize; i++){
        if(adjacentMatrix[newNode][i] == 1 && nodeColor[i] == newColor){
            isColored = true;
        }
    }
    return isColored;
}
