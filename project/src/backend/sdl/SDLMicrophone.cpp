#include "SDLMicrophone.h"

// need to figure out how to record audio for an infinite amount of time
// for something like game voice chat
namespace lime {
	uint32_t deviceId;

	uint8_t* recordingBuffer = NULL;
	uint8_t recordingBufferBytePos = 0;
	uint8_t recordingBufferByteSize = 0;

	int recordingTime = 0;
	int bufferLength = 0;

	uint8_t* SDLMicrophone::GetRecordingBuffer() {
		return recordingBuffer;
	}

	void SDLMicrophone::AudioRecordCallback(void* userdata, uint8_t* stream, int len) {
		SDL_memcpy(&recordingBuffer[recordingBufferBytePos], stream, len);
		recordingBufferBytePos += len;
	}

	void SDLMicrophone::Open(int recordingTimeSeconds) {
		SDL_Log("Opening microphone!");

		//SDL_AudioDeviceID recorderId = 0;

		SDL_AudioSpec receivedRecorderSpec;
		SDL_AudioSpec recorderSpec;
		SDL_zero(recorderSpec);

		// todo: make these changable
		recorderSpec.format = AUDIO_S16;
		recorderSpec.freq = 44100;
		recorderSpec.samples = 4096;
		recorderSpec.channels = 2;
		recorderSpec.callback = AudioRecordCallback;

		int recorderDeviceCount = SDL_GetNumAudioDevices(SDL_TRUE);

		if (recorderDeviceCount < 1) {
			SDL_Log("No audio capture device!");
			SDL_Log(SDL_GetError());
			return;
		}

		for (int i = 0; i < recorderDeviceCount; ++i) {
			SDL_Log(SDL_GetAudioDeviceName(i, SDL_TRUE));
		}

		// currently hardcoded to first index
		// SDL version Lime uses on its develop branch does not support getting default driver info.
		deviceId = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, SDL_TRUE), SDL_TRUE, &recorderSpec, &receivedRecorderSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

		int bytesPerSample = receivedRecorderSpec.channels * (SDL_AUDIO_BITSIZE(receivedRecorderSpec.format) / 8);
		int bytesPerSecond = receivedRecorderSpec.freq * bytesPerSample;

		recordingTime = recordingTimeSeconds;
		// padding ?
		bufferLength = recordingTime + 1;

		recordingBufferByteSize = bufferLength * bytesPerSecond;

		recordingBuffer = new Uint8[recordingBufferByteSize];
		SDL_memset(recordingBuffer, 0, recordingBufferByteSize);

		SDL_Log("Set up recording");
	}

	void SDLMicrophone::Close() {
		SDL_CloseAudioDevice(deviceId);

		recordingBuffer = NULL;
		delete[] recordingBuffer;
	}

	/*int SDLMicrophone::Get() {
		return -1;
	}*/

	void SDLMicrophone::Resume() {
		SDL_PauseAudioDevice(deviceId, 0);
	}

	void SDLMicrophone::Pause() {
		SDL_PauseAudioDevice(deviceId, 1);
	}

	void SDLMicrophone::Unlock() {
		SDL_UnlockAudioDevice(deviceId);
	}

	void SDLMicrophone::Lock() {
		SDL_LockAudioDevice(deviceId);
	}

}
