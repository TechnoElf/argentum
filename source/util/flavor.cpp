/*
 * Created by janis on 2024-01-30
 */

#include "flavor.h"

namespace ag {
    const char* Flavor::random() {
        int rand = std::rand();
        int list = rand & 0xff;
        int index = rand >> 8;

        switch (list % 2) {
            case 0: return nopon_quotes[index % nopon_quotes.size()];
            case 1: return xeno_quotes[index % xeno_quotes.size()];
            default: return ">:(";
        }
    }
}