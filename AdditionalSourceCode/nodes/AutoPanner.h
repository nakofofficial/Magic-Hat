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

namespace AutoPanner_impl
{
// ==============================| Node & Parameter type declarations |==============================

DECLARE_PARAMETER_RANGE_SKEW(dry_wet_mixer_c0Range, 
                             -100., 
                             0., 
                             5.42227);

using dry_wet_mixer_c0 = parameter::from0To1<core::gain, 
                                             0, 
                                             dry_wet_mixer_c0Range>;

using dry_wet_mixer_c1 = dry_wet_mixer_c0;

using dry_wet_mixer_multimod = parameter::list<dry_wet_mixer_c0, dry_wet_mixer_c1>;

using dry_wet_mixer_t = control::xfader<dry_wet_mixer_multimod, faders::linear>;

using dry_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, dry_wet_mixer_t>, 
                                    core::gain>;
template <int NV>
using oscillator_t = wrap::no_data<core::oscillator<NV>>;

DECLARE_PARAMETER_RANGE(peak_modRange, 
                        -1., 
                        1.);

template <int NV>
using peak_mod = parameter::from0To1<jdsp::jpanner<NV>, 
                                     0, 
                                     peak_modRange>;

template <int NV>
using peak_t = wrap::mod<peak_mod<NV>, 
                         wrap::no_data<core::peak>>;

template <int NV>
using modchain_t_ = container::chain<parameter::empty, 
                                     wrap::fix<1, oscillator_t<NV>>, 
                                     core::smoother<NV>, 
                                     math::pow<NV>, 
                                     math::sig2mod<NV>, 
                                     peak_t<NV>>;

template <int NV>
using modchain_t = wrap::control_rate<modchain_t_<NV>>;

template <int NV>
using frame2_block_t_ = container::chain<parameter::empty, 
                                         wrap::fix<2, modchain_t<NV>>>;

template <int NV>
using frame2_block_t = wrap::frame<2, frame2_block_t_<NV>>;

template <int NV>
using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, frame2_block_t<NV>>, 
                                    jdsp::jpanner<NV>, 
                                    core::gain>;

namespace dry_wet1_t_parameters
{
}

template <int NV>
using dry_wet1_t = container::split<parameter::plain<AutoPanner_impl::dry_wet_mixer_t, 0>, 
                                    wrap::fix<2, dry_path_t>, 
                                    wet_path_t<NV>>;

namespace AutoPanner_t_parameters
{
}

template <int NV>
using AutoPanner_t_ = container::chain<parameter::plain<AutoPanner_impl::dry_wet1_t<NV>, 0>, 
                                       wrap::fix<2, dry_wet1_t<NV>>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public AutoPanner_impl::AutoPanner_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(AutoPanner);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(20)
		{
			0x005B, 0x0000, 0x5000, 0x6E61, 0x656E, 0x5F72, 0x6D41, 0x756F, 
            0x746E, 0x0000, 0x0000, 0x0000, 0x8000, 0x003F, 0x8000, 0x003F, 
            0x8000, 0x003F, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& dry_wet1 = this->getT(0);                                   // AutoPanner_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(0).getT(0);                           // AutoPanner_impl::dry_path_t
		auto& dry_wet_mixer = this->getT(0).getT(0).getT(0);              // AutoPanner_impl::dry_wet_mixer_t
		auto& dry_gain = this->getT(0).getT(0).getT(1);                   // core::gain
		auto& wet_path = this->getT(0).getT(1);                           // AutoPanner_impl::wet_path_t<NV>
		auto& frame2_block = this->getT(0).getT(1).getT(0);               // AutoPanner_impl::frame2_block_t<NV>
		auto& modchain = this->getT(0).getT(1).getT(0).getT(0);           // AutoPanner_impl::modchain_t<NV>
		auto& oscillator = this->getT(0).getT(1).getT(0).getT(0).getT(0); // AutoPanner_impl::oscillator_t<NV>
		auto& smoother = this->getT(0).getT(1).getT(0).getT(0).getT(1);   // core::smoother<NV>
		auto& pow = this->getT(0).getT(1).getT(0).getT(0).getT(2);        // math::pow<NV>
		auto& sig2mod = this->getT(0).getT(1).getT(0).getT(0).getT(3);    // math::sig2mod<NV>
		auto& peak = this->getT(0).getT(1).getT(0).getT(0).getT(4);       // AutoPanner_impl::peak_t<NV>
		auto& jpanner = this->getT(0).getT(1).getT(1);                    // jdsp::jpanner<NV>
		auto& wet_gain = this->getT(0).getT(1).getT(2);                   // core::gain
		
		// Parameter Connections -------------------------------------------------------------------
		
		dry_wet1.getParameterT(0).connectT(0, dry_wet_mixer); // DryWet -> dry_wet_mixer::Value
		this->getParameterT(0).connectT(0, dry_wet1);         // Panner_Amount -> dry_wet1::DryWet
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		peak.getParameter().connectT(0, jpanner);               // peak -> jpanner::Pan
		
		// Default Values --------------------------------------------------------------------------
		
		; // dry_wet1::DryWet is automated
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		oscillator.setParameterT(0, 0.); // core::oscillator::Mode
		oscillator.setParameterT(1, 1);  // core::oscillator::Frequency
		oscillator.setParameterT(2, 1.); // core::oscillator::FreqRatio
		oscillator.setParameterT(3, 1.); // core::oscillator::Gate
		oscillator.setParameterT(4, 0.); // core::oscillator::Phase
		oscillator.setParameterT(5, 1.); // core::oscillator::Gain
		
		smoother.setParameterT(0, 100.); // core::smoother::SmoothingTime
		smoother.setParameterT(1, 0.);   // core::smoother::DefaultValue
		
		pow.setParameterT(0, 1.); // math::pow::Value
		
		sig2mod.setParameterT(0, 1.); // math::sig2mod::Value
		
		;                             // jpanner::Pan is automated
		jpanner.setParameterT(1, 1.); // jdsp::jpanner::Rule
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 1.);
		this->setExternalData({}, -1);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool isProcessingHiseEvent() { return true; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
	
	void setExternalData(const ExternalData& b, int index)
	{
		// External Data Connections ---------------------------------------------------------------
		
		this->getT(0).getT(1).getT(0).getT(0).getT(0).setExternalData(b, index); // AutoPanner_impl::oscillator_t<NV>
		this->getT(0).getT(1).getT(0).getT(0).getT(4).setExternalData(b, index); // AutoPanner_impl::peak_t<NV>
	}
};
}

#undef getT
#undef connectT
#undef setParameterT
#undef setParameterWT
#undef getParameterT
// ======================================| Public Definition |======================================

namespace project
{
// polyphonic template declaration

template <int NV>
using AutoPanner = wrap::node<AutoPanner_impl::instance<NV>>;
}


