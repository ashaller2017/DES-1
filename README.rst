###################
 DES in C
###################
C implementation of Data Encryption Standard algorithm.

Overview
========
The Data Encryption Standard (DES) is a block cipher (a form of shared secret encryption) that was selected by the National 
Bureau of Standards as an official Federal Information Processing Standard (FIPS) for the United States in 1976 and which 
has subsequently enjoyed widespread use internationally. It is based on a symmetric-key algorithm that uses a 56-bit key.

This implementation of DES is not optimized in any way. The code has been written to provide readability and easy 
understanding of the algorithm. Padding scheme used in this implementation is `[PKCS5] <ftp://ftp.rsasecurity.com/pub/pkcs/pkcs-5v2/pkcs5v2-0.pdf>`_

Compilation & Installation
==========================
To use, please have a txt file saved as input.txt (it will be either your plaintext or ciphertext). Then you must either have a text file with 8 numbers between 0 and 255 saved as key.txt or generate a key when prompeted. Finally if choosing a mdoe with a IV, you must save a IV.txt or generate one when prompted.

So far I have the ECB, CBC working. I will commit to this fork when I have time to finish the remaining modes. 
====


The primary repository for DES is located at: `http://github.com/tarequeh/DES/ <http://github.com/tarequeh/DES/>`_ The blog post
discussing the implementation can be found at: `CodeXN <http://www.codexn.com>`_
This implementation of DES was written by `Tareque Hossain <mailto:tareque@codexn.com>`_
