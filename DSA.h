#pragma once
#ifndef DSA_H
#define DSA_H
#include "AvlTree.h"
#include "List.h"
#include "methodTreeIntoArray.h"
#include "Lecture.h"
#include <assert.h>
//#include <iostream>

enum TYPE_DSA_EXCEPTION {
	DSA_mem = 1,
	DSA_invalidInput,
	DSA_failure
};
class dsaExceptions {
	TYPE_DSA_EXCEPTION type;
public:
	dsaExceptions(TYPE_DSA_EXCEPTION type)
		:
		type(type)
	{}
	TYPE_DSA_EXCEPTION getType() {
		return type;
	}
};

class DSA{
private:
	AvlTree<int, AvlTree<Lecture, Lecture>>* courses;
	List<int>* free_rooms_by_hour;
	int** schedule;
	List<int>::iterator** schedule_iter;
	int num_of_lectures;
	int num_of_rooms;
	int num_of_busy_hours;
	int hours;
	int rooms;

public:
	DSA(int hours, int rooms)
		:
		courses(nullptr),
		free_rooms_by_hour(nullptr),
		schedule(nullptr),
		schedule_iter(nullptr),
		num_of_lectures(0),
		num_of_rooms(rooms),
		num_of_busy_hours(0),
		hours(hours),
		rooms(rooms)
		{
			if( hours < 0 || rooms< 0) 
				throw dsaExceptions(DSA_invalidInput);
			
			//** AVL init
			//*************יכול להיות שיש כאן בעיה, ייתכן שאנחנו לא מוחקים את עץ השיעורים
			try{
				courses = new AvlTree<int, AvlTree<Lecture, Lecture>>(2);
			}
			catch(avlExceptions &a){
				if(a.getType() == AVL_mem) 
					throw dsaExceptions(DSA_mem);
			}
			
			//** 2D ARRAYS INIT
			try{
				schedule = new int*[hours];
			}
			catch(std::bad_alloc a){
				throw dsaExceptions(DSA_mem);
			}

			for(int i = 0; i < hours; ++i){
				try{
					schedule[i] = new int[rooms];
				}
				catch(std::bad_alloc a){
					throw dsaExceptions(DSA_mem);
				}
				for(int j=0; j<rooms ; j++){
					schedule[i][j] = -1;
				}
			}
			try{
				schedule_iter = new List<int>::iterator*[hours];
			}
			catch(std::bad_alloc a){
				throw dsaExceptions(DSA_mem);
			}
			for(int i = 0; i < hours; ++i){
				try{
					schedule_iter[i] = new List<int>::iterator[rooms];
				}
				catch(std::bad_alloc a){
					throw dsaExceptions(DSA_mem);
				}
			}
				//** LIST ARRAY
			try{
				 free_rooms_by_hour = new List<int>[hours];
			}
			catch(std::bad_alloc a){
				throw dsaExceptions(DSA_mem);
			}
			for(int i=0; i<hours; i++){
				for(int j=0; j<rooms ; j++){
					try{
						schedule_iter[i][j] = (free_rooms_by_hour[i]).insert(j);
					}
					catch(listExceptions a){
						if(a.getType() == LIST_mem)
							throw dsaExceptions(DSA_mem);
					}
				}
			}	
		}
				
	
	~DSA() {

		for (int i = 0; i<hours; i++) {
			for (int j = 0; j<rooms; j++) {
				free_rooms_by_hour[i].erase(schedule_iter[i][j]);
			}
		}
		//for(int i=0; i<hours; i++){
		//	delete [] schedule_iter[i];
		//}
		delete [] schedule_iter;
		delete[] free_rooms_by_hour;
		for(int i=0; i<hours; i++){
			delete [] schedule[i];
		}
		delete [] schedule;
		delete courses;
	}

