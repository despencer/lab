import jinja2
import argparse
import sys

def main():
    parser = argparse.ArgumentParser(description='Generates greetings file')
    parser.add_argument('srcdir', help='source dir')
    parser.add_argument('dstdir', help='destination dir')
    args = parser.parse_args()

    env = jinja2.Environment(loader=jinja2.FileSystemLoader(args.srcdir))
    with open(args.dstdir + '/main.c', mode='w') as target:
        target.write(env.get_template('main.c.jinja').render(name="World"))
    return 0

if __name__ == "__main__":
    sys.exit(main())