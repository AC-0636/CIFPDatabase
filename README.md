# CIFPDatabase  
###############################  
This program is created to obtain information from CIFP (Coded Instrument Flight Procedures) database published by FAA.  
**The database itself is not included since it excess the limited of the upload file size**  
###############################  
  


##**CIFP file link**:##  
The original CIFP file can be downloaded from the FAA website:  
https://www.faa.gov/air_traffic/flight_info/aeronav/digital_products/cifp/download/  
The document is information is generated base on Airlines Electronic Engineering Committee (AEEC) Aeronautical Radio Incorporated (ARINC) Navigation System Data Base (NDB) international standard (ARINC 424) format. 
  


##**Reference link/tool/extra material**##:  
**1.ARINC424-17**
The current version of ARINC424 used is version 18, however, the program in this repo is using ARINC424 version 17 as reference. For more information of ARINC424-17, visit:  
http://s8f1feefd4f70cc50.jimcontent.com/download/version/1347002609/module/6126893315/name/ARINC%20424-17.pdf  
  

**2. airnav.com**  
http://airnav.com/airports/  
arinav.com is a website provided all the airports information, e.g.: location, communication, runway info, arrivial procedure, departure procedure, approach procedure etc...  
This website is used during deveopment phase for understanding the CIFP code, as well as a reference to check the correctness of the generated database.  
  

**3.skyvector.com**
https://skyvector.com/  
skyvector.com is a website provided airway and airspace information of the world.  
This website is used during deveopment phase for understanding the CIFP code, as well as a reference to check the correctness of the generated database.  
  
  
**4. SpatiaLite**  
An SQLite extention named **SpatiaLite** is used in constructing the database.  
For more general information, see:  
https://www.gaia-gis.it/fossil/libspatialite/index  
For functions in SpatiaLite library:  
http://www.gaia-gis.it/gaia-sins/spatialite-sql-4.2.0.html  

  
##**Information in the database**##:  
The current edition of the generated database include the following information:  
**-Airspaces**
**-Airway/Route**  
**-Approaches**
**-Area**
**-Runways**
**-SIDs** (Standard Instrument Departure)  
**-STARs** (Standard Terminal Arrivals)  
**-Waypoints**  
  

##How to use##    
Download the CIFP file from FAA website and put it in the following path:  
**/CIFPDatabase/CIFP file/**  
Run the code, and the output database named "CIFP.db" will be generated and it can be found in:  
**/CIFPDatabase/STARsSIDs0_1/**  
*Depends on the performance of the computer, the whole process will takes ~70mins to complete*

