# SNAKE project
---
A game of snake from the old Nokia phones, basically.
Personal project over the holidays of 2020, during/after quarantine.

---
Written in C using Xcode version 11.5 on macOS Catalina (10.15.5), build version 11E608c (`xcodebuild -version`). 
When opened in Xcode, automatically runs in Terminal where it is supposed to for compatibility reasons using utf-8 as default encoding, LF as default line breaks

---
Uses `#pragma mark` for visual assistance on the sliding menu in Xcode, may be an issue when running on Windows - `#pragma mark` is used everywhere **EXCEPT**  `rlutil/h`, which is a library by Tapio to have colors in Terminal/cmd.
May also have issues when running on Windows, as it has been built using UTF-8 character encodings (Windows cmd uses regional encoding)
Go [here](https://github.com/tapio/rlutil) to see the library of `rlutil` on GitHub (has a wiki).
