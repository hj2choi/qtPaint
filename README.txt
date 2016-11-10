README.txt
Author: Hong Joon CHOI, 20161472
ITSC  : hjchoi@connect.ust.hk


CONFIGURATION
----------------------
Note: This project only works on linux platform.

navigate towards the paint directory, then, enter the command "make".
After that, you will be able to find runnable application "paint" in the directory.




OPERATION INSTRUCTIONS
----------------------
* Project setup
   * Click anywhere on the screen or click "new Image" under "File" menu to start the new paint project.
   * You can clear or resize your image using Clr or Rs button, located under edit menu and toolbar.
   * This program supports Save, load, and virtually unlimited level of undo and redo function.

* Toolbars and draw tools
   * There are six draw tools in Toolbar, including pen, line, eraser, rectangle, fill and color picker.
   * Right click anywhere on the screen to open the corresponding tool configuration dialog.
   * You might find useful properties under configuration dialog. For example, you can draw circle and elipses with rectangle draw tool.

* Colors
   * There are two color settings: Forground and background color.
   * Both colors are be bounded to drawing tool settings.
   * On clearing and resizing image, the image are initialized with background color.

* Image layers
   * you can work with multiple image layers. Precisely white color is set to be transparent.
   * switch between layers by selecting icons on the toolbar.
   * eye icon left to each layers are layer display button. You can show or hide individual layers at your convenience.




LIST OF FILES
----------------------
Makefile
paint.pro

main.cpp
my_widget.cpp
my_widget.h
my_toolbar.cpp
my_toolbar.h

my_pendialog.cpp
my_pendialog.h
my_eraserdialog.cpp
my_eraserdialog.h
my_linedialog.cpp
my_linedialog.h
my_rectdialog.cpp
my_rectdialog.h

stack.h
my_filldialog.cpp
my_filldialog.h
my_colorpicker_dialog.cpp
my_colorpicker_dialog.h
LayeredPixmap.cpp
LayeredPixmap.h

and bmp files for icons.







KNOWN ISSUES
----------------------

- Setup
   * running the program with command "paint" might cause the program to malfunction.

- Fill
   * You don't get a correct result if you attempt to fill large area (around 700x700) at one go.

- Undo and redo
   * Minor issue: Rarely causes segmentation fault at program termination, usually when maximum undo level is set to 0.

- Save
   * Hidden layers (Layer display turned off) are not saved.

- Load
   * Load image do not restore layer properties.

- Layer icons
   * Sometimes, image on layer icons do not get updated right away. (usually after redo and load)