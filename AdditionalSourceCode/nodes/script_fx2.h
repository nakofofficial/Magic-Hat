#pragma once

// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace script_fx2_impl
{
// ======================| Node & Parameter type declarations |======================

namespace script_fx2_t_parameters
{
}

template <int NV>
using script_fx2_t_ = container::chain<parameter::plain<project::pitchShift<NV>, 0>, 
                                       wrap::fix<2, project::pitchShift<NV>>>;

// ==========================| Root node initialiser class |==========================

template <int NV> struct instance: public script_fx2_impl::script_fx2_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(script_fx2);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(16)
		{
			0x005B, 0x0000, 0x5300, 0x6968, 0x7466, 0x0000, 0x0000, 0x00C0, 
            0x0000, 0x0040, 0x0000, 0x0033, 0x8000, 0xCD3F, 0xCCCC, 0x003D
		};
	};
	
	instance()
	{
		// Node References ----------------------------------------------------------
		
		auto& faust = this->getT(0); // project::pitchShift<NV>
		
		// Parameter Connections ----------------------------------------------------
		
		this->getParameterT(0).connectT(0, faust); // Shift -> faust::shiftsemitones
		
		// Default Values -----------------------------------------------------------
		
		;                              // faust::shiftsemitones is automated
		faust.setParameterT(1, 1000.); // core::faust::windowsamples
		faust.setParameterT(2, 10.);   // core::faust::xfadesamples
		
		this->setParameterT(0, 2.98023e-08);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
};
}

#undef getT
#undef connectT
#undef setParameterT
#undef setParameterWT
#undef getParameterT
// ===============================| Public Definition |===============================

namespace project
{
// polyphonic template declaration

template <int NV>
using script_fx2 = wrap::node<script_fx2_impl::instance<NV>>;
}


