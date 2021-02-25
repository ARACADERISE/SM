if [ ! -d /bin/run ]; then
        sudo cp /home/c_master/sm/run /usr/local/bin
        chmod +x /usr/local/bin/run
        echo "Type 'run' to run the program!"
fi
