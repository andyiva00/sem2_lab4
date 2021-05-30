// Курс: 1, Семестр: 2, Группа: МКН-116
// Лабораторная работа: №4, Вариант: 6
// Студенит: Тимофеев Денис

//TODO: Оптимизировать хранение данных или поиск данных из большого файла
//TODO: Индексация векторов, если такое возможно
//TODO: Вывести на экран данные для пользовательской точки с координатами (X, Y, Z)
//TODO: Записать получившийся вектор во внешний файл
//TODO: Записать в файл выборку согласно условию из ТЗ (Информация о средней температуре в каждый момент времени)

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<double> split(const std::string str, char delim)
{
	std::vector<double> tmpVector;
	std::stringstream tmpStr;
	tmpStr.str(str);
	std::string segment;
	
	//int for ther first string
	std::getline(tmpStr, segment, delim);
	tmpVector.push_back(std::stoi(segment));
	
	//double for others
	while (std::getline(tmpStr, segment, delim))
	{
		tmpVector.push_back(std::stod(segment));
	}
	return tmpVector;
}

int main()
{
	std::ifstream timeStampsFile("BD.txt");
	std::ifstream coordsFile("BD_Coords.txt");

	std::vector<std::vector<double>> dataCoords;

	if (coordsFile.is_open())
	{
		std::string coordsLine;

		//skip header
		std::getline(coordsFile, coordsLine, '\n');
		while (std::getline(coordsFile, coordsLine, '\n'))
		{
			dataCoords.push_back(split(coordsLine, '\t'));
		}

		coordsFile.close();
	}

	if (timeStampsFile.is_open())
	{
		std::string timeStampsLine;
		std::vector<std::vector<double>> dataVector;

		//skip header
		std::getline(timeStampsFile, timeStampsLine, '\n');
		while (std::getline(timeStampsFile, timeStampsLine, '\n'))
		{
			std::vector<double> vectorLine = split(timeStampsLine, '\t');
			double curPointID = vectorLine[1];
			for (auto& dataCoordsVector : dataCoords)
			{
				if (curPointID == dataCoordsVector[0])
				{
					vectorLine.push_back(dataCoordsVector[1]);
					vectorLine.push_back(dataCoordsVector[2]);
					vectorLine.push_back(dataCoordsVector[3]);
					dataVector.push_back(vectorLine);
					break;
				}
			}
		}
		timeStampsFile.close();
	}
}