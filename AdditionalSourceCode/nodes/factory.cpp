/** Autogenerated Main.cpp. */

// ===============================| Include only the DSP files  |===============================

#include <hi_dsp_library/hi_dsp_library.h>
#include <hi_faust/hi_faust.h>
#include "includes.h"
// =========================| Now we can add the rest of the codebase |=========================

#include <JuceHeader.h>

// =====================================| Project Factory |=====================================

namespace project
{

struct Factory: public scriptnode::dll::StaticLibraryHostFactory
{
	Factory()
	{
		TempoSyncer::initTempoData();
		// Node registrations -----------------------------------------------------------------
		
		registerPolyNode<project::reverb<1>, project::reverb<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::pitchShift<1>, project::pitchShift<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::distortion<1>, project::distortion<NUM_POLYPHONIC_VOICES>>();
		registerPolyNode<project::distorion<1>, wrap::illegal_poly<project::distorion<1>>>();
		registerPolyNode<project::script_fx1<1>, wrap::illegal_poly<project::script_fx1<1>>>();
		registerPolyNode<project::script_fx2<1>, wrap::illegal_poly<project::script_fx2<1>>>();
	}
};
}

scriptnode::dll::FactoryBase* hise::FrontendHostFactory::createStaticFactory()
{
	return new project::Factory();
}
