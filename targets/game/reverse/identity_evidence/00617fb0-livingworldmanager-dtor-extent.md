# 0x00617FB0 LivingWorldManager destructor: true extent 1174 bytes

The carved gen-dump row recorded 1168 bytes (end 0x00618440). The body does not
end there: the final epilogue (`mov ecx,[esp+0x1c]; pop edi; pop esi; pop ebp;
pop ebx; mov fs:[0],ecx; ...`) continues past 0x00618440 and the single `ret`
is at body offset +0x495 (0x00618445). `python3 tools/dis_retail.py 0x00617FB0
1180` shows `c3` at +0x495 followed by `cc` padding from +0x496, so the extent
is 0x496 = 1174 bytes. The compiled C++ is 1174 bytes with every relocation
slot matching.

Identity: the constructor at 0x006171D0 installs vftables 0x01116BFC and
0x01116BE8; the first block's name() virtual returns "LivingWorldManager"
(see game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldManager.cpp).

Name corrections: the banked stash spelled five member/element classes with
invented descriptive names (Lwm00C, Lwm1AC, Lwm210, Lwm270, LwmOwned264). The
member destructors are reached through retail ILT thunks whose slot order is
the linker hash order of the decorated name; `python3 tools/ilt_oracle.py
check` contradicts the descriptive decorations (p_false ~1e-3) and accepts only
address-derived spellings. The classes are therefore named after the retail
body each ILT jumps to: 0x0060EBB0, 0x00614820, 0x006129E0, 0x006152A0 and
0x0060B6B0. No functional identity is claimed for them beyond that address.

Vftable naming: the destructor stores retail's vftables 0x01116BFC (primary,
SubsystemInterface side) and 0x01116BE8 (Snapshot side). The gate accepts a
new vftable reference only under a name encoding its own address, and MSVC
puts the base-class name in the vftable name (`??_7<Class>@@6B<Base>@@@`), so
the class keeps its real name and each base is spelled through a thin
address-named wrapper (Rva00D16BFC, Rva00D16BE8) that adds no members or
stores. The result stays byte-exact.
