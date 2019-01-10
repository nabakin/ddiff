# ddiff

Windows: `cl /I "libs" main.c`
Linux: `gcc main.c -lm`

## Ideas:
- Processing option to compare via hashes
- Processing option to compare file names only
- Processing option to compare via file names, then perform a regular diff (a)
- Default output option is to print to console all changes for processing option
- Output option to quiet
- Output option to only print file changes for (a)
- Output option to a directory (outputs data in a more digestable format as files) and some formatting options for this?