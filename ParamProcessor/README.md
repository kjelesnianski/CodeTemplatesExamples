Assignment:

- Assume you receive a binary file that has a JSON file appended to the end of
  the binary file. This JSON file contains runtime params to run with the
  attached binary

- Task 1: Determine between 3 binary file states
  - Vanilla (No magic number (WXYZ) or attached JSON (BBBBBB))
  - BASE (Has a magic number  appended to the last 4 bytes of file)
  - Variant (Has a magic number and JSON data appended to the file)

Vanilla Format  AAAAAAAAAAAAAAAAAAAA
BASE            AAAAAAAAAAAAAAAAAAAAWXYZ
                  - WXYZ is 4 bytes
Variant         AAAAAAAAAAAAAAAAAAAAWXYZBBBBBBBSIZE
                  - BBBBBBB is variable size
                  - SIZE is 4 bytes specifying BBBBBB length
                  - Still need to confirm the variant has a valid magic number (WXYZ)

- Task 2:
    - Extract the appended JSON data and write to a temp file
    - Print JSON data
    - Run binary with given runtime params
    - Update JSON runtime param data, save JSON file, and append again to
      binary to create a new variant