	void AddLecture(int hour, int roomID, int courseID){
		if(courseID<=0 || hour<0 || roomID<0)
			throw dsaExceptions(DSA_invalidInput);
		
		if (schedule[hour][roomID] != -1) {
			throw dsaExceptions(DSA_failure);
		}
		
		schedule[hour][roomID] = courseID;
		(free_rooms_by_hour[hour]).erase(schedule_iter[hour][roomID]);
		schedule_iter[hour][roomID] = List<int>::iterator();

		num_of_lectures++;
		
		if(free_rooms_by_hour[hour].getSize() == num_of_rooms -1)
			num_of_busy_hours++;
		
		AvlTree<Lecture, Lecture>* lectures = NULL;
		try{
			lectures = courses->find(&courseID);
		}
		catch (avlExceptions &a){
			if(a.getType() == AVL_mem)
				throw dsaExceptions(DSA_mem);
		}
		if(lectures == nullptr){
			//std::cout << "Course doesn't Exist." << std::endl;
			AvlTree<Lecture, Lecture>* lectures = nullptr;
			try{
				lectures = new AvlTree<Lecture, Lecture>(1);
			}
			catch (avlExceptions &a){
				if(a.getType() == AVL_mem)
					throw dsaExceptions(DSA_mem);
			}
			Lecture* lecture = nullptr;
			try{
				lecture = new Lecture(hour, roomID);
			}
			catch (lecExceptions &a){
				delete lectures;
				if(a.getType() == LEC_mem)
					throw dsaExceptions(DSA_mem);
			}
			//lecture->print();
			try{
				lectures->insert(lecture, lecture);
			}
			catch (avlExceptions &a){
				delete lecture;
				delete lectures;
				if(a.getType() == AVL_mem)
					throw dsaExceptions(DSA_mem);
				if (a.getType() == AVL_failure)
					throw dsaExceptions(DSA_failure);
			}
			delete lecture;
			try{
				courses->insert(&courseID, lectures);
			}
			catch (avlExceptions &a) {
				delete lecture;
				delete lectures;
				if (a.getType() == AVL_mem)
					throw dsaExceptions(DSA_mem);
				if (a.getType() == AVL_failure)
					throw dsaExceptions(DSA_failure);
			}
		}
		else{
			Lecture* lecture = nullptr;
			try{
				lecture = new Lecture(hour, roomID);
			}
			catch (lecExceptions &a){
				if(a.getType() == LEC_mem)
					throw dsaExceptions(DSA_mem);
			}
			try{
				lectures->insert(lecture, lecture);
			}
			catch (avlExceptions &a){
				delete lecture;
				if (a.getType() == AVL_mem)
					throw dsaExceptions(DSA_mem);
				if (a.getType() == AVL_failure)
					throw dsaExceptions(DSA_failure);
			}
		}
		
			
	}

	int GetCourseID(int hour, int roomID){	
		if(roomID <0 || hour < 0) throw dsaExceptions(DSA_invalidInput);
		if(schedule[hour][roomID] == -1) throw dsaExceptions(DSA_failure);
		return schedule[hour][roomID];
	}
	
	int DeleteLectureFromSchedule(int hour, int roomID){
		List<int>::iterator end = free_rooms_by_hour[hour].end();
		if(schedule[hour][roomID] == -1 || schedule_iter[hour][roomID] != end) 
			throw dsaExceptions(DSA_failure);
		int courseID = schedule[hour][roomID];
		schedule[hour][roomID] = -1;
		List<int>::iterator iter;
		try{
			iter = free_rooms_by_hour[hour].insert(roomID);
		}
		catch (listExceptions &a){
			if(a.getType() == LIST_mem)
				throw dsaExceptions(DSA_mem);
		}
		schedule_iter[hour][roomID] = iter;
		return courseID;
	}

