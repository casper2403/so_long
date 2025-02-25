#!/bin/bash

# File: run_tests.sh
# Usage: chmod +x run_tests.sh && ./run_tests.sh

# Initialize log file
> test.log

# Color codes
RED='\e[91m'
GREEN='\e[92m'
YELLOW='\e[93m'
BLUE='\e[94m'
MAGENTA='\e[95m'
CYAN='\e[96m'
WHITE='\e[97m'
RESET='\e[0m'
BOLD='\e[1m'

# Visual elements
SEPARATOR="${BLUE}================================================================${RESET}"
TEST_HEADER="${CYAN}▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲▲${RESET}"
VALGRIND_HEADER="${MAGENTA}◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆${RESET}"
MAP_SEPARATOR="${GREEN}────────────────────────────────────────────────────────────────${RESET}"

# Configuration
MAP_DIR="maps"

header() {
    echo -e "\n${SEPARATOR}"
    echo -e "${BOLD}${BLUE}$(printf "%*s" $(( (${#1} + 60) / 2 )) "$1")${RESET}"
    echo -e "${SEPARATOR}\n"
}

# Rebuild project
header "REBUILDING PROJECT"
make re

# Regular tests
header "RUNNING REGULAR TESTS"

for map in "${MAP_DIR}"/*.ber; do
    echo -e "\n${TEST_HEADER}"
    echo -e "${BOLD}${YELLOW} Testing map: ${CYAN}${map} ${RESET}"
    echo -e "${MAP_SEPARATOR}"
    ./so_long "${map}"
    echo -e "${MAP_SEPARATOR}"
    echo -e "${TEST_HEADER}\n"
    sleep 0.3
done

# Valgrind tests
header "RUNNING VALGRIND TESTS"

for map in "${MAP_DIR}"/*.ber; do
    echo -e "\n${VALGRIND_HEADER}"
    echo -e "${BOLD}${MAGENTA} Memory check for: ${CYAN}${map} ${RESET}"
    echo -e "${MAP_SEPARATOR}"
    
    # Create temporary file for Valgrind output
    TEMP_FILE=$(mktemp)
    
    # Run Valgrind and capture output
    valgrind --leak-check=full --show-leak-kinds=all \
             --track-origins=yes --verbose \
             --log-fd=1 ./so_long "${map}" > "${TEMP_FILE}" 2>&1
    
    # Show Valgrind output in terminal
    cat "${TEMP_FILE}"
    
    # Save leak summary to log file
    echo -e "\n=== Valgrind leak summary for ${map} ===" >> test.log
    grep -A5 "LEAK SUMMARY:" "${TEMP_FILE}" >> test.log
    echo "==========================================" >> test.log
    
    # Cleanup temporary file
    rm "${TEMP_FILE}"
    
    echo -e "${MAP_SEPARATOR}"
    echo -e "${VALGRIND_HEADER}\n"
    sleep 0.3
done

echo -e "${BOLD}${GREEN}✔ All tests completed ${RESET}\n"
echo -e "${BOLD}${CYAN}Valgrind leak summaries saved to test.log${RESET}"
