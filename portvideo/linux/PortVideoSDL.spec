%define version 0.4
%define release 1

Summary:      portVideo demo application
Name:         PortVideoSDL
Version:      %{version}
Release:      %{release}
License:      GPL
Group:        Applications/Multimedia
URL:          http://www.iua.upf.es/mtg/reacTable/PortVideo/
Source0:      %{name}-%{version}.tar.gz
BuildRoot:    %{_tmppath}/%{name}-%{version}-buildroot
Packager:     Martin Kaltenbrunner

Requires: SDL libraw1394 libdc1394
BuildRequires: gcc-c++ SDL-devel libraw1394-devel libdc1394-devel

%description
A cross-platform framework that provides uniform access to camera devices 
for video processing or display. It comes with a SDL demo application 
which compiles and runs on Win32, Linux and MacOS X systems and supports 
many USB, Firewire and DV cameras.

%prep
%setup -q -n %{name}-%{version}

%build
cd linux
make

%install
rm -rf $RPM_BUILD_ROOT
cd linux
make DESTDIR=$RPM_BUILD_ROOT BINDIR=%{_bindir} PREFIX=%{_prefix} install

%clean
rm -rf %{buildroot}

%files
%{_bindir}/%{name}
%{_prefix}/share/%{name}/readme.txt
%{_prefix}/share/%{name}/license.txt

%changelog
* Tue Aug 11 2009 Martin Kaltenbrunner <modin@yuri.at>
                * updates from reacTIVision 1.4 release
                * added camera configuration file
                * added on-screen camera settings
                * improved Linux Firewire support
                * improved Linux V4L support
                * disabled initial camera dialog on Mac & Win
                * updated SDL library to 1.2.13
                * added fullscreen mode to demo
* Tue Sep 20 2006 Martin Kaltenbrunner <mkalten@iua.upf.es>
		* implemented disconnect detection
		* Linux Firewire FORMAT7 support
		* Mac Universal Binary Support
		* updated to XCode 2.4
		* updated to MS Visual Studio .NET 2005
		* updated SDL to 1.2.11
* Tue Dec 20 2005 Martin Kaltenbrunner <mkalten@iua.upf.es>
		* improved the win32 RGB to gray conversion
		* allow saving of frames (RAW and BMP)
		* added a finish method to the FrameProcessor
		* updated DsVideoLib builds without DirectX SDK
		* added V4L_DEVICE variable (thanks to Frank Barknecht)
		* various bug fixes
* Mon Jan 03 2005 Martin Kaltenbrunner <mkalten@iua.upf.es>
           	* added cameraTool which returns a cameraEngine for any platform
		* made the SDL demo more modular (FrameProcessor)
		* fixed problem with video4linux cameras
* Fri Dec 24 2004 Martin Kaltenbrunner <mkalten@iua.upf.es>
                 * initial Release

