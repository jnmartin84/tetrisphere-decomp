#!/usr/bin/env python3
import sys, struct
sys.argv = ["x", "assets/CD3F0.bin"]
exec(open("pending/session23/lwrender2.py").read().split("if __name__")[0])

def u32(d,o): return struct.unpack_from(">I",d,o)[0]
def u16(d,o): return struct.unpack_from(">H",d,o)[0]

dec,ops = decode_asset(0x5921F0, 12)
offMat=u32(dec,4); offB=u32(dec,8); offV=u32(dec,0xC); offP=u32(dec,0x10)
total=u32(dec,0x14); count=u32(dec,0x18)
print("offMat",hex(offMat),"offB",hex(offB),"offV",hex(offV),"offP",hex(offP),"count",count)

# The offB section begins with a u16 offset table. Find its length by assuming
# the first offset points just past the table. Then each entry -> a block.
# Print the first several block headers + batch records.
# offset table: read u16s until value >= (first_offset) i.e. entries increasing then data.
first = u16(dec, offB)
print("first offB u16:", hex(first))
# number of table entries = first/2 (if table is offsets and first entry points past table)
# but let's just print raw table region
ntab = 0
o = offB
table = []
while True:
    v = u16(dec, o)
    table.append(v)
    o += 2
    if len(table)*2 >= table[0]:
        break
print("table entries:", len(table), "first block at rel", hex(table[0]))
print("table:", [hex(x) for x in table])

# decode each block
for bi,rel in enumerate(table):
    base = offB + rel
    numBatch = u16(dec, base)
    nibOff = u16(dec, base+2)
    print(f"\nBLOCK {bi} @rel0x{rel:X} numBatch={numBatch} nibDataOff=0x{nibOff:X}")
    recs=[]
    for j in range(numBatch):
        r = base+4+j*6
        firstVtx=u16(dec,r); b2=dec[r+2]; cnt=dec[r+3]; b4=dec[r+4]; b5=dec[r+5]
        recs.append((firstVtx,b2,cnt,b4,b5))
        print(f"   batch{j}: firstVtx={firstVtx} b2={b2} cnt={cnt} b4={b4} b5={b5}")
    nibstart = base+nibOff
    if bi==len(table)-1:
        nibend = nibstart + 0x60
    else:
        nibend = offB + table[bi+1]
    raw = dec[nibstart:nibend]
    print("   nibbytes:", " ".join(f"{b:02X}" for b in raw[:64]))
    if bi>=3: break
