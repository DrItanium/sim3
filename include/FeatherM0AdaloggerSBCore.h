// sim3
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

#ifndef SIM3_ADAFRUIT_FEATHER_M0_ADALOGGER_SBCORE_H
#define SIM3_ADAFRUIT_FEATHER_M0_ADALOGGER_SBCORE_H
#include <Arduino.h>
#include <SdFat.h>
#include "Types.h"
#include "SBCoreArduino.h"
#include "MemoryMappedFileThing.h"
#include "CacheLine.h"

#define USE_PSRAM_CHIP
#ifdef USE_PSRAM_CHIP
#include "PSRAMChip.h"
#endif

/**
 * @brief a version of the ArduinoSBCore meant for the grand central m4
 */
class FeatherM0AdaloggerSBCore : public SBCoreArduino {
public:
    static constexpr auto SDCardEnablePin = 4;
    static constexpr auto CardDetectPin = 7;
    static constexpr auto PSRAMEnablePin = 12;
public:
    static constexpr Address RamSize = 8_MB;
    static constexpr Address RamStart = 0x0000'0000;
    static constexpr Address RamMask = RamSize - 1;
public:
    using Cache = ::Cache<MemoryCell32, 256, 64>;
    using Parent = SBCoreArduino;
    FeatherM0AdaloggerSBCore();
    ~FeatherM0AdaloggerSBCore() override = default;
    void begin() override;
protected:
    ByteOrdinal ioSpaceLoad(Address address, TreatAsByteOrdinal ordinal) override;
    ShortOrdinal ioSpaceLoad(Address address, TreatAsShortOrdinal ordinal) override;
    Ordinal ioSpaceLoad(Address address, TreatAsOrdinal ordinal) override;
    void ioSpaceStore(Address address, ByteOrdinal value) override;
    void ioSpaceStore(Address address, ShortOrdinal value) override;
    void ioSpaceStore(Address address, Ordinal value) override;
    ByteOrdinal doIACLoad(Address address, TreatAsByteOrdinal ordinal) override;
    ShortOrdinal doIACLoad(Address address, TreatAsShortOrdinal ordinal) override;
    Ordinal doIACLoad(Address address, TreatAsOrdinal ordinal) override;
    void doIACStore(Address address, ByteOrdinal value) override;
    void doIACStore(Address address, ShortOrdinal value) override;
    void doIACStore(Address address, Ordinal value) override;
    Ordinal doRAMLoad(Address address, TreatAsOrdinal ordinal) override;
    ShortOrdinal doRAMLoad(Address address, TreatAsShortOrdinal ordinal) override;
    ByteOrdinal doRAMLoad(Address address, TreatAsByteOrdinal ordinal) override;
    void doRAMStore(Address address, ByteOrdinal value) override;
    void doRAMStore(Address address, ShortOrdinal value) override;
    void doRAMStore(Address address, Ordinal value) override;
    bool inRAMArea(Address target) noexcept override;
    Address toRAMOffset(Address target) noexcept override;
private:
    auto& getCacheLine(Address target, MemoryThing& thing) noexcept { return theCache_.getCacheLine(target, thing); }
private:
#ifndef USE_PSRAM_CHIP
    using RAM = MemoryMappedFileThing;
#else
    using RAM = PSRAMChip<PSRAMEnablePin, 20_MHz>;
#endif
private:
    RAM memoryImage_;
    // we have so much space available, let's have some fun with this
    Cache theCache_;
};

using SBCore = FeatherM0AdaloggerSBCore;
#endif // end SIM3_ADAFRUIT_FEATHER_M0_ADALOGGER_SBCORE_H
