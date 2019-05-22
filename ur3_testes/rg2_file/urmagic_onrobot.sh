#!/bin/bash

if [ -z $DISPLAY ]; then
  export DISPLAY=:0
fi

#file copy with detect
MOUNTPOINT="$1"

cd "$MOUNTPOINT"



backup_file()
{
        filename=$(basename $1)
        dir=$(dirname $1)
        extension="${filename##*.}"
        filenametrunc="${filename%.*}"
        echo $filename
        echo $dir
        echo $extension
        echo $filenametrunc

        if [ ${extension:0:3} = "old" ];then
                index=${extension:3:1}
                if [ $index -lt 9 ]; then
                        newfilename=$dir/$filenametrunc".old"$[$index+1]
                        if [ -f $newfilename ]; then 
                                backup_file $newfilename
                                echo "recursive backup: "$newfilename
                        fi
                        cp -f $1 $newfilename
                fi
        fi

        if [ ${extension:0:3} = "bak" ];then
                index=${extension:3:1}
                if [ $index -lt 9 ]; then
                        newfilename=$dir/$filenametrunc".bak"$[$index+1]
                        if [ -f $newfilename ]; then 
                                backup_file $newfilename
                                echo "recursive backup: "$newfilename
                        fi
                        cp -f $1 $newfilename
                fi
        fi

        if [ ${extension} = "urp" ];then
                        newfilename=$dir/$filenametrunc".old0"
                        if [ -f $newfilename ]; then 
                                backup_file $newfilename
                        fi
                        cp -f $1 $newfilename
        fi

       if [ ${extension} = "script" ];then
                        newfilename=$dir/$filenametrunc".bak0"   
                        if [ -f $newfilename ]; then 
                                backup_file $newfilename
                        fi
                        cp -f $1 $newfilename
        fi
}

. /etc/profile


ver_str=$(URControl -v | awk '{print $2}')
major_ver=$(echo $ver_str | tr "." " " | awk '{print $1}')
minor_ver=$(echo $ver_str | tr "." " " | awk '{print $2}')
int_ver=$(($major_ver*100+$minor_ver))


cd "$MOUNTPOINT"
if [ $int_ver -lt 108 ] ; then
    FILES2COPY=("$MOUNTPOINT/ON/RETRO/*")
    DESTINATION="/programs/"    
    cd "$MOUNTPOINT"

    for file in ${FILES2COPY[*]} 
    do
        if [ ! -f $DESTINATION/$(basename "$file") ] ; then
            cp "${file}" "$DESTINATION/."
        else
            if ! cmp  ${file} $DESTINATION/$(basename "$file") ; then
                backup_file $DESTINATION/$(basename "$file")
            fi

            cp -f "${file}" "$DESTINATION/."
        fi
        FILESCOPIED=$(( FILESCOPIED + 1 ))
    done    
    DISPLAY=:0 java onrobot
elif [ $int_ver -lt 303 ] ; then
    FILES2COPY=("$MOUNTPOINT/ON/CLASSIC/*")
    DESTINATION="/programs/"
    cd "$MOUNTPOINT"

    for file in ${FILES2COPY[*]} 
    do
        if [ ! -f $DESTINATION/$(basename "$file") ] ; then
            cp "${file}" "$DESTINATION/."
        else
            if ! cmp  ${file} $DESTINATION/$(basename "$file") ; then
                backup_file $DESTINATION/$(basename "$file")
            fi

            cp -f "${file}" "$DESTINATION/."
        fi
        FILESCOPIED=$(( FILESCOPIED + 1 ))
    done    
    DISPLAY=:0 java onrobot
else
    file=("$MOUNTPOINT/ON/CAP/OnRobot.jar")
    DESTINATION="/root/.urcaps/"
    if [ -f $DESTINATION/$(basename "$file") ]; then
        rm $DESTINATION/$(basename "$file")
    fi  
    if [ ! -d "/home/onrobot/" ]; then
        mkdir "/home/onrobot/"
    fi
    cp -f "onrobot.gripper.properties" "/home/onrobot/onrobot.gripper.properties" 
    if [ -f $DESTINATION/com.ur.urcap.$(basename "$file") ]; then
        if [ "$(cmp $file $DESTINATION/com.ur.urcap.$(basename "$file"))" ]; then
            cp -f "${file}" "$DESTINATION/com.ur.urcap.$(basename "$file")"
            DISPLAY=:0 java onrobot
            pkill java
        else
            DISPLAY=:0 java onrobot
        fi
    else
            cp -f "${file}" "$DESTINATION/com.ur.urcap.$(basename "$file")"
            DISPLAY=:0 java onrobot
            pkill java
    fi
fi
