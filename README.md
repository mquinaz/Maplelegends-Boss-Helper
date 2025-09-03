# Maplelegends Boss Helper

## QT C++ application to help bossing in Maplelegends

Note down when you defeat a mini-boss, and see the corresponding timer for its possible respawn interval. Able to reset it in case of error, and ability to share it among friends for sharing wanted timers.

Ability to filter down bosses you want to see, and multimap bosses like Headless Horseman and Bigfoot.

## Compilation

Developed in Fedora and crosscompiled to Windows using Qt version 6.9.1 https://www.qt.io/offline-installers.

1. **We need the tools for Linux/Fedora**

    mkdir build-host && cd build-host

    ```bash
        cmake .. \
          -G Ninja \
          -DCMAKE_BUILD_TYPE=Release \
          -DCMAKE_INSTALL_PREFIX=$HOME/qt6-host
    ```
        
    ninja -j$(nproc)
    
    ninja install
    
2. **When cross-compiling, we need to force CMake to use MingGW tools instead of native GCC/Clang**
 
    touch mingw64-toolchain.cmake && vim mingw64-toolchain.cmake
    
    ```bash
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_SYSTEM_PROCESSOR x86_64)
    
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
    
    set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)
    ```
3. **We need the tools to build Qt libraries that run on windows with the cross-compiler MingGW**

    mkdir build-win && cd build-win

    ```bash
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
    ```

    ninja -j$(nproc)
    
    ninja install

4. **Build the project using the windows build**

    cd ~/MaplelegendsBossHelper && mkdir build-win && cd build-win
    
    $HOME/qt6-win-6.9.2/bin/qmake ../MaplelegendsBossHelper.pro
    
    make -j$(nproc)
    
5. **Use windeployqt to scan .exe and copies the needed dependencies**
    
    Copy generated release folder to windows
    
    Install the same version of qt in windows
    
    C:\Qt\6.9.2\mingw_64\bin\windeployqt.exe MaplelegendsBossHelper.exe
    
6. **Run MaplelegendsBossHelper.exe**
    
