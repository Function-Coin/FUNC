
Debian
====================
This directory contains files used to package funcd/func-qt
for Debian-based Linux systems. If you compile funcd/func-qt yourself, there are some useful files here.

## func: URI support ##


func-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install func-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your funcqt binary to `/usr/bin`
and the `../../share/pixmaps/func128.png` to `/usr/share/pixmaps`

func-qt.protocol (KDE)

