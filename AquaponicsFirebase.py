
import pyrebase
import time
import serial

# Send code to Raspberry pi wired to arduino and sensors wired into the aquaponic structure

# Get serial from the arduino connected to the Raspberry Pi
ser = serial.Serial('/dev/serial/by-id/usb-Arduino_www.arduino.cc__Arduino_Uno_5563931363351506061-if00', 9600)

#Insert Email and Password for Aquaponics Gmail Account
email = "**********@gmail.com"
password = "**********"


# Fill in given fields with Firebase Credentials
config = {
    "apiKey": "**********",
    "authDomain": "**********.firebaseapp.com",
    "databaseURL": "https://**********.firebaseio.com",
    "projectID": "**********",
    "storageBucket": "**********.appspot.com",
    "messagingSenderId": "**********",
    "appId": "**********"
}

# Initialize sign in to database
firebase = pyrebase.initialize_app(config)
auth = firebase.auth()
user = auth.sign_in_with_email_and_password(email, password)
db = firebase.database()

# Flush Serial
ser.flush_Input()

# data to save
while 1:

    # Retrieve data sent from Serial
        # Once more sensors are added turn into array
    data1 = ser.readline()
    data2 = ser.readline()
    data3 = ser.readline()
    data4 = ser.readline()

    # Split data into pieces based on the split character (#)
    pieces1 = data1.decode().split("#")
    pieces2 = data2.decode().split("#")
    pieces3 = data3.decode().split("#")
    pieces4 = data4.decode().split("#")

    # Name data into their proper sensors
    humidity = pieces1[0]
    waterTemp = pieces2[0]
    temperature = pieces3[0]
    pH = pieces4[0]

    # Create structure to send sensor data to firebase database for android app to recieve
    data = {"Temperature": temperature,
            "Humidity": humidity,
            "Water Temperature": waterTemp,
            "pH": pH}

    # Send data to firebase database as a child of Sensors and Data
    db.child("Sensors").child("Data").set(data)

  







