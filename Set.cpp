#include "Set.h"

Set::Set(size_t size) : n(0), buckets(nullptr), bucketsCount(0)
{
	if (size % elementsInBucket == 0)
	{
		bucketsCount = size / elementsInBucket;
	}
	else
	{
		bucketsCount = size / elementsInBucket + 1;
	}

	buckets = new uint8_t[bucketsCount]{ 0 };
	this->n = size;
}

Set::Set(const Set& that) : n(0), buckets(nullptr), bucketsCount(0)
{
	uint8_t* buckets = new (std::nothrow) uint8_t[that.bucketsCount];
	if (!buckets)
		return;
	for (size_t i = 0; i < that.bucketsCount; ++i)
	{
		buckets[i] = that.buckets[i];
	}
	this->n = that.n;
	this->bucketsCount = that.bucketsCount;
}

Set& Set::operator=(const Set& that)
{
	if (this == &that)
		return *this;

	uint8_t* tempBuckets = new (std::nothrow) uint8_t[that.bucketsCount];
	if (!tempBuckets)
		return *this;

	for (size_t i = 0; i < that.bucketsCount; ++i)
	{
		tempBuckets[i] = that.buckets[i];
	}

	delete[] this->buckets;
	buckets = tempBuckets;
	this->n = that.n;
	this->bucketsCount = that.bucketsCount;

	return *this;
}

Set::~Set()
{
	delete[] buckets;
	buckets = nullptr;
}

void Set::add(unsigned num)
{
	if (num >= n)
		return;

	unsigned a = 128 >> (num % elementsInBucket);

	buckets[num / elementsInBucket] |= (128 >> (num % elementsInBucket));

}

void Set::remove(unsigned num)
{
	if (num >= n)
		return;

	buckets[num / elementsInBucket] &= ~(128 >> (num % elementsInBucket));
}

bool Set::contains(size_t num) const
{
	if (num >= n)
		return false;

	return buckets[num / elementsInBucket] & (128 >> (num % elementsInBucket));
}

void Set::print() const
{
	std::cout << "{ ";
	for (size_t i = 0; i < n; ++i)
	{
		if (contains(i))
		{
			std::cout << i << " ";
		}
	}
	std::cout << "}";
}

Set getIntersection(const Set& lhs, const Set& rhs)
{
	Set result(std::min(lhs.n, rhs.n));
	size_t bucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);

	for (size_t i = 0; i < bucketsCount; ++i)
	{
		result.buckets[i] = lhs.buckets[i] & rhs.buckets[i];
	}

	return result;
}

Set getUnion(const Set& lhs, const Set& rhs)
{
	Set result(std::max(lhs.n, rhs.n));
	size_t minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);

	for (size_t i = 0; i < minBucketsCount; ++i)
	{
		result.buckets[i] = lhs.buckets[i] | rhs.buckets[i];
	}

	const Set& biggerSet = lhs.bucketsCount > rhs.bucketsCount ? lhs : rhs;

	for (size_t i = minBucketsCount; i < biggerSet.bucketsCount; ++i)
	{
		result.buckets[i] = biggerSet.buckets[i];
	}

	return result;
}
