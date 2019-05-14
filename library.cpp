//#pragma once
#include <stdlib.h>
#include <cstddef>
#include "library.h"
#include "DSA.h"

void * Init(int hours, int rooms){
	DSA* sys = nullptr;
	try {
		sys = new DSA(hours, rooms);
	}
	catch (dsaExceptions a) {
		if (a.getType() == DSA_mem)
			return NULL;
	}
	return (void*)sys;
}

StatusType AddLecture(void *DS, int hour, int roomID, int courseID) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		((DSA*)DS)->AddLecture(hour, roomID, courseID);
	}
	catch (dsaExceptions a) {
		if (a.getType() == DSA_mem)
			return ALLOCATION_ERROR;
		if (a.getType() == DSA_invalidInput)
			return INVALID_INPUT;
		if (a.getType() == DSA_failure)
			return FAILURE;
	}
	return SUCCESS;
}

StatusType GetCourseID(void *DS, int hour, int roomID, int *courseID) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		*courseID = ((DSA*)DS)->GetCourseID(hour, roomID);
	}
	catch (dsaExceptions a) {
		if (a.getType() == DSA_mem)
			return ALLOCATION_ERROR;
		if (a.getType() == DSA_invalidInput)
			return INVALID_INPUT;
		if (a.getType() == DSA_failure)
			return FAILURE;
	}
	return SUCCESS;

}

StatusType DeleteLecture(void *DS, int hour, int roomID) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		((DSA*)DS)->DeleteLecture(hour, roomID);
	}
	catch (dsaExceptions a) {
		if (a.getType() == DSA_mem)
			return ALLOCATION_ERROR;
		if (a.getType() == DSA_invalidInput)
			return INVALID_INPUT;
		if (a.getType() == DSA_failure)
			return FAILURE;
	}
	return SUCCESS;
}

StatusType ChangeCourseID(void *DS, int oldCourseID, int newCourseID) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		((DSA*)DS)->ChangeCourseID(oldCourseID, newCourseID);
	}
	catch (dsaExceptions a) {
		if (a.getType() == DSA_mem)
			return ALLOCATION_ERROR;
		if (a.getType() == DSA_invalidInput)
			return INVALID_INPUT;
		if (a.getType() == DSA_failure)
			return FAILURE;
	}
	return SUCCESS;
}

StatusType CalculateScheduleEfficiency(void *DS, float *efficiency) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		*efficiency = ((DSA*)DS)->CalculateScheduleEfficiency();
	}
	catch (dsaExceptions a) {
		if (a.getType() == DSA_mem)
			return ALLOCATION_ERROR;
		if (a.getType() == DSA_invalidInput)
			return INVALID_INPUT;
		if (a.getType() == DSA_failure)
			return FAILURE;
	}
	return SUCCESS;

}

StatusType GetAllFreeRoomsByHour(void *DS, int hour, int **rooms, int* numOfRooms) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		((DSA*)DS)->GetAllFreeRoomsByHour(hour, rooms, numOfRooms);
	}
	catch (dsaExceptions a) {
		if (a.getType() == DSA_mem)
			return ALLOCATION_ERROR;
		if (a.getType() == DSA_invalidInput)
			return INVALID_INPUT;
		if (a.getType() == DSA_failure)
			return FAILURE;
	}
	return SUCCESS;
}

StatusType GetAllLecturesByCourse(void *DS, int courseID, int **hours, int **rooms, int *numOfLectures) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		((DSA*)DS)->GetAllLecturesByCourse(courseID, hours, rooms, numOfLectures);
	}
	catch (dsaExceptions a) {
		if (a.getType() == DSA_mem)
			return ALLOCATION_ERROR;
		if (a.getType() == DSA_invalidInput)
			return INVALID_INPUT;
		if (a.getType() == DSA_failure)
			return FAILURE;
	}
	return SUCCESS;
}

void Quit(void **DS) {
	
	if (DS == NULL)
		return;
	delete ((DSA*)(*DS));
	*DS = NULL;
}