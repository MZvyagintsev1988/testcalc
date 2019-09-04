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
    sudo apt-get update -qq
    sudo apt-get install -qq strace sendemail libio-socket-ssl-perl libnet-ssleay-perl
    
    wget -q http://files.viva64.com/beta/pvs-studio-7.04.34029.84-amd64.deb
    sudo dpkg --install pvs-studio-7.04.34029.84-amd64.deb
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
    pvs-studio-analyzer credentials $PVS_USERNAME $PVS_KEY -o PVS-Studio.lic
    
    if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
      git diff --name-only HEAD $(git merge-base HEAD $TRAVIS_BRANCH) > .pvs-pr.list
      pvs-studio-analyzer analyze -j8 -l PVS-Studio.lic -S .pvs-pr.list -o PVS-Studio-${CC}.log --disableLicenseExpirationCheck
    else
      pvs-studio-analyzer analyze -j8 -l PVS-Studio.lic -o PVS-Studio-${CC}.log --disableLicenseExpirationCheck
    fi
    
    plog-converter -t html PVS-Studio-${CC}.log -o PVS-Studio-${CC}.html -w
  fi
}

travis_after_failure() {
  sendemail -t zvyagintsev@viva64.com \
              -u "PVS-Studio $CC report, commit:$TRAVIS_COMMIT" \
              -m "PVS-Studio $CC report, commit:$TRAVIS_COMMIT" \
              -s smtp.gmail.com:587 \
              -xu $MAIL_USER \
              -xp $MAIL_PASSWORD \
              -o tls=yes \
              -f $MAIL_USER \
              -a PVS-Studio-${CC}.log PVS-Studio-${CC}.html
}

set -e
set -x

$1;
