# Usage:

# . ~$ awk -f transposing_Data_Generic.awk [file]

# where transposing_Data_Generic.awk is this file and [FILE]
# is file name you intend to transpose

BEGIN { FS=OFS="\t" }
{ printf "%s%s", (FNR>1 ? OFS : ""), $ARGIND }
ENDFILE {
    print ""
    if (ARGIND < NF) {
        ARGV[ARGC] = FILENAME
        ARGC++
    }
}

