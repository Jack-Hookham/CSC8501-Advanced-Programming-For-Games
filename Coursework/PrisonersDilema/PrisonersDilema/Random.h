#pragma once

#include <random>

//Provides functions for various types of random number generation

namespace RandomGen
{
	static std::random_device rd;
	static std::default_random_engine dre{ rd() };
	static std::mt19937 randGenerator(dre);

	static inline const int generateRandomWithinRange(const int upperBound, const int lowerBound) { return std::uniform_int_distribution<int>(upperBound, lowerBound)(randGenerator); }
	static inline const int generateRandomWeighted(const std::vector<double> weights) { return std::discrete_distribution<int>(weights.begin(), weights.end())(randGenerator); }
};