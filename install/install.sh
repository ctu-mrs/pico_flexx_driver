#!/bin/bash

# get path to script
SCRIPT_PATH="$( cd "$(dirname "$0")" ; pwd -P )"

FILENAME=royale-sdk_3.23.0-86_amd64.deb

# install pmd sdk
echo "Installing PMD SDK ToF camera drivers"
cd $SCRIPT_PATH/install
wget --no-check-certificate -O $FILENAME https://nasmrs.felk.cvut.cz/index.php/s/ZRFNrdw0rMEw5ZY/download
sudo dpkg -i $FILENAME

echo "Done"

