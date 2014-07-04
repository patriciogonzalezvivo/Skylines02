#!/bin/sh

# Install Server
chmod 755 JourneyServer.sh
sudo cp JourneyServer.sh /etc/init.d
sudo update-rc.d JourneyServer.sh defaults
