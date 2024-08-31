## 01 Is It Bruteforce?
### Challenge Text
We have a document that was encrypted using a random substitution cipher.

Can you find out the plaintext quote at the end of the file?

### Solution
We need to perform a [frequency analysis](https://www.dcode.fr/frequency-analysis) on the given text and match it to the 
[frequencies of the English alphabet](https://en.wikipedia.org/wiki/Letter_frequency).
Upon trying a few substitutions, a part of the ciphertext gets cracked.
We can see that the plaintext is a part of the play [Julius Caesar](http://shakespeare.mit.edu/julius_caesar/full.html).
Knowing that, we can now find out the substitutions and decrypt the unknown parts of the cipher.

### Flag
`didyouthinkofaknownplaintextattack`

## 02 Robert X William
### Challenge Text
Robert and William were talking in secret.
We intercepted their messages, but they were using XOR based symmetric key encryption.

Can you find out the key for us?

We know that the key's format is `cnsctf{<text>}`.

Message 1: `2f07071718035b31070d17154422043d191616443b1f1a1c040c3b4b11181111061d53171c1414060f07553f353a45161b1900072b041a02`

Message 2: `2d01044304141e000d0101050a1145131c0711083a4d37051805264b2c1e1d12110b532a1a150f011d0c01050b18167f131c17441321381f`

### Solution
We know that the key starts with `cnsctf{`, so we XOR it with the messages to get a part of the plaintext.
```python
partial_flag = "cnsctf{"
part_flag_len = len(partial_flag)
partial_flag = bytearray(partial_flag.encode("utf-8"))

C1 = "2f07071718035b31070d17154422043d191616443b1f1a1c040c3b4b11181111061d53171c1414060f07553f353a45161b1900072b041a02"
C2 = "2d01044304141e000d0101050a1145131c0711083a4d37051805264b2c1e1d12110b532a1a150f011d0c01050b18167f131c17441321381f"

C1arr = bytes.fromhex(C1)
C2arr = bytes.fromhex(C2)

P1 = bytearray(a^b for (a,b) in zip(C1arr, partial_flag))
print(P1)
P2 = bytearray(a^b for (a,b) in zip(C2arr, partial_flag))
print(P2)
```
Now, the key is reused, so we can guess the next parts chars of the messages and XOR 
them with the ciphertexts to get the flag chars.
```python
C1arr = P1 + C1arr[part_flag_len:]
C2arr = P2 + C2arr[part_flag_len:]

C2arr[part_flag_len] ^= int.from_bytes(b's')
print(C2arr)
C1arr[part_flag_len] ^= C2arr[part_flag_len]
print(C1arr)
```
Repeat this until we have the whole flag.

### Flag
`cnsctf{shouldve_used_multi_keys}`

## 03 Flipper
### Challenge Text
We forgot our credentials to a portal. Can you help us log in?
nc 10.0.118.104 3000

### Solution
We connect to the server an get a portal.
```
Welcome to our super cool AES-encryption portal!
Oops! We forgot the admin credentials, but we remember the username was like c?s and the password was like c?f.
When we tried 'user:c?s' and 'pass:c?f', the portal gave us these hex strings: 

d5fe39265aad5e0601969f76eab7730327235b200a17ed028cc80503d1ff00a2
d5fe39265aad5e0601969f76eab7730365aacb376cd8408412861a1b6fa74ee6

To unlock the portal, enter the correct hex strings that decrypt to the right credentials. Good luck!
Enter your 8 digit roll no :
```
Now, it looks like the strings given are AES encrypted versions of `user:c?s` and `pass:c?f`.
And the first half of these hex strings is the IV.
We need to change these strings so that they decrypt to right credentials.
`c?s` and `c?f` could be `cns` and `ctf` respectively, so we now just need to know what part to change.

This looks like a [bit flip attack](https://crypto.stackexchange.com/a/66086) on AES encryption.
In AES CBC, the first block is easy to modify by changing the IV, 
and it won't damage the rest of the plaintext. The parts we need to modify are in the first block, at index `6`.

So, we need to flip the byte in the IV at index `6`.

We know that `Plaintext[6] = '?'`.
Therefore, we need to XOR the current plaintext (`?`) and the desired plaintexts 
(`n` and `t`). We then need to XOR this resulting byte with `IV[6]` to get the new IV.

How does this work?
```
## Following operations are for a single target byte in a block
P = '?'     ## Given Plaintext
P' = 'n'    ## Desired Plaintext
P ^ P = 0x00 ## XOR property
0 ^ P = P   ## XOR property

For AES CBC:
P = Decrypt(C) ^ IV   ## ^ is XOR operation

We can say that,
P' = P ^ P ^ P' = 0 ^ P'

Therefore:
P ^ P ^ P' = Decrypt(C) ^ IV ^ P ^ P'
P' = Decrypt(C) ^ IV ^ P ^ P'

Now,
IV' = IV ^ P ^ P'

Replacing IV will IV' will give us P' instead of P
```

### Solution Script
```python
def decode(num):
    hexstring = input("Enter the string: ")
    enc = bytes.fromhex(hexstring)
    ch = enc[6]
    if(num == 1):
        xor= ord('?') ^ ord('n')
    else:
        xor= ord('?') ^ ord('t')
    ch = ch^xor
    ch = int.to_bytes(ch)
    enc = enc[:6] + ch + enc[7:]
    ans = enc.hex()
    print(f"Changed: {ans}")

decode(1)
decode(2)
```
On running it, we get the following output:
```
Enter the string: d5fe39265aad5e0601969f76eab7730327235b200a17ed028cc80503d1ff00a2
Changed: d5fe39265aad0f0601969f76eab7730327235b200a17ed028cc80503d1ff00a2
Enter the string: d5fe39265aad5e0601969f76eab7730365aacb376cd8408412861a1b6fa74ee6
Changed: d5fe39265aad150601969f76eab7730365aacb376cd8408412861a1b6fa74ee6
```

### Example Flag
`cnsctf{23210000_1725098487.6725466_cf4fdacb16e7f3b9742c23ed6b7b79f377ba812e0aaf42e923d142096783f07a}`

## 04 dDes
### Challenge Text
DES is weak, so we made a tool to encrypt our messages twice using DES.
Double encryption is twice as strong right?

Will you be able to crack it?

Some points about the tool:
1. The keys are 6 digit numbers padded with two space chars. Eg. `'012345  '`
2. The encryption function is  
`C = DES_Enc(K2, DES_Enc(K1, P))`. 
3. DES runs in `ECB` mode.
4. All messages will be padded with spaces `' '` to make their length a multiple of `8`.
5. Any message with length already at a multiple of `8`, 
will have a block padded at the end. 
So `8` bytes of `P` will be padded with `8` more bytes instead of `0`.

### Solution
On connecting to the server, we get a flag and an encryption oracle.
```
Enter your 8 digit Roll no : 23210000
This is the DDes encryptor.
We only support hex strings of valid ASCII chars 0x00 - 0x7f
    Eg. `ez` = `657a` or `$7` = `2437`

Here is the flag:
691ccf4e6f28a20917f671a8848228b77cdfddc9c0aa0a4971f17a4f6737fc7b54530c8008440146b307b450d7e70383a020c4c75fc5380ebe98b148faf0aa5bcca4e8b0931baf244ee095c6d5af53084414c237b6b44258549a1c729368d9d76274ea27a2ef1c61
What would you like to encrypt? 3757
3420a65a7eb825d2
What would you like to encrypt?
```

We give it some data and get the corresponding encrypted strings.  
Looking at the challenge text, we get a few things:
- There are 2 keys which are 6 digit random numbers padded with 2 spaces at the end.
- The keys change each time we connect to the server.
- The encryption oracle accepts only hex encoded ascii data.

According to [a StackExchange question](https://security.stackexchange.com/questions/122624/how-does-the-meet-in-the-middle-attack-work-on-double-des), double DES is vulnerable to a `meet in the middle` attack which is a known plaintext attack.  
This attack is performed in 3 steps:
- Encrypt the plaintext with all possible keys.
- Decrypt the ciphertext with all possible keys.
- Find the intersection between the results.

We can perform this quickly due to a small key (6 digits).

### Python code:
```python
#!/usr/bin/python3 -u
from Crypto.Cipher import DES

flag_cipher = bytes.fromhex("691ccf4e6f28a20917f671a8848228b77cdfddc9c0aa0a4971f17a4f6737fc7b54530c8008440146b307b450d7e70383a020c4c75fc5380ebe98b148faf0aa5bcca4e8b0931baf244ee095c6d5af53084414c237b6b44258549a1c729368d9d76274ea27a2ef1c61")
chosen_p = bytes.fromhex("3757").decode()
chosen_c = bytes.fromhex("3420a65a7eb825d2")

def pad(msg: str) -> bytes:
    block_len = 8
    over = len(msg) % block_len
    pad = block_len - over
    return (msg + " " * pad).encode()

def double_decrypt(msg: bytes, key1: bytes, key2: bytes) -> str:    
    cipher2 = DES.new(key2, DES.MODE_ECB)
    enc_msg = cipher2.decrypt(msg)
    cipher1 = DES.new(key1, DES.MODE_ECB)
    return cipher1.decrypt(enc_msg).decode()

def single_encrypt(orig_msg: str) -> dict[bytes, bytes]:
    out: dict[bytes, bytes] = {}
    msg: bytes = pad(orig_msg)
    for k in range(999999):
        key = (f"{k:06}  ").encode()
        cipher = DES.new(key, DES.MODE_ECB)
        ciphertext = cipher.encrypt(msg)
        out[ciphertext] = key
    return out

def single_decrypt(msg: bytes) -> dict[bytes, bytes]:
    out: dict[bytes, bytes] = {}
    for k in range(999999):
        key = (f"{k:06}  ").encode()
        cipher = DES.new(key, DES.MODE_ECB)
        plaintext = cipher.decrypt(msg)
        out[plaintext] = key
    return out

def find_intersection(d1: dict[bytes, bytes], d2: dict[bytes, bytes]) -> tuple[bytes, bytes]:
    set1 = set(d1.keys())
    set2 = set(d2.keys())
    intersection = set1.intersection(set2)
    val = next(iter(intersection))
    return (d1[val], d2[val])

if __name__ == "__main__":
    phase_1 = single_encrypt(chosen_p)
    phase_2 = single_decrypt(chosen_c)
    key1, key2 = find_intersection(phase_1, phase_2)
    print(f"key1: {key1}, key2: {key2}")
    flag = double_decrypt(flag_cipher, key1, key2)
    print(f"flag: {flag}")
```
Running the script for the problem gives us:
```
key1: b'315375  ', key2: b'937173  '
flag: cns_ddes{23210000_1725100141.2284143_181e9b51263488d01039716ea8c2bba138b1ece0bb90a5e580d798f9a763c841}  
```
### Example Flag:
`cns_ddes{23210000_1725100141.2284143_181e9b51263488d01039716ea8c2bba138b1ece0bb90a5e580d798f9a763c841}`
