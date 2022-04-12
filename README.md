# UnityStyleInput
Unreal engine unity style input
在UE4中使用类似Unity Input.cs风格的输入API。


因为走绑定Action的逻辑太麻烦，很多时候不需要绑定，因此写了这个工具。



# How to initialize? 如何初始化？:

```
UsInput::ReleasedStateRestore();
UsInput::Instance()->InitializeInput(contextObject);
```

# How to release? 如何释放？:

```
UsInput::Instance()->ReleaseInput();
UsInput::Release();
```


# How to use? 如何使用？:

```
//Button:
if(UsInput::Instance()->IsPress(KEYCODE_SPACE)){
	//...
}

//Axis:
FKey key = ...
float axisValue = UsInput::Instance()->AxisValue(key);
```

# Other Tips 其他提示:
## 1. ASCII KeyCode转FKey


KeyCode已经做成常量放在头文件中，Unity用的是小写字母作为ASCII Code，UE需要大写的，
然后使用接口`FInputKeyManager::Get().GetKeyFromCodes(keycode, charCode);`




## 2. 如何取到需要的FKey


用EKeys，如：`EKeys::A`。然后做参数传入UsInput直接可以拿到具体值。
