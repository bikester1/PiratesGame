#pragma once

namespace PiratesLife {

	template <class T>
	class vec3Array
	{
	public:

		T *vec3Array::putVec(T x, T y, T z);

		T *vec3Array<T>::setVec(int i, T x, T y, T z);

		T vec3Array::getVec(int i);

		T *vec3Array<T>::ptr();

		int vec3Array<T>::getSize();

		vec3Array();

		~vec3Array();

	private:
		T *myArray;
		int maxSize;
		int curIndex;

		void expandArray();
	};

}
