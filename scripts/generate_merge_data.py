import argparse
from random import randint

def generate(size, lower, upper):
    left = []
    right = []
    for _ in range(size//2):
        left.append(randint(lower, upper))
        right.append(randint(lower, upper))

    with open(f'../resources/merge/{size}.txt', 'w') as f:
        for e in sorted(left):
            print(e, file=f)

        for e in sorted(right):
            print(e, file=f)

    with open(f'../resources/merge/{size}_ref.txt', 'w') as f:
        for e in sorted(left + right):
            print(e, file=f)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', '--size', type=int, required=True)
    parser.add_argument('-l', '--lower', type=int, required=True)
    parser.add_argument('-u', '--upper', type=int, required=True)
    args = parser.parse_args()
    generate(args.size, args.lower, args.upper)

