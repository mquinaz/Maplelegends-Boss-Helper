# Maplelegends Boss Helper (Qt C++)

https://github.com/user-attachments/assets/4d864d60-2af3-4e41-bdbd-2c4767a2fed4

Keep track when you defeat a mini-boss, and see the corresponding timer for its possible respawn interval. Able to reset it in case of error, and ability to share wanted timers in a easy and accurate way. 
Either view the timers as local time, like 18:30 or view it as absolute time .1:30 meaning theres 1 hour 30 minutes left. 

The left timer corresponds to the minimum respawn time and the right timer corresponds to the maximum respawn timer; hence if the left square is green and right is red it means, the boss can already be there but there is a possibility it has not respawn; if both are green it means either the boss already respawned, or if its not there, someone else killed it. 

There is also quick links in their Name for its Maplelegends library entry; A side panel to filter down bosses you want to see. Also note that mulltimap bosses Headless Horseman and Bigfoot were also taken into account.
Finally, even if you close the application you are able to restore its timers just by normally opening it, to share timers between someone you must edit the generated time.txt with a format like so: 

Wed Sep 3 17:14:53 2025.

### **To use, just download this folder and open Release/MaplelegendsBossHelper.exe; This next section is just for developers.**

## Compilation

Developed in Fedora and crosscompiled to Windows using Qt version 6.9.1 https://www.qt.io/offline-installers.

1. **We need the tools for Linux/Fedora**

```bash
    mkdir build-host && cd build-host

    cmake .. \
      -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=$HOME/qt6-host-tools

    ninja -j$(nproc)
    
    ninja install
```

2. **When cross-compiling, we need to force CMake to use MingGW tools instead of native GCC/Clang**
     ```bash
    touch mingw64-toolchain.cmake && vim mingw64-toolchain.cmake
    
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_SYSTEM_PROCESSOR x86_64)
    
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
    
    set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)
    ```
3. **We need the tools to build Qt libraries that run on windows with the cross-compiler MingGW**

    ```bash
    mkdir build-win && cd build-win

    cmake .. \
      -G Ninja \
      -DCMAKE_TOOLCHAIN_FILE=$HOME/mingw64-toolchain.cmake \
      -DCMAKE_INSTALL_PREFIX=$HOME/qt6-win-6.9.2 \
      -DQT_HOST_PATH=$HOME/qt6-host-tools \
      -DQT_BUILD_EXAMPLES=OFF \
      -DQT_BUILD_TESTS=OFF \
      -DBUILD_qtactiveqt=OFF \
      -DBUILD_qtwebengine=OFF \
      -DBUILD_qt3d=OFF

    ninja -j$(nproc)
    
    ninja install
    ```


4. **Build the project using the windows build**

    ```bash
    cd ~/Maplelegends-Boss-Helper && mkdir build-win && cd build-win
    
    $HOME/qt6-win-6.9.2/bin/qmake ../Maplelegends-Boss-Helper.pro -spec win32-g++ \
        QMAKE_CC=x86_64-w64-mingw32-gcc \
        QMAKE_CXX=x86_64-w64-mingw32-g++ \
        QMAKE_LINK=x86_64-w64-mingw32-g++ \
        QMAKE_LINK_SHLIB=x86_64-w64-mingw32-g++
    
    make -j$(nproc)
    ```

5. **Use windeployqt to scan .exe and copies the needed dependencies**
    
    Copy generated release folder to windows
    
    Install the same version of qt in windows

    ```bash
    C:\Qt\6.9.2\mingw_64\bin\windeployqt.exe Maplelegends-Boss-Helper.exe
    ```   
6. **Run MaplelegendsBossHelper.exe**
    
