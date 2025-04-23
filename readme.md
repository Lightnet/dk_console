# dk_console

# LICENSE: MIT

# Information:
  Update to match raylib 5.5 build for window.
  
# Inputs:
- Tab key toggle to open dev console.
- Input text for keyboard chars.
- Arrow Up and down for scroll text. 
- Mouse wheel scroll for scroll text.

## Notes:
- Using scroll index which take a while to move text content. Was to keep it simple.
- Delay input lerp for toggle was insert when toggle open.

# Notes:
 * Clamp and Lerp from raylib.h.
 * Split up header to c due to redine function names. Reason for other project require module setup.
 * CMake is not library just application build test.
 * Rework folder to match standard layout.
 * Some files are origin from fork github.
 * #define LOG_SIZE 10000 cap I think 11 MB. Change you want.
 * 

# Dev Console

DK Console is a super simple drop-in dev console for your Raylib game/engine.

Webassembly Demo: https://dkvilo.github.io/dk_console/wasm-build/console.html

[DEMO VIDEO](https://www.youtube.com/watch?v=c6IXiEBWHXk)

<img src="https://github.com/dkvilo/dk_console/blob/master/Resources/prev.png" />

## Usage

1. Copy the `dk_console.h` and `dk_ui.h` files into your project.
2. Include the header in your main file.
3. Follow the example integration in `source/main.c`

Happy coding!
