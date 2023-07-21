//Look & Feel

const nOffWhite = "0xFFFaf9f6";
const nBlack = "0xFF121212";



//Components References
const var presetLabel = Content.getComponent("presetLabel");
const var presetWrapper = Content.getComponent("presetWrapper");
const var Next = Content.getComponent("nextPreset");
const var Prev = Content.getComponent("prevPreset");
const var PrList = Engine.getUserPresetList();

//Component Properties
Content.setPropertiesFromJSON("presetWrapper", {
    "width": 150,
    "height": 25,
    "popupMenuItems":
    "Ambience::Outdoor Drums\nAmbience::Aired Vox\nAmbience::GrandSpace \nAmbience::Distance Piano\nRooms::Teenage Bedroom\nRooms::Studio Closet \nRooms::Coarsed Area\nFx::SuperBounce\nFx::Randomised Response",
    "allowCallbacks": "Context Menu",
    "popupMenuAlign": true,
    "popupOnRightClick": false
    
});

//Components Controls Attachments
presetWrapper.setControlCallback(onPresetWrapperControl);
presetWrapper.setMouseCallback(function(event)
{
	this.setValue(event.result);
    this.changed();
});
Prev.setControlCallback(onPrevControl);
Next.setControlCallback(onNextControl);
//Engine.loadUserPreset("Factory/Fx/Preset1.preset");


//Paint Routines
presetWrapper.setPaintRoutine(function(g)
{
	
	g.setColour(nOffWhite);
	var items = this.get("popupMenuItems").split("\n");
	var t = items[value - 1];
	        
	//  Without submenu name
	//var t2 = t.substring(t.indexOf(":") + 2, t.length);
	g.setOpacity(0.5);
	g.drawAlignedText(" Select Preset", [0,2,150,20], "centred");
});





//Control Functions
inline function onPresetWrapperControl(component, value)
{
		if (value)
		{
			local items = component.get("popupMenuItems").split("\n");
			local t = items[value - 1];
			
			//  Without submenu name
			local t2 = t.substring(t.indexOf(":") + 2, t.length);
			presetLabel.set("text", t2);
			
			//Engine.loadUserPreset("Factory/Fx/Preset" + value);
		}
};
   
           
        


// Prev-Button ----------------------------------------------------------------------------------------------
inline function onPrevControl(component, value)
{
    if (value)
    {
        if (presetWrapper.getValue() <= 1)
        {
            local items = presetWrapper.get("popupMenuItems").split("\n");
            
            presetWrapper.setValue(items.length +1);
        }
        Engine.loadPreviousUserPreset(0);
        presetWrapper.setValue(presetWrapper.getValue() - 1);
	    presetWrapper.changed();
    }

};


// Next-Button ----------------------------------------------------------------------------------------------
inline function onNextControl(component, value)
{
    if (value)
    {
        local items = presetWrapper.get("popupMenuItems").split("\n");
        if (presetWrapper.getValue() == items.length)
        {
            presetWrapper.setValue(0);
        }
        Engine.loadNextUserPreset(0);
        presetWrapper.setValue(presetWrapper.getValue() + 1);
	    presetWrapper.changed();
    }

};

