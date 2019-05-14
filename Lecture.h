#pragma once
#ifndef LECTURE_H
#define LECTURE_H
#include <exception>
enum TYPE_LEC_EXCEPTION {
	LEC_mem = 1,
	LEC_invalidInput,
	LEC_failure
};
class lecExceptions {
	TYPE_LEC_EXCEPTION type;
public:
	lecExceptions(TYPE_LEC_EXCEPTION type)
		:
		type(type)
	{}
	TYPE_LEC_EXCEPTION getType() {
		return type;
	}
};

class Lecture
{
private:
	int hour;
	int room;
	public:
		Lecture(int in_hour = -1, int in_room = -1)
			:
			hour(in_hour),
			room(in_room)
		{}

		~Lecture() {}
		bool operator<(const Lecture& lecture_2) {
			if (hour > lecture_2.hour)
				return false;
			if (hour < lecture_2.hour)
				return true;
			return room < lecture_2.room;
		}
		bool operator==(const Lecture& lecture_2) {
			return ((room == lecture_2.room)&&(hour == lecture_2.hour));
		}
		int getHour(){
			return hour;
		}
		int getRoom(){
			return room;
		}
		
		void setHour(int new_hour){
			hour = new_hour;
		}
		
		void setRoom(int new_room){
			room = new_room;
		}
		void print() {
			std::cout << "Current lecture is at: " << hour << "," << room << std::endl;
		}
};
#endif