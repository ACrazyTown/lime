#ifndef LIME_UI_MICROPHONE_H
#define LIME_UI_MICROPHONE_H

#include <stdint.h>

namespace lime {


	class Microphone {

		public:

			static uint8_t* GetRecordingBuffer(int id);

			static int Open(int recordingTimeSeconds);
			static void Close(int id);
			static void Resume(int id);
			static void Pause(int id);
			static void Lock(int id);
			static void Unlock(int id);

	};


}


#endif