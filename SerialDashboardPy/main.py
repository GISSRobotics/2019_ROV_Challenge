import serial
import time
import datetime
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# SERIAL
COM = '/dev/cu.usbserial-1450'  # first on the left
BAUD = 9600

ser = serial.Serial(COM, BAUD, timeout=.1)

print('Waiting for device')
time.sleep(3)
print(ser.name)

# MATPLOTLIB
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []


def animate(i, xs, ys):
    string = str(ser.readline().decode().strip('\r\n').strip('~'))  # Capture serial output as a decoded string
    # print(val, end="\n", flush=True)

    vals = string.split('-')

    # check that this is one key-val pair
    if len(vals) == 3:
        key = vals[0]
        val = vals[2]

        if key == "Temperature:":
            print(val)
            xs.append(datetime.datetime.now().strftime('%M:%S'))
            ys.append(round(float(val), 1))

    xs = xs[-20:]
    ys = ys[-20:]

    ax.clear()
    ax.plot(xs, ys)

    # Format plot
    plt.xticks(rotation=45, ha='right')
    plt.subplots_adjust(bottom=0.30)
    plt.title('Temperature')
    plt.ylabel('Temperature (deg C)')
    plt.xlabel('Time (MM:SS)')

ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=500)
plt.show()
