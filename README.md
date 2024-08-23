# Ray C++ Example Program

## Create Virtual Env & Activate

```
python3 -m venv .venv
source .venv/bin/activate
pip install "ray[cpp]"

```

## Build C++ Main Application

```
mkdir build && cd build
cmake ..
make
```

## Run Program
```
./main
```
