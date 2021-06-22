#include <stdio.h>
#include <time.h>
#include <po_hi_time.h>

// Pomocnicze stale aby kod byl czytelniejszy
#define PERSON_ON_VIDEO_DETECTED 1
#define WINDOW_OPENED 1
#define DOOR_OPENED 1
#define MOVEMENT_DETECTED 1

#define CORRECT_PIN 500 // 500 to poprawny pin
#define PIN_ENTRY_TIME 50 // 50 sekund na wpisanie dobrego pinu, po tym czasie wlaczy sie alarm

enum Access_Type
{
	authorized,
	unauthorized,
	no_person_in_room
};

// ---------------------Funkcje pomocnicze:---------------------------
int detectPersonOnVideo(int video_stream)
{
	// normalnie tutaj odbywal by sie proces
	// rozpoznania czy ktos jest na zapisie wideo
	// z wykorzystaniem algorytmow
	// rozpoznawania postaci
	if(video_stream == PERSON_ON_VIDEO_DETECTED)
	{
		printf("Wykryto postac na zapisie wideo\n");
		return 1;
	}
	else
	{
		printf("Nie wykryto postaci na zapisie wideo\n");
		return 0;		
	}
}

int detectWindowOpened(int window_state)
{
	if(window_state == WINDOW_OPENED)
	{
		printf("Wykryto otwarcie okna\n");
		return 1;
	}
	else
	{
		printf("Nie wykryto otwarcia okna\n");
		return 0;		
	}
}

int detectDoorOpened(int door_state)
{
	if(door_state == DOOR_OPENED)
	{
		printf("Wykryto otwarcie drzwi\n");
		return 1;
	}
	else
	{
		printf("Nie wykryto otwarcia drzwi\n");
		return 0;		
	}
}

int detectMovement(int movement_data)
{
	if(movement_data == MOVEMENT_DETECTED)
	{
		printf("Wykryto ruch\n");
		return 1;
	}
	else
	{
		printf("Nie wykryto ruchu\n");
		return 0;		
	}
}

int validatePin(int entered_pin)
{
	if(entered_pin == CORRECT_PIN)
	{
		printf("Wprowadzono poprawny pin\n");
		return 1;
	}
	else
	{
		printf("Wprowadzono niepoprawny pin\n");
		return 0;		
	}
}

int getTime()
{
	struct timespec mytime;
	clock_gettime (CLOCK_REALTIME, &mytime);
	
	return mytime.tv_sec;
}

enum Access_Type validateAccess(int is_pin_correct, int person_on_video_detected, int person_entered)
{
	// static zapewnia przechowanie wewnetrznego stanu miedzy wywolaniami
	static int timeOfPersonEntered = 0;
	static int timeOfCorrectPin = 0;
	
	if(!person_on_video_detected && !person_entered && !timeOfPersonEntered) // nie wykryto postaci na wideo ani na sensorach, rowniez w poprzednich wywolaniach
	{
	    printf("Brak ruchu w pokoju\n");
	    return no_person_in_room;
	}
		
	
	if(is_pin_correct) // wprowadzono poprawny pin
	{
		timeOfCorrectPin = getTime();
		printf("Uprawnienia osoby sa poprawne\n");
		return authorized;
	}
		
		
	// wykrylismy ruch i nie wprowadzono poprawnego pinu 	
	// zapisujemy tylko czas pierwszego wejscia osoby, w przeciwnym wypadku kolejne "wejscia" opoznialyby odpalenie alarmu	
	if((person_entered || person_on_video_detected) && !is_pin_correct && !timeOfPersonEntered)
	{
		timeOfPersonEntered = getTime();
		printf("Wykryto ruch, oczekiwanie na wprowadzenie pinu\n");
		return no_person_in_room; // tylko tymczasowo, po uplywie czasu na wpisanie pinu zostanie aktywowany alarm
	}
	
	if(getTime() - timeOfPersonEntered > PIN_ENTRY_TIME) // minal czas na wpisanie pinu
	{
	    printf("Nieuprawniony dostep\n");
		return unauthorized;
	}
}

int turnOnAlarm(enum Access_Type access_type)
{
	switch(access_type)
	{
		case authorized:
		printf("Wprowadzono poprawny pin\n");
		return 0;
		
		case no_person_in_room:
		printf("Nie ma nikogo w pomieszczeniu\n");
		return 0;	
		
		case unauthorized:
		printf("Wprowadzono niepoprawny pin\n");
		return 0;	
	}
}

void printTimestamp(char *threadName)
{
	struct timespec mytime;
	clock_gettime (CLOCK_REALTIME, &mytime);

	printf ("At time %3lu:%3lu, %s : ", mytime.tv_sec % 3600, mytime.tv_nsec/1000000, threadName);
}



// ------------------------------Funkcje wywolywane z poziomu AADL:--------------------------
void roomController_VideoThread (int video_stream, int *person_on_video_detected)
{
	printTimestamp("video_thread");
	
	*person_on_video_detected = detectPersonOnVideo(video_stream);
}

void roomController_WindowControlThread (int window_state, int *window_opened)
{
	printTimestamp("window_sensor_thread");
	
	*window_opened = detectWindowOpened(window_state);
}

void roomController_DoorControlThread (int door_state, int *door_opened)
{
	printTimestamp("door_sensor_thread");
	
	*door_opened = detectDoorOpened(door_state);
}

void roomController_MovementControlThread (int movement_data, int *person_in_room)
{
	printTimestamp("movement_sensor_thread");
	
	*person_in_room = detectMovement(movement_data);
}

void roomController_PinControlThread (int entered_pin, int *is_pin_correct)
{
	printTimestamp("pin_device_thread");
	
	*is_pin_correct = validatePin(entered_pin);
}

void roomController_AccessControlThread (int is_pin_correct, int person_on_video_detected, int person_entered, enum Access_Type *access_type)
{
	printTimestamp("access_control_thread");
	
	*access_type = validateAccess(is_pin_correct, person_on_video_detected, person_entered);
}


void roomController_AlarmControlThread (enum Access_Type access_type, int *turn_on_alarm)
{
	printTimestamp("alarm_control_thread");
	
	*turn_on_alarm = turnOnAlarm(access_type);
}
