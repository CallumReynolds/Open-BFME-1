# W3DPowerDrawA at 0x0079AEC0

Retail RET at +0x73C followed by INT3 establishes the 1853-byte extent.
The existing named row, the Zero Hour W3DControlBar.cpp donor, and ten PowerBar
image strings independently support the callback identity.

The preferred bank emits 1853 bytes with 73 stack-displacement differences.
A TU-local type derived from ICoord2D with an empty default constructor, used
only for the position local, reproduces all 1853 bytes and 116 relocation
slots. All-coordinate and size-only construction instead emit 1855 bytes with
160 differences. No shared coordinate definition changes. The empty constructor
is a source reconstruction choice, not a newly claimed EA symbol.

Direct calls were read with callees.py. Existing bindings name ImageCollection's
84-byte findImageByName and GameWindow's 58-byte screen-position and 41-byte
size methods. The local-player accessor's existing Rva002EE330PlayerList pin
routes through 0x0000762B to 0x000DF860; the 46-byte implementation reads the
receiver's +0x0C player and applies its existing ControlBar fallback. Preserve
that established call ABI; no new binding is added.

The original W3DControlBar.cpp now emits the exact callback under the bank's
include order and string temporary ABI. This retains the other bodies and
funclets in their original translation unit. Strict verification is required
before this is a conversion.

Strict add_match passed all23 home-TU bodies,10 literal refs and23 DIR32 refs.
The required eh_state_pins writer repinned10 unique stale labels and verified
their bytes; the post-repair check exits0 (10correct unique,3existing unanchored).
