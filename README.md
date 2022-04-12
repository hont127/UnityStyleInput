# UnityStyleInput
Unreal engine unity style input

#Init:
"""
UsInput::ReleasedStateRestore();
UsInput::Instance()->InitializeInput(contextObject);
"""

#Release:
"""
UsInput::Instance()->ReleaseInput();
UsInput::Release();
"""


#Use:
//Button:
if(UsInput::Instance()->IsPress(KEYCODE_SPACE)){
	//...
}

//Axis:
FKey key = ...
float axisValue = UsInput::Instance()->AxisValue(key);