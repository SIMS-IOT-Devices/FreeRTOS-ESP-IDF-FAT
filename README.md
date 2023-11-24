# FreeRTOS-ESP-IDF-FAT
FAT filesystem usage example

The installation process:
1. Create CSV partitions file in the project outside the main directory
2. In manuconfig update:
	a. Partition Table ---> Partition Table ---> Custom partition table CSV (for partitions.csv)
 	b. Serial flasher config  ---> Flash size (2 MB)  ---> 4MB.
