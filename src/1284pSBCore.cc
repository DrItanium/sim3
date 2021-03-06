// Copyright (c) 2021, Joshua Scoggins
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by jwscoggins on 8/21/21.
//

#ifdef ARDUINO_AVR_ATmega1284
#include <Arduino.h>

#include <SPI.h>
#include "Types.h"
#include "1284pSBCore.h"
#include <SdFat.h>
SdFat SD;

void
ATMEGA1284PSBCore::begin() {
    Serial.println(F("BRINGING UP HITAGI SBCORE EMULATOR!"));
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    SPI.begin();
    while (!SD.begin(SDCardPin)) {
        Serial.println(F("NO SDCARD...WILL TRY AGAIN!"));
        delay(1000);
    }
    Serial.println(F("SDCARD UP!"));
    if (auto theFile = SD.open("boot.sys", FILE_READ); !theFile) {
        Serial.println(F("Could not open \"boot.sys\"! SD CARD may be corrupt?"));
        while (true) { delay(1000); }
    } else {
        memoryImage_.begin();
#ifndef USE_PSRAM_CHIP
        Serial.println(F("SUCCESSFULLY OPENED \"live.bin\""));
#endif
        // now we copy from the pristine image over to the new one in blocks
        Address size = theFile.size();
        constexpr auto CacheSize = Cache::CacheSize;
        auto* transferCache = theCache_.asTransferCache();
#ifndef USE_PSRAM_CHIP
        Serial.println(F("CONSTRUCTING NEW MEMORY IMAGE IN \"live.bin\""));
#else
        Serial.println(F("TRANSFERRING IMAGE TO PSRAM!"));
#endif
        for (Address i = 0; i < size; i += CacheSize) {
            while (SD.card()->isBusy());
            auto numRead = theFile.read(transferCache, CacheSize);
            if (numRead < 0) {
                SD.errorHalt();
            }
            // wait until the sd card is ready again to transfer
            (void)memoryImage_.write(i, transferCache, numRead);
            // wait until we are ready to
            Serial.print(F("."));
        }
        Serial.println(F("CONSTRUCTION COMPLETE!!!"));
        // make a new copy of this file
        theFile.close();
        while (SD.card()->isBusy());
        // okay also clear out the cache lines since the transfer buffer is shared with the cache
        theCache_.clear();
    }
}



ByteOrdinal
ATMEGA1284PSBCore::ioSpaceLoad(Address address, TreatAsByteOrdinal) {
    return 0;
}
void
ATMEGA1284PSBCore::ioSpaceStore(Address address, ByteOrdinal value) {
    // nothing to do here right now
}
Ordinal
ATMEGA1284PSBCore::ioSpaceLoad(Address address, TreatAsOrdinal ) {
    // right now there is nothing to do here
    return 0;
}
ShortOrdinal
ATMEGA1284PSBCore::ioSpaceLoad(Address address, TreatAsShortOrdinal) {
    switch (address) {
        case 2:
            Serial.flush();
            break;
        case 0:
            return Serial.read();
        default:
            break;
    }
    return 0;
}

void
ATMEGA1284PSBCore::ioSpaceStore(Address address, ShortOrdinal value) {
    switch (address) {
        case 2:
            Serial.flush();
            break;
        case 0:
            Serial.write(static_cast<char>(value));
            break;
        default:
            break;
    }
}
void
ATMEGA1284PSBCore::ioSpaceStore(Address address, Ordinal value) {
    // nothing to do right now
}
ByteOrdinal
ATMEGA1284PSBCore::doIACLoad(Address address, TreatAsByteOrdinal ordinal) {
    return 0;
}
ShortOrdinal
ATMEGA1284PSBCore::doIACLoad(Address address, TreatAsShortOrdinal ordinal) {
    return 0;
}
void
ATMEGA1284PSBCore::doIACStore(Address address, ByteOrdinal value) {
    // do nothing
}
void
ATMEGA1284PSBCore::doIACStore(Address address, ShortOrdinal value) {
    // do nothing
}
Ordinal
ATMEGA1284PSBCore::doIACLoad(Address address, TreatAsOrdinal) {
    switch (address) {
        case HaltRegisterOffset:
            haltExecution();
            break;
        case ConsoleRegisterOffset:
            return static_cast<Ordinal>(Serial.read());
        case ConsoleFlushOffset:
            Serial.flush();
            break;
        default:
            break;
    }
    return 0;
}
void
ATMEGA1284PSBCore::doIACStore(Address address, Ordinal value) {
    switch (address) {
        case HaltRegisterOffset:
            haltExecution();
            break;
        case ConsoleRegisterOffset:
            Serial.write(static_cast<char>(value));
        case ConsoleFlushOffset:
            Serial.flush();
            break;
        default:
            break;
    }
}
Ordinal
ATMEGA1284PSBCore::doRAMLoad(Address address, TreatAsOrdinal thingy) {
    return getCacheLine(address, memoryImage_).get(address, thingy);
}
ShortOrdinal
ATMEGA1284PSBCore::doRAMLoad(Address address, TreatAsShortOrdinal thingy) {
    return getCacheLine(address, memoryImage_).get(address, thingy);
}
ByteOrdinal
ATMEGA1284PSBCore::doRAMLoad(Address address, TreatAsByteOrdinal thingy) {
    return getCacheLine(address, memoryImage_).get(address, thingy);
}
void
ATMEGA1284PSBCore::doRAMStore(Address address, ByteOrdinal value) {
    getCacheLine(address, memoryImage_).set(address, value);
}
void
ATMEGA1284PSBCore::doRAMStore(Address address, ShortOrdinal value) {
    getCacheLine(address, memoryImage_).set(address, value);
}
void
ATMEGA1284PSBCore::doRAMStore(Address address, Ordinal value) {
    getCacheLine(address, memoryImage_).set(address, value);
}
bool
ATMEGA1284PSBCore::inRAMArea(Address target) noexcept{
    // since the ram starts at address zero, there is no need to worry about shifting the offset
    return target >= RamStart && target < RamSize;
}
Address
ATMEGA1284PSBCore::toRAMOffset(Address target) noexcept{
    return target & RamMask;
}
ATMEGA1284PSBCore::ATMEGA1284PSBCore() : Parent(),
memoryImage_(
#ifndef USE_PSRAM_CHIP
0,64_MB, 64_MB,"live.bin", FILE_WRITE
#else
0
#endif
) {}


#endif
