EDMA CSL EXAMPLE 
====================
The folders in this directory contain a example that demonstrates the usage of EDMA CSL 3.x API's.

Directory structure:
---------------------

src - contains the example source files
inc - contains the example include files
build  - contains the example project and the linker command file 

To Run the Example in the little endian mode:
-------------------------------------------

1. Choose the Little endian configuration in the CCS setup

2. Open the Edma_interrupt.pjt in the CCS 

3. Ensure that the gel file is loaded

4. In the project build options configure the endianness to little endian

5. Include the libraries rts64plus.lib and the little endian csl library
Note: By default, the project is configured in little endian mode, so the above step may not be required

6. Build the project.

7. Load the OUTPUT file.

8. Execute.


To Run the Example in the big endian mode:
-------------------------------------------

1. Choose the Big endian configuration in the CCS setup

2. Open the Edma_interrupt.pjt in the CCS 

3. Ensure that the gel file is loaded

4. In the project build options configure the endianness to big endian

5. Include the libraries rts64pluse.lib and the big endian csl library

6. Build the project.

7. Load the OUTPUT file.

8. Execute. 
