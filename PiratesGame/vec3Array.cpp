#include "vec3Array.h"

namespace PiratesLife {

	template <class T>
	T *vec3Array<T>::putVec(T x, T y, T z) {

		if (curIndex > maxSize / 2)
			vec3Array<T>::expandArray();

		myArray[curIndex++] = x;
		myArray[curIndex++] = y;
		myArray[curIndex++] = z;
		return myArray;
	}

	template <class T>
	T *vec3Array<T>::setVec(int i, T x, T y, T z) {
		if (i >= maxSize - 3)
			return NULL;

		if (curIndex > maxSize / 2)
			vec3Array<T>::expandArray();

		myArray[i++] = x;
		myArray[i++] = y;
		myArray[i++] = z;
		curIndex += 3;
		return myArray;
	}

	template <class T>
	void vec3Array<T>::expandArray() {
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
	T vec3Array<T>::getVec(int i) {
		return myArray[i];
	}

	template <class T>
	int vec3Array<T>::getSize() {
		return curIndex;
	}

	template <class T>
	T *vec3Array<T>::ptr() {
		return myArray;
	}

	template <class T>
	vec3Array<T>::vec3Array() {
		curIndex = 0;
		maxSize = 20;
		myArray = new T[20];
	}

	template <class T>
	vec3Array<T>::~vec3Array() {
		delete myArray;
	}

}