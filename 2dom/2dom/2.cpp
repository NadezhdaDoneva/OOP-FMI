// 2dom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#pragma warning (disable : 4996)
using namespace std;


namespace GlobalConstants {
    constexpr int MAX_SONG_NAME_SIZE = 64;
    constexpr int MAX_CONTENT_SIZE = 256;
	constexpr unsigned SECONDS_IN_HOURS = 3600;
	constexpr unsigned SECONDS_IN_MINUTE = 60;
	constexpr unsigned DAY_SECONDS = 24 * 3600;
	constexpr unsigned MAX_MINUTES_PER_HOUR = 59;
	constexpr unsigned MAX_SECONDS_PER_MINUTE = 59;
	constexpr unsigned MAX_COUNT_GENRES = 5;
	constexpr unsigned MAX_SONGS_IN_PLAYLIST = 30;
}

//class Time - we will use it for Song duration
class Time
{
private:
	unsigned timeInSeconds = 0;

	bool validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldVlaue, unsigned multiplier)
	{

		if (newValue >= lowerBound && newValue <= upperBound)
		{
			(timeInSeconds -= (oldVlaue * multiplier)) += (newValue * multiplier);
			return true;
		}
		else
			return false;
	}


public:

	Time() = default;
	Time(unsigned hours, unsigned mins, unsigned seconds)
	{
		setHours(hours);
		setMins(mins);
		setSeconds(seconds);
	}

	unsigned getTimeInSeconds() const {
		return timeInSeconds;
	}

	unsigned getHours() const
	{
		return timeInSeconds / GlobalConstants::SECONDS_IN_HOURS;
	}

	unsigned getMins() const
	{
		return (timeInSeconds / 60) % 60;
	}

	unsigned getSeconds() const
	{
		return timeInSeconds % 60;
	}
	bool setHours(unsigned hours)
	{
		//return validateAndSet(0, 23, hours, getHours(), GlobalConstants::SECONDS_IN_HOURS);
		return timeInSeconds += hours * GlobalConstants::SECONDS_IN_HOURS;
	}

	bool setMins(unsigned mins)
	{
		return validateAndSet(0, GlobalConstants::MAX_MINUTES_PER_HOUR, mins, getMins(), GlobalConstants::SECONDS_IN_MINUTE);
	}
	bool setSeconds(unsigned seconds)
	{
		return validateAndSet(0, GlobalConstants::MAX_SECONDS_PER_MINUTE, seconds, getSeconds(), 1);
	}

	void formatedPrint(unsigned time) const {
		if (time <= 9) {
			cout << 0 << time;
		}
		else {
			cout << time;
		}
	}

	void printTime() const {
		unsigned hours = getHours();
		unsigned minutes = getMins();
		unsigned seconds = getSeconds();

		formatedPrint(hours);
		cout << ':';
		formatedPrint(minutes);
		cout << ':';
		formatedPrint(seconds);
	}
};


enum class Genre : char {
    Rock = 1,
    Pop = 1 << 1,
    HipHop = 1 << 2,
    Electronic = 1 << 3,
    Jazz = 1 << 4
};


class Song {
private:
	char name[GlobalConstants::MAX_SONG_NAME_SIZE] = "";
	Time duration;
	char genre = 0;
	char content[GlobalConstants::MAX_CONTENT_SIZE] = "";
	bool isOk = true;

public:
	//constructors
	Song() = default;
	Song(const char* name, const Time& duration, const char* genre, const char* fileName) {
		setName(name);
		setDuration(duration);
		setGenre(genre);
		setContent(fileName);
	}

	//getters
	const char* getName() const {
		return name;
	}

	Time getDuration() const {
		return duration;
	}

	char getGenre() const {
		return genre;
	}

	const char* getContent() const {
		return content;
	}


	//setters
	bool setName(const char* name) {
		if (!name) {
			return false;
		}

		strcpy(this->name, name);
		return true;
	}

	void setDuration(const Time& duration) {
		this->duration = duration;
	}

	bool setGenre(const char* genre) {
		while (*genre) {
			if (*genre == 'r') {
				this->genre |= (int)Genre::Rock;
			}
			else if (*genre == 'p') {
				this->genre |= (int)Genre::Pop;
			}
			else if (*genre == 'h') {
				this->genre |= (int)Genre::HipHop;
			}
			else if (*genre == 'e') {
				this->genre |= (int)Genre::Electronic;
			}
			else if (*genre == 'j') {
				this->genre |= (int)Genre::Jazz;
			}
			else {
				return false;
			}
			genre++;
		}
		return true;
	}

