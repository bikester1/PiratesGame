#include "managedArray.h"
#include <float.h>

namespace PiratesLife {

	template <class T>
	void managedArray<T>::putVec(T itm) {

		if (curIndex > maxSize / 2)
			managedArray<T>::expandArray();

		myArray[curIndex++] = itm;
	}

	template <class T>
	int managedArray<T>::setVec(int i, T itm) {
		if (i >= curIndex)
			return -1;

		if (curIndex > maxSize / 2)
			managedArray<T>::expandArray();

		myArray[i] = itm;
		return 1;
	}

	template <class T>
	void managedArray<T>::expandArray() {
		int i = 0;

		maxSize *= 2;
		T *tempArray = new T[maxSize];

		for (i = 0; i < curIndex; i++) {
			tempArray[i] = myArray[i];
		}

		delete myArray;
		myArray = tempArray;
	}

	template <class T>
	T managedArray<T>::getVec(int i) {
		return myArray[i];
	}

	template <class T>
	int managedArray<T>::getSize() {
		return curIndex;
	}

	template <class T>
	T *managedArray<T>::ptr() {
		return myArray;
	}

	template <class T>
	managedArray<T>::managedArray() {
		curIndex = 0;
		maxSize = 20;
		myArray = new T[20];
	}

	template <class T>
	managedArray<T>::~managedArray() {
		delete myArray;
	}

}