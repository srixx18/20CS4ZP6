
# Final Product

An output for Win64 architecture is added under the ``output/win64`` folder.

To run - double click the executable .jar file. 

***Note: Java 8 or Above JRE/JDK is required.***

To run on other platforms, please refer to 5.2.2.2 in FinalDoc.

# 20CS4ZP6

A crypto loyalty point system

## Swing GUI

### Prerequisite
1. JAVA 1.8 SDK
2. Netbeans IDE

### IDE - NetBeans

[Apache NetBeans 11 LTS (NB 11.0)](https://netbeans.apache.org/download/nb110/nb110.html) (Recommended)

No wizard installer available for this version. Can be built from the source. 
**Lower version can have installer, but haven't been tested on.**

[Apache Ant](https://ant.apache.org/bindownload.cgi) is required for building from the source for version 11.0.
  

**Netbeans Building instruction:**

1. set environment variable for ant

2. cd to the Netbeans unzip folder

3. run command "ant"

  

### Project Import Instruction
1. After build, open the IDE from the terminal by key in "./nbbuild/netbeans/bin/netbeans"
2. file>Open Project..>Select the **EC-SwingGui** project
3. Installing dependencies dialog will pop-up, accept it and go next
4. Done
  
  

### Annotation

1. .jar files are located under the **EC-SwingGui/lib/** folder. We are not using maven, so we need to place the .jar files manually.
2. "Wallet" and "Admin" classes are runnable, to switch the default running class. Right click the project "EC-SwingGui" from the directory tree in Netbeans and select "properties". Under the "Run" section in the "Project Properties" dialog allows you to switch the default running class.

## C++ Build Instructions

### Environmental Setup
1. Download [Visual Studio Community 2019](https://visualstudio.microsoft.com/vs/community/)
2. Install the Visual Studio installer
3. Run the installer, from "Workloads" tab, under "Desktop & Mobile" section, check "Desktop development with C++"
4. Click Install

### Visual Studio setup
To make sure that our c++ program does not get confused with tab and space, Visual Studio require the following settings:
1. Open Visual Studio
2. Under Tools -> Options -> Text Editor -> C/C++ -> Tabs -> Tab, choose "Insert spaces"

### Build
1. clone the repo
2. open visual studio, choose "Open a project or solution", locate DigitalLoyaltyMoney.sln and then click ok
3. under Solution Explorer, right click "DigitalLoyaltyMoney" and select "build"

### Project folder structure
<pre>
c++/DigitalLoyaltyMoney/
  DigitalLoyaltyMoney/
    Admin.cpp
    Admin.h
    DigitalLoyaltyMoney.vcxproj
    DigitalLoyaltyMoney.vcxproj.filters
    DigitalLoyaltyMoney.user
    Wallet.cpp
    Wallet.h
    main.cpp
  DigitalLoyaltyMoney.sln
</pre>