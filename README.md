FAT filesystem usage example by the usage of the FatFs library in ESP IDF 5.0

The installation process:
1. Create CSV partitions file in the project outside the main directory
2. In manuconfig update: <br>
	a. Partition Table ---> Partition Table ---> Custom partition table CSV (for partitions.csv) <br>
 	b. Serial flasher config  ---> Flash size (2 MB)  ---> 4MB.
