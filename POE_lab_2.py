
'''
Code for interpreting servo angles and IR distance sensor data from an
Arduino serial monitor.
By @arwensadler
'''


import serial
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import math


# Set the serial port
arduinoComPort = "COM9"



# Set the baud rate
baudRate = 9600



# open the serial port
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

# List to store the yaw servo angles
angles_y = []

# List to store the pitch servo angles
angles_p = []

# List to store the sweep values
values = []

# List to store converted values in
cm = []

# List to store x values
xs = []

# List to store y values
ys = []

# List to store z values
zs = []

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

#
# main loop to read data from the Arduino, then display it
#
while True:
  #
  # ask for a line of data from the serial port, the ".decode()" converts the
  # data from an "array of bytes", to a string
  #
  lineOfData = serialPort.readline().decode()

  #
  # check if data was received
  #
  if len(lineOfData) > 0:
    #
    # data was received, convert it into 4 integers
    #
    a, b, c = (int(x) for x in lineOfData.split(','))

    #
    #
    #
    angles_y.append(int(a)) # Add the angle of the yaw servo to the yaw list
    angles_p.append(int(b)) # Add the angle of the pitch servo to the pitch list
    cm = 9829.8/(int(c)-0.0169) # Convert the sensor value to centimeters
    values.append(float(cm)) # Add cm to the values list
    print(int(a),int(b),float(cm))

  elif len(angles_y) > 0:

    for i in angles_y:
        # Get the x, y, and z distances
        h = values[i-1]*math.cos(math.radians(angles_p[i-1]))
        z = values[i-1]*math.sin(math.radians(angles_p[i-1]))
        x = h*math.cos(math.radians(angles_y[i-1]))
        y = h*math.sin(math.radians(angles_y[i-1]))

        print(x,y,z)
        xs.append(float(x))
        ys.append(float(y))
        zs.append(float(z))
        
    # Plot the xs, ys, and zs
    ax.scatter(xs,ys,zs)
    ax.set_xlabel('Width')
    ax.set_ylabel('Depth')
    ax.set_zlabel('Height')
    plt.show()
