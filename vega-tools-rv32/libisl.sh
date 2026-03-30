#!/bin/bash

# Check if libisl is installed
if ! ldconfig -p | grep -q libisl; then
  echo "libisl is not installed on this system."
  exit 1
fi

# Get the installed libisl version
ISL_VERSION=$(ldconfig -p | grep libisl | head -n 1 | awk '{print $4}')

if [ -z "$ISL_VERSION" ]; then
  echo "Unable to find the installed libisl version."
  exit 1
fi

# Define the target symbolic link for libisl.so.22
TARGET_DIR="/usr/lib/x86_64-linux-gnu"
LIBISL_TARGET="$TARGET_DIR/libisl.so.22"

# Create symbolic link if not already present
if [ -L "$LIBISL_TARGET" ]; then
  echo "Symbolic link for libisl.so.22 already exists."
else
  echo "Creating symbolic link from $ISL_VERSION to libisl.so.22..."
  sudo ln -sf "$ISL_VERSION" "$LIBISL_TARGET"
  echo "Symbolic link created: $LIBISL_TARGET -> $ISL_VERSION"
fi

# Verify the symbolic link
if [ -L "$LIBISL_TARGET" ]; then
  echo "Symbolic link for libisl.so.22 successfully created."
else
  echo "Failed to create symbolic link."
fi

