#pragma once
#include <iostream>
#include <chrono>
#include <omp.h>

using namespace std;
extern int tasks_created;

//Define a struct to create a node of the linked list
struct Node {
	int info;
	Node* next;
};

//Function to grow the linked list
void append(int value, Node** h);
void Process(Node* p);

//Generate fibonacci sequence of each node in the linked list
int fibSeq(int i);
int fibPar(int i);



