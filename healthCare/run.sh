#!/bin/bash

# Create the 'data' directory if it doesn't exist
echo "Creating 'data' directory if it doesn't exist..."
mkdir -p ./data

# Check if the required JSON files exist, if not, create empty files
JSON_FILES=("doctors.json" "patients.json" "appointments.json" "departments.json")

for file in "${JSON_FILES[@]}"
do
    if [ ! -f "./data/$file" ]; then
        echo "Creating empty $file..."
        touch "./data/$file"
    else
        echo "$file already exists."
    fi
done

# Run the healthcare system binary
echo "Running healthcare_system binary..."
./build/bin/healthcare_system

