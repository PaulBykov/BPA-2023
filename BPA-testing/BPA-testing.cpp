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

const string logsFolder = "D:/LABS2/BPA-2023/result/logs";
const string outputsFolder = "D:/LABS2/BPA-2023/result/outputs";


int main(){
    setlocale(LC_ALL, "rus");

    try{
        for (auto& entry : fs::directory_iterator(testCaseFolder)) {
            if (entry.is_directory()) {
                for (auto& fileEntry : fs::directory_iterator(entry.path())) {
                    if (fileEntry.is_regular_file() && fileEntry.path().extension() == ".txt") {
                        std::string parameter = "-in:" + fileEntry.path().string();
                        std::string command = exePath + " " + parameter;

                        std::cout << "\nTEST: " << fileEntry.path().filename() << "\n";
                        int result = system(command.c_str());

                        if (result != 0) {
                            std::cout << "Ошибка при передаче файла " << fileEntry.path().filename() << " как параметра." << std::endl;
                        }
                    }
                }
            }
        }
    }
    catch(exception err) {
        cout << err.what() << "\n";
    }


    system("pause");
    return 0;
  
}
