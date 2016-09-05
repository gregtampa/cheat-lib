# cheat-lib

![picture alt](https://raw.githubusercontent.com/nkga/cheat-lib/master/doc/img/sample.png "Cheat sample")

Library written from scratch in C++ for developing external (overlay) cheats. Features included:
- Type generic memory reads and writes from a process
- Window with hotkey support that automatically resizes and repositions to match the game window
- High-performance DirectX 11 renderer that can draw arbitrary shapes, lines, and text
- Simple 3D linear algebra / game math library

Included is a sample cheat for Battlefield 4 that features:
- ESP (Wallhacks)
- Radar minimap
- Recoil adjustment

### Background

This library consists of a compilation of shared features between cheats (typically written in C)
for a variety of different games that I've written over the years (with some features omitted for
private use only).

The most interesting elements are the transparent window overlay and its renderer. The renderer
is fairly lightweight and uses Win32 APIs to rasterize any installed system font.

The included sample is a fairly complete showcase of the features included with library.
Assuming you pack/protect the executable with something unique it will bypass any PunkBuster
anti-cheat features. It should pass FairFight protections in their current state (since
transparent overlays are not captured correctly via BitBlt), but in the future this may change
and it is left as an exercise to the user to intercept and block the call as it is fairly
trivial.

### Usage

Refer to the sample project `p_bf4` included with the release.

Include "Cheat.hpp" from core, and create a new class `FSampleCheat` that inherits from `FCheat`.

```cpp
class FSampleCheat : public FCheat {
public:
    b32 Create();
    b32 Ready();
    void Update();
};
```

Implement `Create`, `Ready` and `Update` virtual functions:

```cpp
b32 FSampleCheat::Create() {
    /* Sample keybind for exiting the overlay:
    static FWindow::FBind const binds[] = {
        { 'Q',   MOD_ALT | MOD_SHIFT, this, KeyQuit },
    };
    Window.RegisterKeys(binds, COUNT(binds));
    */

    return true;
}

b32 FSampleCheat::Ready() {
    return true;
}

void FSampleCheat::Update() {
}
```

Run the cheat using the sample below:

```cpp
FCheatSample cheat = {};
cheat.Run(cmdLine, L"Window Title", "Window Class");
```

### Building

1. Install [Visual Studio 2015](https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx).
2. Open `cheats.sln`.
3. Change solution configuration to `Release`.
4. Build solution.
