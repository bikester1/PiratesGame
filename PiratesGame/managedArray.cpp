#include "ManagedArray.h"
#include <float.h>

namespace PiratesLife {

	template <class T>
	void ManagedArray<T>::putVec(T itm) {

		if (curIndex > maxSize / 2)
			ManagedArray<T>::expandArray();

		myArray[curIndex++] = itm;
	}

	template <class T>
	int ManagedArray<T>::setVec(int i, T itm) {
		if (i >= curIndex)
			return -1;

		if (curIndex > maxSize / 2)
			ManagedArray<T>::expandArray();

		myArray[i] = itm;
		return 1;
	}

	template <class T>
	void ManagedArray<T>::expandArray() {
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
	T ManagedArray<T>::getVec(int i) {
		return myArray[i];
	}

	template <class T>
	int ManagedArray<T>::getSize() {
		return curIndex;
	}

	template <class T>
	T *ManagedArray<T>::ptr() {
		return myArray;
	}

	template <class T>
	ManagedArray<T>::ManagedArray() {
		curIndex = 0;
		maxSize = 20;
		myArray = new T[20];
	}

	template <class T>
	ManagedArray<T>::~ManagedArray() {
		delete myArray;
	}

}