	void DeleteLectureFromAVL(int hour, int roomID, int courseID){
		if(courses->getSize() == 0 ) 
			throw dsaExceptions(DSA_failure);
		AvlTree<Lecture, Lecture>* tempLecturesAVL = nullptr;
		try{
			tempLecturesAVL = courses->find(&courseID); //** expecting pointer?**//
		}
		catch(avlExceptions &a){
			if(a.getType() == AVL_mem) 
				throw dsaExceptions(DSA_mem);
		}
		Lecture tempLecture(hour, roomID);
		try{
			tempLecturesAVL->pop(&tempLecture);//** expecting pointer?**//
		}
		catch(avlExceptions &a){
			if(a.getType() == AVL_mem) 
				throw dsaExceptions(DSA_mem);
		}
		if (tempLecturesAVL->getSize() == 0) {
			delete tempLecturesAVL;
			courses->pop(&courseID);
		}
	}
			
	void DeleteLecture(int hour, int roomID){
		if( hour < 0 || roomID < 0) 
			throw dsaExceptions(DSA_invalidInput);
		int courseID = DeleteLectureFromSchedule(hour, roomID);
		DeleteLectureFromAVL(hour, roomID, courseID);
		if(free_rooms_by_hour[hour].getSize() == num_of_rooms)
			num_of_busy_hours--;
		num_of_lectures--;
	}
	
