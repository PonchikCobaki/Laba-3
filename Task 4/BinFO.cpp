#include "BinFO.h"

// ������� �������������� �����
void CreateRandomBinDataset(std::string dir)
{
	using namespace std;
	using std::cout;
	random_device rd;
	mt19937 mersenne(rd());

	u_short size;
	cout << "���������� ������� �������: ";
	cin >> size;
	string firstNames[] = { "����", "ϸ��", "�������", "�����", "��������",
		"������", "���", "������", "����", "����" };
	string lastNames[] = { "������", "ϸ����", "����������", "�������",
		"�����������", "��������", "���������", "�����", "����������", "���������" };
	ExamResultsBinary users;


	ofstream outBinFile(dir, ios::binary);
	for (u_int i = 0; i < size; i++) {
		strcpy_s(users.firstName, LENGTH_FIRST_NAME, firstNames[mersenne() % 10].c_str());
		strcpy_s(users.lastName, LENGTH_LAST_NAME, lastNames[mersenne() % 10].c_str());
		users.mathScore = mersenne() % 101;
		users.ruLangScore = mersenne() % 101;
		users.enLangScore = mersenne() % 101;

		//strcpy_s(users.firstName, LENGTH_FIRST_NAME, firstNames[i % 10].c_str());
		//strcpy_s(users.lastName, LENGTH_LAST_NAME, lastNames[i % 10].c_str());
		//users.mathScore = i % 101;
		//users.ruLangScore = i % 101;
		//users.enLangScore = i % 101;

		outBinFile.write(users.firstName, sizeof(*users.lastName) * LENGTH_FIRST_NAME);
		outBinFile.write(users.lastName, sizeof(*users.firstName) * LENGTH_LAST_NAME);
		outBinFile.write((char*)&users.mathScore, sizeof(users.mathScore));
		outBinFile.write((char*)&users.ruLangScore, sizeof(users.ruLangScore));
		outBinFile.write((char*)&users.enLangScore, sizeof(users.enLangScore));

		//cout << i + 1 << " " << setw(FIRST_NAME_FIELD_WIDTH) << users.firstName << " " << setw(LAST_NAME_FIELD_WIDTH) 
		//	<< users.lastName << " " << setw(MATCH_SCORE_FIELD_WIDTH) << users.mathScore <<
		//	" " << setw(RU_SCORE_FIELD_WIDTH) << users.ruLangScore << " " << setw(EN_SCORE_FIELD_WIDTH) << users.enLangScore << endl;
	}
	outBinFile.close();
	cout << "END" << endl;
	system("pause");
}

// ������� ������ �����
bool ReadingBinaryFile(const std::string& dir, std::list<ExamResults>& usersData, const u_int& dataReadIndBeg,
	const u_int& dataReadIndCount, u_int& dataCountOut)
{
	using namespace std;

	// �������� �����
	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening input buffer file on time reading" << endl;
		system("pause");
		return true;
	}

	ExamResultsBinary dataBuffer = {};


	// �������� ������ �����
	usersData.clear();
	usersData.resize(dataReadIndCount);
	inBinFile.seekg(dataReadIndBeg * dataBuffer.writeSize, ios::beg);

	auto userData = usersData.begin();
	for (u_int i = 0; i < dataReadIndCount; ++i, ++userData) {

		// ������ � ���������-������ ��� ��������� �����
		inBinFile.read(dataBuffer.firstName, sizeof(*dataBuffer.firstName) * LENGTH_FIRST_NAME);
		inBinFile.read(dataBuffer.lastName, sizeof(*dataBuffer.lastName) * LENGTH_LAST_NAME);
		inBinFile.read(reinterpret_cast<char*>(&dataBuffer.mathScore), sizeof(dataBuffer.mathScore));
		inBinFile.read(reinterpret_cast<char*>(&dataBuffer.ruLangScore), sizeof(dataBuffer.ruLangScore));
		inBinFile.read(reinterpret_cast<char*>(&dataBuffer.enLangScore), sizeof(dataBuffer.enLangScore));

		// ������ ��������� � ����
		userData->firstName = string(dataBuffer.firstName);
		userData->lastName = string(dataBuffer.lastName);
		userData->mathScore = dataBuffer.mathScore;
		userData->ruLangScore = dataBuffer.ruLangScore;
		userData->enLangScore = dataBuffer.enLangScore;
		userData->totalScore = userData->mathScore + userData->ruLangScore + userData->enLangScore;
	}

	// ������ ���-�� ������
	dataCountOut = inBinFile.seekg(0, ios::end).tellg() / dataBuffer.writeSize;
	inBinFile.seekg(dataReadIndBeg * dataBuffer.writeSize, ios::beg);

	inBinFile.close();

	return false;
}

