#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import print_function

import csv
import os


def main():
    with open('cities.csv', 'rb') as f:
        reader = csv.reader(f, delimiter=',', quotechar='|')
        reader.next()

        h = {}
        for row in reader:
            state = row[1]
            city = row[2]

            if state not in h:
                h[state] = []

            h[state].append(city)

        states_path = os.path.join(os.path.dirname(__file__), 'states')

        try:
            os.makedirs(states_path)
        except OSError:
            pass

        for state in h:
            state_file_path = os.path.join(states_path, state)
            with open(state_file_path, 'w') as f:
                for city in h[state]:
                    f.write(city)
                    f.write('\n')


if __name__ == '__main__':
    main()
