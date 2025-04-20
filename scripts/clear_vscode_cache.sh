#!/bin/bash

BOLD_GREY="\033[1;90m"
BOLD_RED="\033[1;31m"
BOLD_REV_WHITE="\033[1;90;107m"
BOLD_REV_RED="\033[1;91m"
RES="\033[0m"
# \033 same as \e or \x1B
# echo -e to print ansi escape codes

CACHE_DIR="$HOME/.var/app/com.visualstudio.code/cache"

# Check if dir exists
if [ ! -d "${CACHE_DIR}" ]; then
  echo -e "${BOLD_REV_RED}Error:${RES} Cache directory not found: ${CACHE_DIR}"
  exit 1
fi

# Ask for confirmation to delete
echo -e "${BOLD_GREY}Delete items in the dir:${RES}"
printf "${BOLD_RED}'%s'? (y/n): ${RES}" "${CACHE_DIR}"
read -n 1 -r confirm # Check one char only
echo

if [[ "$confirm" == "y" || "$confirm" == "Y" ]]; then
  echo
  # Delete dir contents, not dir itself
  rm -rf "${CACHE_DIR}/"*

  # Success or no?
  if [ $? -eq 0 ]; then
    echo -e "${BOLD_REV_WHITE} Deletion done. ${RES}"
  else
    echo -e "${BOLD_REV_RED} Error during deletion. ${RES}"
    exit 1
  fi
else
  echo "Deletion cancelled."
fi

exit 0 