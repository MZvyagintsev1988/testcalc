#/bin/bash


download_extract() {
  aria2c -x 16 $1 -o $2
  tar -xf $2
}

travis_before_install() {
  git submodule update --init --recursive
}

travis_install() {
  if [ "$CXX" = "g++" ]; then
    sudo apt-get install -qq g++-4.8
  elif [ "$CXX" = "clang" ]; then
    sudo apt-get install clang
  fi
  
  if [ "$PVS_ANALYZE" = "Yes" ]; then
    wget -q -O - https://files.viva64.com/etc/pubkey.txt \
      | sudo apt-key add -
    sudo wget -O /etc/apt/sources.list.d/viva64.list \
      https://files.viva64.com/etc/viva64.list
    
    sudo apt-get update -qq
    sudo apt-get install -qq pvs-studio 
  fi
}

travis_script() {
  CMAKE_ARGS="-DHEADLESS=ON ${CMAKE_ARGS}"
  if [ "$PVS_ANALYZE" = "Yes" ]; then
    CMAKE_ARGS="-DCMAKE_EXPORT_COMPILE_COMMANDS=On ${CMAKE_ARGS}"
  fi
  
  cmake $CMAKE_ARGS CMakeLists.txt
  make -j8
  
  if [ "$PVS_ANALYZE" = "Yes" ]; then
    pvs-studio-analyzer credentials $PVS_USERNAME $PVS_KEY
    
    if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
      git diff --name-only HEAD $(git merge-base HEAD $TRAVIS_BRANCH) > .pvs-pr.list
      pvs-studio-analyzer analyze -j8 -o PVS-Studio-${CC}.log --disableLicenseExpirationCheck -S .pvs-pr.list
    else
      pvs-studio-analyzer analyze -j8 -o PVS-Studio-${CC}.log --disableLicenseExpirationCheck
    fi
    
  - plog-converter -t errorfile PVS-Studio-${CC}.log --cerr -w
  fi
}

set -e
set -x

$1;
