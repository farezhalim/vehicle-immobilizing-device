# App

The app developed for this project is used to disable the immobilization process by communicating to the device via bluetooth.

## Android app

The Android app was programmed using Java and has only two screens for ease of use. The first screen allows the user to log-in using their authorized username and password, which will permit access to the second screen of the app which performs the main function of the disabling module:
1. Enable Bluetooth, set the phone as discoverable, discover nearby Bluetooth devices and pair with the immobilizer device 
2. Query the database using the MAC address to retrieve the correct unlock password associated with the device
3. Send the unlock password as a plaintext file to the immobilizer device through Bluetooth file transfer.

User authentication is done using realtime database hosted on Google Firebase.
The passcodes for each device shall also be stored on this database, and can be queried using each device's unique MAC address. 
The app does the query automatically after paired with the immobilization device.

### Known bugs
Some of the known bugs within the app:
*  crash on back press in the main screen

## iOS app

An iOS app was initially developed, however limitations of iOS prevented further development. iOS limits what a developer can use an iPhones bluetooth capabilities for. Therefore, file transfer with a paired device could not be implemented through an iOS app. The code here has been included, however should be treated as an archive of work done.