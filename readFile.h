#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

class _ReadFile
{

public:
	void readFile(const std::string& pathFile);
	std::string getNeuralNetwokStatus();
private:
	std::string neuralNetwokStatus;
};