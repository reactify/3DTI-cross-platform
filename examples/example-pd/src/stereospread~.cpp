/**
 *
 * Thanks to Johannes M Zmolnig for writing the HOWTO:
 *       http://iem.kug.ac.at/pd/externals-HOWTO/
 * */

extern "C" {
	#include "m_pd.h" //a C header, so wrap it in extern "C"
}
#include "StereoSpread.h"

static t_class *stereospread_tilde_class;

typedef struct _stereospread_tilde
{
	t_object	x_obj;				// Pointer to object
	double		f_float2Sig;		// Dummy variable for conversion of floats in inlet to signals
	StereoSpread* stereoSpread;
} t_stereospread_tilde;


#pragma mark - Setters

static void stereospread_tilde_setWidth(t_stereospread_tilde *x, t_float f)
{
	x->stereoSpread->setWidth(f);
}


#pragma mark - DSP

static t_int *stereospread_tilde_perform(t_int *w)
{
	t_stereospread_tilde *x	= (t_stereospread_tilde *)(w[1]);

	// 2 signal input: left and right
	t_sample  *leftInBuffer = (t_sample *)(w[2]);
	t_sample  *rightInBuffer = (t_sample *)(w[3]);
	
	// 2 signal outputs:
	t_sample *leftOutBuffer = (t_sample *)(w[4]);
	t_sample *rightOutBuffer = (t_sample *)(w[5]);
	
	int bufferSize = (int)(w[6]);
	
	float *inBuffers[2] = {leftInBuffer, rightInBuffer};
	float *outBuffers[2] = {leftOutBuffer, rightOutBuffer};
	x->stereoSpread->process(inBuffers, outBuffers, bufferSize);
	
	return (w+7);
}


static void stereospread_tilde_dsp(t_stereospread_tilde *x, t_signal **sp)
{
	dsp_add(stereospread_tilde_perform, 6, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n);
}


#pragma mark - Object

static void stereospread_tilde_debug(t_stereospread_tilde *x)
{
	post("stereospread~ : %s at %s ", __DATE__, __TIME__);
}


static void *stereospread_tilde_new(t_symbol * s)
{
	t_stereospread_tilde *x = (t_stereospread_tilde *)pd_new(stereospread_tilde_class);
	stereospread_tilde_debug(x);
	
	double __unused samplingRate = (double)sys_getsr();
	x->stereoSpread = new StereoSpread();

	// right signal inlet
	inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
	// width arg inlet
	inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("Width"));
	
	// left outlet
	outlet_new(&x->x_obj, &s_signal);
	// right outlet
	outlet_new(&x->x_obj, &s_signal);
	
	return (void *)x;
}


static void *stereospread_tilde_del(t_stereospread_tilde *x)
{
	delete x->stereoSpread;
	return 0;
}

extern "C" __attribute__((visibility("default"))) void stereospread_tilde_setup(void)
{
	stereospread_tilde_class = class_new (gensym("stereospread~"),
											 (t_newmethod)stereospread_tilde_new,
											 (t_method)stereospread_tilde_del,
											 sizeof (t_stereospread_tilde),
											 CLASS_DEFAULT, A_DEFSYMBOL, 0);
	
	class_addmethod(stereospread_tilde_class, (t_method)stereospread_tilde_dsp, gensym("dsp"), (t_atomtype)0);
	class_addmethod(stereospread_tilde_class, (t_method)stereospread_tilde_debug, gensym("debug"), (t_atomtype)0);
	
	class_addmethod(stereospread_tilde_class, (t_method)stereospread_tilde_setWidth, gensym("Width"), A_FLOAT, (t_atomtype)0);
    
	// Enables 'floats' as signals on first inlet
	CLASS_MAINSIGNALIN(stereospread_tilde_class, t_stereospread_tilde, f_float2Sig);
	
	class_sethelpsymbol(stereospread_tilde_class, gensym("stereospread~-help"));
}
