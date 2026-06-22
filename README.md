# yt-dlp-qt

yt-dlp-qt is a minimal Qt6 GUI wrapper for [yt-dlp](https://github.com/yt-dlp/yt-dlp), designed to simplify the process of downloading YouTube videos while leaving room for future enhancements.

## Requirements
[![yt-dlp](https://avatars.githubusercontent.com/u/79589310?s=48&v=4)](https://github.com/yt-dlp/yt-dlp)


yt-dlp:
 - ffmpeg

[![qt](https://avatars.githubusercontent.com/u/159455?s=48&v=4)](https://github.com/qt/qtbase)

QT6:
 - qt6-base-dev
 - qt6-base-doc-dev // optional

```sh
sudo apt update
sudo apt install yt-dlp qt6-base-dev qt6-base-doc-dev
```

## Build

```sh
mkdir build
cd build
cmake ..
make -j8
```

## Useful Links
- Resolution Dropdown Menu - [ComboBox](https://doc.qt.io/qt-6/qml-qtquick-controls-combobox.html)
- Audio Format - [RadioButton](https://doc.qt.io/qt-6/qradiobutton.html)
