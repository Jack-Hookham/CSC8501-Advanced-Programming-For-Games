#pragma once

#include <random>

namespace util
{
	//Compute value as a percentage of total
	template<typename T>
	inline float computePercent(const T value, const T total)
	{
		if (total == 0)
		{
			throw std::invalid_argument("Divide by zero exception");
		}
		else
		{
			float result = ((float)value / (float)total) * 100.0f;
			return result;
		}
	}
}

//Provides functions for various types of random number generation

namespace RandomGen
{
	static std::random_device rd;
	static std::default_random_engine dre{ rd() };
	static std::mt19937 randGenerator(dre);

	static inline const int generateRandomWithinRange(const int upperBound, const int lowerBound) { return std::uniform_int_distribution<int>(upperBound, lowerBound)(randGenerator); }
	static inline const int generateRandomWeighted(const std::vector<double> weights) { return std::discrete_distribution<int>(weights.begin(), weights.end())(randGenerator); }
};