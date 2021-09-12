#pragma once
#include "Config.h"

enum LengthOfTableFields	// перечисленпие кол-ва читаемых учетных записей 
{
	DATA_FIELD_LENGTH = 14,	// кол-во читаемых учетных записей выводимых в консоль
};

enum IndexConst {
	IND_CONV_FACTOR = 1, // index conversion factor
};

enum DataBuffersSize {
	SUBFILE_SIZE = 7 * DATA_FIELD_LENGTH, // 7*14=98; размер подфайлов для удаления/изменения данных
};


// указатели на соответствующие функции
using readingBinaryFileFnc		= bool(*)(const std::string& dir, std::list<ExamResults>& usersData, const u_int& uDataReadIndBegOut,
										const u_int& uDataReadIndCountOut, u_int& uDataCountOut);
using writeInBinaryFileFnc		= bool(*)(const std::string& dir);
using deletingFromBinaryFileFnc = bool(*)(const std::string& dir, const u_int& droppedInd,
										const u_int& dataCount, writeInBinaryFileFnc writeInBinFileFnc);
using changeDataInBinaryFileFnc	= bool(*)(const std::string& dir, const u_int& changeInd, const u_int& dataCount,
										const ExamResults& userData, writeInBinaryFileFnc writeInBinFile);
using appendInBinaryFileFnc		= bool(*)(const std::string& dir, const u_int& appInd, const bool& offset, const u_int& dataCount,
										const ExamResults& userData, writeInBinaryFileFnc writeInBinFileFnc);

// функция автозаполнения файла
void CreateRandomBinDataset(std::string dir);

// функция чтения файла
bool ReadingBinaryFile(const std::string& dir, std::list<ExamResults>& usersData, const u_int& uDataReadIndBeg,
		const u_int& uDataReadIndCount, u_int& uDataCountOut);
// функция записи в файл
bool WriteInBinaryFile(const std::string& dir);
// функция удаления из файла
bool DeletingFromBinaryFile(const std::string& dir, const u_int& droppedInd,
		const u_int& dataCount, writeInBinaryFileFnc writeInBinFileFnc);
// функция изменения файла
bool ChangeDataInBinaryFile(const std::string& dir, const u_int& changeInd, const u_int& dataCount,
		const ExamResults& userData, writeInBinaryFileFnc writeInBinFile);
// функция добавления в файл
bool AppendInBinaryFile(const std::string& dir, const u_int& appInd, const bool& offset, const u_int& dataCount,
		const ExamResults& userData, writeInBinaryFileFnc writeInBinFileFnc);
