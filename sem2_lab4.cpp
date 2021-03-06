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

struct dataStruct
{
	std::vector<double> timeVector;
	std::vector<int> pointIDVector;
	std::vector<double> temperatureVector;
	std::vector<double> displacementVector;
	std::vector<double> xVector;
	std::vector<double> yVector;
	std::vector<double> zVector;
};

void PrepareData(dataStruct* preparedDataStruct, const char* timeStampsFileName, const char* coordsFileName)
{
	std::ifstream timeStampsFile(timeStampsFileName);
	std::ifstream coordsFile(coordsFileName);

	if (coordsFile.is_open() && timeStampsFile.is_open())
	{
		std::vector<int> coordsPointIDVector;
		std::vector<double> coordsXVector, coordsYVector, coordsZVector;

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

		std::vector<int> preparedPointIDVector;
		std::vector<double> preparedTimeVector, preparedTemperatureVector, preparedDisplacementVector;
		std::vector<double> preparedXVector, preparedYVector, preparedZVector;

		//skip header
		std::getline(timeStampsFile, tmpString, '\n');
		while (std::getline(timeStampsFile, tmpString, '\n'))
		{
			std::vector<int>::iterator it;

			std::vector<std::string> splitStringVector = split(tmpString, '\t');
			it = std::find(coordsPointIDVector.begin(), coordsPointIDVector.end(), std::stoi(splitStringVector[1]));
			if (it != coordsPointIDVector.end())
			{
				int index = (int)std::distance(coordsPointIDVector.begin(), it);
				preparedTimeVector.push_back(std::stod(splitStringVector[0]));
				preparedPointIDVector.push_back(std::stoi(splitStringVector[1]));
				preparedTemperatureVector.push_back(std::stod(splitStringVector[2]));
				preparedDisplacementVector.push_back(std::stod(splitStringVector[3]));
				preparedXVector.push_back(coordsXVector[index]);
				preparedYVector.push_back(coordsYVector[index]);
				preparedZVector.push_back(coordsZVector[index]);
			}
		}

		preparedDataStruct->timeVector = preparedTimeVector;
		preparedDataStruct->pointIDVector = preparedPointIDVector;
		preparedDataStruct->temperatureVector = preparedTemperatureVector;
		preparedDataStruct->displacementVector = preparedDisplacementVector;
		preparedDataStruct->xVector = preparedXVector;
		preparedDataStruct->yVector = preparedYVector;
		preparedDataStruct->zVector = preparedZVector;

		coordsFile.close();
		timeStampsFile.close();
	}
}

void SavePreparedData(dataStruct *preparedDataStruct, const char* outFileName)
{
	std::ofstream outFile(outFileName);

	if (outFile.is_open())
	{
		//output header
		outFile << "Time\tPoint ID\tTemperature\tDisplacement X\tX\tY\tZ" << std::endl;

		for (int i = 0; i < (int)preparedDataStruct->pointIDVector.size(); i++)
		{
			outFile << preparedDataStruct->timeVector[i] << '\t' << preparedDataStruct->pointIDVector[i] << '\t' <<
				preparedDataStruct->temperatureVector[i] << '\t' << preparedDataStruct->displacementVector[i] << '\t' <<
				preparedDataStruct->xVector[i] << '\t' << preparedDataStruct->yVector[i] << '\t' <<
				preparedDataStruct->zVector[i] << std::endl;
		}

		outFile.close();
	}
}

void SaveFiltredDate(dataStruct* filtredDataStruct, const char* outFileName)
{
	std::ofstream outFile(outFileName);

	if (outFile.is_open())
	{
		//output header
		outFile << "Time\tPoint ID\tTemperature\tDisplacement X\tX\tY\tZ" << std::endl;

		for (int i = 0; i < (int)filtredDataStruct->pointIDVector.size(); i++)
		{
			outFile << filtredDataStruct->timeVector[i] << '\t' << filtredDataStruct->pointIDVector[i] << '\t' <<
				filtredDataStruct->temperatureVector[i] << '\t' << filtredDataStruct->displacementVector[i] << '\t' <<
				filtredDataStruct->xVector[i] << '\t' << filtredDataStruct->yVector[i] << '\t' <<
				filtredDataStruct->zVector[i] << std::endl;
		}

		outFile.close();
	}
}

void FilterPreparedData(dataStruct* preparedDataStruct, dataStruct* filtredDataStructPtr)
{
	double filterByX, filterByY, filterByZ, filterByTime;

	std::cout << "Enter X: ";
	std::cin >> filterByX;
	std::cout << "Enter Y: ";
	std::cin >> filterByY;
	std::cout << "Enter Z: ";
	std::cin >> filterByZ;
	std::cout << "Enter Time: ";
	std::cin >> filterByTime;

	std::cout << "\nTime\tPoint ID\tTemperature\tDisplacement X\tX\tY\tZ" << std::endl;
	for (int i = 0; i < (int)preparedDataStruct->pointIDVector.size(); i++)
	{
		if (preparedDataStruct->xVector[i] == filterByX
			&& preparedDataStruct->yVector[i] == filterByY
			&& preparedDataStruct->zVector[i] == filterByZ
			&& preparedDataStruct->timeVector[i] == filterByTime)
		{
			filtredDataStructPtr->timeVector.push_back(preparedDataStruct->timeVector[i]);
			filtredDataStructPtr->pointIDVector.push_back(preparedDataStruct->pointIDVector[i]);
			filtredDataStructPtr->temperatureVector.push_back(preparedDataStruct->temperatureVector[i]);
			filtredDataStructPtr->displacementVector.push_back(preparedDataStruct->displacementVector[i]);
			filtredDataStructPtr->xVector.push_back(preparedDataStruct->xVector[i]);
			filtredDataStructPtr->yVector.push_back(preparedDataStruct->yVector[i]);
			filtredDataStructPtr->zVector.push_back(preparedDataStruct->zVector[i]);

			std::cout << preparedDataStruct->timeVector[i] << '\t' << preparedDataStruct->pointIDVector[i] << '\t' <<
				preparedDataStruct->temperatureVector[i] << '\t' << preparedDataStruct->displacementVector[i] << '\t' <<
				preparedDataStruct->xVector[i] << '\t' << preparedDataStruct->yVector[i] << '\t' <<
				preparedDataStruct->zVector[i] << std::endl;
		}
		
	}

}

int main()
{
	dataStruct preparedDataStruct, * preparedDataStructPtr;
	dataStruct filtredDataStruct, * filtredDataStructPtr;
	preparedDataStructPtr = &preparedDataStruct;
	filtredDataStructPtr = &filtredDataStruct;

	// 1. Подготавливаем данные для обработки
	PrepareData(preparedDataStructPtr, "BD.txt", "BD_Coords.txt");

	// 2. Записываем подготовленные данные в файл
	SavePreparedData(preparedDataStructPtr, "BD_Out.txt");

	// 3. Взаимодействие с пользователем и сохранение отфильтрованных данных в файл
	FilterPreparedData(preparedDataStructPtr, filtredDataStructPtr);
	SaveFiltredDate(filtredDataStructPtr, "BD_FiltredOut.txt");
	
}