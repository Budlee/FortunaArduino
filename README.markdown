THIS IS FORTUNAAAAAA

So basically for a project I implemented FORTUNA the pseudo random number generator by Bruce Schnier and Niels Ferguson.

You have to look in the files for the licence of any libs that I have used but my code is all free to use.

You can get this FORTUNA working on your pc and on your arduino which I like as I like to write code on PC and then transfer it over. Part of the reason I did it on PC was to valgrind it for mem leaks

Its actually not difficult to put into a normal arduino library so if you know roughly what to do i.e. ZIP up the lib, add it to arduino then it is very simple. 

This implementation alows you to save a stash of entropy to eeprom so when you boot FORTUNA is ready to go.

With all the entropy that FORTUNA needs to be collect before it can be used it does take a while. I t took around 3mins on an ARDUINO mega to get going so don't be surprised if it takes a while on other boards.

I have also done testing with NIST and it does appear to be random. I tested by collecting the first 8 bytes of data on boot for a few weeks (this is the more important test (ensures seed is random)) and then also collected the output stream after seeding (as it goes through AES this is fairly obvious that it will be random).

Happy randomness
