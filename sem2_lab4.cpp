// Курс: 1, Семестр: 2, Группа: МКН-116
// Лабораторная работа: №4, Вариант: 6
// Студенит: Тимофеев Денис

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

std::vector<float> split(const std::string str, char delim)
{
	std::vector<float> tmpVector;
	std::stringstream tmpStr;
	tmpStr.str(str);
	std::string segment;
	while (std::getline(tmpStr, segment, delim))
	{
		tmpVector.push_back(::atof(segment.c_str()));
	}
	return tmpVector;
}

int main()
{
	std::ifstream timeStampsFile("BD.txt");
	std::ifstream coordsFile("BD_Coords.txt");

	if (timeStampsFile.is_open() && coordsFile.is_open())
	{
		std::string timeStampsLine;
		std::string coordsLine;

		std::vector<std::vector<float>> dataVector;

		//skip header
		std::getline(timeStampsFile, timeStampsLine, '\n');
		while (std::getline(timeStampsFile, timeStampsLine, '\n'))
		{
			std::vector<float> vectorLine = split(timeStampsLine, '\t');
			float curPointID = vectorLine[1];

			coordsFile.clear();
			coordsFile.seekg(0);

			//skip header
			std::getline(coordsFile, coordsLine, '\n');
			while (std::getline(coordsFile, coordsLine, '\n'))
			{
				std::vector<float> vectorCoords = split(coordsLine, '\t');
				if (curPointID == vectorCoords[0])
				{
					vectorLine.push_back(vectorCoords[1]);
					vectorLine.push_back(vectorCoords[2]);
					vectorLine.push_back(vectorCoords[3]);
					dataVector.push_back(vectorLine);
					break;
				}
			}
		}

		//TODO: Оптимизировать хранение данных или поиск данных из большого файла
		//TODO: Индексация векторов, если такое возможно
		//TODO: Вывести на экран данные для пользовательской точки с координатами (X, Y, Z)
		//TODO: Записать получившийся вектор во внешний файл
		//TODO: Записать в файл выборку согласно условию из ТЗ (Информация о средней температуре в каждый момент времени)

		timeStampsFile.close();
		coordsFile.close();
	}

}