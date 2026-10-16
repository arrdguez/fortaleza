#!/usr/bin/env python3
"""Desempaquetador de ejecutables MS-DOS comprimidos con LZEXE 0.91.

Uso: unlzexe.py ENTRADA.EXE SALIDA.EXE

Reconstruye un MZ válido (imagen descomprimida + tabla de relocaciones) que
puede cargarse en Ghidra/IDA o ejecutarse en DOSBox.
"""
import struct
import sys


class BitReader:
    def __init__(self, data, pos):
        self.d = data
        self.p = pos
        self._reload()

    def _reload(self):
        self.buf = struct.unpack_from('<H', self.d, self.p)[0]
        self.p += 2
        self.cnt = 16

    def bit(self):
        b = self.buf & 1
        self.buf >>= 1
        self.cnt -= 1
        if self.cnt == 0:
            self._reload()
        return b

    def byte(self):
        b = self.d[self.p]
        self.p += 1
        return b

    def word(self):
        w = struct.unpack_from('<H', self.d, self.p)[0]
        self.p += 2
        return w


def decompress(data, start):
    br = BitReader(data, start)
    out = bytearray()
    while True:
        if br.bit():
            out.append(br.byte())
            continue
        if not br.bit():
            length = (br.bit() << 1 | br.bit()) + 2
            span = br.byte() - 0x100
        else:
            lo = br.byte()
            hi = br.byte()
            span = ((hi & 0xF8) << 5 | lo) - 0x2000
            length = hi & 7
            if length:
                length += 2
            else:
                length = br.byte()
                if length == 0:
                    break
                if length == 1:
                    continue  # ajuste de segmento, sin efecto en salida lineal
                length += 1
        for _ in range(length):
            out.append(out[span])
    return bytes(out)


def parse_relocs(data, pos):
    relocs = []
    seg = 0
    off = 0
    while True:
        b = data[pos]
        pos += 1
        if b:
            off += b
        else:
            w = struct.unpack_from('<H', data, pos)[0]
            pos += 2
            if w == 0:
                seg += 0x0FFF
                continue
            if w == 1:
                break
            off += w
        seg += off >> 4
        off &= 0xF
        relocs.append((off, seg))
    return relocs


def unpack(path_in, path_out):
    d = open(path_in, 'rb').read()
    (sig, cblp, cp, crlc, cparhdr, minalloc, maxalloc, ss, sp, csum, ip, cs,
     lfarlc, ovno) = struct.unpack_from('<14H', d, 0)
    hdr = cparhdr * 16
    lz = hdr + cs * 16  # cabecera LZEXE en CS:0000
    o_ip, o_cs, o_sp, o_ss, cmp_paras, inc_paras, unp_size, chk = \
        struct.unpack_from('<8H', d, lz)
    code = d[lz + 0x0E: lz + 0x0E + 8]
    if b'*FAB*' not in d[lz:lz + 0x200]:
        print('aviso: firma *FAB* no encontrada, puede no ser LZEXE 0.91')
    image = decompress(d, hdr)
    relocs = parse_relocs(d, lz + 0x158)

    # Construir nuevo MZ
    reloc_bytes = b''.join(struct.pack('<HH', o, s) for o, s in relocs)
    hdr_size = 0x1C + len(reloc_bytes)
    hdr_paras = (hdr_size + 15) // 16
    hdr_size = hdr_paras * 16
    total = hdr_size + len(image)
    new_cp = (total + 511) // 512
    new_cblp = total % 512
    # memoria extra: lo que pedía el packer menos el crecimiento de imagen
    orig_load = (cp * 512 - (512 - cblp if cblp else 0)) - hdr
    extra = minalloc + (orig_load - len(image)) // 16 + inc_paras
    new_min = max(0, min(0xFFFF, extra))
    header = struct.pack('<14H', 0x5A4D, new_cblp, new_cp, len(relocs),
                         hdr_paras, new_min, 0xFFFF, o_ss, o_sp, 0, o_ip,
                         o_cs, 0x1C, 0)
    header += reloc_bytes
    header = header.ljust(hdr_size, b'\0')
    open(path_out, 'wb').write(header + image)
    print(f'{path_in}: imagen {len(image)} bytes, {len(relocs)} relocs, '
          f'entrada {o_cs:04X}:{o_ip:04X}, pila {o_ss:04X}:{o_sp:04X}')


if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    unpack(sys.argv[1], sys.argv[2])
