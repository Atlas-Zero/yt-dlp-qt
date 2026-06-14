# yt-dlp-qt

## Build

```
mkdir build
cd build
cmake ..
make -j8
```

## Requirements

yt-dlp:
 - ffmpeg

QT6:
 - qt6-base-dev
 - qt6-base-doc-dev // optional

```
sudo apt update
sudo apt install yt-dlp qt6-base-dev qt6-base-doc-dev
```

### Alternativen

astral-uv (snap)

```
sudo snap refresh
sudo snap install astral-uv
```

& lib direkt holen 

`uv add yt-dlp`

oder yt-dlp auch direkt über snap

```
sudo snap refresh
sudo snap install yt-dlp
```

weiters könnte man es direkt von der Source 
[yt-dlp](https://github.com/yt-dlp/yt-dlp) installieren

## Useful Links
Resolution Dropdown Menu - [ComboBox](https://doc.qt.io/qt-6/qml-qtquick-controls-combobox.html)
Audio Format - [RadioButton](https://doc.qt.io/qt-6/qradiobutton.html)