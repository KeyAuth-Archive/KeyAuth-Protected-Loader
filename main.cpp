#include <iostream>
#include <Windows.h>
#include <string>
#include <thread>

#include "auth.hpp"
#include "skStr.h"
#include "variables.h"
#include "xor.hpp"
#include "FileDownload.h"
#include "colorize.h"
#include "antiDebug.h"
#include "misc.h"
std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);


int main()
{
	SetConsoleTitleA(skCrypt(" Ohionese Loader "));
	ShellExecute(0, 0, "http://www.discord.gg/fp8pXaUgSn", 0, 0, SW_SHOW); // wow join my server u bastard!
	Misc::MoveCenter();
	Misc::RemoveExtras();
	Misc::PlayMusic("Freestyle.wav"); // this is downloaded locally, if you're going to use it just make sure you set the directory first then play the song

	std::thread antiDBG(AntiDebug::AntiDebug); // create thread for the anit debugging
	antiDBG.detach(); 

	Api::KeyAuthApp.init();
	if (!Api::KeyAuthApp.data.success)
	{
		Sleep(1500);
		exit(0);
	}

	std::string key;
	colorize::coolPrint("Enter License : ", 1);
	std::cin >> key;
	Api::KeyAuthApp.license(key);
	
	if (!Api::KeyAuthApp.data.success)
	{

		colorize::coolPrint(Api::KeyAuthApp.data.message, 3);

		Sleep(1500);
		exit(0);
	}

	Sleep(1000);
	system("CLS");

	

	colorize::coolPrint(xorstr_("Welcome to the Spoofer"), 0);
	
	// if you want something like a one time spoof
	// set a variable up in your keyauth and check if the variable has been changed to whatever your desired value is 
	// then if it's done then boom

	// add options here if you want to ex enter 1 to spoof for battleye etc

	Api::KeyAuthApp.check();
	Explorer::SetPath(""); // set file path ex C:\\windows\\ use 2 \\ not just one
	Explorer::DownloadFile("", ""); // keyauth file number & keyauth file name :)
	Explorer::DownloadFile("", ""); // keyauth file number & keyauth file name :)

	system("start kdmapper.exe driver.sys"); // start your driver
	system("CLS");
	colorize::coolPrint(xorstr_("Spoofed, Enjoy your day!"), 0);

	
	
	Sleep(10000);
	exit(0);
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}


static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}
