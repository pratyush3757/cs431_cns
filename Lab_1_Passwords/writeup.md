## 01 sanity
### Challenge Text
1. They like their passwords to be exactly `9` chars.
2. They were seen typing `easy` in the end of the password.
3. It starts with `w`.
4. 4th char is a number.

### Solution
1. Convert to zip to hash.
2. `john --mask w?a?a?d?aeasy sanity.hash`

### Password
`wAs1teasy`

### Flag
`we_will_keep_this_simple`

## 02 lotr
### Challenge Text
1. They like their passwords to not be longer than `15` chars.
2. The password policy made them have at least `08` chars.
3. They were born in 2001, the same year `The Lord of the Rings: The Fellowship of the Ring` came out.
4. The password contain one or more of these words (lowercase): `gandalf`, `ring`, `mordor`

### Solution
1. Convert to zip to hash.
2. Create permutations of the words and dates using `crunch -p <words>`
3. `john --wordlist=lotr.lst lotr.hash`

### Password
`mordorring01`

### Flag
`you_shall_not_pass`

## 03 sherlocked
### Challenge Text
1. They like their passwords to not be longer than `15` chars.
2. The password policy made them have at least `08` chars.
3. They live on 221B Baker Street.
4. They were born on 1976-07-19.

### Solution
1. Create permutations of the words and dates using `crunch -p <words>`

### Password
`221bbaker1976`

### Flag
`elementary_my_dear_watson`

## 04 ryan
### Challenge Text
1. They like their passwords to not be longer than `16` chars.
2. The password policy made them have at least `08` chars.
3. They love Deadpool.
4. They were born on 1976-10-23.

### Solution
1. Create permutations of the words and dates using `crunch -p <words>`

### Password
`dead1023pool`

### Flag
`are_you_there_god_this_is_me`

## 05 bohemian
### Challenge Text
1. They like their passwords to not be longer than `13` chars.
2. The password policy made them have at least `08` chars.
3. They love listening to british rock. Especially Queen's `I want to break free`.
4. They were born on 1975-10-13.

### Solution
1. Create permutations of the words and dates using `crunch -p <words>`

### Password
`breakfree1975`

### Flag
`we_will_rock_you_delilah`

## 06 creed
### Challenge Text
1. They like their passwords to not be longer than `12` chars.
2. The password policy made them have at least `09` chars.
3. It has the word `assassin` at the end.

### Solution

1. Start with 9 chars long mask `?aassassin`.
2. Find password at 12 chars `john --mask=?a?a?a?aassassin creed.hash`

### Password
`1337assassin`

### Flag
`its_russian_stealth_if_theres_no_one_to_see_you`

## 07 didyouputyourname
### Challenge Text
1. They like their passwords to be exactly `9` chars.
2. Their dog's name is Ginger.
3. Their godfather's name is Sirius.

### Solution
1. Permute the words and cut them to be 9 chars long.
2. OR use the words with a mask with `?a` for other chars.

### Password
`siriusgin`

### Flag
`things_are_heating_up_in_potter_fandom`

## 08 carrottoon
### Challenge Text
1. They like their passwords to be exactly `12` chars.
2. They love reading comics.
3. The password ends with `ool`.

### Solution
1. Permute the location of the words, with other chars being all printable ascii (`?a`).
2. `john --mask=comics?a?a?a?aool carrottoon.hash`

### Password
`comicsarecool`

### Flag
`none_of_these_flags_are_about_the_course`
