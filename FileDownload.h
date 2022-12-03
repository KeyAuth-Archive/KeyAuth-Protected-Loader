#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <skStr.h>
#include <fstream>

#include "variables.h"
#include <filesystem>

namespace Explorer {

	void DownloadFile(std::string fileNumber, std::string fileName)
	{
		std::vector<std::uint8_t> bytes = Api::KeyAuthApp.download(fileNumber);

		if (!Api::KeyAuthApp.data.success) // check whether file downloaded correctly
		{
			Sleep(1500);
			exit(0);
		}

		std::ofstream file(fileName, std::ios_base::out | std::ios_base::binary);
		file.write((char*)bytes.data(), bytes.size());
		file.close();
	}

	void SetPath(std::string path)
	{
		std::filesystem::current_path(path);
	}
}