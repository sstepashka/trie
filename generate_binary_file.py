#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import struct


def tokenize(string):
    return list(map(str.strip, string.split()))


def main():
    features = list(filter(lambda name: not name.startswith('.'), os.listdir('./states')))
    features = map(str.lower, features)

    features_count = len(features)

    output = open('./trie/output.bin', 'wb')
    output.write(struct.pack('L', features_count))

    for feature in features:
        print(feature)
        with open(os.path.join('./states', feature)) as f:
            lines = map(str.lower, map(str.strip, f.readlines()))

        key = bytearray(feature if isinstance(feature, unicode) else unicode(feature, 'utf-8'), 'utf-8')
        key_len = len(key)

        output.write(struct.pack('L', key_len))
        output.write(key)

        samples_count = len(lines)
        output.write(struct.pack('L', samples_count))

        for line in lines:
            tokens = tokenize(line)

            tokens_count = len(tokens)

            output.write(struct.pack('L', tokens_count))

            for token in tokens:
                token_bytes = bytearray(token if isinstance(token, unicode) else unicode(token, 'utf-8'), 'utf-8')

                token_len = len(token_bytes)
                output.write(struct.pack('L', token_len))

                output.write(token_bytes)

    output.close()


if __name__ == '__main__':
    main()
