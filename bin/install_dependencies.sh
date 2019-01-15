ARD_VER="1.8.7"
echo "Downloading version $ARD_VER of the Arduino IDE..."
wget http://downloads.arduino.cc/arduino-$ARD_VER-linux64.tar.xz
tar xf arduino-$ARD_VER-linux64.tar.xz
git clone https://github.com/jrowberg/i2cdevlib.git
sudo mv i2cdevlib/Arduino/* arduino-$ARD_VER/libraries
sudo mv arduino-$ARD_VER /usr/local/share/arduino
sudo ln -s /usr/local/share/arduino/arduino /usr/local/bin/arduino
arduino --install-library "Adafruit SleepyDog Library,Adafruit MQTT Library"