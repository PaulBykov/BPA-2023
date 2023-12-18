#include <string>
#include <iostream>
#include <filesystem>
#include <stdio.h> 
#include <direct.h>
#include "windows.h"

namespace fs = std::filesystem;

using namespace std;


const string exePath = "D:/LABS2/BPA-2023/result/BPA-2023.exe";
const string testCaseFolder = "D:/LABS2/BPA-2023/result/TEST_CASES";


int main() {
	setlocale(LC_ALL, "rus");

	try {
		for (auto& entry : fs::directory_iterator(testCaseFolder)) {
			if (entry.is_directory()) {
				for (auto& fileEntry : fs::directory_iterator(entry.path())) {
					if (fileEntry.is_regular_file() && fileEntry.path().extension() == ".txt") {
						string parameter = "-in:" + fileEntry.path().string();
						string command = exePath + " " + parameter;

						cout << "\nTEST: " << fileEntry.path().filename() << "\n";
						int result = system(command.c_str());

					}
				}
			}
		}
	}
	catch (exception err) {
		cout << err.what() << "\n";
	}


	system("pause");
	return 0;

}
