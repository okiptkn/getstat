# getstat

fetch and print status on dwm bar, the codes are mainly cherry picked from the [suckless](https://dwm.suckless.org/dwmstatus/) repo

## Requirements
in order to compile `getstat` you need the following dependencies :
- Xlib header files  
- `libmpdclient`

### extra dependencies
- dwm with statuscolors patch
- mail directory of your favorite offline mail client
- powerline font

## Features
- mpd status (Playing, Paused, Stopped, and Unavailable)
- wifi essid
- mail counter
- date and time

## Preview
![getstatpreview](img/prev1.png)

## Installation
- edit `config.h` to suits your setup and run (as root if necessary) :
```
make
make clean install     
```

- or you can just copy/move the generated getstat binary to your `$PATH`
```
make
mv getstat /your/PATH/directory/getstat
```

- testing run :
```
make
./getstat
```


## License
This software is licensed under GNU General Public License v3.0 - see [LICENSE](LICENSE) for detailed information


