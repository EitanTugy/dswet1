#pragma once
#ifndef METHODTREEINTOARRAY_H
#define METHODTREEINTOARRAY_H
#include "AvlTree.h"
#include "Lecture.h"
template<class T>
class methodTreeIntoArray {
	T* array;
	int index;
public:
	methodTreeIntoArray(T*arr)
	//	:
		//index(0),
	//	array(arr)
	{
		index = 0;
		array = arr;
	}
	void doSomething(T& obj) {
		array[index++] = obj;
	}

	void changeToArrayOfNodes(AvlTree<Lecture, Lecture>::Node** nodes_arr) {
		//AvlTree<Lecture, Lecture>::Node** nodes_arr = new AvlTree<Lecture, Lecture>::Node*[index];
		for (int i = 0; i < index; i++) 
			nodes_arr[i] = new AvlTree<Lecture, Lecture>::Node(&array[i], &array[i], 1);
		//return *nodes_arr;
	}
};
#endif