# FourSquareCipher
C++ program for encrypting text files using the four-square cipher encryption technique


## Introduction
The four-square cipher is a manual symmetric encryption technique which utilizes four 5×5 matrices of letters arranged in a square. Each of these 5×5 squares contains all of the letters of the alphabet, though leaving out the letter Q to bring it down to fit in 25 characters. The plaintext is split into digraphs (pairs of two letters) and then encrypted by laying a grid over the four squares and identifying the corresponding intersections of the letters. Two of the four squares are constructed using two ordered keywords chosen by the user who is doing the encrypting. These keywords uniquely determine how the text will be encrypted, so it is necessary to know the two words used for encryption in order for the user to decrypt the encrypted message.

See further explanation at https://learncryptography.com/classical-encryption/four-square-cipher.



## Details
Once compiled, the C++ source code is able to encrypt or decrypt a text file with the keywords of the user's choice. The text file to be encrypted/decrypted must be located in the current working directory, otherwise the user must input the complete file path. Once the text file and two keywords are given, the program writes a new text file -- an encryption or decryption of the original text file -- that is named by the user and placed in the working directory. Once the file is written and closed, the program terminates. In order to decrypt an encrypted text file, the user must run the program again, input the name of the encrypted file, and input the same keywords with which the original text was encrypted. The file that is written by the program will then be a readable decryption of the encrypted text file. 
#

**NOTE: Any non-alphabetic text will be ignored when encrypting a text file. Thus, any decryption will only contain the alphabetic characters of the original text that was encrypted. It is the responsibility of the user to be able to decipher the decrypted text void of spacing and sentence structure.**
