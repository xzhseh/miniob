#!/bin/bash

# Helper functions

install_mac() {
  # Install Homebrew.
  if test ! $(which brew); then
    echo "Installing Homebrew (https://brew.sh/)"
    ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
  fi
  # Install packages if not yet.
  brew ls --versions clang-format || brew install clang-format
}

install_linux() {
  # Install packages.
  sudo apt-get -y install clang-format-14
}

echo "----------------------------------------------------------"
echo "# Run \`chmod +x run_clang_format.sh\` if permission denied."
echo "# Currently only format the code under \`./src\` directory."
echo "----------------------------------------------------------"

echo "Check if \`clang-format\` has been installed."

UNAME=$(uname | tr "[:lower:]" "[:upper:]" )

case $UNAME in
DARWIN)
    install_mac ;;
LINUX)
    version=$(cat /etc/os-release | grep VERSION_ID | cut -d '"' -f 2)
    case $version in
        18.04) install_linux ;;
        20.04) install_linux ;;
        22.04) install_linux ;;
        *) ;;
    esac
    ;;

*) ;;
esac

echo "----------------------------------------------------------"
echo "Begin formatting the code."

# Run `chmod +x run_clang_format.sh` if permission denied
# Currently only format the code under ./src directory
case $UNAME in
DARWIN)
    echo "Running \`clang-format\` for MacOS."
    find ./src -name "*.cpp" -o -name "*.h" | xargs clang-format -i ;;
LINUX)
    echo "Running \`clang-format-14\` for Linux."
    find ./src -name "*.cpp" -o -name "*.h" | xargs clang-format-14 -i ;;
*) ;;
esac

# Check the return value
if (( $? == 0 )); then
    echo "Successfully formatting all the code files in \`src\` directory."
else
    echo "\`clang-format\` failed to run, please check if the installation is successful or not!"
fi

echo "----------------------------------------------------------"

cd src/observer/sql/parser && ./gen_parser.sh

if (( $? == 0 )); then
    echo "Finish generating the yacc / lex files."
else
    echo "Error when running \`gen_parser.sh\`, please check your yacc / lex files"
fi

echo "----------------------------------------------------------"
