# INTRODUCTION
The purpose of this project is to manage lights and other systems (water levels, heater, solar panels, etc.) in a van running on a 12 volts battery<br />
It runs on a [Raspberry Pi Zero W](https://www.raspberrypi.org/products/raspberry-pi-zero-w/) and uses the [GPIO port](https://pinout.xyz/) to interface with the electronic components<br />
There is a basic [electronic schema](https://github.com/cpu150/raspberrypi_van/blob/master/electronic/schema.pdf)<br />
The code is written in C++ and use [raspberrypi_gpio](https://github.com/cpu150/raspberrypi_gpio) project which is a C++ wrapper around the [bcm2835](http://www.airspayce.com/mikem/bcm2835) library

# DEPENDENCIES
## `RASPBERRYPI_GPIO` GIT REPOSITORY
The *raspberrypi_gpio* repository is connected to this repository via a git submodule.

# COMPILATION
This project use *make* to compile. Here are the available make commands:<br />
    - `all`       - build the project applying the *release* configuration<br />
    - `debug`     - build the project applying the *debug* configuration<br />
    - `clean`     - delete all generated files<br />
    - `install`   - copy files (binaries and scripts) to the OS folders and register the service to make it run at startup<br />
    - `uninstall` - remove files (binaries and scripts) from the OS folders and unregister the service

# Full install from fresh Raspberry Pi image flashed
## Update system
sudo apt-get update -y ; sudo apt-get upgrade -y ; sudo apt-get purge ; sudo apt-get autoclean ; sudo apt-get autoremove

## Install tools
sudo apt-get install -y git vim zsh<br />
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

## Setup aliases
vim ~/.zshrc<br />

    # Alias
    alias ls='ls -color'
    
    # Alias git
    alias st='git status'
    alias ci='git commit -am'
    alias br='git branch -a'
    alias co='git checkout'
    alias up='git fetch --all -Ptpmf --recurse-submodules ; git pull ; git submodule update'
    alias pu='git push'
    alias di='git diff'
    alias ditool='git difftool'
    alias mas='git checkout master ; git pull ; git submodule update'
    alias graphs="git log --graph --abbrev-commit --decorate --format=format:'%C(bold blue)%h%C(reset) - %C(bold cyan)%aD%C(reset) %C(bold green)(%ar)%C(reset)%C(bold yellow)%d%C(reset)%n''          %C(white)%s%C(reset) %C(dim white)- %an%C(reset)' --all"
    alias upall='git_update_all "$@"'
    alias upstr='git branch --set-upstream-to=origin/'
    
    # Bash script functions
    # Update all local branches, checking out each branch in succession.
    # Eventually returns to the original branch. Use "-n" for dry-run.
    git_update_all() {
        local run br
        br=$(git name-rev --name-only --exclude="tags\/*" HEAD 2>/dev/null)
        [ "$1" = "-n" ] && shift && run=echo
        
        for x in $( git branch | cut -c3- ) ; do
            $run git checkout $x && $run git pull --ff-only || return 2
        done
        
        [ ${#br} -gt 0 ] && $run git checkout "$br"
    }
    
    # If using kitty terminal then copy terminfo when using ssh
    [ "$TERM" = "xterm-kitty" ] && alias ssh="kitty +kitten ssh"

## Download, compile and install code
git clone https://github.com/cpu150/raspberrypi_van<br />
cd raspberrypi_van/source<br />
git submodule init ; git submodule update<br />
raspberrypi_gpio/bcm2835/install.sh<br />
make all<br />
make install<br />

## Update system
sudo apt-get update -y ; sudo apt-get upgrade -y ; sudo apt-get purge ; sudo apt-get autoclean ; sudo apt-get autoremove ; omz update

## Shutdown or reboot
sudo halt
