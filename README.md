##############################
#       Employee CRUD 	     #
#			                 #
#        By Zhiyi Xu         #
##############################

# This file only includes the instructions of using the app.
# For more information please check the Report.pdf file.

## Steps
#========For Mac=======
1. Unzip the "employeeapp-c++.zip"
2. Open the terminal and enlarge the size of the window
3. cd to the folder employeeapp (/.../employeeapp-c++)
4. Run the command: g++ main.cpp
5. Run the command: ./a.out
6. The program should be running
7. End the program with ctrl+C if something goes wrong

Make sure you install the node js first

## Example

# Adding 2 employees(a developer and a project manager).
===========
no
1
1
Firstname
Lastname
95/06/26
12345
123
12
1
2
Firstname2
Lastname2
95/06/17
2
1234
12
12
12
no

# Editing the second employee 
# (number of employees and client (should not be editable))
======================
2
2
4
0
9 (should see the error info)
no
no

# Delete the first employee
======================
3
asdf (should see the re-enter request)
5 (should see the re-enter request)
1
no

# Print table
======================
4

# Change setup 
# (max length of office number)
======================
5
ghjk (should see the re-enter request)
yes
6
3
1

# Export to a TXT file
======================
6
Libra

# Delete and Create a new table
# (with edited settings)
======================
7
hjk (should see the re-enter request)
yes
4 (should see "The employee table is empty")
5 (should see the edited settings)
no

# Exiting the App
======================
0

# Check the Exported file
======================
cat Libra.txt 
