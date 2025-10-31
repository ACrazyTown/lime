#include <graphics/RenderEvent.h>
#include <system/CFFI.h>


namespace lime {


	ValuePointer* RenderEvent::callback = 0;
	ValuePointer* RenderEvent::eventObject = 0;

	static int id_type;
	static int id_vsync;
	static bool init = false;


	RenderEvent::RenderEvent () {

		type = RENDER;

	}


	void RenderEvent::Dispatch (RenderEvent* event) {

		if (RenderEvent::callback) {

			if (RenderEvent::eventObject->IsCFFIValue ()) {

				if (!init) {

					id_type = val_id ("type");
					id_vsync = val_id ("vsync");

				}

				value object = (value)RenderEvent::eventObject->Get ();

				alloc_field (object, id_type, alloc_int (event->type));
				alloc_field (object, id_vsync, alloc_bool (event->vsync));

			} else {

				RenderEvent* eventObject = (RenderEvent*)RenderEvent::eventObject->Get ();

				eventObject->type = event->type;
				eventObject->vsync = event->vsync;

			}

			RenderEvent::callback->Call ();

		}

	}


}
