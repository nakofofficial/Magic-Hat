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

namespace distorion_impl
{
// ========================| Node & Parameter type declarations |========================

DECLARE_PARAMETER_RANGE_STEP(xfader_c0Range, 
                             -15., 
                             0., 
                             0.1);

using xfader_c0 = parameter::from0To1<core::gain, 
                                      0, 
                                      xfader_c0Range>;

DECLARE_PARAMETER_RANGE_STEP(xfader_c1Range, 
                             0., 
                             0.5, 
                             0.01);

template <int NV>
using xfader_c1 = parameter::from0To1<project::distortion<NV>, 
                                      1, 
                                      xfader_c1Range>;

template <int NV>
using xfader_multimod = parameter::list<xfader_c0, xfader_c1<NV>>;

template <int NV>
using xfader_t = control::xfader<xfader_multimod<NV>, faders::rms>;

namespace distorion_t_parameters
{
}

template <int NV>
using distorion_t_ = container::chain<parameter::plain<distorion_impl::xfader_t<NV>, 0>, 
                                      wrap::fix<2, xfader_t<NV>>, 
                                      project::distortion<NV>, 
                                      core::gain>;

// ============================| Root node initialiser class |============================

template <int NV> struct instance: public distorion_impl::distorion_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(distorion);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(20)
		{
			0x005B, 0x0000, 0x4400, 0x7369, 0x6F74, 0x7472, 0x6F69, 0x006E, 
            0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 
            0x0000, 0x0000, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References --------------------------------------------------------------
		
		auto& xfader = this->getT(0); // distorion_impl::xfader_t<NV>
		auto& faust = this->getT(1);  // project::distortion<NV>
		auto& gain = this->getT(2);   // core::gain
		
		// Parameter Connections --------------------------------------------------------
		
		this->getParameterT(0).connectT(0, xfader); // Distortion -> xfader::Value
		
		// Modulation Connections -------------------------------------------------------
		
		auto& xfader_p = xfader.getWrappedObject().getParameter();
		xfader_p.getParameterT(0).connectT(0, gain);  // xfader -> gain::Gain
		xfader_p.getParameterT(1).connectT(0, faust); // xfader -> faust::Drive
		
		// Default Values ---------------------------------------------------------------
		
		; // xfader::Value is automated
		
		faust.setParameterT(0, 0.);   // core::faust::Bypass
		;                             // faust::Drive is automated
		faust.setParameterT(2, 0.19); // core::faust::Offset
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.);
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
// =================================| Public Definition |=================================

namespace project
{
// polyphonic template declaration

template <int NV>
using distorion = wrap::node<distorion_impl::instance<NV>>;
}


