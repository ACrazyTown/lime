#ifndef LIME_SDL_MICROPHONE_H
#define LIME_SDL_MICROPHONE_H

#include <SDL.h>

namespace lime {

	struct MicrophoneRecordingData {
		uint8_t* recordingBuffer;
		uint8_t recordingBufferBytePos;
		uint8_t recordingBufferByteSize;
		int recordingTime;
		int bufferLength;
	};

	class SDLMicrophone {

		public:

			static uint8_t* GetRecordingBuffer();

			static void Open(int recordingTimeSeconds);
			static void Close();
			static void Resume();
			static void Pause();
			static void Lock();
			static void Unlock();

		private:

			static void AudioRecordCallback(void* userdata,	uint8_t* stream, int len);
	};


}


#endif