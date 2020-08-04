# SNAKE project
---
A game of snake from the old Nokia phones, basically.
Personal project over the holidays of 2020, during/after quarantine.

---
## Game Features

- When playing and you press the Enter key, the game toggles the debug output
- When `esc` is pressed, the game exits
- When all objects are collected, you must go into the door, which changes graphics when it can be gone into. The game prints that you have won and you must press any key to continue

---

## REQUIREMENTS:
This app requires `rlutil.h`, an extension to allow colors and some extra features in Terminal. It is a utility not made by me, therefore it is not added in this repository (as of 21. June). The link to it is [here instead](https://github.com/tapio/rlutil), as I may not have the latest version.

---

Written in C using Xcode version 11.5 on macOS Catalina (10.15.5), build version 11E608c (`xcodebuild -version`). 
When opened in Xcode, automatically runs in Terminal where it is supposed to for compatibility reasons using utf-8 as default encoding, LF as default line breaks. **Xcode shows an invalid conversion in `rlutil.h`, do not attempt to fix it - it will break stuff.**

Every file other than main.c and rlutil.h should not be compiled separately. In Xcode, this is turning off the target membership of the current file

---
May also have issues when running on Windows, as it has been built using UTF-8 character encodings (Windows cmd uses regional encoding)
Go [here](https://github.com/tapio/rlutil) to see the library of `rlutil` on GitHub (has a wiki).

---
Code is located in the `snake` folder, `snake.xcodeproj` is useful only when running on a Mac in Xcode.
