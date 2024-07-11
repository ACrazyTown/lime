package lime.ui;

import lime._internal.backend.native.NativeCFFI;
import haxe.io.Bytes;

@:access(lime._internal.backend.native.NativeCFFI)
class Microphone
{
	public static function getRecordingBuffer(id:Int):Bytes
	{
		#if (lime_cffi && !macro)
		return NativeCFFI.lime_microphone_get_recording_buffer(id, Bytes.alloc(0));
		#end

		return null;
	}

	public static function open(recordingTimeSeconds:Int):Int
	{
		#if (lime_cffi && !macro)
		return NativeCFFI.lime_microphone_open(recordingTimeSeconds);
		#end

		return -1;
	}

	public static function close(id:Int):Void
	{
		#if (lime_cffi && !macro)
		NativeCFFI.lime_microphone_close(id);
		#end
	}

	public static function resume(id:Int):Void
	{
		#if (lime_cffi && !macro)
		NativeCFFI.lime_microphone_resume(id);
		#end
	}

	public static function pause(id:Int):Void
	{
		#if (lime_cffi && !macro)
		NativeCFFI.lime_microphone_pause(id);
		#end
	}

	public static function lock(id:Int):Void
	{
		#if (lime_cffi && !macro)
		NativeCFFI.lime_microphone_lock(id);
		#end
	}

	public static function unlock(id:Int):Void
	{
		#if (lime_cffi && !macro)
		NativeCFFI.lime_microphone_unlock(id);
		#end
	}
}