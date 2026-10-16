#!/usr/bin/env python3
"""Extrae cadenas Turbo Pascal (byte de longitud + texto CP437) de una imagen DOS.

Uso: tpstrings.py FICHERO.EXE [min_len] > salida.txt
Formato de salida: OFFSET_HEX<TAB>LONGITUD<TAB>texto (\\n escapado)
"""
import struct
import sys

OK = set(range(0x20, 0x7F)) | {0x0D, 0x0A} | set(range(0x80, 0xA8)) | {0xAD, 0xA8}


def load_image(path):
    d = open(path, 'rb').read()
    if d[:2] == b'MZ':
        hdr = struct.unpack_from('<H', d, 8)[0] * 16
        return d[hdr:], hdr
    return d, 0


def scan(img, min_len=3):
    i = 0
    n = len(img)
    while i < n:
        L = img[i]
        if L >= min_len and i + 1 + L <= n:
            s = img[i + 1:i + 1 + L]
            if all(c in OK for c in s) and sum(c >= 0x41 for c in s) * 2 >= L:
                yield i, s
                i += 1 + L
                continue
        i += 1


def main():
    path = sys.argv[1]
    min_len = int(sys.argv[2]) if len(sys.argv) > 2 else 3
    img, _ = load_image(path)
    for off, s in scan(img, min_len):
        txt = s.decode('cp437').replace('\r', '').replace('\n', '\\n')
        print(f'{off:06X}\t{len(s)}\t{txt}')


if __name__ == '__main__':
    main()
