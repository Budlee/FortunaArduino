THIS IS FORTUNAAAAAA

So basically for a project I implemented FORTUNA the pseudo random number generator by Bruce Schnier and Niels Ferguson. I have made it and it works but I have no time to sort it out.

You have to look in the files for the licence of any libs that I have used

Basically you can get this working on your pc and on your arduino which I like as I like to write code on PC and then transfer it over. The reason I did it on PC was to valgrind it for mem leaks


Its actually not difficult to sort and if you know roughly what to do i.e. ZIP up the lib, add it to arduino and then off you go. 

Oh yer you can also save a stash of entropy if you want to eeprom so when you boot it is ready to go.

With all the entropy that needsmto be collected it takes about 3mins on an ARDUINO mega to get going so don't be surprised if it takes a while.

I have also done testing with NIST and it does appear to be random. I tested by getting the first 8 bytes of data on boot (the more important test (ensures seed is random)) and also ensured that the stream out is random (as it goes through AES this is fairly obvious)

Happy randomness
