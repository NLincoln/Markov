#pragma once

#include <vector>
#include <map>
#include <random>
#include <numeric>

template<typename T>
using MarkovChain = std::map<T, std::map<T, double>>;
using uint = unsigned int;

uint GetRandomUINT(uint min, uint max)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint> uni(min, max);
	return uni(rng);
}

double GetRandomDouble()
{
	uint max = GetRandomUINT(0, UINT_MAX);
	return static_cast<double>(max) / UINT_MAX;
}

template <typename T>
class Markov
{
	MarkovChain<T> Chain;
	T CurrentState;

public:
	void SetState(T state)
	{
		CurrentState = state;
	}

	void RandomizeState()
	{
		//"Randomly" chosen to be the first word
		CurrentState = Chain.begin()->second.begin()->first;
	}

	T GetState()
	{
		return CurrentState;
	}

	T NextState()
	{
		double Sum = 0;
		for (auto Entry : Chain[CurrentState])
			Sum += Entry.second;
		double Choice = GetRandomDouble() * Sum;
		T NextState;

		for (auto Entry : Chain[CurrentState])
		{
			Choice -= Entry.second;
			if (Choice < Entry.second)
			{
				NextState = Entry.first;
				break;
			}
		}
		CurrentState = NextState;
		return CurrentState;
	}


	std::map<T, double>& operator[](T key)
	{
		return Chain[key];
	}
};