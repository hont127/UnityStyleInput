# UnityStyleInput
Unreal engine unity style input
在UE4中使用类似Unity Input.cs风格的输入API。

#How to initialize? 如何初始化？:

```
UsInput::ReleasedStateRestore();
UsInput::Instance()->InitializeInput(contextObject);
```

#How to release? 如何释放？:

```
UsInput::Instance()->ReleaseInput();
UsInput::Release();
```


#How to use? 如何使用？:

```
//Button:
if(UsInput::Instance()->IsPress(KEYCODE_SPACE)){
	//...
}

//Axis:
FKey key = ...
float axisValue = UsInput::Instance()->AxisValue(key);
```
