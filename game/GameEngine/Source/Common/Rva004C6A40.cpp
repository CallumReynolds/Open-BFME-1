// The callback globals are address-derived; the second call passes two stack slots.
extern int g_012F3934;
extern int g_012F3930;

void j_00042a50(void);
void j_0002fcb1(void);

// callees.py infers ILT 0x2FCB1 as __cdecl with two stack slots and an unused
// result; the ledger's thunk name is untyped, so the call goes through that
// inferred signature.
typedef void (__cdecl *Rva004C6A40Register)(int first, int second);

void dup_004c6a40()
{
	j_00042a50();
	((Rva004C6A40Register)j_0002fcb1)(g_012F3930, g_012F3934);
}
