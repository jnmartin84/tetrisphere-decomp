#!/usr/bin/env python3
import sys, struct, math
sys.argv = ["x", "assets/CD3F0.bin"]
exec(open("pending/session23/lwrender2.py").read().split("if __name__")[0])

def u32(d,o): return struct.unpack_from(">I",d,o)[0]
def u16(d,o): return struct.unpack_from(">H",d,o)[0]
def s16(d,o): return struct.unpack_from(">h",d,o)[0]

def extract_positions(d):
    offV=u32(d,0xC); offP=u32(d,0x10); n=(offP-offV)//16
    P=[]
    for i in range(n):
        o=offV+i*16
        P.append([s16(d,o),s16(d,o+2),s16(d,o+4)])
    return P

def extract_faces(d):
    assert u32(d,0)==0x18
    offB=u32(d,8); offV=u32(d,0xC); offP=u32(d,0x10)
    nverts=(offP-offV)//16
    first=u16(d,offB); ntab=first//2
    table=[u16(d,offB+2*i) for i in range(ntab)]
    faces=[]
    batchsum=0
    for rel in table:
        base=offB+rel
        numBatch=u16(d,base); nibOff=u16(d,base+2)
        recs=[]
        for j in range(numBatch):
            r=base+4+j*6
            firstVtx=u16(d,r); vtxCount=d[r+3]; triCount=d[r+4]
            recs.append((firstVtx,vtxCount,triCount))
        cur=[base+nibOff]; half=[0]
        def nextnib():
            b=d[cur[0]]
            if half[0]==0:
                half[0]=1; return (b>>4)&0xF
            else:
                half[0]=0; v=b&0xF; cur[0]+=1; return v
        for (firstVtx,vtxCount,triCount) in recs:
            for t in range(triCount):
                a=firstVtx+nextnib(); b=firstVtx+nextnib(); c=firstVtx+nextnib()
                faces.append([a,b,c])
            batchsum=firstVtx+vtxCount
    return faces, table, batchsum

for idx in (12,19,84):
    d,ops=decode_asset(0x5921F0, idx)
    P=extract_positions(d)
    F,table,batchsum=extract_faces(d)
    nverts=len(P)
    mx=max(F,key=lambda t:max(t))[0] if F else 0
    allmax=max(max(t) for t in F)
    allmin=min(min(t) for t in F)
    oor=[t for t in F if max(t)>=nverts or min(t)<0]
    degen=[t for t in F if t[0]==t[1] or t[1]==t[2] or t[0]==t[2]]
    # edge-length sanity
    xs=[p[0] for p in P]; ys=[p[1] for p in P]; zs=[p[2] for p in P]
    diag=math.sqrt((max(xs)-min(xs))**2+(max(ys)-min(ys))**2+(max(zs)-min(zs))**2)
    def elen(i,j):
        return math.sqrt(sum((P[i][k]-P[j][k])**2 for k in range(3)))
    import random
    samp=F if len(F)<2000 else random.sample(F,2000)
    edges=[]
    for t in samp:
        edges+= [elen(t[0],t[1]),elen(t[1],t[2]),elen(t[0],t[2])]
    avgedge=sum(edges)/len(edges)
    print(f"\n=== asset {idx}  ops={ops} ===")
    print(f"  verts={nverts}  blocks={len(table)}  triangles={len(F)}  (tri/vert={len(F)/nverts:.2f})")
    print(f"  index range [{allmin}..{allmax}]  nverts={nverts}  in-range={'PASS' if not oor else 'FAIL('+str(len(oor))+')'}")
    print(f"  degenerate tris={len(degen)}")
    print(f"  batchsum(final firstVtx+vtxCount)={batchsum} vs nverts={nverts}  match={'YES' if batchsum==nverts else 'NO'}")
    print(f"  bbox diag={diag:.0f}  avg triangle edge={avgedge:.1f}  (edge/diag={avgedge/diag:.3f})")
    print(f"  sample tris: {F[:6]}")
