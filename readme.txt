PortVideo is a cross-platform framework that provides uniform access to camera devices for video processing or display. It comes with a SDL demo application which compiles and runs on Win32, Linux and MacOS X systems and supports many USB, Firewire and DV cameras. This application has been developed by Martin Kaltenbrunner [modin@yuri.at] as a part of the reacTIVision framework at the Music Technology Group in Barcelona, Spain.

This Framework is in its early stages and basically has been built out of spare parts found in other open-source projects and currently provides a reasonably working software for the task. Its design is quite rudimentary and will therefore see some major improvements and changes in the future.

In general there is a simple wrapper class CameraEngine and various subclasses for each platform and camera type. The CameraTool simply returns the chosen or first available camera, initializes it with the desired width, height and color depth. Once started, a new image buffer will be returned every time you call getFrame().

DEMO APPLICATION:
-----------------
There is a simple SDL demo application included, which shows the basic usage of this framework. If you want to start right away, simply implement and add a subclass of FrameProcessor. See the FrameInverter example source code for more information.

Upon startup, the application is looking for the first available camera on the system. If a camera is found and correctly initialized, the live image from the camera is  displayed. Hitting 'T' will show the processed image, which in this demo is a simple imversion of the original. You can toggle the fullscreen mode by pressing the 'F' key. Hitting 'P' can pause the display and hitting 'ESC' will quit the application. You also can save a bitmap image by typing 'B' as well as a raw buffer image by typing 'R'.

PLATFORM NOTES:
---------------
Win32: On this platform we are using the DsVideoLib by Thomas Pintaric as a back-end to access the camera. This basically allows you to choose any WDM camera which is installed correctly, which means you can use basically any USB, Firewire or DV camera. The necessary SDL library as well as a Visual Studio .NET project is provided, so you should be able to compile the project right away. 

Mac OS X: The camera back-end for Mac OS X is using QuickTime VideoDigitizer components. This code is based on the seeSaw example application by Daniel Heckenberg and uses a modified version of his VdigGrab.c file. We tested this code also with some USB and DV cameras and most of them worked satisfactory. 
Firewire cameras are handled by the dc1394 library which provides improved configuration options and much better performance than QuickTime.
There is an Xcode project included, which should also allow you to compile the code without problems, provided you have the SDL framework installed.

Linux: On Linux we currently support Firewire cameras and USB cameras based on Video4Linux2 and Video4Linux. There is currently no support for DV cameras. In order to compile the demo application type "make" in the "linux" folder". Make sure you have the SDL libraries and headers installed as well as the libraw1394 and libdc1394 2.0 libraries and headers.

LICENSE:
--------
This framework is free software, licensed under the GNU General Public License due to the GPL license of most of its subcomponents (DsVideoLib etc.) See the file license.txt for the exact license terms.

