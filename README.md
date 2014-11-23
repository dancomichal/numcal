numcal
======

## Installation and Build Prerequisites

You need to install cuba development pacakge (in fedora using mvala/saske repository from corp) one can do
```
yum install cuba-devel
```

To build numcal

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make
```

To install do
```
make install
```
or one can just run it from build directory
```
src/numcal --seed 0 --fun 12
```

