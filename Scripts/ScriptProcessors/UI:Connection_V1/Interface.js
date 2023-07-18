Content.makeFrontInterface(500, 400);

const var Delay1 = Synth.getEffect("Delay1");
const var HardcodedMasterFX1 = Synth.getEffect("HardcodedMasterFX1");
const var HardcodedMasterFX2 = Synth.getEffect("HardcodedMasterFX2");
const var HardcodedMasterFX3 = Synth.getEffect("HardcodedMasterFX3");



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
 