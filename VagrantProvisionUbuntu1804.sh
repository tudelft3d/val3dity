#!/usr/bin/env bash

# Set environment variables
BUILDS="/opt"
HOME="/home/vagrant"
echo HOME: $HOME

apt-get update >/dev/null 2>&1

# CMake, C/++ compiler ---------------------------------------------------------
echo "Installing C/++ compiler and CMake..."
apt-get install -y cmake gcc g++ >/dev/null 2>&1

# pip --------------------------------------------------------------------------
echo "Installing pip..."
apt-get install -y python3-pip >/dev/null 2>&1

# CGAL requirements ------------------------------------------------------------
echo "Installing Eigen3, Boost, GMP, MPFR..."
# get Boost
apt-get install -y libboost-all-dev >/dev/null 2>&1
# get Eigen3
apt-get install -y libeigen3-dev >/dev/null 2>&1
# get GMP and MPFR
apt-get install -y libgmp10 libgmp-dev libmpfr-dev libmpfr6 >/dev/null 2>&1

apt-get update >/dev/null 2>&1
apt-get upgrade -y >/dev/null 2>&1

# GEOS -------------------------------------------------------------------------
echo "Downloading and building GEOS 3.7.2 ..."
cd $BUILDS
wget https://git.osgeo.org/gitea/geos/geos/archive/3.7.2.tar.gz >/dev/null 2>&1
tar xf 3.7.2.tar.gz
rm 3.7.2.tar.gz
mkdir $BUILDS/geos/build && cd $BUILDS/geos/build
cmake ..
make
geos_test=$(make check | grep -o '100% tests passed')
if [ "$geos_test" = "100% tests passed" ]; then
    make install
    ldconfig
    make clean
else
    echo "GEOS test failed, exiting provisioning"
    exit 1
fi


# CGAL -------------------------------------------------------------------------
# For some reason CGAL cannot link Eigen3 to boost_thread when the release tarball
# is used for compilation. However, everything works when CGAL is compiled from
# the source tarball (copy of GitHub master branch).
CGAL_VERSION=4.13.1
echo "Downloading and building CGAL "$CGAL_VERSION
cd $BUILDS
wget https://github.com/CGAL/cgal/archive/releases/CGAL-$CGAL_VERSION.tar.gz >/dev/null 2>&1

tar -xf CGAL-$CGAL_VERSION.tar.gz
rm CGAL-$CGAL_VERSION.tar.gz

mkdir $BUILDS/cgal-releases-CGAL-$CGAL_VERSION/build && cd $BUILDS/cgal-releases-CGAL-$CGAL_VERSION/build
cmake .. -DWITH_Eigen3=ON -DCMAKE_BUILD_TYPE="Release"
make
make install
make clean
ldconfig


# pytest -----------------------------------------------------------------------
echo "Installing python packages"
pip3 install pytest
pip3 install --upgrade pyyaml

# val3dity ---------------------------------------------------------------------
echo "Building val3dity..."
# Vagrant shared folders incur a heavy performance penalty within the
# virtual machine when there is heavy I/O, so they should only be used for
# source files. Any compilation step, database files, and so on should be done
# outside the shared folder filesystem inside the guest filesystem itself.
mkdir $HOME/val3dity_build && cd $HOME/val3dity_build
cmake $HOME/val3dity
make
make install
cd $HOME

val3dity --version

chown vagrant:vagrant $HOME/val3dity_build

echo "See VAGRANT.md for additional configuration instructions and then run 'vagrant ssh' to log into the val3dity virtual machine."
