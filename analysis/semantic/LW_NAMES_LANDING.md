# Original animation routine names: semantic batch 010

The ROM diagnostics directly name `LWAllocateMemory` and `LWPlayAnimation`.
This batch replaces `func_8002CF70` and `func_8002D93C` with those names in their
four production source files, including all declarations and callers. It applies
173 identifier substitutions. Every other source byte is preserved, including
comments containing old names. Field/type reconstruction remains deferred.

This is an incremental ledger against fc38500, following the GBI audit; it does
not replace historical cumulative batch_009 or rewrite its original baseline.
The two linked symbols remain at 0x8002CF70 and 0x8002D93C respectively.

`ROM_STRING_SEMANTICS.md` preserves the research before these renames;
`ROM_STRING_LW_EVIDENCE.json` verifies 38 diagnostics against the original ROM.
Their old-name references and notes-only status describe that earlier snapshot.
The present landing supersedes that status for these two function names only.

Validation: pristine and renamed builds report FULL MATCH. An independent full
byte comparison includes the 64-byte header: all 8,388,608 bytes agree. The ROM
SHA256 is f7cbc93ac273488bfb89955ab6ae9b60c730907872107a67a56b945e8579ef87.
The existing lexical rename guard is included with its 24 passing tests. Its
report verifies inverse restoration of source and checks 994 production inputs.
The input manifest records the local macOS compiler; its hashes do not imply
that another host must use those same compiler executable bytes.

Recheck on this provisioned host:

```sh
python3 tools/semantic/identifier_renames.py --ledger analysis/semantic/batch_010.json
PATH=/opt/homebrew/bin:$PATH ./matchdiff.sh
cmp tetrisphere.z64 build/tetrisphere.us.z64
```

Only source and text evidence belong in Git. No ROM, assets or compiler binaries
are included. This batch is prepared for local landing; it does not push GitHub.
