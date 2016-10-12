#!/bin/bash

# Util for generating .h file from html fils for ESP8266 Device Hive firmware

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

TARGETFILE="$DIR/pages.h"

print() {
  echo "$@" >> $TARGETFILE
}

echo "/* This is autogenerated file. Do not modify directly. */" > $TARGETFILE
print "#ifndef _PAGES_H_"
print "#define _PAGES_H_"
print '#include "../sources/irom.h"'
print "typedef struct {const char *path; const char *data; unsigned int data_len;} WEBPAGE;"

index="WEBPAGE web_pages[] = { "
comma=""
for file in $DIR/*.html; do
    filename=$(basename "$file")
    echo "Generating $filename ..."
    name=${filename/./_}
    data=$(cat "$file" | sed 's/^ *//' | tr -d '\n\r\t' | sed 's/"/\\"/g')
    print "RO_DATA char $name[] = \"$data\";"
    index="$index$comma {\"/$filename\", $name, sizeof($name)}"
    comma=", "
done
print "$index };"
print "#endif /* _PAGES_H_ */"
echo "$(basename $TARGETFILE) successfully generated."
