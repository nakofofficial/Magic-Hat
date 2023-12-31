Content.makeFrontInterface(500, 400);

const var Knob1 = Content.getComponent("Knob1");
const var Knob2 = Content.getComponent("Knob2");
const var Knob3 = Content.getComponent("Knob3");
const var Knob4 = Content.getComponent("Knob4");
const var Knob5 = Content.getComponent("Knob5");


//Knobs max value variable
reg knob2referenceValue;
reg knob3referenceValue;
reg knob4referenceValue;
reg knob5referenceValue;


//Passing all knobs value to variables 
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


//Main knob controlling independents knobs, respecting each range
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
 