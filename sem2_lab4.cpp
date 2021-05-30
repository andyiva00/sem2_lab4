// Курс: 1, Семестр: 2, Группа: МКН-116
// Лабораторная работа: №4, Вариант: 6
// Студенит: Тимофеев Денис

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <variant>

std::vector<std::string> split(const std::string str, char delim)
{
	std::vector<std::string> tmpVector;
	std::stringstream tmpStr;
	tmpStr.str(str);
	std::string segment;
	
	while (std::getline(tmpStr, segment, delim))
	{
		tmpVector.push_back(segment);
	}
	return tmpVector;
}

int main()
{
	std::ifstream timeStampsFile("BD.txt");
	std::ifstream coordsFile("BD_Coords.txt");

	if (coordsFile.is_open() && timeStampsFile.is_open())
	{
		std::vector<int>	coordsPointIDVector;
		std::vector<double> coordsXVector;
		std::vector<double> coordsYVector;
		std::vector<double> coordsZVector;

		std::string tmpString;

		//skip header
		std::getline(coordsFile, tmpString, '\n');
		while (std::getline(coordsFile, tmpString, '\n'))
		{
			std::vector<std::string> splitStringVector = split(tmpString, '\t');
			coordsPointIDVector.push_back(std::stoi(splitStringVector[0]));
			coordsXVector.push_back(std::stod(splitStringVector[1]));
			coordsYVector.push_back(std::stod(splitStringVector[2]));
			coordsZVector.push_back(std::stod(splitStringVector[3]));
		}
				
		std::vector<double> preparedTimeVector;
		std::vector<int>	preparedPointIDVector;
		std::vector<double> preparedTemperatureVector;
		std::vector<double> preparedDisplacementVector;
		std::vector<double> preparedXVector;
		std::vector<double> preparedYVector;
		std::vector<double> preparedZVector;
		std::vector<std::variant<std::vector<int>, std::vector<double>>> dataPrepared;

		//skip header
		std::getline(timeStampsFile, tmpString, '\n');
		while (std::getline(timeStampsFile, tmpString, '\n'))
		{
			std::vector<int>::iterator it;

			std::vector<std::string> splitStringVector = split(tmpString, '\t');
			it = std::find(coordsPointIDVector.begin(), coordsPointIDVector.end(), std::stoi(splitStringVector[1]));
			if (it != coordsPointIDVector.end())
			{
				int index = std::distance(coordsPointIDVector.begin(), it);
				preparedTimeVector.push_back(std::stod(splitStringVector[0]));
				preparedPointIDVector.push_back(std::stoi(splitStringVector[1]));
				preparedTemperatureVector.push_back(std::stod(splitStringVector[2]));
				preparedDisplacementVector.push_back(std::stod(splitStringVector[3]));
				preparedXVector.push_back(coordsXVector[index]);
				preparedYVector.push_back(coordsXVector[index]);
				preparedZVector.push_back(coordsXVector[index]);
			}
		}

		dataPrepared.push_back(preparedTimeVector);
		dataPrepared.push_back(preparedPointIDVector);
		dataPrepared.push_back(preparedTemperatureVector);
		dataPrepared.push_back(preparedDisplacementVector);
		dataPrepared.push_back(preparedXVector);
		dataPrepared.push_back(preparedYVector);
		dataPrepared.push_back(preparedZVector);

		preparedTimeVector.clear();
		preparedPointIDVector.clear();
		preparedTemperatureVector.clear();
		preparedDisplacementVector.clear();
		preparedXVector.clear();
		preparedYVector.clear();
		preparedZVector.clear();
		coordsPointIDVector.clear();
		coordsXVector.clear();
		coordsYVector.clear();
		coordsZVector.clear();

		coordsFile.close();
		timeStampsFile.close();
	}
}