/*
 * Created by janis on 2024-01-30
 */

#pragma once

#include <string>
#include <array>

namespace ag {
    struct Flavor {
        static constexpr std::array<const char*, 4> nopon_quotes = {
            "Meh! Meh! Meh!",
            "Destiny calling. Rude not to say \"hello\" back.",
            "Piece of cake time for a break.",
            "Meeeeeeeeeeehhhhhhhhhh"
        };

        static constexpr std::array<const char*, 8> xeno_quotes = {
            "Oi!",
            "Ridiculous! It's perfectly safe!",
            "Well that was a bloody waste of my time and talents.",
            "Keep your heads or lose them.",
            "Well of course not, I can express some emotion.",
            "Oh, bloody hell",
            "Are you insane? ... In fact, never mind. Forget I asked.",
            "It's the big bad boss. Boo!"
        };

    public:
        static const char* random();

    private:
    };
}