// ������� ������ � ����
bool WriteInBinaryFile(const std::string& dir)
{
	using namespace std;

	// ������� �����
	ofstream binFile(dir, ios::binary | ios::trunc);
	binFile.close();

	string	dirBuf = dir.substr(0, dir.length() - 4) + "_buffer"s
		+ dir.substr(dir.length() - 4, 4);
	u_int	bufFileSize;
	ExamResultsBinary confVal;
	char* dataBuffer = new char[confVal.writeSize];

	// ������ ������ � �������� ���� �� ��������� �����	//

	// ����������� ������� ����� �������
	ifstream inBufBinFile(dirBuf, ios::binary);
	if (!inBufBinFile.is_open()) {
		cerr << "Error opening input buffer file on time writing" << endl;
		system("pause");
		return true;
	}
	bufFileSize = inBufBinFile.seekg(0, ios::end).tellg() / confVal.writeSize;
	inBufBinFile.seekg(0, ios::beg);

	// ������� �������� � ������ �������� ������� �����
	if (bufFileSize == 0) {
		inBufBinFile.close();
	}
	else {
		ofstream outBinFile(dir, ios::binary | ios::app);
		if (!outBinFile.is_open()) {
			cerr << "Error opening output file on time writing" << endl;
			system("pause");
			return true;
		}

		// ������
		for (u_int j = 0; j < bufFileSize; ++j) {
			inBufBinFile.read(dataBuffer, confVal.writeSize);
			outBinFile.write(dataBuffer, confVal.writeSize);
		}
		inBufBinFile.close();
		outBinFile.close();
		//cout << "\n";
	}

	remove(dirBuf.c_str());	// �������� ��������
	return false;
}

// ������� �������� �� �����
bool DeletingFromBinaryFile(const std::string& dir, const u_int& droppedInd,
	const u_int& dataCount, writeInBinaryFileFnc writeInBinFileFnc)
{
	using namespace std;

	// ����������� ��� ������ � ���������
	string	dirBuf = dir.substr(0, dir.length() - 4) + "_buffer"s
		+ dir.substr(dir.length() - 4, 4);

	// ����������� ��� ������ � �������
	ExamResultsBinary confVal;
	char* dataBuffer = new char[confVal.writeSize];

	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening input file on time deleting" << endl;
		system("pause");
		return true;
	}

	// ������ ������ � ������� //

	// ������� ��������, ���� �� ��� ����������
	ofstream outFile(dirBuf, ios::binary | ios::trunc);
	outFile.close();


	// ������
	ofstream outBufBinFile(dirBuf, ios::binary | ios::app);
	if (!outBufBinFile) {
		cerr << "Error opening output buffer file on time deleting" << endl;
		system("pause");
		return true;
	}
	for (u_int dataInd = 0; dataInd < dataCount; ++dataInd) {
		// �������� ��������, ����� �������� ��� ������ � �������
		if (droppedInd != dataInd) {
			inBinFile.read(dataBuffer, confVal.writeSize);
			outBufBinFile.write(dataBuffer, confVal.writeSize);
		}
		else {
			//inBinFile.seekg(confVal.writeSize, ios::cur);	// ������� ������ ��������� �����
			inBinFile.read(confVal.firstName, sizeof(*confVal.firstName) * LENGTH_FIRST_NAME);
			inBinFile.read(confVal.lastName, sizeof(*confVal.lastName) * LENGTH_LAST_NAME);
			inBinFile.read(reinterpret_cast<char*>(&confVal.mathScore), sizeof(confVal.mathScore));
			inBinFile.read(reinterpret_cast<char*>(&confVal.ruLangScore), sizeof(confVal.ruLangScore));
			inBinFile.read(reinterpret_cast<char*>(&confVal.enLangScore), sizeof(confVal.enLangScore));
			cout << dataInd << "delete structre: " << confVal.firstName << " " << confVal.lastName << " " << confVal.mathScore
				<< " " << confVal.ruLangScore << " " << confVal.enLangScore << endl;
			//inBinFile.read(dataBuffer, confVal.writeSize);
			//cout << "dataInd " << dataInd << " data " << dataBuffer << endl;
		}
	}
	outBufBinFile.close();

	inBinFile.close();


	// ������ � �������� ���� ��������� ������
	writeInBinFileFnc(dir);
	return false;
}

