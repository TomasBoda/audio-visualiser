# User Manual
This document serves as a user manual to the Music Visualiser application.

## Navigation
The application is controlled using a toolbar located on the top of the window.
The toolbar contains three main menus, which are File, Playback and Visualiser.

### File
This menu is used for general actions and consists of two options.
- `Choose new file...` - this action shows a file selection dialog and allows the user to select a new audio file to be played (can be triggered using the `Ctrl+N` shortcut)
- `Quit` - this action quits the application (can be triggered using the `Ctrl+Q` shortcut)

### Playback
This menu is used for controlling the audio playback and consists of two options.
- `Resume` - this action resumes the audio playback (can be triggered using the `Ctrl+R` shortcut)
- `Pause` - this action pauses the audio playback (can be triggered using the `Ctrl+P` shortcut)

### Visualiser
This menu is used for switching current visualiser and consists of two options.
- `Equalizer` - this action changes the current visualiser to [Equalizer](#equalizer-visualiser) visualiser (can be triggered using the `Ctrl+E` shortcut)
- `Circular` - this action changes the current visualiser to [Circular](#circular-visualiser) visualiser (can be triggered using the `Ctrl+C` shortcut)
- `Volumes` - this action changes the current visualiser to [Volumes](#volumes-visualiser) visualiser (can be triggered using the `Ctrl+V` shortcut)

## Visualisers
There are three visualisers the user can choose from, which are [Equalizer](#equalizer-visualiser), [Circular](#circular-visualiser) and [Volumes](#volumes-visualiser).

### Equalizer Visualiser
This visualiser is the most natural way to visualise the frequency spectrum of an audio file. It represents a two-dimensional grid, where the horizontal space represents the frequency value in Hertz and the vertical space represents the corresponding frequency magnitude in decibels. \
There are two colored lines representing the left and right channel of the audio file. The red line represents the left channel and the blue line represents the right channel.

### Circular Visualiser
This visualiser also represents the frequency spectrum of an audio file. In this case, the spectrum is visualised around a central oval, striking to every direction. \
the left side of the circle represents the frequency spectrum of the left channel and the right side of the circle represent the frequency spectrum of the right channel.

### Volumes Visualiser
This visualiser is represents a waveform of the whole audio file based on the maximum volume at any given second of its duration. \
Each second of the audio file is represented as a small rectangle, that's height corresponds to the maximum volume of that second. \
There is also a blue line that moves from left to right over time, representing a pointer to the current second of the audio playback.

