README                                                      Rev.6.02 Nov.30,2022

1. Contents
   Starter Kit (STK) for Renesas FGIC RAJ240090 / RAJ240100.
   This STK containts following items.
    * User's Manual / Quick start guide
    * Evaluation board (EVB) Instrucation manual
    * Sample firmware, its specification, and device file for software developers
    * GUI-based SMBus monitoring tool (RSB TOOL2) and its manual
    * Add-on function for CS+ (QE for Battery Management) and its manual
    * RAJ240090 / RAJ240100 Data sheet
    * This README

 <<Caution>> Old version of RAJ240100 devices have limitations of characteristics and functions.
             If you have any issues with these limitations, please check an IC marking of the device
             mounted on the evaluation boards. If marking 2nd line is A20, the device is
             an old version and does NOT support the following functions.

            (1) -40 degC function
            (2) Over voltage / Under voltage detection w/o MCU
            (3) Over temperature / Under temperature detection w/o MCU
            (4) Automatic mode transition function in low power operation mode

            If you would like to evaluate the latest devices,
            please contact your regional sales representatives.

2. Directory tree structure and explanation
Readme.txt                             ; This file
|----Doc
|    r01an4062ej0xxx-raj240100     ; User's Manual for STK
|    r01an3919ej0xxx-raj240xxx     ; Sample code Specification
|    r01an3920ej0xxx-raj240xxx     ; RSB_TOOL2 Specification
|    r01ds0301ej0xxx-raj240100     ; RAJ240090 / RAJ240100 Data sheet
|    RTK0EF0014D0000xBx            ; Evaluation module schematics
|    
|----Device File                       ; RAJ240090/100 device custom file for old version of CS+ (CC-RL compiler)
|      Device_Custom_FGC128K-S_E101c.zip
|    
|----src\090_100_SPL                   ; Regarding each files, refer to Sample code Specification
|    |  RAJ240100_CS+v8.01_or_later.mtpj ;           Project file for CS+ for CC V8.01 or later
|    |  cstart.asm                     ; 
|    |  stkinit.asm                    ; Default calibration data
|     --src                            ; Source file folder
|         RAJ240090.dr                 ; Link directive file
|         pfdl.lib                     ; Data flash Access library
|----tool                              ; Windows application for Evaluation
|    |  
|    |--Parameter                      ; Sample parameter file
|    |    RAJ240090_SampleCode_Fixed.mot           ; Sample fixed data for RAJ240090 (8 serias cell)
|    |    RAJ240100_SampleCode_Fixed.mot           ; Sample fixed data for RAJ240100 (10 serias cell)
|    |    RAJ240090-100_SampleCode_Own.mot
|    |
|     --RSB_TOOL2                      ; Windows application folder
|         RSB_TOOL2_for_Sample_Rev6.31.exe         ; RSB TOOL2 execution file
|         Battcom.dll                              ; RSB TOOL2 DLL file (Note 1)
|         msbm2.ini                                ; Battcom.dll setting file (Note 1)
|         RSB_TOOL2.ini                            ; RSB TOOL2 setting file
|         DefaultFile
|           RAJ240090_sample_default.mot           ; Composite file of Sample code and Fixed&Own data
|           RAJ240100_sample_default.mot           ; Composite file of Sample code and Fixed&Own data
|         UpdateFiles      			   ; Target file folder to update
|         SequenceFile                             ; For generic function
|         configuration                            
|           |--memory                              : RSB TOOL2 memory configuration file folder (Note 1)   
|           |    RAJ240090_CS+_Sample_90_6.20_1#1.bin
|           |    RAJ240100_CS+_Sample_100_6.20_1#1.bin
|           |--sbs                                 ; RSB TOOL2 command configuration file folder (Note 1)
|           |    SBS_STD.bin           
|           |    CS+_Sample_90_1#4.bin   
|           |    CS+_Sample_100_1#4.bin
|
 -------USB driver for USB-SMBus host adapter      ; Driver file (Note 1)
     |    RTK0EF0029Z0000xBx.inf                   ; USB-SMBus I/F driver for regacy windows
     |    rtk0ef0029z0000xbx.cat                   ; Certificate file of USB driver
      ------
            |--64bit
                 RTK0EF0029Z0000xBx.inf            ; USB-SMBus I/F driver for regacy windows
                 rtk0ef0029z0000xbx.cat            ; Certificate file of USB driver for 64bit windows

Note 1: DO NOT edit these files and contents.
        If you change(d) these, the RSB TOOL2 may not work correctly.

3. Contact
   If you have problems or questions,
   please contact Renesas contact person in each region.

4. Revision History
   [*SC:SampleCode, *RT:RSBtool2, *SP:Specification *DR:USB_Driver *UM:UsersManual *QS:QuickStart *DS:DataSheet]
   Rev.1.00 Nov.21,2017 First Release
   Rev.2.00 Mar.30,2018 Added the new function of RSB TOOL2 to reset the factory default.
   Rev.3.00 Jun,06,2018 Improved the some issue of the source code and specification. *SC*SP
   Rev.4.00 Sep.18,2019 Updated RSB_TOOL2
   Rev.6.01 Mar.24,2022 Fixed the FCC update function
   Rev.6.02 Nov.30,2022 Updated RSB_TOOL2   