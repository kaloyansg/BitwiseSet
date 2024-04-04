#pragma once
#include <iostream>

class Set
{
public:
	Set(size_t);
	Set(const Set&);
	Set& operator=(const Set&);
	~Set();

	void add(unsigned);
	void remove(unsigned);
	bool contains(size_t) const;
	void print()const;

	friend Set getUnion(const Set&, const Set&);
	friend Set getIntersection(const Set&, const Set&);

private:
	size_t n;
	uint8_t* buckets;
	size_t bucketsCount;
	static constexpr size_t elementsInBucket = sizeof(uint8_t) * 8;
};

