#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DobleLinkedList.h"
#include "Stack.h"
#include "QueueTemplate.h"

template<typename T>
class Vertex {
public: 
    DobleLinkedList<unsigned int> edges;
    T data;
};

template<typename T>
class Graph {
public:
    Graph() {
        vertices = nullptr;
        size = 0;
        visited = nullptr;
    }
    ~Graph() {
        clearGraph();
    }

    //FUNCTOIN THAT RETURNS SIZE OF GRAPH
    unsigned int getSize() {
        return size;
    }
    //FUNCTOIN THAT DISPLAYS ALL DATA IN GRAPH
    void display() {
        if (!isEmpty()) {
            for (int i = 0; i < size; i++) {
                std::cout << "[" << i << "] " << vertices[i].data << ": ";
                vertices[i].edges.display();
            }
        }
    }
    //FUNCTOION THAT SETS DATA HOLD IN VERTEX
    bool setVertexData(unsigned int vertex, T d) {
        if (isEmpty() || vertex >= size)
            return false;
        vertices[vertex].data = d;
        return true;

    }
    //FUNCTION THAT RETRIVES THE DATA HOLD IN VERTEX
    T* getVertexData(unsigned int vertex) {
        if (isEmpty() || vertex >= size)
            return nullptr;
        return &vertices[vertex].data;
    }
    //FUNCTION THAT CREATES THE GRAPH
    bool createGraph(unsigned int n) {
        if (vertices)
            return false;
        vertices = new(std::nothrow) Vertex<T>[n];
        if (!vertices)
            return false;
        visited = new(std::nothrow) bool[n];
        if (!visited) {
            clearGraph();
            return false;
        }
        size = n;
        return true;
    }
    //FUNCTION THAT MANAGES INSERTING DIRECTED
    bool insertEdgeDirected(unsigned int src, unsigned int dest) {
        if (isEmpty())
            return false;
        if (src >= size || dest >= size)
            return false;
        if (vertices[src].edges.search(dest))
            return false;
        vertices[src].edges.addToHead(dest);
        return true;
    }
    //FUNCTION THAT MANAGES DELETING DIRECTED
    bool deleteEdgeDirected(unsigned int src, unsigned int dest) {
        if (isEmpty())
            return false;
        if (src >= size || dest >= size)
            return false;
        if (vertices[src].edges.search(dest))
            return false;
        vertices[src].edges.deleteValue(dest);
        return true;
    }
    //FUNCTOIN THAT MANAGES INSERTING UNDIRECTED
    bool insertEdgeUndirected(unsigned int src, unsigned int dest) {
        if (isEmpty())
            return false;
        if (src >= size || dest >= size)
            return false;
        if (vertices[src].edges.search(dest))
            return false;
        vertices[src].edges.addToHead(dest);
        vertices[dest].edges.addToHead(src);
        return true;
    }
    //FUNCTION THAT MANAGES DELETING UNDIRECTED
    bool deleteEdgeUndirected(unsigned int src, unsigned int dest) {
        if (isEmpty())
            return false;
        if (src >= size || dest >= size)
            return false;
        if (vertices[src].edges.search(dest))
            return false;
        vertices[src].edges.deleteValue(dest);
        vertices[dest].edges.deleteValue(src);
        return true;
    }
    //FUNCTION THAT DELETES THE GRAPH
    bool clearGraph() {
        if (isEmpty())
            return false;
        delete [] vertices;
        vertices = nullptr;
        delete [] visited;
        visited = nullptr;
        size = 0;
        return true;
    }
    //FUNCTION THAT CHECKS IF THE GRAPH IS EMPTY
    bool isEmpty() {
        return vertices == nullptr;
    }
    //FUNCTION THAT SAVES THE FILE INTO TXT WITH GIVEN NAME
    bool saveFile(std::string fileName) {
        if (isEmpty())
            return false;
        std::fstream file;
        file.open(fileName, std::ios::out);
        if (!file.is_open())
            return false;
        file << "Grafo\n";
        file << size << "\n";
        for (int i = 0; i < size; i++) 
            file << vertices[i].edges.toString() << "\n";
        file.close();
        return true;
    }
    //FUNCTION THAT LOADS FILE AND RECIVES THE NAME
    bool loadFile(std::string fileName) {
        if (!isEmpty())
            clearGraph();

        std::fstream file;
        file.open(fileName, std::ios::in);
        if (!file.is_open())
            return false;

        //first i check if it is a valid graph file
        std::string line, cell;
        std::getline(file,line);
        if (line != "Grafo") return false;

        //then i save the size of the graph
        std::getline(file, line);
        if (!isValidInt(line)) return false;
        int nSize = stoi(line);

        //I create the new graph of size nSize
        if (nSize <= 0) return false;
        if (!createGraph(nSize)) return false;

        //I iterate nSize times to store the concets
        int i = 0, num;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            while (std::getline(ss, cell, ' ')) {
                if (!isValidInt(cell)) {
                    clearGraph();
                    return false;
                }
                num = stoi(cell); 
                if (!insertEdgeDirected(i,num)) {
                    clearGraph();
                    return false;
                }
            }
            i++;
        }
        file.close();
        return true;
    }
    //DEPTH FISRT SEARCH
    bool depthFirstSearch(unsigned int vertex) {
        if (isEmpty() || vertex >= size)
            return false;
        clearVisited();
        StackTemplate<unsigned int> stack;
        stack.push(vertex);
        std::cout << "DFS: (" << vertex << "): ";
        while (!stack.isEmpty()) {
            unsigned int currVertex = *stack.getTop();
            stack.pop();
            if (!visited[currVertex]) {
                visited[currVertex] = true; 
                std::cout << currVertex << " ";
                DobleLinkedList<unsigned int>::iterator it =  vertices[currVertex].edges.begin();
                while (it != vertices[currVertex].edges.end()) {
                    if (!visited[*it])
                        stack.push(*it);
                    ++it;
                }
            }
        }
        std::cout << "\n";
        return true;
    }
    //BREATH FIRST SEARCH
    DobleLinkedList<unsigned int>* breathFirstSearchPath(unsigned int vertex, unsigned int fVertex) {
        if (isEmpty() || vertex >= size || fVertex >= size)
            return nullptr;

        unsigned int previous[size];
        previous[0] = 0;
        for (int i = 1; i < size; i++)
            previous[i] = INT_MAX; 

        clearVisited();

        QueueTemplate<unsigned int> queue;

        queue.enqueue(vertex);
        while (!queue.isEmpty()) {
            unsigned int currVertex = *queue.getFront();
            queue.dequeue();

            if (!visited[currVertex]) {
                visited[currVertex] = true; 

                DobleLinkedList<unsigned int>::iterator it =  vertices[currVertex].edges.begin();
                while (it != vertices[currVertex].edges.end()) {
                    if (!visited[*it]) {
                        previous[*it] = currVertex; // I save currVertex in previous array
                        queue.enqueue(*it);
                    }
                    ++it;
                }
            }
        }
        //taking advantage of the linked list no stack is needed
        DobleLinkedList<unsigned int>* path = new DobleLinkedList<unsigned int>();
        if (!visited[fVertex]) return path;

        for (unsigned int v = fVertex; v != vertex; v = previous[v]) {
            path->addToHead(v); //adds nodes in reverse order
        }
        path->addToHead(vertex); //include at the beginning vertex

        return path;
    }
    
private: 
    unsigned int size;
    Vertex<T> *vertices;
    bool *visited;

    void clearVisited() {
        for (int i = 0; i < size; i++) 
            visited[i] = false;
    };
    //HELPER FUNCTION FOR LOAD FILE THAT CHECKS IF STRING IS VALID INT
    bool isValidInt(std::string& str) {
        if (str.empty()) return false;
        for(int i = 0; i < str.length(); i++)
            if (!isdigit(str[i]))
                return false;
        return true;
    }
};