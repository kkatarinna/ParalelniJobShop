import argparse
from random import randint

def generate(size, lower, upper):
    xs = []
    for _ in range(size):
        xs.append(randint(lower, upper))

    with open(f'../resources/sort/{size}.txt', 'w') as f:
        for e in xs:
            print(e, file=f)

    with open(f'../resources/sort/{size}_ref.txt', 'w') as f:
        for e in sorted(xs):
            print(e, file=f)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', '--size', type=int, required=True)
    parser.add_argument('-l', '--lower', type=int, required=True)
    parser.add_argument('-u', '--upper', type=int, required=True)
    args = parser.parse_args()
    generate(args.size, args.lower, args.upper)