	bool setContent(const char* fileName) {
		std::ifstream ifs(fileName, std::ios::binary);

		if (!ifs.is_open()) {
			return false;
		}

		ifs.read((char*)&content, GlobalConstants::MAX_CONTENT_SIZE);
		ifs.close();
		return true;
	}


	//modifying songs functionalities
	void createNewRythm(const size_t k, const char* filename) {
		for (size_t i = k; i < strlen(content) * 8; i += k) {
			int idxOfChar = strlen(content) - i;
			if (idxOfChar < 0) {
				break;
			}
			content[idxOfChar] |= 1;
		}
		save(filename);
	}

		void mixSongs(Song& firstSong, const Song& secondSong) {
			char newContent[GlobalConstants::MAX_CONTENT_SIZE] = "";
			for (size_t i = 0; i < strlen(firstSong.getContent()); i++) {
				if (i >= strlen(secondSong.getContent())) {
					newContent[i] = firstSong.getContent()[i];
				}
				else {
					newContent[i] = firstSong.getContent()[i];
					newContent[i] ^= secondSong.getContent()[i];
				}
			}
			strcpy(firstSong.content, newContent);
		}

		//additional functionalities - print, save and set content after mix
		void printContent(const char* content) {
			cout << content;
		}

		void printGenre(char genre) const {
			if (genre == 1) {
				cout << "Rock";
			}
			else if (genre == (1 << 1)) {
				cout << "Pop";
			}
			else if (genre == (1 << 2)) {
				cout << "HipHop";
			}
			else if (genre == (1 << 3)) {
				cout << "Electronic";
			}
			else if (genre == (1 << 4)) {
				cout << "Jazz";
			}
		}

		void printGenres() const {
			unsigned countGenres = GlobalConstants::MAX_COUNT_GENRES;
			char genres = genre;
			while (genres != 0 && countGenres != 0) {
				char currGenre = 1 << (countGenres - 1);
				if ((currGenre & genres) != 0) {
					printGenre(currGenre);
					if (genres != 0 && (genres % currGenre) != 0) {
						cout << '&';
					}
				}
				genres %= currGenre;
				countGenres--;
			}
		}

		void print() const {
			cout << name << ", ";
			duration.printTime();
			cout << ", ";
			printGenres();
			cout << endl;
		}

		bool save(const char* fileName) {
			std::ofstream ofs(fileName, std::ios::binary);
			if (!ofs.is_open()) {
				return false;
			}

			ofs.write(content, strlen(content));
			return true;
		}

		void setContentAfterMix(const char* newContent) {
			strcpy(content, newContent);
		}

	};

class Playlist
{
private:
	Song songsArr[GlobalConstants::MAX_SONGS_IN_PLAYLIST];
	size_t countSongs = 0;
public:
	//constructors
	Playlist() = default;
	Playlist(const Song* songsArr, size_t countSongs) {
		setSongsArr(songsArr, countSongs);
		setCountSongs(countSongs);
	}

	//getters
	size_t getCountSongs() const {
		return countSongs;
	}

	const Song* getSongsArr() const {
		return songsArr;
	}

	//setters
	bool setSongsArr(const Song* songsArr, size_t countSongs) {
		if (countSongs > GlobalConstants::MAX_SONGS_IN_PLAYLIST) {
			return false;
		}

		for (size_t i = 0; i < countSongs; i++)
		{
			this->songsArr[i] = songsArr[i];
		}
		return true;
	}

	bool setCountSongs(size_t countSongs) {
		this->countSongs = countSongs;
	}

	bool add(const char* songName, const unsigned hours, const unsigned minutes,
		const unsigned seconds, const char* genre, const char* fileName) {
		if (countSongs >= GlobalConstants::MAX_SONGS_IN_PLAYLIST) {
			return false;
		}
		Song s;
		Time duration;
		s.setName(songName);
		duration.setHours(hours);
		duration.setMins(minutes);
		duration.setSeconds(seconds);
		s.setDuration(duration);
		s.setGenre(genre);
		s.setContent(fileName);
		if (s.setName(songName) && duration.setHours(hours) && duration.setMins(minutes) && 
			duration.setSeconds(seconds) && s.setGenre(genre) && s.setContent(fileName)) {
			songsArr[countSongs++] = s;
			return true;
		}
		return false;
	}


