?getUpdate@UpdateModule@@UAEPAVUpdateModuleInterface@@XZ = 0x001B2D20 (14 B).
Retail bytes: lea eax,[ecx-0xC]; test eax,eax; je; lea eax,[ecx+4]; ret; xor eax,eax; ret
= UpdateModule::getUpdate entered through BehaviorModuleInterface (+0xC) returning the
UpdateModuleInterface subobject (+0x10). BFME UpdateModule layout: ~UpdateModule 0x001B2B10 stores
0x0109CBAC at +0x10 (UpdateModule's own vtable for its UpdateModuleInterface subobject; the ctor 0x001B2FB0
stores the interface base vtable 0x0109CBA0 there first), then BehaviorModule's vtables at +0 / +0xC
(0x0109CB5C, 0x0109CA98). This body is slot 8 of UpdateModule's BehaviorModuleInterface vtable 0x0109CCD0.
The old row at 0x0011A150 (ecx-0x10 / +4) adjusts by a different subobject offset: another class's
getter (GateProxyBehavior/GateOpenAndCloseBehavior per review; 15 names claim it, one_identity.py --list); retired. Approved by the project lead 2026-10-15.
