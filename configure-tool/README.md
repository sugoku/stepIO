# stepIO Configuration Tool

To build:

- You must be on Python 3.6 to build (maybe 3.5)
- `py -3.6 -m venv stepIOenv` or `python3 -m venv stepIOenv`
- `call stepIOenv\scripts\activate` or `source stepIOenv/bin/activate`
- `pip3 install fbs PyQt5 pyserial`
- `fbs freeze`
- Go to `target/stepIO Configuration Tool` and there it is!
  - To get rid of some of the clutter, you can move most of the files in the root folder into the `lib` folder, except for dlls starting with `python` or `Qt5`, as well as `Icon.ico` and `base_library.zip`

Copyright © 2020 sugoku