	//functionalities
	void print() const {
		for (size_t i = 0; i < countSongs; i++) {
			songsArr[i].print();
		}
	}

	Song findSongByName(const char* name) const {
		Song s;
		s.setName(name);

		for (size_t i = 0; i < countSongs; i++) {
			if (strcmp(songsArr[i].getName(), name) == 0) {
				s = songsArr[i];
				break;
			}
		}
		return s;
	}

	Song* findSongByGenre(const char* genre) const {
		char g;
		while (*genre) {
			if (*genre == 'r') {
				g |= (int)Genre::Rock;
			}
			else if (*genre == 'p') {
				g |= (int)Genre::Pop;
			}
			else if (*genre == 'h') {
				g |= (int)Genre::HipHop;
			}
			else if (*genre == 'e') {
				g |= (int)Genre::Electronic;
			}
			else if (*genre == 'j') {
				g |= (int)Genre::Jazz;
			}
			genre++;
		}
		Song songsInOneGenre[GlobalConstants::MAX_SONGS_IN_PLAYLIST];
		int idx = 0;
		for (size_t i = 0; i < countSongs; i++) {
			if ((songsArr[i].getGenre() & g) != 0) {
				songsArr[i].print();
				songsInOneGenre[idx++] = songsArr[i];
			}
		}
		return songsInOneGenre;
	}

	void sortByDuration() {
		for (size_t i = 0; i < countSongs - 1; i++) {
			size_t minElIdx = i;
			for (size_t j = i + 1; j < countSongs; j++) {
				if (songsArr[j].getDuration().getTimeInSeconds() < songsArr[minElIdx].getDuration().getTimeInSeconds()) {
					minElIdx = j;
				}
			}
			if (minElIdx != i) {
				swap(songsArr[i], songsArr[minElIdx]);
			}
		}
	}

	void sortByName() {
		for (size_t i = 0; i < countSongs - 1; i++) {
			size_t minElIdx = i;
			for (size_t j = i + 1; j < countSongs; j++) {
				if (strcmp(songsArr[j].getName(), songsArr[minElIdx].getName()) < 0) {
					minElIdx = j;
				}
			}
			if (minElIdx != i) {
				swap(songsArr[i], songsArr[minElIdx]);
			}
		}
	}

	void mixSongs(const char* firstSongName, const char* secondSongName, const char* fileName) {
		Song firstSong = findSongByName(firstSongName);
		Song secondSong = findSongByName(secondSongName);
		char newContent[GlobalConstants::MAX_CONTENT_SIZE] = "";
		for (size_t i = 0; i < strlen(firstSong.getContent()); i++) {
			if (i >= strlen(secondSong.getContent())) {
				newContent[i] = firstSong.getContent()[i];
			}
			else {
				newContent[i] = firstSong.getContent()[i];
				if (newContent[i] != secondSong.getContent()[i]) {
					newContent[i] = '1';
				}
				else {
					newContent[i] = '0';
				}
			}
		}
		firstSong.setContentAfterMix(newContent);
		firstSong.save(fileName);
	}

	bool save(const char* songName, const char* fileName) {
		Song song = findSongByName(songName);
		std::ofstream ofs(fileName, std::ios::binary);
		if (!ofs.is_open()) {
			return false;
		}

		ofs.write(song.getContent(), strlen(song.getContent()));
		return true;
	}
};

int main()
{
	Playlist p;
	p.add("Master Of Puppets", 0, 8, 36, "r", "song5.dat");
	p.add("Tear in my heart", 0, 3, 14, "prj", "song5.dat");
	p.add("Buba Lazi - AGD ft Petq & Nelly", 0, 4, 5, "p", "song2.dat");

	p.print();
	cout << endl;

	p.sortByName();
	p.print();
	cout << endl;

	p.sortByDuration();
	p.print();
	cout << endl;

	Song buboBubo = p.findSongByName("Buba Lazi - AGD ft Petq & Nelly");
	buboBubo.createNewRythm(3, "song2.dat");
	buboBubo.print();
	cout << endl;

	cout << "Pop songs: " << endl;
	Song* pops = p.findSongByGenre("p");

	p.mixSongs("Buba Lazi - AGD ft Petq & Nelly", "Tear in my heart", "song2.dat");
	p.save("Buba Lazi - AGD ft Petq & Nelly", "song3.dat");

}

