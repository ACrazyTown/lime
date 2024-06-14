#ifndef LIME_UI_MICROPHONE_H
#define LIME_UI_MICROPHONE_H


namespace lime {


	class Microphone {

		public:

			static void Open();
			static void Close();
			static void Pause(int index);
			static void Callback();
			static int Get();
			static void Lock();
			static void Unlock();

	};


}


#endif