	void ChangeCourseID(int oldCourseID, int newCourseID){
		if(oldCourseID <=0 || newCourseID <=0)
			throw dsaExceptions(DSA_invalidInput);
		if(courses->getSize() == 0)
			throw dsaExceptions(DSA_failure);
		AvlTree<Lecture, Lecture>* old_lectures = nullptr;
		try{
			old_lectures = courses->find(&oldCourseID);
		}
		catch (avlExceptions &a){
			if(a.getType() == AVL_mem)
				throw dsaExceptions(DSA_mem);
			if (a.getType() == AVL_failure) {
				throw dsaExceptions(DSA_failure);
			}
		}
		int num_of_old_lectures = old_lectures->getSize();
		Lecture* old_lecture_arr = nullptr;
		try{
			old_lecture_arr = new Lecture[num_of_old_lectures];
		}
		catch (lecExceptions &a) {
			if(a.getType() == LEC_mem)
				throw dsaExceptions(DSA_mem);
		}

		methodTreeIntoArray<Lecture> method = methodTreeIntoArray<Lecture>(old_lecture_arr);
		

		try {
			old_lectures->inOrder(method); //now we have all lectures sorted in array.
		}
		catch (avlExceptions &a) {
			if (a.getType() == AVL_mem)
				throw dsaExceptions(DSA_mem);
		}
		//std::cout << old_lecture_arr[0].getHour() << std::endl;
		for (int i = 0; i < num_of_old_lectures; i++) {	//updating schedule
			int curr_hour = old_lecture_arr[i].getHour();
			int curr_room = old_lecture_arr[i].getRoom();
			schedule[curr_hour][curr_room] = newCourseID;
		}
		
		AvlTree<Lecture, Lecture>* new_lectures = nullptr;
		try{
			new_lectures = courses->find(&newCourseID);
		}
		catch (avlExceptions &a){
			if
				
				(a.getType() == AVL_mem)
			{
				delete old_lecture_arr;
				throw dsaExceptions(DSA_mem);
			}
			if(a.getType() == AVL_failure){
				AvlTree<Lecture, Lecture>::Node** nodes_arr = new AvlTree<Lecture, Lecture>::Node*[num_of_old_lectures];
				method.changeToArrayOfNodes(nodes_arr);
				AvlTree<Lecture, Lecture>* new_old_lectures = nullptr;
				try{
					//std::cout << "type = " << nodes_arr->getType() << std::endl;
					new_old_lectures = new AvlTree<Lecture, Lecture>(nodes_arr, num_of_old_lectures, 1);
					//std::cout << "hi2" << std::endl;
					courses->pop(&oldCourseID);
					courses->insert(&newCourseID, new_old_lectures);
				}
				catch (avlExceptions &a) {
					delete nodes_arr;
					delete old_lecture_arr;
					if(a.getType() == AVL_mem)
						throw dsaExceptions(DSA_mem);
				}
				delete nodes_arr;
				//delete new_old_lectures;
				//delete old_lecture_arr;
				//std::cout << "failure" << " , " << "failure" << std::endl;
				return;
			}
		}
		int num_of_new_lectures = new_lectures->getSize();
		
		Lecture* new_lecture_arr = nullptr;
		try {
			new_lecture_arr = new Lecture[num_of_new_lectures];
		}
		catch (lecExceptions &a) {
			if (a.getType() == LEC_mem)
				throw dsaExceptions(DSA_mem);
		}

		methodTreeIntoArray<Lecture> method2 = methodTreeIntoArray<Lecture>(new_lecture_arr);
		try {
			new_lectures->inOrder(method2); //now we have all lectures sorted in array.
		}
		catch (avlExceptions &a) {
			if (a.getType() == AVL_mem)
				throw dsaExceptions(DSA_mem);
		}
		//std::cout << "first old lecture is at: " << old_lecture_arr[0].getHour() << "," << old_lecture_arr[0].getRoom() << std::endl;
		//std::cout << "first new lecture is at: " << new_lecture_arr[0].getHour() << "," << new_lecture_arr[0].getRoom() << std::endl;
		for (int i = 0; i<num_of_old_lectures; i++) {	//updating schedule
			int curr_hour = old_lecture_arr[i].getHour();
			int curr_room = old_lecture_arr[i].getRoom();
			schedule[curr_hour][curr_room] = newCourseID;
		}

		Lecture* merged_lectures = nullptr;
		try{
			merged_lectures = new Lecture[num_of_old_lectures + num_of_new_lectures];
		}
		catch (avlExceptions &a){
			delete old_lecture_arr;
			delete new_lecture_arr;
			if(a.getType() == AVL_mem)
				throw dsaExceptions(DSA_mem);
		}
		mergeArrays(old_lecture_arr, num_of_old_lectures, new_lecture_arr, num_of_new_lectures, merged_lectures);
		//std::cout << "first in old Lecture: " << old_lecture_arr[0].getHour() << "," << old_lecture_arr[0].getRoom()  << " first in merged Lecture: " << merged_lectures[0].getHour() << "," << merged_lectures[0].getRoom() << std::endl;
		//now we have our arrays merged.
		//let's build a tree out of it.
		
		AvlTree<Lecture, Lecture>::Node** nodes_arr = nullptr;
		int i;
		try{
			nodes_arr = new AvlTree<Lecture, Lecture>::Node*[num_of_old_lectures + num_of_new_lectures];
			
			for (i = 0; i < num_of_old_lectures + num_of_new_lectures; i++) {
				nodes_arr[i] = new AvlTree<Lecture, Lecture>::Node(&(merged_lectures[i]), &(merged_lectures[i]), 1);
				//merged_lectures[i].print();
			}
		}
		catch (avlExceptions &a) {
			for (int j = 0; j < i; j++)
				delete nodes_arr[j];
			delete nodes_arr;
			delete merged_lectures;
			delete old_lecture_arr;
			delete new_lecture_arr;
			if (a.getType() == AVL_mem)
				throw dsaExceptions(DSA_mem);
		}
		AvlTree<Lecture, Lecture>* new_old_lectures = nullptr;
		try{
			new_old_lectures = new AvlTree<Lecture, Lecture>(nodes_arr, num_of_old_lectures + num_of_new_lectures, 1);
			courses->pop(&oldCourseID);
			courses->pop(&newCourseID);
			//std::cout << "Merged tree size is: " << new_old_lectures->getSize() << std::endl;
			//std::cout << " first in merged Lecture: " << merged_lectures[0].getHour() << "," << merged_lectures[0].getRoom() << std::endl;
			//here Is problem V
			//std::cout << "1- Trying to insert both courses' lectures." << std::endl;
			courses->insert(&newCourseID, new_old_lectures);	
		}
		catch (avlExceptions &a) {
			delete nodes_arr;
			//std::cout << "end 1" << std::endl;
			//delete merged_lectures;
			//delete old_lecture_arr;
			//delete new_lecture_arr;
			if(a.getType() == AVL_mem)
				throw dsaExceptions(DSA_mem);
			if (a.getType() == AVL_failure) {
				//std::cout << "end 3" << std::endl;
				throw dsaExceptions(DSA_failure);
			}

				
		}
		delete nodes_arr;
		//delete new_old_lectures;
		//delete merged_lectures;
		//delete new_lecture_arr;
		//delete old_lecture_arr;
	}
	
