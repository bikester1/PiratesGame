#pragma once

namespace PiratesLife {

	template <class T>
	class managedArray
	{
	public:

		void managedArray::putVec(T itm);

		int managedArray<T>::setVec(int i, T itm);

		T managedArray::getVec(int i);

		T *managedArray<T>::ptr();

		int managedArray<T>::getSize();

		managedArray();

		~managedArray();

	private:
		T *myArray;
		int maxSize;
		int curIndex;

		void expandArray();
	};

}
