
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