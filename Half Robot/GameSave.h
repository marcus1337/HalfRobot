#pragma once
#include <ctime>
#include <assert.h>

class GameSave {
public:
	GameSave() {
		for (int i = 0; i < 10; i++) {
			levelsCleared[i] = false;
		}
		lives = 15;
	}

	void setLives(int _lives) {
		lives = _lives;
	}

	int getLives() {
		return lives;
	}

	void setLevelCleared(int lvl) {
		assert(lvl >= 0 && lvl < 10);
		levelsCleared[lvl] = true;
	}

	struct CurrentDate {
		std::string year;
		std::string month;
		std::string day;
		int min;
		int hour;
		CurrentDate() {
			updateAge();
		}

		void updateAge() {
			using namespace std;
			time_t t = time(0);
			struct tm now;
			localtime_s(&now, &t);
			year = to_string(now.tm_year + 1900);
			month = to_string(now.tm_mon + 1);
			day = to_string(now.tm_mday);
			min = now.tm_min;
			hour = now.tm_hour;
		}

		void write(std::ostream& f)
		{
			writeStr(f, year);
			writeStr(f, month);
			writeStr(f, day);
			f.write((char*)&hour, sizeof(hour));
			f.write((char*)&min, sizeof(min));

		}
		void read(std::istream& f)
		{
			readStr(f, year);
			readStr(f, month);
			readStr(f, day);
			f.read((char*)&hour, sizeof(hour));
			f.read((char*)&min, sizeof(min));

		}

	private: 
		void writeStr(std::ostream& f, std::string& str) {
			size_t size = str.size();
			f.write((char*)&size, sizeof(size));
			f.write(&str[0], size);
		}

		void readStr(std::istream& f, std::string& str) {
			size_t size;
			f.read((char*)&size, sizeof(size));
			str.resize(size);
			f.read(&str[0], size);
		}

	};

	CurrentDate getAge() {
		return updateTime;
	}

	void setAge(CurrentDate _someDate) {
		updateTime = _someDate;
	}

	void write(std::ostream& f)
	{
		f.write((char*)&lives, sizeof(lives));
		f.write((char*)&levelsCleared, sizeof(levelsCleared));
		updateTime.write(f);
	}
	void read(std::istream& f)
	{
		f.read((char*)&lives, sizeof(lives));
		f.read((char*)&levelsCleared, sizeof(levelsCleared));
		updateTime.read(f);
	}

	bool isLvlClear(int lvl) {
		assert(lvl >= 0 && lvl < 10);
		return levelsCleared[lvl];
	}

	bool allLvlClear() {
		for (int i = 1; i < 9; i++) {
			if (!levelsCleared[i])
				return false;
		}

		return true;
	}

private:
	bool levelsCleared[10];
	CurrentDate updateTime;
	int lives;
};