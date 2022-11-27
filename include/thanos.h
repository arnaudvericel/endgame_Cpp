#ifdef THANOS // only compile this part if thanos has been requested by the user
#ifndef THANOS_H
#define THANOS_H

#include <iostream>
#include <vector>
#include "unistd.h"
#include <fstream>
#include <cstdlib>

using namespace std;

struct ThanosQuotes {
    string database[18] = {
        "Little one, it’s a simple calculus. This universe is finite, its resources, finite. If life is left unchecked, life will cease to exist. It needs correcting.",
        "I hope they remember you.",
        "I finally rest, and watch the sun rise on a grateful universe. The hardest choices require the strongest wills.",
        "I will shred this universe down to it’s last atom and then, with the stones you’ve collected for me, create a new one... a grateful universe.",
        "In all my years of conquest, violence, slaughter, it was never personal. But I’ll tell you now, what I’m about to do to your stubborn, annoying little planet… I’m gonna enjoy it. Very, very much.",
        "You’re strong. But I could snap my fingers, and you’d all cease to exist.",
        "Today, I lost more than you can know. But now is no time to mourn. Now is no time at all.",
        "I know what it’s like to lose. To feel so desperately that you’re right, yet to fail nonetheless.",
        "Dread it. Run from it. Destiny still arrives. Or should I say, I have.",
        "I ignored my destiny once, I can not do that again. Even for you. I’m sorry Little one.",
        "The work is done. I won. I am inevitable.",
        "The universe required correction.",
        "I used the stones to destroy the stones. It nearly… killed me. But the work is done. it always will be.",
        "You’re not the only one cursed with knowledge.",
        "Reality can be whatever I want.",
        "You should’ve gone for the head.",
        "A small price to pay for salvation.",
        "You couldn’t live with your own failure. Where did that bring you? Back to me."
    };

    int get_nb_quotes() const;
};

class Thanos {
private:
    ThanosQuotes punchlines;

public:
    // constructor
    Thanos() = default;

    // destructor
    ~Thanos() = default;

    void print_artwork() const;

    // monologue methods
    void talks_to_gamora() const;
    void init_punchline() const;
    void regular_ending() const;
    void balanced_ending() const;
};

#endif
#endif
