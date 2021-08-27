#pragma once
#include "Config.h"

enum LengthOfTableFields
{
	DATA_FIELD_LENGTH = 14,
	OUR_FIELD_LENGTH = 35,
};

enum IndexConst {
	IND_CONV_FACTOR = 1, // index conversion factor
};

enum DataBuffersSize {
	SUBFILE_SIZE = 7 * DATA_FIELD_LENGTH, // 7*14=98; размер подфайлов для удаления/изменения данных
};



using readingBinaryFileFnc =		void(*)(const std::string& dir, std::list<ExamResults>& usersData, const u_int& uDataReadIndBegOut,
										const u_int& uDataReadIndCountOut, u_int& uDataCountOut);
using writeInBinaryFileFnc =		void(*)(const std::string& dir);
using deletingFromBinaryFileFnc =	void(*)(const std::string& dir, const u_int& droppedInd,
										const u_int& dataCount, writeInBinaryFileFnc writeInBinFileFnc);
using changeDataInBinaryFileFnc =	void(*)(const std::string& dir, const u_int& changeInd, const u_int& dataCount,
										const ExamResults& userData, writeInBinaryFileFnc writeInBinFile);
using appendInBinaryFileFnc =		void(*)(const std::string& dir, const u_int& appInd, const bool& offset, const u_int& dataCount,
										const ExamResults& userData, writeInBinaryFileFnc writeInBinFileFnc);


void CreateRandomBinDataset(std::string dir);


void ReadingBinaryFile(const std::string& dir, std::list<ExamResults>& usersData, const u_int& uDataReadIndBegOut,
		const u_int& uDataReadIndCountOut, u_int& uDataCountOut);
void WriteInBinaryFile(const std::string& dir);
void DeletingFromBinaryFile(const std::string& dir, const u_int& droppedInd,
		const u_int& dataCount, writeInBinaryFileFnc writeInBinFileFnc);
void ChangeDataInBinaryFile(const std::string& dir, const u_int& changeInd, const u_int& dataCount,
		const ExamResults& userData, writeInBinaryFileFnc writeInBinFile);
void AppendInBinaryFile(const std::string& dir, const u_int& appInd, const bool& offset, const u_int& dataCount,
		const ExamResults& userData, writeInBinaryFileFnc writeInBinFileFnc);

//
//void PrintSearchItem();
//
//void PrintAppendItem();
//
//void PrintStatisticsItem();
//

