
#include "Markov.h"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, const char** argv)
{
	std::string InFileName = "Karenina.txt";
	std::string OutFileName = "Output.txt";

	if (argc == 3)
	{
		InFileName = argv[1];
		OutFileName = argv[2];
	}
	else if (argc == 2)
		InFileName = argv[1];

	Markov<std::string> Chain;
	std::ifstream Corpus(InFileName);
	std::string Word;
	std::string PrevWord;

	Corpus >> PrevWord;

	while(Corpus >> Word)
	{
		if(Chain[PrevWord].count(Word) == 0)
		{
			//Haven't seen this combo of words before: Set it to 0;
			Chain[PrevWord][Word] = 0;
		}
		Chain[PrevWord][Word]++;
		PrevWord = Word;
	}
	Corpus.close();

	std::ofstream outfile(OutFileName);

	Chain.RandomizeState();
	
	for (uint i = 0; i < 10000; ++i)
	{
		outfile << Chain.NextState() << " ";
		if (i & 10 == 0)
			outfile << std::endl;
	}
	outfile.close();
}