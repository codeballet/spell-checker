# Spell Checker

The Spell Checker program checks the spelling of text files, using a dictionary of your choice.

The dictionary is loaded into a Hash Table, implementing a custom version of [Dan Bernstein's "djb2" algorithm](http://www.cse.yorku.ca/~oz/hash.html).

The program is written in C, as an assignment for the CS50 course at Harvard.

## Compiling

In order to compile the program, you need to have 'make' and 'clang' installed.

To compile an executable file:

```
make speller
```

## Usage

Load a dictionary of your choice and a text file by entering:

```
speller [DICTIONARY] text_file
```

If you do not enter a dictionary of your own choice, the default `./dictionaries/large` will be loaded.

## Expected output

The output will look something like this:

```
MISSPELLED WORDS

[...]

WORDS MISSPELLED:
WORDS IN DICTIONARY:
WORDS IN TEXT:
TIME IN load:
TIME IN check:
TIME IN size:
TIME IN unload:
TIME IN TOTAL:
```

## Licence

MIT
