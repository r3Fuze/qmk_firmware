echo "Compiling..." &&
qmk compile &&

echo "Creating JSON file..." &&
qmk c2json --no-cpp > r3fuze.json &&

echo "Copying file to C:/Users/morten/Documents/qmk" &&
cp ~/qmk_firmware/input_club_whitefox_r3fuze.bin /mnt/c/Users/morten/Documents/qmk &&

echo "Done"
