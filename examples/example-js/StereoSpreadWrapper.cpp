
#include "../../StereoSpread.cpp"

extern "C" {
	
	void *stereospread_new()
	{
		return new StereoSpread();
	}
	
	void stereospread_set_width(StereoSpread *s, float w)
	{
		s->setWidth(w);
	}
	
	void stereospread_process(StereoSpread *s, float** inBuffers, float** outBuffers, const int bufferSize)
	{
		s->process(inBuffers, outBuffers, bufferSize);
	}
	
	void stereospread_process_inline(StereoSpread *s, float* inBuffer, float* outBuffer, const int bufferSize)
	{
		s->process_inline(inBuffer, outBuffer, bufferSize);
	}
	
	void stereospread_free(StereoSpread *s)
	{
		delete s;
	}
};