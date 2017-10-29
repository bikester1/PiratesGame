#pragma once

namespace PiratesLife {

	template <class T>
	class ManagedArray
	{
	public:

		void ManagedArray::putVec(T itm);

		int ManagedArray<T>::setVec(int i, T itm);

		T ManagedArray::getVec(int i);

		T *ManagedArray<T>::ptr();

		int ManagedArray<T>::getSize();

		ManagedArray();

		~ManagedArray();

	private:
		T *myArray;
		int maxSize;
		int curIndex;

		void expandArray();
	};

}
