# arduino_rfid_ethernet_mysql
Arduino to MYSQL , Store RFID data to MYSQL, Arduino Attendece RFID Logger to MYSQL

# THE Hardware/Arduino SETUP
The setup Consist An Arduino UNO (any varient will just work great with an Ethernet Sheild or Module)
Arduino Ethernet Sheild.
Pizzo
LED
Some Connecting Wire

# THE CIRCUTE
This part is pretty Simple. 
Put an Ethernet Sheild on Your Arduino.
Connect the TX wire from RFID (RDM6300 in my prototype) to Digital IO 6 in the Ethernet Sheild.
Put a Pizzo (optional but verry usefull) in the Digital IO 5. Connect the other end of the Pizzo to a GND of the Sheild. 
Done

# THE LAMP / MYSQL SERVER SETUP
An LAMP or WAMP Server with a Database named "arduino" that Consists a Table "Person".
The Person Table Consists only 3 feilds "ID", "Name", "DateTime"
Use the following command to creat Database and Table
////////////////////////////////////////////////////////////////
CREATE DATABASE arduino;
USE arduino;
CREATE TABLE Person
(
    [ID] AUTOINCREMENT,
    [Name] TEXT(255),
    [DateTime] DATETIME DEFAULT NOW() NOT NULL
);
///////////////////////////////////////////////////////////////


# CONNECTING / INTERFACING
1. CREAT Database and Table
2. Place the "inm.php" file in the root folder of LAMP / WAMP
3. edit the "inm.php" with appropreate database Username and Password
4. edit the "arduino_rfid_ethernet_mysql.ino" file with appropreate IPAddress (if you are not connecting the arduino via DHCP) and server address (User the Remote or Local Servers IP or Domain Name of the remote Server) and finally change the Granted IDs of RFID cards that you have.
5.Upload Skech to Arduino
6.User Serial Monitor (Clt+Shift+M) to debug
7.Check the Database table for successfull storing of RFID tag.

Keep Trying.

Thanks
munwrecker@gmail.com
