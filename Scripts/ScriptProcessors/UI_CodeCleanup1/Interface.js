Content.makeFrontInterface(500, 400);

const var Delay1 = Synth.getEffect("Delay1");
const var HardcodedMasterFX1 = Synth.getEffect("HardcodedMasterFX1");
const var HardcodedMasterFX2 = Synth.getEffect("HardcodedMasterFX2");
const var HardcodedMasterFX3 = Synth.getEffect("HardcodedMasterFX3");

const var Knob1 = Content.getComponent("Knob1");
const var Knob2 = Content.getComponent("Knob2");
const var Knob3 = Content.getComponent("Knob3");
const var Knob4 = Content.getComponent("Knob4");
const var Knob5 = Content.getComponent("Knob5");

reg knob2referenceValue;
reg knob3referenceValue;
reg knob4referenceValue;
reg knob5referenceValue;


inline function onButton1Control(component, value)
{
	if(value == 1)
	{
		Delay1.setBypassed(1);
		HardcodedMasterFX1.setBypassed(1);
		HardcodedMasterFX2.setBypassed(1);
		HardcodedMasterFX3.setBypassed(1);
	}
	
	else if(value == 0)
	{
		Delay1.setBypassed(0);
		HardcodedMasterFX1.setBypassed(0);
		HardcodedMasterFX2.setBypassed(0);
		HardcodedMasterFX3.setBypassed(0);
	}


	
};

Content.getComponent("Button1").setControlCallback(onButton1Control);



inline function onKnob2Control(component, value)
{
	knob2referenceValue = Knob2.getValue();	
};
Content.getComponent("Knob2").setControlCallback(onKnob2Control);


inline function onKnob3Control(component, value)
{
	knob3referenceValue = Knob3.getValue();
};

Content.getComponent("Knob3").setControlCallback(onKnob3Control);


inline function onKnob4Control(component, value)
{
	knob4referenceValue = Knob4.getValue();
};

Content.getComponent("Knob4").setControlCallback(onKnob4Control);


inline function onKnob5Control(component, value)
{
	knob5referenceValue = Knob5.getValue();
};

Content.getComponent("Knob5").setControlCallback(onKnob5Control);



inline function onKnob1Control(component, value)
{
	Knob2.setValue(Knob1.getValue() * knob2referenceValue / 1.0);
	Knob3.setValue(Knob1.getValue() * knob3referenceValue / 1.0);
	Knob4.setValue(Knob1.getValue() * knob4referenceValue / 1.0);
	Knob5.setValue(Knob1.getValue() * knob5referenceValue / 1.0);	
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
 