	void mergeArrays(Lecture* a, int size_a, Lecture* b, int size_b, Lecture* m){
		int i_a = 0, i_b = 0;
		for(int i=0; i<size_a + size_b; i++)
		{
			if(i_a == size_a){
				m[i] = b[i_b];
				i_b++;
				continue;
			}
			if(i_b == size_b){
				m[i] = a[i_a];
				i_a++;
				continue;
			}
			if ((a[i_a]) < (b[i_b])) {
				//a[i_a].print();
				m[i] = a[i_a++];
			}
			else {
				//b[i_b].print();
				m[i] = b[i_b++];
			}
				
		}
	}
	
	float CalculateScheduleEfficiency(){
		if(!num_of_lectures)
			throw dsaExceptions(DSA_failure);
		return (float)((float)num_of_lectures / ((float)num_of_rooms * (float)num_of_busy_hours));
	}
	
	void GetAllFreeRoomsByHour(int hour, int **rooms, int* numOfRooms){
		if(!numOfRooms || !rooms || hour < 0) throw dsaExceptions(DSA_invalidInput);
		int num_of_free_rooms = (free_rooms_by_hour[hour]).getSize();
		if(num_of_free_rooms == 0) throw dsaExceptions(DSA_failure);
		//int* freeRoomArr = nullptr;
		try{
			*rooms = new int[num_of_free_rooms];
		}
		catch (std::bad_alloc a){
			throw dsaExceptions(DSA_mem);
		}

		List<int>::iterator iter = (free_rooms_by_hour[hour]).begin();
		for (int i = 0; i < num_of_free_rooms; i++) {
			(*rooms)[i] = *iter;
		}
		//std::cout << free_rooms_by_hour[hour].getSize() << std::endl;
		*numOfRooms = num_of_free_rooms;
	}
	
	void GetAllLecturesByCourse(int courseID, int **hours, int **rooms, int *numOfLectures){
		//std::cout << "trying to find courses for: " << courseID << std::endl;
		if(courseID <=0 || !hours || !rooms || !numOfLectures)
			throw dsaExceptions(DSA_invalidInput);
		AvlTree<Lecture, Lecture>* lectures = nullptr;
		try{
			lectures = courses->find(&courseID);
		}
		catch (avlExceptions &a){
			if(a.getType() == AVL_mem)
				throw dsaExceptions(DSA_mem);
			if(a.getType() == AVL_failure)
				throw dsaExceptions(DSA_failure);
		}
		
		int num_of_lectures_in_curr_course = lectures->getSize();
		//std::cout << "num of lectures in course: " << courseID << " is " << num_of_lectures_in_curr_course << std::endl;
		Lecture* lecture_arr = new Lecture[num_of_lectures_in_curr_course];
		methodTreeIntoArray<Lecture> method = methodTreeIntoArray<Lecture>(lecture_arr);
		lectures->inOrder(method); //now we have all lectures sorted in array.
		
		*hours = new int[num_of_lectures_in_curr_course];
		*rooms = new int[num_of_lectures_in_curr_course];
		*numOfLectures = num_of_lectures_in_curr_course;
		
		for(int i=0; i<num_of_lectures_in_curr_course; i++)
		{
			Lecture curr_lecture = lecture_arr[i];
			
			(*hours)[i] = curr_lecture.getHour();
			(*rooms)[i] = curr_lecture.getRoom();
		}
	}

};
#endif