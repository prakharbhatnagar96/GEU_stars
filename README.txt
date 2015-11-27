Development Team:- 
			Nipun Kulshrestha	CSE B		5th Sem		Roll no. 39	2007500
			Prakhar Bhatnagar	CSE B		5th Sem		Roll no. 49	2007510


** The project done is Assembler.
** The code should be compiled in Codeblocks.
** INSTRUCTIONS-->

		1. You cannot leave any line without any label. If you do not want to use any label in a line, you have to use "." 
		   as a label.
		2. As we use BYTE with X and C in SIC, we have defined two new mnemonics BYTEX and BYTEC 
		   BYTEX will treat the operand as a hexadecimal.
		   BYTEC will treat the operand as a character.
		3. Instruction Format of our assembler: 
			8 bit opcode|16 bit address
		   We are not using index adressing.
	           BYTEX F1 --> F1
		   BYTEC ABC --> 656667
		4. Program should start with START statement and ends with END statement.
		5. PROGRAM STRUCTURE: 
				label("." for no label) mnemonic OPERAND
			--> We did not use any structure, queue, linked list.Whole assembler code is based on file handling.
		6. The program has an external file "optab.txt" which contains all mnemonics with their codes.
		
	The program contains 4 header files(user defined):-

		1. asse.h - calls the assembler function according to the procedure.
			int mainp() : It calls several functions of assemble.h and objecp.h and returns the 
				      error code to the main program.

		2. assemble.h - contains all the passes of assembling(pass 1,pass 2).
			pass1() : ->it performs several operations on the program file(addrssing symtab,optab checking). 
				  ->gives intermediate.h.

			pass2() : it calculates object code for each instruction and write them into object.txt.

		3. objecp.h - write the header record and call the text record function.
			obj() : write header records and calls text1().
 
		4. res.h - write text records and end records.	
			text1() : write text record and end record.
 
** Thanks To Dr. Devesh Pratap Singh for guiding us through the Project.
** A Special Thanks to Hon. HOD Sir for giving us such an oppurtunity.