// ������� ��������� �����
bool ChangeDataInBinaryFile(const std::string& dir, const u_int& changeInd, const u_int& dataCount,
	const ExamResults& userData, writeInBinaryFileFnc writeInBinFileFnc)
{
	using namespace std;

	// ����������� ��� ������ � ���������
	string	dirBuf = dir.substr(0, dir.length() - 4) + "_buffer"s
		+ dir.substr(dir.length() - 4, 4);

	// ����������� ��� ������ � �������
	ExamResultsBinary uDataBin;
	char* dataBuffer = new char[uDataBin.writeSize];

	// ������ ������ � ��������	//
	// ������� ��������, ���� �� ��� ����������
	ofstream outFile(dirBuf, ios::binary | ios::trunc);
	outFile.close();

	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening input file on time change" << endl;
		system("pause");
		return true;
	}
	// ������ � �������
	ofstream outBufBinFile(dirBuf, ios::binary | ios::app);
	if (!outBufBinFile) {
		cerr << "Error opening output buffer file on time change" << endl;
		system("pause");
		return true;
	}
	for (u_int dataInd = 0; dataInd < dataCount; ++dataInd) {
		// ��������� ��������
		if (changeInd != dataInd) {
			inBinFile.read(dataBuffer, uDataBin.writeSize);
			outBufBinFile.write(dataBuffer, uDataBin.writeSize);
		}
		else {
			inBinFile.seekg(uDataBin.writeSize, ios::cur);

			// ����������� ������ � ��������� ��� ������
			strcpy_s(uDataBin.firstName, LENGTH_FIRST_NAME, userData.firstName.c_str());
			strcpy_s(uDataBin.lastName, LENGTH_LAST_NAME, userData.lastName.c_str());
			uDataBin.mathScore = userData.mathScore;
			uDataBin.ruLangScore = userData.ruLangScore;
			uDataBin.enLangScore = userData.enLangScore;

			// ������ ���������
			outBufBinFile.write(uDataBin.firstName, sizeof(*uDataBin.lastName) * LENGTH_FIRST_NAME);
			outBufBinFile.write(uDataBin.lastName, sizeof(*uDataBin.firstName) * LENGTH_LAST_NAME);
			outBufBinFile.write((char*)&uDataBin.mathScore, sizeof(uDataBin.mathScore));
			outBufBinFile.write((char*)&uDataBin.ruLangScore, sizeof(uDataBin.ruLangScore));
			outBufBinFile.write((char*)&uDataBin.enLangScore, sizeof(uDataBin.enLangScore));
		}
	}

	outBufBinFile.close();
	inBinFile.close();

	// ������ � �������� ���� ��������� ������
	writeInBinFileFnc(dir);
	return false;
}

// ������� ���������� � ����
bool AppendInBinaryFile(const std::string& dir, const u_int& appInd, const bool& offset, const u_int& dataCount,
	const ExamResults& userData, writeInBinaryFileFnc writeInBinFileFnc)
{
	using namespace std;

	// ����������� ��� ������ � ���������
	string	dirBuf = dir.substr(0, dir.length() - 4) + "_buffer"s
		+ dir.substr(dir.length() - 4, 4);

	// ����������� ��� ������ � �������
	ExamResultsBinary uDataBin;
	char* dataBuffer = new char[uDataBin.writeSize];

	// ������ ������ � ��������	//
	// ������� ��������, ���� �� ��� ����������
	ofstream outFile(dirBuf, ios::binary | ios::trunc);
	outFile.close();

	ifstream inBinFile(dir, ios::binary);
	if (!inBinFile) {
		cerr << "Error opening input file on time change" << endl;
		system("pause");
		return true;
	}
	// ������ � �������
	ofstream outBufBinFile(dirBuf, ios::binary | ios::app);
	if (!outBufBinFile) {
		cerr << "Error opening output buffer file on time change" << endl;
		system("pause");
		return true;
	}
	for (u_int dataInd(0); dataInd < dataCount; ++dataInd) {
		// ��������� ��������
		if (appInd != dataInd) {
			inBinFile.read(dataBuffer, uDataBin.writeSize);
			outBufBinFile.write(dataBuffer, uDataBin.writeSize);
		}
		else {
			if (offset == true) {
				inBinFile.read(dataBuffer, uDataBin.writeSize);
				outBufBinFile.write(dataBuffer, uDataBin.writeSize);
			}

			// ����������� ������ � ��������� ��� ������
			strcpy_s(uDataBin.firstName, LENGTH_FIRST_NAME, userData.firstName.c_str());
			strcpy_s(uDataBin.lastName, LENGTH_LAST_NAME, userData.lastName.c_str());
			uDataBin.mathScore = userData.mathScore;
			uDataBin.ruLangScore = userData.ruLangScore;
			uDataBin.enLangScore = userData.enLangScore;

			// ������ ���������
			outBufBinFile.write(uDataBin.firstName, sizeof(*uDataBin.lastName) * LENGTH_FIRST_NAME);
			outBufBinFile.write(uDataBin.lastName, sizeof(*uDataBin.firstName) * LENGTH_LAST_NAME);
			outBufBinFile.write((char*)&uDataBin.mathScore, sizeof(uDataBin.mathScore));
			outBufBinFile.write((char*)&uDataBin.ruLangScore, sizeof(uDataBin.ruLangScore));
			outBufBinFile.write((char*)&uDataBin.enLangScore, sizeof(uDataBin.enLangScore));

			if (offset == false) {
				inBinFile.read(dataBuffer, uDataBin.writeSize);
				outBufBinFile.write(dataBuffer, uDataBin.writeSize);
			}
		}
	}

	outBufBinFile.close();
	inBinFile.close();

	// ������ � �������� ���� ��������� ������
	writeInBinFileFnc(dir);
	return false;
}
