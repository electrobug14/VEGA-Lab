#!/bin/bash
#-------------------------------------------------------------------- 
#Project Name		: MDP - Microprocessor Development Project
#Project Code		: HD083D
#Created		: 07-Jan-2020
#Filename		: setup-cdac-board.sh
#Purpose		: Environment script
#Description		: 
#Author(s)		: Premjith A V
#Email			: premjith@cdac.in
#--------------------------------------------------------------------    
#See LICENSE for license details.


VEGA_SDK=`pwd`

CONFIG_PATH=~/.config/vega-tools
mkdir -p $CONFIG_PATH

set_property(){
filename=$CONFIG_PATH/settings.mk

if ! grep -R "^[#]*\s*${1}=.*" $filename &> /dev/null; then
  #echo "APPENDING because '${1}' not found"
  echo "$1=$2" >> $filename 
else
  #echo "SETTING because '${1}' found already"
  sed -i "s|^[#]*\s*${1}=.*|$1=$2|" $filename
fi
}

get_property()
{
 filename=$CONFIG_PATH/settings.mk
 sed -rn "s/^${1}=([^\n]+)$/\1/p" $filename
}


echo "Setting up VEGA SDK Environment"

set_property "VEGA_SDK" "$VEGA_SDK"
set_property "VEGA_MACHINE" "CDAC"



cd ./bsp && ./clean.sh > /dev/null && autoreconf -f -i  
cd ..
make clean > /dev/null

echo "VEGA SDK Environment added"

vega_tool_flag=$(get_property "VEGA_TOOLS")

if [ -z "$vega_tool_flag" ]
then
      echo "WARNING: Please install vega-tools, and setup environment!"
fi




