# https://medium.com/@philipp.h/reduce-clutter-when-using-pyinstaller-in-one-directory-mode-b631b9f7f89b
# thank you for this useful tip!
import sys
from pathlib import Path
sys.path.append(str(Path.cwd()/'lib'))