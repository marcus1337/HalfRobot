#pragma once
#include <fstream>

class Settings {
public:
	Settings() {
		soundOn = true;
		_w = -1;
		_h = -1;
	}

	void setWH(int w, int h) {
		_w = w;
		_h = h;
	}

	void getWH(int& w, int& h) {
		w = _w;
		h = _h;
	}

	int getW() {
		return _w;
	}

	int getH() {
		return _h;
	}

	bool isSoundOn() {
		return soundOn;
	}

	void setSoundOn(bool _soundOn) {
		soundOn = _soundOn;
	}

	void write(std::ostream& f)
	{
		f.write((char*)&soundOn, sizeof(soundOn));
		f.write((char*)&_w, sizeof(_w));
		f.write((char*)&_h, sizeof(_h));

	}
	void read(std::ifstream& f)
	{
		f.read((char*)&soundOn, sizeof(soundOn));
		f.read((char*)&_w, sizeof(_w));
		f.read((char*)&_h, sizeof(_h));
	
	}

private:
	bool soundOn;
	int _w; int _h;

};