![Zombie Cafe Revival banner](/src/assets/images/banner.png)

# Zombie Cafe Revival 2.0

This is my fork of [Airyzz/zombie-cafe-revival](https://github.com/Airyzz/zombie-cafe-revival). Huge thanks to Airyzz for reverse engineering and reviving Zombie Cafe, and for making the original project available.

My intention with this fork is to keep the original revival work intact while adding a small optional mod menu for easier testing and casual gameplay in BlueStacks/Android. More updates might come later, including work on fixing crashes and improving stability.

## Download

Latest APK from this fork: [ZombieCafe-debug-menu.apk](release/ZombieCafe-debug-menu.apk)

## Mod Menu

This fork adds a small in-game mod menu with:

- +1 toxin
- Max toxin
- +1 money
- +10k money
- Max money

![Mod menu screenshot](docs/mod-menu.png)

## Original Project

The original Zombie Cafe Revival project is an effort to reverse engineer and revive the game, reimplementing online services, fixing crashes, and adding new content.

You can read Airyzz's technical article here: [Zombie Cafe Revival article](https://airyz.xyz/p/zombie-cafe-revival/)

## Building

### Requirements

- cmake
- make
- go
- apktool
- jarsigner

### LibZombieCafeExtension

LibZombieCafeExtension is an extra library that applies runtime patches to the game's `libZombieCafeAndroid.so`.

```bash
cd src/lib/cpp
mkdir build
cd build
cmake ../ -DCMAKE_TOOLCHAIN_FILE=$NDK_HOME/build/cmake/android.toolchain.cmake -DANDROID_ABI=armeabi-v7a -DANDROID_PLATFORM=android-8

make
```

### Running Tools

Part of the build process for this project is running custom tools to convert the human readable file structure into the game's expected file formats.

```bash
go run ./tool/build_tool/ -i src/ -o build/

cp src/lib/cpp/build/libZombieCafeExtension.so ./build/lib/armeabi/libZombieCafeExtension.so

apktool b ./build -o ./build/out/out.apk

jarsigner -verbose -keystore debug.keystore -storepass zombiecafe ./build/out/out.apk alias_name

adb install -r ./build/out/out.apk
```