import sys
import re
from py_asciimath.translator.translator import ASCIIMath2Tex

def process_file(filepath):
    try:
        # Read the file content
        with open(filepath, 'r') as file:
            content = file.read()

        # Initialize the AsciiMath to LaTeX converter
        asciimath2tex = ASCIIMath2Tex(log=False, inplace=True)

        # Pattern to match $ASCIIMATH STUFF HERE$
        pattern = re.compile(r'`\$(.*?)\$`', re.DOTALL)

        # Function to replace AsciiMath with LaTeX
        def convert_to_latex(match):
            asciimath_string = match.group(1).strip()
            latex_output = asciimath2tex.translate(asciimath_string, from_file=False, pprint=False)
            return latex_output

        # Replace all matches in the content
        updated_content = re.sub(pattern, convert_to_latex, content)

        # Write the updated content back to the file
        with open(filepath, 'w') as file:
            file.write(updated_content)

        print(f"File '{filepath}' processed successfully.")
    except FileNotFoundError:
        print(f"Error: File '{filepath}' not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python a.py filepath.md")
    else:
        process_file(sys.argv[1])
