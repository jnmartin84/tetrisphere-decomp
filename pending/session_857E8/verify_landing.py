from pathlib import Path
import struct, subprocess, hashlib, json, sys
root=Path.cwd()
assert root in (Path.home()/'wt/codex_857e8',Path.home()/'claude_tetrisphere')
out=Path(sys.argv[1]);out.mkdir(parents=True,exist_ok=True)
ref=Path('tetrisphere.z64').read_bytes()
rom=Path('build/tetrisphere.us.z64').read_bytes()
elf=Path('build/tetrisphere.us.elf').read_bytes()
assert len(ref)==len(rom)==8388608 and rom==ref
assert elf[:6]==b'\x7fELF\x01\x02'
phoff=struct.unpack_from('>I',elf,28)[0]
phentsize,phnum=struct.unpack_from('>HH',elf,42)
target=None
for i in range(phnum):
    typ,off,va,pa,fs,ms,fl,al=struct.unpack_from('>8I',elf,phoff+i*phentsize)
    if typ==1 and va<=0x800857E8 and 0x80088914<=va+fs:
        target=elf[off+0x800857E8-va:off+0x80088914-va]
assert target is not None and len(target)==12588
assert target==ref[0x60B98:0x63CC4]
spliced=ref[:0x60B98]+target+ref[0x63CC4:]
assert spliced==rom
nm=subprocess.check_output(['mips-linux-gnu-nm','-n','build/tetrisphere.us.elf'],text=True)
symbols={line.split()[-1]:int(line.split()[0],16) for line in nm.splitlines() if len(line.split())==3}
expected={'func_800857E8':0x800857E8,'func_80088914':0x80088914,'func_800906E8':0x800906E8,'func_800920E4':0x800920E4,'D_8013D170':0x8013D170,'D_8013D268_t':0x8013D268,'storage857_prefix':0x8013D270,'storage857_DD10':0x8013DD10,'storage857_middle':0x8013E478,'storage857_F348':0x8013F348,'D_8013FAB0':0x8013FAB0}
assert all(symbols[k]==v for k,v in expected.items())
pragmas=[str(p) for p in Path('src').rglob('*.c') if '#pragma GLOBAL_ASM' in p.read_text()]
assert pragmas==[],pragmas
def sha(b):return hashlib.sha256(b).hexdigest()
report={'rom_size':len(rom),'rom_sha256':sha(rom),'header_identical':rom[:64]==ref[:64],'target_size':len(target),'target_instructions':len(target)//4,'target_sha256':sha(target),'independent_elf_extraction':'PASS','whole_rom_splice':'PASS','remaining_global_asm_pragmas':0,'symbols':{k:hex(v) for k,v in expected.items()},'source_hashes':{str(p):sha(p.read_bytes()) for p in map(Path,['src/game2.c','asm/data/game_bss_b.bss.s','undefined_syms.txt','tetrisphere.yaml'])}}
if len(sys.argv)>2:
    trace=Path(sys.argv[2])
    current_input=subprocess.check_output(['python3','tools/asm-processor/asm_processor.py','-O2','-mips1','src/game2.c'])
    assert current_input==(trace/'ug.c').read_bytes()
    stock=(trace/'stock.O').read_bytes();probe=(trace/'probe.O').read_bytes()
    assert stock==probe
    report['stock_observer_identical']=True
    report['stock_uopt_output_sha256']=sha(stock)
    report['observer_input_sha256']=sha((trace/'ug.c').read_bytes())
(out/'CODEX_VERIFICATION.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
