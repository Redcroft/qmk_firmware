#pragma once

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0


// Behaviors That Can Be Configured


#define TAPPING_TERM 250
        // how long before a tap becomes a hold, if set above 500, a key tapped during the tapping term will turn it into a hold too

#define PERMISSIVE_HOLD
       // makes tap and hold keys trigger the hold if another key is pressed before releasing, even if it hasn't hit the TAPPING_TERM
#define IGNORE_MOD_TAP_INTERRUPT
        // makes it possible to do rolling combos (zx) with keys that convert to other keys on hold, by enforcing the TAPPING_TERM for both keys.

#define TAPPING_FORCE_HOLD
        // makes it possible to use a dual role key as modifier shortly after having been tapped (see Hold after tap)
        // Breaks any Tap Toggle functionality (TT or the One Shot Tap Toggle)