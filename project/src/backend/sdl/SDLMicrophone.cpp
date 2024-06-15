#include "SDLMicrophone.h"

// need to figure out how to record audio for an infinite amount of time
// for something like game voice chat
namespace lime {
	/*
	uint32_t deviceId;

	uint8_t* recordingBuffer = NULL;
	uint8_t recordingBufferBytePos = 0;
	uint8_t recordingBufferByteSize = 0;

	int recordingTime = 0;
	int bufferLength = 0;
	*/

	std::map<int, MicrophoneRecordingData*> recordingData = std::map<int, MicrophoneRecordingData*> ();

	uint8_t* Microphone::GetRecordingBuffer(int id) {
		return recordingData[id]->recordingBuffer;
	}

	void SDLMicrophone::AudioRecordCallback(void* userdata, uint8_t* stream, int len) {
		int id = static_cast<int>(reinterpret_cast<uintptr_t>(userdata)); // Correct casting
        if (recordingData.find(id) == recordingData.end()) {
            SDL_Log("No recording data found for ID: %d", id);
            return;
        }

		MicrophoneRecordingData* mrd = recordingData[id];
		SDL_memcpy(&mrd->recordingBuffer[mrd->recordingBufferBytePos], stream, len);
		mrd->recordingBufferBytePos += len;
	}

	int Microphone::Open(int recordingTimeSeconds) {
		SDL_Log("Opening microphone!");

		SDL_AudioDeviceID recorderId = 0;

		MicrophoneRecordingData* mrd = new MicrophoneRecordingData();

		SDL_AudioSpec receivedRecorderSpec;
		SDL_AudioSpec recorderSpec;
		SDL_zero(recorderSpec);

		// todo: make these changable
		recorderSpec.format = AUDIO_S16;
		recorderSpec.freq = 44100;
		recorderSpec.samples = 4096;
		recorderSpec.channels = 2;
		recorderSpec.callback = SDLMicrophone::AudioRecordCallback;

		int recorderDeviceCount = SDL_GetNumAudioDevices(SDL_TRUE);

		if (recorderDeviceCount < 1) {
			SDL_Log("No audio capture device!");
			SDL_Log(SDL_GetError());
			return -1;
		}

		for (int i = 0; i < recorderDeviceCount; ++i) {
			SDL_Log(SDL_GetAudioDeviceName(i, SDL_TRUE));
		}

		// currently hardcoded to first index
		// SDL version Lime uses on its develop branch does not support getting default driver info.
		recorderId = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, SDL_TRUE), SDL_TRUE, &recorderSpec, &receivedRecorderSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
		recorderSpec.userdata = reinterpret_cast<void*>(static_cast<uintptr_t>(recorderId));

		int bytesPerSample = receivedRecorderSpec.channels * (SDL_AUDIO_BITSIZE(receivedRecorderSpec.format) / 8);
		int bytesPerSecond = receivedRecorderSpec.freq * bytesPerSample;

		mrd->recordingTime = recordingTimeSeconds;
		// padding ?
		mrd->bufferLength = mrd->recordingTime + 1;

		mrd->recordingBufferByteSize = mrd->bufferLength * bytesPerSecond;

		mrd->recordingBuffer = new Uint8[mrd->recordingBufferByteSize];
		SDL_memset(mrd->recordingBuffer, 0, mrd->recordingBufferByteSize);

		SDL_Log("Set up recording");

		return recorderId;
	}

	void Microphone::Close(int id) {
		MicrophoneRecordingData* rdata = recordingData[id];

		SDL_CloseAudioDevice(id);

		rdata->recordingBuffer = NULL;
		delete[] rdata->recordingBuffer;

		recordingData.erase(id);
	}

	/*int SDLMicrophone::Get() {
		return -1;
	}*/

	void Microphone::Resume(int id) {
		SDL_PauseAudioDevice(id, 0);
	}

	void Microphone::Pause(int id) {
		SDL_PauseAudioDevice(id, 1);
	}

	void Microphone::Unlock(int id) {
		SDL_UnlockAudioDevice(id);
	}

	void Microphone::Lock(int id) {
		SDL_LockAudioDevice(id);
	}

}
