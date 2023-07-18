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

namespace script_fx1_impl
{
// =======================| Node & Parameter type declarations |=======================

DECLARE_PARAMETER_RANGE_SKEW(xfader_c0Range, 
                             -100., 
                             0., 
                             5.42227);

using xfader_c0 = parameter::from0To1<core::gain, 
                                      0, 
                                      xfader_c0Range>;

using xfader_c1 = xfader_c0;

using xfader_multimod = parameter::list<xfader_c0, xfader_c1>;

using xfader_t = control::xfader<xfader_multimod, faders::rms>;

using chain_t = container::chain<parameter::empty, 
                                 wrap::fix<2, core::gain>>;

template <int NV>
using chain1_t = container::chain<parameter::empty, 
                                  wrap::fix<2, project::reverb<NV>>, 
                                  core::gain>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, chain_t>, 
                                 chain1_t<NV>>;

namespace script_fx1_t_parameters
{
}

template <int NV>
using script_fx1_t_ = container::chain<parameter::plain<script_fx1_impl::xfader_t, 0>, 
                                       wrap::fix<2, xfader_t>, 
                                       split_t<NV>>;

// ===========================| Root node initialiser class |===========================

template <int NV> struct instance: public script_fx1_impl::script_fx1_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(script_fx1);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(18)
		{
			0x005B, 0x0000, 0x5000, 0x7261, 0x6D61, 0x7465, 0x7265, 0x0000, 
            0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 
            0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References ------------------------------------------------------------
		
		auto& xfader = this->getT(0);                // script_fx1_impl::xfader_t
		auto& split = this->getT(1);                 // script_fx1_impl::split_t<NV>
		auto& chain = this->getT(1).getT(0);         // script_fx1_impl::chain_t
		auto& gain = this->getT(1).getT(0).getT(0);  // core::gain
		auto& chain1 = this->getT(1).getT(1);        // script_fx1_impl::chain1_t<NV>
		auto& faust = this->getT(1).getT(1).getT(0); // project::reverb<NV>
		auto& gain1 = this->getT(1).getT(1).getT(1); // core::gain
		
		// Parameter Connections ------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // Parameter -> xfader::Value
		
		// Modulation Connections -----------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);  // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, gain1); // xfader -> gain1::Gain
		
		// Default Values -------------------------------------------------------------
		
		; // xfader::Value is automated
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		faust.setParameterT(0, 0.2);    // core::faust::delayTime
		faust.setParameterT(1, 0.);     // core::faust::damping
		faust.setParameterT(2, 2.4577); // core::faust::size
		faust.setParameterT(3, 0.5);    // core::faust::diffusion
		faust.setParameterT(4, 0.71);   // core::faust::feedback
		faust.setParameterT(5, 0.1);    // core::faust::modDepth
		faust.setParameterT(6, 2.);     // core::faust::modFreq
		
		;                            // gain1::Gain is automated
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 1.);
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
// ================================| Public Definition |================================

namespace project
{
// polyphonic template declaration

template <int NV>
using script_fx1 = wrap::node<script_fx1_impl::instance<NV>>;
}


