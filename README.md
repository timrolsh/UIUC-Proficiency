# UIUC CS Proficiency Exam Notes

Collection of my notes for UIUC CS proficiency exams for classes CS 124, CS 128, CS 173, CS 225, and STAT 107. My foundation before preparing for these exams was knowledge from AP Computer Science A and some minor knowledge of data structures and C++. My notes build on this foundational level of understanding.

## STAT107 Runtime Environment

* The environment and the necessary dependencies used in the STAT107 class are all defined in the [Conda](https://www.anaconda.com/download/success) configuration file [environment.yaml](./STAT107/environment.yml) located in the root of the [STAT107](./STAT107) folder
* To create and activate a virtual environment for this project using conda, run:

```bash
conda env create -f environment.yml;
conda activate stat107;
```

* Tip: for imports and type annotations to work in VSCode, open Code from the terminal running the activated virtual environment (will be indicated by `(stat107)`) using `code .`
