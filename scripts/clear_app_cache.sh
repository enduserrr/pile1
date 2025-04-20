#!/bin/bash

WB="\033[1;97m"
GC="\033[3;90m"
YE="\033[0;93m"
BOLD_RED="\033[1;31m"
BOLD_REV_RED="\033[1;91m"
RES="\033[0m"

BASE_DIR="$HOME/.var/app"

if [ "$#" -ne 1 ]; then
  echo -e "${BOLD_REV_RED}Usage:${RES} $0 <application_id>" >&2 # Print errors to stderr
  echo -e "Example: $0 com.visualstudio.code" >&2
  exit 1
fi

APP_ID="$1"
CACHE_DIR="${BASE_DIR}/${APP_ID}/cache"

if [ ! -d "${BASE_DIR}/${APP_ID}" ]; then # Check for base app dir
  echo -e "${BOLD_REV_RED}Error:${RES} Application directory not found for '${APP_ID}': ${BASE_DIR}/${APP_ID}" >&2
  exit 1
fi

if [ ! -d "${CACHE_DIR}" ]; then # Check for cache dir
  echo -e "${BOLD_REV_RED}Error:${RES} Cache directory not found for '${APP_ID}': ${CACHE_DIR}" >&2
  exit 1
fi

echo -e "${BOLD_RED}DELETE APP CACHE FOR:${RES}"
echo -e "App:${GC} ${APP_ID} ${RES}"
echo -e "Dir:${GC} ${CACHE_DIR} ${RES}"
printf "${WB}Confirm delete: (y/n): ${RES}"
read -n 1 -r confirm # Read one char, no need to press enter
echo

if [[ "$confirm" == "y" || "$confirm" == "Y" ]]; then
  rm -rf "${CACHE_DIR}/"*

  if [ $? -eq 0 ]; then # Deletion status
    # Check if the dir is empty ('.' or '..' might remain)
    if [ -z "$(ls -A "${CACHE_DIR}")" ]; then
        echo -e "${GC}Cache cleared successfully for ${APP_ID}${RES}"
    else
        echo -e "${YE} Warning: ${RES} Deletion finished, directory not empty. (check permissions)" >&2
    fi
  else
    echo -e "${BOLD_RED} Error:${RES} Deletion failed for '${APP_ID}' in ${CACHE_DIR}. Check permissions." >&2
    exit 1
  fi
else
  echo -e "Deletion cancelled for ${APP_ID}"
fi

exit 0