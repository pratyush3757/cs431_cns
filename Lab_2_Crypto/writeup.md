## 01 Columns
### Challenge Text
We have a message encrypted using Columnar Transposition: `UOLTICH1EEAOREIITMFSHLEE6NRIRANPSHBRFEFCR`

We only know that the key is 5 chars long.

The flag is the plaintext in all caps.

### Solution
We need to perform a [Columnar Transposition](https://www.dcode.fr/columnar-transposition-cipher) on the given cipher text, with key length 5.
Originally, the plaintext was encrypted with the key `INDIA`. But, we don't know the key but we know the length of the key.    
We can try all possible permutations of the given key length 5 and decrypt the cipher text with each key.    
If we use the [decoding tool](https://www.dcode.fr/columnar-transposition-cipher) with the given cipher text and use all permutations upto key length 6, we see that the best possible plaintext is with permutation (5,3,1,4,2) which gives the flag.  (INDIA: Sorted by character becomes ADIIN)

### Flag
`THENUMBEROFRAILSFORTHERAILFENCECIPHERIS16`

## 02 Rail Force One
### Challenge Text
Someone encrypted this message using Railfence cipher. Can you get the plaintext?

`MHASIDYAKHBEWDEMFXTNURRCPQYTVORSRYAILEIHZTLTGOSREE4EUJATBOFO`

### Solution

We need to perform a [Railfence Decryption](https://www.dcode.fr/rail-fence-cipher) on the given cipher text.    
This problem is dependent on the 01 Columns problem, as the flag gives us the number of rails for the Railfence cipher.   
So, we have the number of rails as 16.   
We can use the [decoding tool](https://www.dcode.fr/rail-fence-cipher) with the given cipher text and the number of rails as 16 to get the flag.

### Flag
`MAYBETRYRAILS4AFTERTHISTCNMEASHIKWFUPVRLZGEUBOOJEOTEYOQRXDHD`

## 03 Rail Force Two
### Challenge Text

Now that you got Rail Force One, you find out that the ciphertext was nested.

What's the decrypted ciphertext in that flag?

Remove the first 23 chars in the flag for Rail Force One and decrypt it again.

### Solution

Based on the previous problem, we know that the flag is nested. We can remove the first 23 characters from the flag and decrypt it again using the Railfence cipher [decoder](https://www.dcode.fr/rail-fence-cipher).   
Removing the first 23 characters from the flag, we get `TCNMEASHIKWFUPVRLZGEUBOOJEOTEYOQRXDHD` as the cipher text, and also first 23 characters give us `MAYBETRYRAILS4AFTERTHIS`. So, our number of rails is 4.

Using the [decoder](https://www.dcode.fr/rail-fence-cipher) with the extracted cipher text and the number of rails as 4, we get the flag.

### Flag
`THEQUICKBROWNFOXJUMPEDOVERTHELAZYDOGS`