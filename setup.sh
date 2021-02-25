if [ ! -d /bin/run ]; then
        HOME_=$(readlink -f "$0")
        HOME_PATH=$(dirname "$HOME_")
        sudo cp $HOME_PATH/run /usr/local/bin
        chmod +x /usr/local/bin/run
        echo "Type 'run' to run the program!"
fi
