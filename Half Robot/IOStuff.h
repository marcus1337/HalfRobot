#pragma once
#include "GameSave.h"
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include "Settings.h"
#include <Windows.h>
#include "Shlobj.h"

#ifndef UNICODE  
	typedef std::string String;
#else
	typedef std::wstring String;
#endif

class IOStuff {
public:
	IOStuff(){
		TCHAR szPath[MAX_PATH];
		appdataPath = "";
		if (SUCCEEDED(SHGetFolderPath(NULL,
			CSIDL_APPDATA, NULL, 0, szPath)))
		{
			appdataPath = szPath;
		}
	}

	void saveSettings(Settings& settings) {
		std::ofstream outfile(appdataPath + "settings.data", std::ofstream::binary);
		settings.write(outfile);
		outfile.close();
	}

	void loadSettings(Settings& settings) {
		std::ifstream infile(appdataPath + "settings.data", std::ifstream::binary);
		if (!infile.good()) {
			infile.close();
			return;
		}
		settings.read(infile);
		infile.close();
	}

	void save(GameSave& data) {
		using namespace std;
		GameSave::CurrentDate dataTime = data.getAge();
		dataTime.updateAge();
		data.setAge(dataTime);
		string saveFile = appdataPath + string("slot") + to_string(1) + ".sav";

		ofstream outfile(saveFile, ofstream::binary);
		data.write(outfile);
		outfile.close();
	}

	GameSave load() {
		using namespace std;
		string saveFile = appdataPath + string("slot") + to_string(1) + ".sav";
		ifstream infile(saveFile, ofstream::binary);
		GameSave data;
		data.read(infile);
		infile.close();
		return data;
	}

	bool fileExist() {
		using namespace std;
		string saveFile = appdataPath + string("slot") + to_string(1) + ".sav";
		ifstream infile(saveFile, ofstream::binary);
		bool _exists = infile.good();
		infile.close();
		return _exists;
	}

private:

	String appdataPath;

	static std::string curPATH() {
		using namespace std;
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		string::size_type pos = string(buffer).find_last_of("\\/");
		string test = string(buffer).substr(0, pos);
		test += "\\bin\\save\\";
		return test;
	}

};