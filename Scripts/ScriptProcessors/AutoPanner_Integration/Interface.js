Content.makeFrontInterface(500, 500);

include("PresetMenu.js");
include("GuiResizing.js");



const var Delay1 = Synth.getEffect("Delay1");
const var HardcodedMasterFX1 = Synth.getEffect("HardcodedMasterFX1");
const var HardcodedMasterFX2 = Synth.getEffect("HardcodedMasterFX2");
const var HardcodedMasterFX3 = Synth.getEffect("HardcodedMasterFX3");
const var HardcodedMasterFX4 = Synth.getEffect("HardcodedMasterFX4");
const var HardcodedMasterFX5 = Synth.getEffect("HardcodedMasterFX5");
const var PhaseFX1 = Synth.getEffect("Phase FX1");

const var Knob1 = Content.getComponent("Knob1");
const var Knob2 = Content.getComponent("Knob2");
const var Knob3 = Content.getComponent("Knob3");
const var Knob4 = Content.getComponent("Knob4");
const var Knob5 = Content.getComponent("Knob5");
const var Knob6 = Content.getComponent("Knob6");
const var Knob7 = Content.getComponent("Knob7");
const var Knob8 = Content.getComponent("Knob8");


reg knob2referenceValue;
reg knob3referenceValue;
reg knob4referenceValue;
reg knob5referenceValue;
reg knob6referenceValue;
reg knob7referenceValue;
reg knob8referenceValue;


inline function onButton1Control(component, value)
{
	if(value == 1)
	{
		Delay1.setBypassed(1);
		HardcodedMasterFX1.setBypassed(1);
		HardcodedMasterFX2.setBypassed(1);
		HardcodedMasterFX3.setBypassed(1);
		HardcodedMasterFX4.setBypassed(1);
		HardcodedMasterFX5.setBypassed(1);
		PhaseFX1.setBypassed(1);
	}
	
	else if(value == 0)
	{
		Delay1.setBypassed(0);
		HardcodedMasterFX1.setBypassed(0);
		HardcodedMasterFX2.setBypassed(0);
		HardcodedMasterFX3.setBypassed(0);
		HardcodedMasterFX4.setBypassed(0);
		HardcodedMasterFX5.setBypassed(0);
		PhaseFX1.setBypassed(0);
	}


	
};

Content.getComponent("Button1").setControlCallback(onButton1Control);



inline function onKnob2Control(component, value)
{
	knob2referenceValue = Knob2.getValue();	
	HardcodedMasterFX1.setAttribute(0, value);
};
Content.getComponent("Knob2").setControlCallback(onKnob2Control);


inline function onKnob3Control(component, value)
{
	knob3referenceValue = Knob3.getValue();
	HardcodedMasterFX2.setAttribute(0, value);
};

Content.getComponent("Knob3").setControlCallback(onKnob3Control);


inline function onKnob4Control(component, value)
{
	knob4referenceValue = Knob4.getValue();
	Delay1.setAttribute(6, value);
};

Content.getComponent("Knob4").setControlCallback(onKnob4Control);


inline function onKnob5Control(component, value)
{
	knob5referenceValue = Knob5.getValue();

	HardcodedMasterFX3.setAttribute(0, value);
};

Content.getComponent("Knob5").setControlCallback(onKnob5Control);

inline function onKnob6Control(component, value)
{
	knob6referenceValue = Knob6.getValue();

	PhaseFX1.setAttribute(3, value);
};

Content.getComponent("Knob6").setControlCallback(onKnob6Control);

inline function onKnob7Control(component, value)
{
	knob7referenceValue = Knob7.getValue();

	HardcodedMasterFX4.setAttribute(0, value);
};

Content.getComponent("Knob7").setControlCallback(onKnob7Control);


inline function onKnob8Control(component, value)
{
	knob8referenceValue = Knob8.getValue();

	HardcodedMasterFX5.setAttribute(0, value);
};

Content.getComponent("Knob8").setControlCallback(onKnob8Control);



inline function onKnob1Control(component, value)
{
	Knob2.setValue(Knob1.getValue() * knob2referenceValue / 1.0);
	Knob3.setValue(Knob1.getValue() * knob3referenceValue / 1.0);
	Knob4.setValue(Knob1.getValue() * knob4referenceValue / 1.0);
	Knob5.setValue(Knob1.getValue() * knob5referenceValue / 1.0);
	Knob6.setValue(Knob1.getValue() * knob6referenceValue / 1.0);
	Knob7.setValue(Knob1.getValue() * knob7referenceValue / 1.0);
	Knob8.setValue(Knob1.getValue() * knob8referenceValue / 1.0);
		
	
	HardcodedMasterFX1.setAttribute(0, Knob2.getValue());
	HardcodedMasterFX2.setAttribute(0, Knob3.getValue());
	Delay1.setAttribute(6, Knob4.getValue());
	HardcodedMasterFX3.setAttribute(0, Knob5.getValue());
	PhaseFX1.setAttribute(3, Knob6.getValue());
	HardcodedMasterFX4.setAttribute(0, Knob7.getValue());
	HardcodedMasterFX5.setAttribute(0, Knob8.getValue());
};

Content.getComponent("Knob1").setControlCallback(onKnob1Control);








function onNoteOn()
{
	
}
 function onNoteOff()
{
	
}
 function onController()
{
	
}
 function onTimer()
{
	
}
 function onControl(number, value)
{
	
}
 