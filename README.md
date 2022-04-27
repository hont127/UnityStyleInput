# UnityStyleInput
Unreal engine unity style input
在UE4中使用类似Unity Input.cs风格的输入API。


因为每次走绑定Action的逻辑太麻烦，很多时候处理输入不需要绑定，写了这个工具。



# How to initialize? :

``` c++
UsInput::ReleasedStateRestore();
UsInput::Instance()->InitializeInput(contextObject);
```

# How to release?:

``` c++
UsInput::Instance()->ReleaseInput();
UsInput::Release();
```


# How to use? :

``` c++
//Button:
if(UsInput::Instance()->IsPress(KEYCODE_SPACE)){
	//...
}

//Axis:
FKey key = ...
float axisValue = UsInput::Instance()->AxisValue(key);
```

# Other Tips:
## 1. KeyCode Convert to FKey KeyCode转FKey

The KeyCode has been made into a constant and placed in the header file. Unity uses lowercase letters as the KeyCode of A-Z, while UE needs uppercase letters. This modification has been made in the header file.
Then use UE's interface `FInputKeyManager::Get().GetKeyFromCodes(keycode, charCode);`

KeyCode已经做成常量放在头文件中，Unity使用小写字母作为A-Z的KeyCode，而UE需要大写，头文件中已做该修改。
然后使用UE的接口`FInputKeyManager::Get().GetKeyFromCodes(keycode, charCode);`




## 2. How to get FKey? 如何取到需要的FKey?

Use UE's `EKeys`, such as: `EKeys::A`. Then pass the parameter to UsInput to get the specific value directly.

用UE的`EKeys`，如：`EKeys::A`。然后做参数传入UsInput直接可以拿到具体值。
