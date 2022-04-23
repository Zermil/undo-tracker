# undo-tracker

Small program made for art streamers on [Twitch](https://www.twitch.tv/)
it tracks how many times CTRL+Z has been pressed and allows them to display
it on their twitch stream through a small chroma keyable SDL window (see screenshots below)

Inspired by: [Clip studio pain undo tracker](https://github.com/dotboris/clip-studio-pain-undo-tracker)

## Installation

Unpack `undo-tracker.zip` to a folder of your choice and run `undo-tracker.exe`
(You can find `undo-tracker.zip` in this project's releases on the right side)

Quick note: do not minimize the program, make sure it's running in the background somewhere, be it 
your other monitor or just'"behind' your main drawing window's program, otherwise it will not 
count correctly (or at all) until maximized again (it still keeps track of your undos, it just won't 
update the text)

## Build

The project mainly targets Windows OS (possible change in the future) so you need MSVC compiler `cl.exe`

Set the path to your visual studio's `vcvars64.bat` script in build.bat then run `build.bat` script
from console:

```console
> build
```

after that all files necessary to run the program are in `./build` directory, you can run the program
from there:

```console
> undo-tracker.exe
```

## Screenshots

![obs](./obs.jpg)