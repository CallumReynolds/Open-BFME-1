# DefaultPhysicsModuleInfo constructor retry at 0x005FD9E0

The complete 91-byte constructor ends with RET at +0x5A. The ILT oracle confirms `??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@XZ` at this address. No production source or ledger row was changed.

`tools/eh_info.py 0x005FD9E0` independently follows the pushed handler at 0x00C3CA88 to FuncInfo 0x00E2C5A4. Its only unwind state binds cleanup 0x00C3CA80, which loads the saved receiver from EBP-0x10 and jumps through ILT 0x00001C80 to the exported, matched `Snapshot::~Snapshot` at 0x0005C520. No receiver adjustment occurs. This proves the native global Snapshot base; the old bank's FXParticleSystem::Snapshot declaration supplied the wrong cleanup identity despite its similar instruction shape.

The sole direct call goes through ILT 0x00006C58 to the matched global `GameClientRandomVariable::setRange` at 0x00096F40 (23 bytes, random_value.cpp). The old bank instead declared FXParticleSystem::GameClientRandomVariable. Native snapshot.h and game_client_random_variable.h remove both invented declarations. The preferred bank retains a partial DefaultPhysicsModuleInfo declaration because its shared header currently omits the witnessed Snapshot base. This bank is evidence, not a production header replacement.

The previous bank emits 91 bytes with 16 nonrelocation differences, measured quality 0.8242. Native types preserve that result. Moving the existing scalar at +0x10 to its member initializer reduces the differences to 14, measured quality 0.8462, with the same size and six relocations. This scalar spelling was tried historically with fabricated types; the new bank combines it with the independently proved native cleanup and call identities.

The remaining first divergence is +0x1F: retail installs the derived vtable before preparing the random-variable receiver and pushing UNIFORM; our compiler schedules the vtable later. The scalar store also precedes the random-variable stores in our initializer variant. The native virtual declarations describe the existing GetSnapshotName, LoadPostProcess and DoXfer ledger methods; their presence alone does not fix scheduling.

An independently implemented noinline setRange copy makes the constructor only 47 bytes by removing its exception frame. Combining it with the scalar initializer also emits 47 bytes. A write barrier after the scalar body store emits 91 bytes with 22 differences and was discarded. No barrier or setter copy is banked. Rotation sweep does not support constructors and is inapplicable to this ordering residue.

Scratch trials are in build/a2_005fd9e0/. re_log.py measured both candidate and previous bank before replacing the preferred stash. The standalone finish_measure invocation reported that its compiled object or dependencies were no longer current; its result was not used as acceptance evidence. The sole-writer banking command completed with the measured 0.8462 score.

The supplied census index reports the existing constructor TU LINKED 0 -> 0, blocked by its non-retail naked constructor emission. No new escape hatch, pin, data row, header change or generated-source edit was introduced. Landing still requires an exact body and convergence with the shared FXParticleSystem class declaration.

A second bounded constructor-context probe improved the native bank further.
A four-byte address-derived scalar wrapper with an inline value constructor
at +0x10 emits 91 bytes with 11 differences (quality 0.8791), restoring the
vptr-before-push schedule. It is a source-shaping experiment, not an EA type
identity. name_oracle has no DefaultPhysicsModuleInfo layout witness. Its
scalar store still precedes the random-variable stores; retail puts it after
them. Native-derived empty variable and grouped-float constructors preserve
14 differences. A default-empty scalar with a body assignment leaves 19 or
16 differences. No such experimental wrapper was introduced in game/ or a
shared header. The second preferred bank retains the native Snapshot and
GameClientRandomVariable identities, and remains nonmatching evidence.

## BFME-2 constructor transfer, 2026-10-15

Reviewed donor revision `3f115674d31dc308b37736f942bcc41ee77d7747`,
`Code/GameEngine/Source/GameClient/System/FXParticleSystem/EmissionInfoDefaultCtors.cpp`.
The donor carries an empty coordinate constructor followed by a scalar body
assignment and coordinate zeroing. Keeping the target bank's native Snapshot
and random-variable declarations while using this coordinate lifetime produces
all 91 target bytes, versus eleven differences in the preferred bank. The
donor's extra two flag fields are absent from the target and are not copied.

The target's existing DoXfer transfers a Coord3D from +4 and a float from +0x10;
its native unwind state independently proves the Snapshot base. These target
facts support correcting the shared header rather than adding another private
class declaration. The coordinate helper retains an address-derived type name;
it does not claim the donor's original field or type identity. The three
coordinate floats, scalar word and random-variable offsets and 32-byte total
size remain unchanged. Copy, assignment and transfer references use the grouped
coordinate. All 755 rows in the constructor, bulk and main FX units pass strict
byte checks together, including seven data rows.

Raw probes and the pre-edit header/bulk sources are retained under
`build/bfme2-physics-transfer/`. The full header gate is required before landing.
