#ifndef LIME_SDL_MICROPHONE_H
#define LIME_SDL_MICROPHONE_H

#include <SDL.h>
#include <ui/Microphone.h>
#include <map>

namespace lime {

	struct MicrophoneRecordingData {
		int deviceId;
		uint8_t* recordingBuffer;
		uint8_t recordingBufferBytePos;
		uint8_t recordingBufferByteSize;
		int recordingTime;
		int bufferLength;
	};

	class SDLMicrophone {

		public:

			static uint8_t* GetRecordingBuffer(int id);

			static int Open(int recordingTimeSeconds);
			static void Close(int id);
			static void Resume(int id);
			static void Pause(int id);
			static void Lock(int id);
			static void Unlock(int id);
			static void AudioRecordCallback(void* userdata,	uint8_t* stream, int len);

	};


}


#endif